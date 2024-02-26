#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>

int counter=0;      //my code with this variable can recognize this time which player is playing

typedef struct File File;
char board[32][32];     //global board

void Botdecision(char *decision){
    if ((rand() % 10)>6)
    {
        *decision='w';
    }
    else *decision='m';
}
void BotType(char *type){
    int random=(rand() % 10);
    if (random>8)
    {
        *type='w';
    }
    else if (random>7)
    {
        *type='d';
    }
    else if (random>6)
    {
        *type='a';
    }
    else
    {
        *type='s';
    }
}
void WallOfBot(int *x,int *y,char *dir,int n){
    if ((rand() % 2)%2==0)
    {
        *dir='H';
    }
    else *dir='V';

    int xSaver;
    int ySaver;
    xSaver=rand() % 15;
    ySaver=rand() % 15;
    while (xSaver>=n)
    {
        xSaver-=n;
    }
    while (ySaver>=n)
    {
        ySaver-=n;
    }
    *x=xSaver;
    *y=ySaver;

}
void setTextColor(int textColor,int backColor){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal>clock());
}
void clearscreen()
{
    system("cls");
}
int bentType(int x1,int y1,int x2,int y2,int turn)
{
    while (turn > 3){
        turn-=4;
    }
    if (x1-1==x2 && y1==y2)
    {
        if (turn==0)
            return 1;
        else
            return 2;
    }
    else if (x1+1==x2 && y1==y2)
    {
        if (turn==0)
            return 2;
        else
            return 1;
    }
    else if (x1==x2 && y1-1==y2)
    {
        if (turn==0)
            return 3;
        else
            return 4;
    }
    else if (x1==x2 && y1+1==y2)
    {
        if (turn==0)
            return 4;
        else
            return 3;
    }
    else return -1;

}

    void stuckError(){
    setTextColor(4,0);
    printf("your opponent will stuck with this wall!\n");
    setTextColor(7,0);
}
void BoardExitError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(4,0);
        printf("You cannot move in this direction because you are out of board!\n");
        sleep(1000);
        printf("please try anothe direction\n");
        setTextColor(7,0);
    }
}
void WallPassingError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(4,0);
        printf("You cannot jupm through the wall!!\n");
        sleep(1000);
        printf("please try anothe direction\n");
        setTextColor(7,0);
    }
}
void ZeroWallError(int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(4,0);
        printf("you dont have wall anymore\nyou can just move\n");
        setTextColor(7,0);
    }
}
void RemainingWalls(int howMany,int swOfPlayerType)
{
    if (swOfPlayerType)
    {
        setTextColor(6,0);
        printf("!!!!!!you have just %d more walls!!!!!!\n",howMany);
        setTextColor(7,0);
    }
}
void PrizeOfWinner()
{
    setTextColor(10,0);
    printf(" () ()\n\\_____/");
    setTextColor(7,0);
}
int paint2(int n,int xOfPlayer,int yOfPlayer,int turn,int x1Saver,int x2Saver){
    char arrey[2*n-1][2*n-1];
    // int power=pow(2*(n-1),2);
    int saver[1000][2];
    int counter=1;
    for (int i = 0; i < 2*n-1; i++)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            arrey[i][j]=board[i][j];
        }

    }

    saver[0][0]=xOfPlayer;
    saver[0][1]=yOfPlayer;

    char H=196;
    char V=179;
    char sign='0';

    for (int k = 0; k < counter; k++)
    {
        if (arrey[saver[k][0]][saver[k][1]+1]!=H && arrey[saver[k][0]][saver[k][1]+1]!=V && saver[k][1]+1<2*n-1)//left
        {
            if (arrey[saver[k][0]][saver[k][1]+2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]+2;
                counter++;
                arrey[saver[k][0]][saver[k][1]+2]=sign;
            }
        }


        if (arrey[saver[k][0]][saver[k][1]-1]!=H && arrey[saver[k][0]][saver[k][1]-1]!=V && saver[k][1]-1>-1)//right
        {
            if (arrey[saver[k][0]][saver[k][1]-2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]-2;
                counter++;
                arrey[saver[k][0]][saver[k][1]-2]=sign;
            }


        }


        if (arrey[saver[k][0]-1][saver[k][1]]!=H && arrey[saver[k][0]-1][saver[k][1]]!=V && saver[k][0]-1>-1)//top
        {
            if (arrey[saver[k][0]-2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]-2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]-2][saver[k][1]]=sign;
            }

        }


        if (arrey[saver[k][0]+1][saver[k][1]]!=H && arrey[saver[k][0]+1][saver[k][1]]!=V && saver[k][0]+1<2*n-1)//down
        {
            if (arrey[saver[k][0]+2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]+2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]+2][saver[k][1]]=sign;
            }

        }

    }

    if (turn==0)      //the turn of player 2
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x1Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }

    }
    else if(turn == 1)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x2Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }
    }
    else if(turn == 2)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[j][2*x2Saver]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }
    }
    else if(turn == 2)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[j][2*x2Saver]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }
    }

    return 0;


}
int paint(int n,int xOfPlayer,int yOfPlayer,int turn,int x1Saver,int x2Saver){    //n,2*x2,2*y2,counter,x1Saver,x2Saver
    char arrey[2*n-1][2*n-1];
    // int power=pow(2*(n-1),2);
    int saver[1000][2];
    int counter=1;
    for (int i = 0; i < 2*n-1; i++)
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            arrey[i][j]=board[i][j];
        }

    }

    saver[0][0]=xOfPlayer;
    saver[0][1]=yOfPlayer;

    char H=196;
    char V=179;
    char sign='0';

    for (int k = 0; k < counter; k++)
    {
        if (arrey[saver[k][0]][saver[k][1]+1]!=H && arrey[saver[k][0]][saver[k][1]+1]!=V && saver[k][1]+1<2*n-1)//left
        {
            if (arrey[saver[k][0]][saver[k][1]+2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]+2;
                counter++;
                arrey[saver[k][0]][saver[k][1]+2]=sign;
            }
        }


        if (arrey[saver[k][0]][saver[k][1]-1]!=H && arrey[saver[k][0]][saver[k][1]-1]!=V && saver[k][1]-1>-1)//right
        {
            if (arrey[saver[k][0]][saver[k][1]-2]!=sign)
            {
                saver[counter][0]=saver[k][0];
                saver[counter][1]=saver[k][1]-2;
                counter++;
                arrey[saver[k][0]][saver[k][1]-2]=sign;
            }


        }


        if (arrey[saver[k][0]-1][saver[k][1]]!=H && arrey[saver[k][0]-1][saver[k][1]]!=V && saver[k][0]-1>-1)//top
        {
            if (arrey[saver[k][0]-2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]-2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]-2][saver[k][1]]=sign;
            }

        }


        if (arrey[saver[k][0]+1][saver[k][1]]!=H && arrey[saver[k][0]+1][saver[k][1]]!=V && saver[k][0]+1<2*n-1)//down
        {
            if (arrey[saver[k][0]+2][saver[k][1]]!=sign && arrey[saver[k][0]][saver[k][1]]!=32)
            {
                saver[counter][0]=saver[k][0]+2;
                saver[counter][1]=saver[k][1];
                counter++;
                arrey[saver[k][0]+2][saver[k][1]]=sign;
            }

        }

    }

    if (turn%2==0)      //the turn of player 2
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x1Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }

    }
    else
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (arrey[2*x2Saver][j]=='0')
            {
                return 1;       //it means your opponent is safe
            }

        }
    }
    return 0;
}

void mORwPrint(){
    setTextColor(9,0);
    printf("if do you want to move press (m)\nand if you want to place a wall press (w)\n");
    setTextColor(7,0);
}

void directionPrint(){
    setTextColor(9,0);
    printf("In which direction do you want to move?\ntop(w),down(s),right(d),left(a)\n");
    setTextColor(14,0);
    printf("and if that is emergency you have q(top L),e(top R),z(down L),c(down R) options too\n");
    setTextColor(7,0);
}

int p3Walls, x3, y3;
int p4Walls, x4, y4;
int y3Saver, y4Saver;
void  multi_4() {

    int n;
    int p1Walls, x1, y1;
    int p2Walls, x2, y2;

    int x1Saver, x2Saver;
    char player;
    int swOfPlayerType = 1;

    scanf("%d", &n);

    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                board[i][j] = 254;
            } else board[i][j] = 32;

        }

    }       //create the board with squares

    scanf("%d %d\n%d %d\n", &x1, &y1, &x2, &y2);
    scanf("%d %d\n%d %d", &x3, &y3, &x4, &y4);

    board[2 * x1][2 * y1] = '1';      //simbol of player1
    board[2 * x2][2 * y2] = '2';      //simbol of player2
    board[2 * x3][2 * y3] = '3';      //simbol of player3
    board[2 * x4][2 * y4] = '4';      //simbol of player4

    //end of board default setting

    for (int i = 0; i < 2 * n - 1; i++)     //print the default board
    {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (board[i][j] == '1') {
                if (j != 2 * n - 2) {
                    setTextColor(10, 0);
                    printf("%c", board[i][j]);
                    setTextColor(7, 0);
                } else {
                    setTextColor(10, 0);
                    printf("%c\n", board[i][j]);
                    setTextColor(7, 0);
                }


            } else if (board[i][j] == '2') {
                if (j != 2 * n - 2) {
                    setTextColor(12, 0);
                    printf("%c", board[i][j]);
                    setTextColor(7, 0);
                } else {
                    setTextColor(12, 0);
                    printf("%c\n", board[i][j]);
                    setTextColor(7, 0);
                }
            } else if (board[i][j] == '3') {
                if (j != 2 * n - 2) {
                    setTextColor(1, 0);
                    printf("%c", board[i][j]);
                    setTextColor(7, 0);
                } else {
                    setTextColor(4, 0);
                    printf("%c\n", board[i][j]);
                    setTextColor(7, 0);
                }
            } else if (board[i][j] == '4') {
                if (j != 2 * n - 2) {
                    setTextColor(14, 0);
                    printf("%c", board[i][j]);
                    setTextColor(7, 0);
                } else {
                    setTextColor(14, 0);
                    printf("%c\n", board[i][j]);
                    setTextColor(7, 0);
                }
            } else if (j != 2 * n - 2) {
                setTextColor(11, 0);
                printf("%c", board[i][j]);
                setTextColor(7, 0);
            } else {
                setTextColor(11, 0);
                printf("%c\n", board[i][j]);
                setTextColor(7, 0);
            }

        }

    }

    //move and place walls will start from bellow

    setTextColor(9, 0);
    printf("pleas Determine how many walls the player1 has\n");
    setTextColor(7, 0);
    scanf("%d", &p1Walls);
    setTextColor(9, 0);
    printf("pleas Determine how many walls the player2 has\n");
    setTextColor(7, 0);
    scanf("%d", &p2Walls);
    setTextColor(9, 0);
    printf("pleas Determine how many walls the player3 has\n");
    setTextColor(7, 0);
    scanf("%d", &p3Walls);
    setTextColor(9, 0);
    printf("pleas Determine how many walls the player4 has\n");
    setTextColor(7, 0);
    scanf("%d", &p4Walls);
    //finish line for player2
    if (x1 >= n / 2) {
        x1Saver = n - 1;
        x2Saver = 0;
    } else {
        x1Saver = 0;
        x2Saver = n - 1;
    }
    y3Saver = 0;
    y4Saver = n - 1;
    getchar();

    while (x1!=x2Saver && x2!=x1Saver && y3!=y4Saver && y4!=y3Saver) {

        while(counter > 3){
            counter -= 4;
        }

        if (swOfPlayerType) {
            mORwPrint();
        } else if (!swOfPlayerType && counter % 2 != 0) {
            setTextColor(9, 0);
            printf("wait for Bot\n");
            setTextColor(7, 0);
        }
        char decision;
        while (1 && !(swOfPlayerType == 0 && counter % 2 != 0)) {

            scanf(" %c", &decision);
            if (decision == 'm' || decision == 'w') {
                break;
            } else {
                setTextColor(6, 0);
                printf("you should choose between w(place a wall) & m(move your piece)\n");
                setTextColor(7, 0);
            }


        }
        if (!swOfPlayerType && counter % 2 != 0) {
            Botdecision(&decision);
        }       //end of select between m & w


        if (decision == 'm') {

            lable:
            while (1) {
                if (!(swOfPlayerType == 0 && counter % 2 != 0)) {
                    directionPrint();
                }
                char type;
                while (1 && !(swOfPlayerType == 0 && counter== 0)) {
                    scanf(" %c", &type);
                    if (type == 'w' || type == 'd' || type == 's' || type == 'a') break;
                    else {
                        setTextColor(4, 0);
                        printf("You have to choose between the four main diractions and secondary directions that you are allowed to use\n");
                        setTextColor(7, 0);
                    }

                }
                if (!swOfPlayerType && counter % 2 != 0) {
                    BotType(&type);
                }       //end of select move type

                if (counter == 0) {
                    board[2 * x1][2 * y1] = 254;

                    //if the direction is main

                    if ((type == 'w' && x1 - 2 > -1 && x1 - 1 == x2 && y1 == y2) || (type == 'w' && x1 - 2 > -1 && x1 - 1 == x3 && y1 == y3) || (type == 'w' && x1 - 2 > -1 && x1 - 1 == x4 && y1 == y4)) {
                        if (board[2 * x1 - 3][2 * y1] == 32) {
                            x1 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'w' && x1 - 1 > -1) {
                        if (board[2 * x1 - 1][2 * y1] == 32) {
                            x1--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 's' && x1 + 2 < n && x1 + 1 == x2 && y1 == y2) || (type == 's' && x1 + 2 < n && x1 + 1 == x3 && y1 == y3) || (type == 's' && x1 + 2 < n && x1 + 1 == x4 && y1 == y4)) {
                        if (board[2 * x1 + 3][2 * y1] == 32) {
                            x1 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 's' && x1 + 1 < n) {
                        if (board[2 * x1 + 1][2 * y1] == 32) {
                            x1++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'd' && y1 + 2 < n && x1 == x2 && y1 + 1 == y2) || (type == 'd' && y1 + 2 < n && x1 == x3 && y1 + 1 == y3) || (type == 'd' && y1 + 2 < n && x1 == x4 && y1 + 1 == y4)) {
                        if (board[2 * x1][2 * y1 + 3] == 32 && board[2 * x1][2 * y1 + 4] == 254) {
                            y1 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'd' && y1 + 1 < n) {
                        if (board[2 * x1][2 * y1 + 1] == 32) {
                            y1++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'a' && y1 - 2 > -1 && x1 == x2 && y1 - 1 == y2) || (type == 'a' && y1 - 2 > -1 && x1 == x3 && y1 - 1 == y3) || (type == 'a' && y1 - 2 > -1 && x1 == x4 && y1 - 1 == y4)) {
                        if (board[2 * x1][2 * y1 - 3] == 32) {
                            y1 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'a' && y1 - 1 > -1) {
                        if (board[2 * x1][2 * y1 - 1] == 32) {
                            y1--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    }

                        //if the direction is not main

                    else {
                        BoardExitError(swOfPlayerType);
                    }

                } else if(counter == 1){
                    board[2 * x2][2 * y2] = 254;
                    if ((type == 'w' && x2 - 2 > -1 && x2 - 1 == x1 && y2 == y1) || (type == 'w' && x2 - 2 > -1 && x2 - 1 == x3 && y2 == y3) || (type == 'w' && x2 - 2 > -1 && x2 - 1 == x4 && y2 == y4)) {
                        if (board[2 * x2 - 3][2 * y2] == 32) {
                            x2 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'w' && x2 - 1 > -1) {
                        if (board[2 * x2 - 1][2 * y2] == 32) {
                            x2--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 's' && x2 + 2 < n && x2 + 1 == x1 && y2 == y1) || (type == 's' && x2 + 2 < n && x2 + 1 == x3 && y2 == y3) || (type == 's' && x2 + 2 < n && x2 + 1 == x4 && y2 == y4)) {
                        if (board[2 * x2 + 3][2 * y2] == 32) {
                            x2 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 's' && x2 + 1 < n) {
                        if (board[2 * x2 + 1][2 * y2] == 32) {
                            x2++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'd' && y2 + 2 < n && x2 == x1 && y2 + 1 == y1) || (type == 'd' && y2 + 2 < n && x2 == x3 && y2 + 1 == y3) || (type == 'd' && y2 + 2 < n && x2 == x4 && y2 + 1 == y4)) {
                        if (board[2 * x2][2 * y2 + 3] == 32) {
                            y2 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'd' && y2 + 1 < n) {
                        if (board[2 * x2][2 * y2 + 1] == 32) {
                            y2++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'a' && y2 - 2 > -1 && x2 == x1 && y2 - 1 == y1) || (type == 'a' && y2 - 2 > -1 && x2 == x3 && y2 - 1 == y3) || (type == 'a' && y2 - 2 > -1 && x2 == x4 && y2 - 1 == y4)) {
                        if (board[2 * x2][2 * y2 - 3] == 32) {
                            y2 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'a' && y2 - 1 > -1) {
                        if (board[2 * x2][2 * y2 - 1] == 32) {
                            y2--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    }


                        //if the direction is not main

                     else {
                        BoardExitError(swOfPlayerType);
                    }
                }

                else if(counter == 2){
                    board[2 * x3][2 * y3] = 254;
                    if ((type == 'w' && x3 - 2 > -1 && x3 - 1 == x4 && y3 == y4) || (type == 'w' && x3 - 2 > -1 && x3 - 1 == x1 && y3 == y1) || (type == 'w' && x3 - 2 > -1 && x3 - 1 == x2 && y3 == y2)) {
                        if (board[2 * x3 - 3][2 * y3] == 32) {
                            x3 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'w' && x3 - 1 > -1) {
                        if (board[2 * x3 - 1][2 * y3] == 32) {
                            x3--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 's' && x3 + 2 < n && x3 + 1 == x4 && y3 == y4) || (type == 's' && x3 + 2 < n && x3 + 1 == x1 && y3 == y1) || (type == 's' && x3 + 2 < n && x3 + 1 == x2 && y3 == y2)) {
                        if (board[2 * x3 + 3][2 * y3] == 32) {
                            x3 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 's' && x3 + 1 < n) {
                        if (board[2 * x3 + 1][2 * y3] == 32) {
                            x3++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'd' && y3 + 2 < n && x3 == x4 && y3 + 1 == y4) || (type == 'd' && y3 + 2 < n && x3 == x1 && y3 + 1 == y1) || (type == 'd' && y3 + 2 < n && x3 == x2 && y3 + 1 == y2)) {
                        if (board[2 * x3][2 * y3 + 3] == 32) {
                            y3 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'd' && y3 + 1 < n) {
                        if (board[2 * x3][2 * y3 + 1] == 32) {
                            y3++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'a' && y3 - 2 > -1 && x3 == x4 && y3 - 1 == y4) || (type == 'a' && y3 - 2 > -1 && x3 == x1 && y3 - 1 == y1) || (type == 'a' && y3 - 2 > -1 && x3 == x2 && y3 - 1 == y2)) {
                        if (board[2 * x3][2 * y3 - 3] == 32) {
                            y3 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'a' && y3 - 1 > -1) {
                        if (board[2 * x3][2 * y3 - 1] == 32) {
                            y3--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    }


                        //if the direction is not main

                     else {
                        BoardExitError(swOfPlayerType);
                    }
                }
                else if(counter == 3){
                    board[2 * x4][2 * y4] = 254;
                    if ((type == 'w' && x4 - 2 > -1 && x4 - 1 == x3 && y4 == y3) || (type == 'w' && x4 - 2 > -1 && x4 - 1 == x1 && y4 == y1) || (type == 'w' && x4 - 2 > -1 && x4 - 1 == x2 && y4 == y2)) {
                        if (board[2 * x4 - 3][2 * y4] == 32) {
                            x4 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'w' && x4 - 1 > -1) {
                        if (board[2 * x4 - 1][2 * y4] == 32) {
                            x4--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 's' && x4 + 2 < n && x4 + 1 == x3 && y4 == y3) || (type == 's' && x4 + 2 < n && x4 + 1 == x1 && y4 == y1) || (type == 's' && x4 + 2 < n && x4 + 1 == x2 && y4 == y2)) {
                        if (board[2 * x4 + 3][2 * y4] == 32) {
                            x4 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 's' && x4 + 1 < n) {
                        if (board[2 * x4 + 1][2 * y4] == 32) {
                            x4++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'd' && y4 + 2 < n && x4 == x3 && y4 + 1 == y3) || (type == 'd' && y4 + 2 < n && x4 == x1 && y4 + 1 == y1) || (type == 'd' && y4 + 2 < n && x4 == x2 && y4 + 1 == y2)) {
                        if (board[2 * x4][2 * y4 + 3] == 32) {
                            y4 += 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'd' && y4 + 1 < n) {
                        if (board[2 * x4][2 * y4 + 1] == 32) {
                            y4++;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if ((type == 'a' && y4 - 2 > -1 && x4 == x3 && y4 - 1 == y3) || (type == 'a' && y4 - 2 > -1 && x4 == x1 && y4 - 1 == y1) || (type == 'a' && y4 - 2 > -1 && x4 == x2 && y4 - 1 == y2)) {
                        if (board[2 * x4][2 * y4 - 3] == 32) {
                            y4 -= 2;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    } else if (type == 'a' && y4 - 1 > -1) {
                        if (board[2 * x4][2 * y4 - 1] == 32) {
                            y4--;
                            break;
                        } else {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                        //if the direction is not main

                     else {
                        BoardExitError(swOfPlayerType);
                    }
                }

            }     //end of move
            board[2 * x1][2 * y1] = '1';      //player 1 moved
            board[2 * x2][2 * y2] = '2';      //player 2 moved
            board[2 * x3][2 * y3] = '3';      //player 3 moved
            board[2 * x4][2 * y4] = '4';      //player 4 moved
        }
        else if (decision=='w')
        {
            while(counter > 3){
                counter-=4;
            }
            if (counter==0)
            {
                if (p1Walls>0)
                {
                    p1Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }
            else if(counter == 1)
            {
                if (p2Walls>0)
                {
                    p2Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }

            else if(counter == 2)
            {
                if (p3Walls>0)
                {
                    p3Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }

            else if(counter == 3)
            {
                if (p4Walls>0)
                {
                    p4Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }



            while (1)
            {
                int xOfWall;
                int yOfWall;
                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                    setTextColor(9,0);
                    printf("Please enter three items bellow\n");
                    sleep(500);
                    setTextColor(9,0);
                    printf("Row\n");
                    sleep(500);
                    printf("Column\n");
                    sleep(500);
                    printf("type : V(vertical) or H(horisontal)\n");
                    setTextColor(7,0);
                    scanf("%d",&xOfWall);
                    scanf("%d",&yOfWall);
                }
                char wallDirect;
                while (1 && !(swOfPlayerType==0 && counter%2!=0))
                {
                    scanf(" %c",&wallDirect);
                    if (wallDirect=='H' || wallDirect=='V')
                    {
                        break;
                    }
                    else
                    {
                        setTextColor(4,0);
                        printf("pay attention to your wall type.you can just insert one of these options:V(vertical),H(horisontal)\n");
                        sleep(1000);
                        setTextColor(6,0);
                        printf("Your mistake can be entering lowercase letters\n");
                        setTextColor(7,0);
                    }
                }
                if (swOfPlayerType==0 && counter%2!=0)
                {
                    WallOfBot(&xOfWall,&yOfWall,&wallDirect,n);
                }        //end of wall selectiont



                xOfWall *= 2;
                yOfWall *= 2;
                if(wallDirect == 'H' && xOfWall-1>-1  && xOfWall<2*n-1 && yOfWall>-1 && yOfWall+2<2*n-1 && board[xOfWall-1][yOfWall] == 32 && board[xOfWall-1][yOfWall + 1] == 32 && board[xOfWall-1][yOfWall + 2]  == 32)
                {
                    board[xOfWall-1][yOfWall] = 196;

                    board[xOfWall-1][yOfWall + 1] = 196;

                    board[xOfWall-1][yOfWall + 2] = 196;

                    if (counter == 0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter == 1 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
                    }
                    else if (counter == 2 && p3Walls<4)
                    {
                        RemainingWalls(p3Walls,swOfPlayerType);
                    }
                    else if (counter == 3 && p4Walls<4)
                    {
                        RemainingWalls(p4Walls,swOfPlayerType);
                    }
                    // break;
                }
                else if (wallDirect=='V' && yOfWall-1>-1 && yOfWall<2*n-1 && xOfWall-2>-1 && xOfWall<2*n-1 && board[xOfWall][yOfWall-1] == 32 && board[xOfWall-1][yOfWall-1]  == 32 && board[xOfWall-2][yOfWall-1] == 32)
                {
                    board[xOfWall][yOfWall-1] = 179;

                    board[xOfWall-1][yOfWall-1] = 179;

                    board[xOfWall-2][yOfWall-1] = 179;

                    if (counter == 0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter == 1 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
                    }
                    else if (counter == 2 && p3Walls<4)
                    {
                        RemainingWalls(p3Walls,swOfPlayerType);
                    }
                    else if (counter == 3 && p4Walls<4)
                    {
                        RemainingWalls(p4Walls,swOfPlayerType);
                    }
                    // break;
                }       //end of putting walls in the board
                else
                {
                    if (swOfPlayerType)
                    {
                        setTextColor(4,0);
                        printf("you can't place your wall here\n");
                        setTextColor(7,0);
                    }
                }



                if (counter==0)
                {
                    if (paint2(n,2*x2,2*y2,counter,x1Saver,x2Saver) && paint2(n, 2*x3, 2*y3, counter, y4Saver, x2Saver) && paint2(n, 2*x4, 2*y4, counter, y3Saver, x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p1Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }


                }
                else if(counter == 1)
                {
                    if (paint2(n,2*x1,2*y1,counter,x1Saver,x2Saver) && paint2(n, 2*x3, 2*y3, counter, x1Saver, y4Saver) && paint2(n, 2*x4, 2*y4, counter, x1Saver, y3Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p2Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }

                }
                else if(counter == 2)
                {
                    if (paint2(n,2*x1,2*y1,counter,y4Saver,x2Saver) && paint2(n, 2*x2, 2*y2, counter, y4Saver, x1Saver) && paint2(n, 2*x4, 2*y4, counter, y4Saver, y3Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p2Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }

                }
                else if(counter == 3)
                {
                    if (paint2(n,2*x1,2*y1,counter,y3Saver,x2Saver) && paint2(n, 2*x3, 2*y3, counter, y3Saver, y4Saver) && paint2(n, 2*x2, 2*y2, counter, y3Saver, x1Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p2Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }

                }



            }

        }


        for (int i = 0; i < 2 * n - 1; i++)     //print the default board
        {
            for (int j = 0; j < 2 * n - 1; j++) {
                if (board[i][j] == '1') {
                    if (j != 2 * n - 2) {
                        setTextColor(10, 0);
                        printf("%c", board[i][j]);
                        setTextColor(7, 0);
                    } else {
                        setTextColor(10, 0);
                        printf("%c\n", board[i][j]);
                        setTextColor(7, 0);
                    }


                } else if (board[i][j] == '2') {
                    if (j != 2 * n - 2) {
                        setTextColor(12, 0);
                        printf("%c", board[i][j]);
                        setTextColor(7, 0);
                    } else {
                        setTextColor(12, 0);
                        printf("%c\n", board[i][j]);
                        setTextColor(7, 0);
                    }
                } else if (board[i][j] == '3') {
                    if (j != 2 * n - 2) {
                        setTextColor(1, 0);
                        printf("%c", board[i][j]);
                        setTextColor(7, 0);
                    } else {
                        setTextColor(4, 0);
                        printf("%c\n", board[i][j]);
                        setTextColor(7, 0);
                    }
                } else if (board[i][j] == '4') {
                    if (j != 2 * n - 2) {
                        setTextColor(14, 0);
                        printf("%c", board[i][j]);
                        setTextColor(7, 0);
                    } else {
                        setTextColor(14, 0);
                        printf("%c\n", board[i][j]);
                        setTextColor(7, 0);
                    }
                } else if (j != 2 * n - 2) {
                    setTextColor(11, 0);
                    printf("%c", board[i][j]);
                    setTextColor(7, 0);
                } else {
                    setTextColor(11, 0);
                    printf("%c\n", board[i][j]);
                    setTextColor(7, 0);
                }

            }

        }
        counter ++;
    }


    if (x2==x1Saver)
    {
        if (swOfPlayerType)
        {
            setTextColor(10,0);
            printf("Hey player 2\nYou won\n");
            PrizeOfWinner();
            setTextColor(7,0);
        }
    }

    else if(x1 == x2Saver){
        if (swOfPlayerType)
        {
            setTextColor(10,0);
            printf("Hey player 1\nYou won\n");
            PrizeOfWinner();
            setTextColor(7,0);
        }
    }

    else if(y3 == y4Saver){
        if (swOfPlayerType)
        {
            setTextColor(10,0);
            printf("Hey player 3\nYou won\n");
            PrizeOfWinner();
            setTextColor(7,0);
        }
    }

    else if(y4 == y3Saver){
        if (swOfPlayerType)
        {
            setTextColor(10,0);
            printf("Hey player 4\nYou won\n");
            PrizeOfWinner();
            setTextColor(7,0);
        }
    }
}


FILE *prjFile;
FILE *prjFile2;
FILE *prjFile3;
FILE *prjFile4;
FILE *prjFile5;

void open_file_board(int n){

    prjFile = fopen("C:\\Users\\ASUS\\Desktop\\U.PROJECT\\prjSaver.txt", "wt");

    if(!prjFile){
        printf("can't open file");
        exit(0);
    }
    for (int i = 0; i < 2*n-1; i++)     //print the updated board
    {
        for (int j = 0; j < 2*n-1; j++)
        {
            if (board[i][j]=='1')
            {
                if (j!=2*n-2)
                {
                    setTextColor(10,0);
                    fprintf(prjFile, "%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(10,0);
                    fprintf(prjFile, "%c\n",board[i][j]);
                    setTextColor(7,0);
                }


            }
            else if (board[i][j]=='2')
            {
                if (j!=2*n-2)
                {
                    setTextColor(12,0);
                    fprintf(prjFile, "%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(12,0);
                    fprintf(prjFile, "%c\n",board[i][j]);
                    setTextColor(7,0);
                }
            }

            else if (j!=2*n-2)
            {
                setTextColor(11,0);
                fprintf(prjFile, "%c",board[i][j]);
                setTextColor(7,0);
            }
            else
            {
                setTextColor(11,0);
                fprintf(prjFile, "%c\n",board[i][j]);
                setTextColor(7,0);
            }

        }

    }
    fclose(prjFile);
}

void open_file_board2(){

    int t=0, z=0, n;
    char boardTxt;


    prjFile2 = fopen("C:\\Users\\ASUS\\Desktop\\U.PROJECT\\prjSaver.txt", "rt");
    prjFile5 = fopen("C:\\Users\\ASUS\\Desktop\\U.PROJECT\\prjSaver2.txt", "rt");

    if(!prjFile2){

        printf("can't open file");
        exit(0);
    }
    if(!prjFile5){

        printf("can't open file");
        exit(0);
    }

    fscanf(prjFile2, "%c", &boardTxt);
    fscanf(prjFile5, "%d", &n);
    while(!feof(prjFile2)){
        printf("%c", boardTxt);
        board[t][z] = boardTxt;
        z++;
        if(z > 2 * n - 1){
            t++;
            z=0;
        }
        fscanf(prjFile2, "%c", &boardTxt);
    }
    fclose(prjFile2);
}

void open_file_info(int n, int x1, int y1, int x2, int y2, int x1Saver, int x2Saver, int p1Walls, int p2Walls, char player, int swOfPlayerType, int counter){

    prjFile3 = fopen("C:\\Users\\ASUS\\Desktop\\U.PROJECT\\prjSaver2.txt", "wt");

    if(!prjFile3){
        printf("can't open file");
        exit(0);
    }

    fprintf(prjFile3, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%c\n%d\n%d", n, x1, y1, x2, y2, x1Saver, x2Saver, p1Walls, p2Walls, player, swOfPlayerType, counter);

    fclose(prjFile3);

}
void open_file_info2(int *n, int *x1, int *y1, int *x2, int *y2, int *x1Saver, int *x2Saver, int *p1Walls, int *p2Walls, char *player, int *swOfPlayerType, int *counter){

    int infoTxt;
    char infoTxt2;
    prjFile4 = fopen("C:\\Users\\ASUS\\Desktop\\U.PROJECT\\prjSaver2.txt", "rt");

    if(!prjFile4){

        printf("can't open file");
        exit(0);
    }

    fscanf(prjFile4, "%d\n", &infoTxt); *n = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x1 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *y1 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x2 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *y2 = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x1Saver = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *x2Saver = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *p1Walls = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *p2Walls = infoTxt;
    fscanf(prjFile4, "%c\n", &infoTxt2); *player = infoTxt2;
    fscanf(prjFile4, "%d\n", &infoTxt); *swOfPlayerType = infoTxt;
    fscanf(prjFile4, "%d\n", &infoTxt); *counter = infoTxt;

    fclose(prjFile4);


}




int main(){
    srand(time(NULL));
    printf("\n");
    setTextColor(9, 0);
    printf("shall we start over(press S) or load the last game(press L)?\n");
    setTextColor(6, 0);
    char order;
    scanf(" %c", &order);
    int n;
    int p1Walls, x1, y1;
    int p2Walls, x2, y2;
    int x1Saver;        //finish line for player1
    int x2Saver;
    char player;
    int swOfPlayerType = 1;


    if(order == 'L'){
        setTextColor(2, 0);
        printf("previous board:\n\n");
        setTextColor(6, 0);
        open_file_board2();
        open_file_info2(&n, &x1, &y1, &x2, &y2, &x1Saver, &x2Saver, &p1Walls, &p2Walls, &player, &swOfPlayerType, &counter);

    }

    else {

        printf("2/4 players?(press 2/4)\n");

        int choose;
        scanf("%d", &choose);

        if(choose == 4){
            multi_4();
            return 0;
        }
        else {

            scanf("%d", &n);
            for (int i = 0; i < 2 * n - 1; i++) {
                for (int j = 0; j < 2 * n - 1; j++) {
                    if (i % 2 == 0 && j % 2 == 0) {
                        board[i][j] = 254;
                    } else board[i][j] = 32;

                }

            }       //create the board whith squares

            scanf("%d %d\n%d %d", &x1, &y1, &x2, &y2);
            board[2 * x1][2 * y1] = '1';      //simbol of player1
            board[2 * x2][2 * y2] = '2';      //simbol of player2

            //end of board defult setting

            for (int i = 0; i < 2 * n - 1; i++)     //print the default board
            {
                for (int j = 0; j < 2 * n - 1; j++) {
                    if (board[i][j] == '1') {
                        if (j != 2 * n - 2) {
                            setTextColor(10, 0);
                            printf("%c", board[i][j]);
                            setTextColor(7, 0);
                        } else {
                            setTextColor(10, 0);
                            printf("%c\n", board[i][j]);
                            setTextColor(7, 0);
                        }


                    } else if (board[i][j] == '2') {
                        if (j != 2 * n - 2) {
                            setTextColor(12, 0);
                            printf("%c", board[i][j]);
                            setTextColor(7, 0);
                        } else {
                            setTextColor(12, 0);
                            printf("%c\n", board[i][j]);
                            setTextColor(7, 0);
                        }
                    } else if (j != 2 * n - 2) {
                        setTextColor(11, 0);
                        printf("%c", board[i][j]);
                        setTextColor(7, 0);
                    } else {
                        setTextColor(11, 0);
                        printf("%c\n", board[i][j]);
                        setTextColor(7, 0);
                    }

                }

            }

            //move and place walls will start from bellow

            setTextColor(9, 0);
            printf("pleas Determine how many walls the player1 has\n");
            setTextColor(7, 0);
            scanf("%d", &p1Walls);
            setTextColor(9, 0);
            printf("pleas Determine how many walls the player2 has\n");
            setTextColor(7, 0);
            scanf("%d", &p2Walls);
            //finish line for player2
            if (x1 >= n / 2) {
                x1Saver = n - 1;
                x2Saver = 0;
            } else {
                x1Saver = 0;
                x2Saver = n - 1;
            }

            getchar();


            while (1) {
                setTextColor(5, 0);
                printf("do you have any friend to play with?Y=(yes) / N=(no,play with Bot)\n");
                setTextColor(7, 0);
                scanf("%c", &player);
                if (player == 'N') {
                    swOfPlayerType = 0;
                    mORwPrint();
                    break;
                } else if (player == 'Y') {
                    break;
                }

            }
        }
    }


    while (x1!=x2Saver && x2!=x1Saver)
    {

        if (swOfPlayerType)
        {
            mORwPrint();
        }
        else if (!swOfPlayerType && counter%2!=0)
        {
            setTextColor(9,0);
            printf("wait for Bot\n");
            setTextColor(7,0);
        }
        char decision;
        while (1 && !(swOfPlayerType==0 && counter%2!=0))
        {

            scanf(" %c",&decision);
            if (decision=='m' ||decision=='w')
            {
                break;
            }
            else
            {
                setTextColor(6,0);
                printf("you should choose between w(place a wall) & m(move your piece)\n");
                setTextColor(7,0);
            }



        }
        if (!swOfPlayerType && counter%2!=0)
        {
            Botdecision(&decision);
        }       //end of select between m & w


        if (decision=='m')
        {

            lable:
            while (1)
            {
                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                    directionPrint();
                }
                char type;
                while (1 && !(swOfPlayerType==0 && counter%2!=0))
                {
                    scanf(" %c",&type);
                    if (type=='w' ||type=='d' ||type=='s' ||type=='a') break;
                    else if (bentType(x1,y1,x2,y2,counter)==1 && (type=='e'||type=='q')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==2 && (type=='z'||type=='c')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==3 && (type=='q'||type=='z')) break;
                    else if (bentType(x1,y1,x2,y2,counter)==4 && (type=='e'||type=='z')) break;

                    else
                    {
                        setTextColor(4,0);
                        printf("You have to choose between the four main diractions and secondary directions that you are allowed to use\n");
                        setTextColor(7,0);
                    }

                }
                if (!swOfPlayerType && counter%2!=0)
                {
                    BotType(&type);
                }       //end of select move type


                int retu=bentType(x1,y1,x2,y2,counter);
                if (counter%2==0)
                {
                    board[2*x1][2*y1]=254;

                    //if the direction is main

                    if (type == 'w' && x1-2>-1 && x1-1==x2 && y1==y2)
                    {
                        if (board[2*x1-3][2*y1]==32)
                        {
                            x1-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'w' && x1-1>-1)
                    {
                        if (board[2*x1-1][2*y1]==32)
                        {
                            x1--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 's' && x1+2<n && x1+1==x2 && y1==y2)
                    {
                        if (board[2*x1+3][2*y1]==32)
                        {
                            x1+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 's' && x1+1<n)
                    {
                        if (board[2*x1+1][2*y1]==32)
                        {
                            x1++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'd' && y1+2<n && x1==x2 && y1+1==y2)
                    {
                        if (board[2*x1][2*y1+3]==32)
                        {
                            y1+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'd' && y1+1<n)
                    {
                        if (board[2*x1][2*y1+1]==32)
                        {
                            y1++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'a' && y1-2>-1 && x1==x2 && y1-1==y2)
                    {
                        if (board[2*x1][2*y1-3]==32)
                        {
                            y1-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if(type == 'a' && y1-1>-1)
                    {
                        if (board[2*x1][2*y1-1]==32)
                        {
                            y1--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }

                        //if the direction is not main

                    else if (retu!=-1 && board[x1+x2][y1+y2]==32)   //x1+x2 & y1+y2 is the average coordinate of they blocks
                    {
                        if (type == 'q' && x1-1>-1 && y1-1>-1 && ((board[2*x1-3][2*y1]!=32 && retu==1) || (board[2*x1][2*y1-3]!=32 && retu==3)))
                        {
                            x1--;
                            y1--;
                            break;
                        }

                        else if (type == 'e' && x1-1>-1 && y1+1<n && ((board[2*x1-3][2*y1]!=32 && retu==1) || (board[2*x1][2*y1+3]!=32 && retu==4)))
                        {
                            x1--;
                            y1++;
                            break;
                        }

                        else if (type == 'z' && x1+1<n && y1-1>-1 && ((board[2*x1+3][2*y1]!=32 && retu==2) || (board[2*x1][2*y1-3]!=32 && retu==3)))
                        {
                            x1++;
                            y1--;
                            break;
                        }

                        else if(type == 'c' && x1+1<n && y1+1<n && ((board[2*x1+3][2*y1]!=32 && retu==2) || (board[2*x1][2*y1+3]!=32 && retu==4)))
                        {
                            x1++;
                            y1++;
                            break;
                        }
                        else BoardExitError(swOfPlayerType);
                    }


                    else
                    {
                        BoardExitError(swOfPlayerType);
                    }
                }


                else
                {
                    board[2*x2][2*y2]=254;
                    if (type == 'w' && x2-2>-1  && x2-1==x1 && y2==y1)
                    {
                        if (board[2*x2-3][2*y2]==32)
                        {
                            x2-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'w' && x2-1>-1)
                    {
                        if (board[2*x2-1][2*y2]==32)
                        {
                            x2--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 's' && x2+2<n && x2+1==x1 && y2==y1)
                    {
                        if (board[2*x2+3][2*y2]==32)
                        {
                            x2+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 's' && x2+1<n)
                    {
                        if (board[2*x2+1][2*y2]==32)
                        {
                            x2++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'd' && y2+2<n && x2==x1 && y2+1==y1)
                    {
                        if (board[2*x2][2*y2+3]==32)
                        {
                            y2+=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'd' && y2+1<n)
                    {
                        if (board[2*x2][2*y2+1]==32)
                        {
                            y2++;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if (type == 'a' && y2-2>-1 && x2==x1 && y2-1==y1)
                    {
                        if (board[2*x2][2*y2-3]==32)
                        {
                            y2-=2;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }
                    else if(type == 'a' && y2-1>-1)
                    {
                        if (board[2*x2][2*y2-1]==32)
                        {
                            y2--;
                            break;
                        }
                        else
                        {
                            WallPassingError(swOfPlayerType);
                        }
                    }


                        //if the direction is not main


                    else if (retu!=-1 && board[x1+x2][y1+y2]==32)   //x1+x2 & y1+y2 is the average coordinate of they blocks
                    {
                        if (type == 'q' && x2-1>-1 && y2-1>-1 && ((board[2*x2-3][2*y2]!=32 && retu==1) || (board[2*x2][2*y2-3]!=32 && retu==3)))
                        {
                            x2--;
                            y2--;
                            break;
                        }

                        else if (type == 'e' && x2-1>-1 && y2+1<n && ((board[2*x2-3][2*y2]!=32 && retu==1) || (board[2*x2][2*y2+3]!=32 && retu==4)))
                        {
                            x2--;
                            y2++;
                            break;
                        }

                        else if (type == 'z' && x2+1<n && y2-1>-1 && ((board[2*x2+3][2*y2]!=32 && retu==2) || (board[2*x2][2*y2-3]!=32 && retu==3)))
                        {
                            x2++;
                            y2--;
                            break;
                        }

                        else if(type == 'c' && x2+1<n && y2+1<n && ((board[2*x2+3][2*y2]!=32 && retu==2) || (board[2*x2][2*y2+3]!=32 && retu==4)))
                        {
                            x2++;
                            y2++;
                            break;
                        }
                        else BoardExitError(swOfPlayerType);
                    }

                    else
                    {
                        BoardExitError(swOfPlayerType);
                    }
                }
            }     //end of move
            board[2*x1][2*y1]='1';      //player 1 moved
            board[2*x2][2*y2]='2';      //player 2 moved

        }




        else if (decision=='w')
        {
            if (counter%2==0)
            {
                if (p1Walls>0)
                {
                    p1Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }
            else
            {
                if (p2Walls>0)
                {
                    p2Walls--;
                }
                else
                {
                    ZeroWallError(swOfPlayerType);
                    goto lable;
                }

            }



            while (1)
            {
                int xOfWall;
                int yOfWall;
                if (!(swOfPlayerType==0 && counter%2!=0))
                {
                    setTextColor(9,0);
                    printf("Please enter three items bellow\n");
                    sleep(500);
                    setTextColor(9,0);
                    printf("Row\n");
                    sleep(500);
                    printf("Column\n");
                    sleep(500);
                    printf("type : V(vertical) or H(horisontal)\n");
                    setTextColor(7,0);
                    scanf("%d",&xOfWall);
                    scanf("%d",&yOfWall);
                }
                char wallDirect;
                while (1 && !(swOfPlayerType==0 && counter%2!=0))
                {
                    scanf(" %c",&wallDirect);
                    if (wallDirect=='H' || wallDirect=='V')
                    {
                        break;
                    }
                    else
                    {
                        setTextColor(4,0);
                        printf("pay attention to your wall type.you can just insert one of these options:V(vertical),H(horisontal)\n");
                        sleep(1000);
                        setTextColor(6,0);
                        printf("Your mistake can be entering lowercase letters\n");
                        setTextColor(7,0);
                    }
                }
                if (swOfPlayerType==0 && counter%2!=0)
                {
                    WallOfBot(&xOfWall,&yOfWall,&wallDirect,n);
                }        //end of wall selectiont



                xOfWall *= 2;
                yOfWall *= 2;
                if(wallDirect == 'H' && xOfWall-1>-1  && xOfWall<2*n-1 && yOfWall>-1 && yOfWall+2<2*n-1 && board[xOfWall-1][yOfWall] == 32 && board[xOfWall-1][yOfWall + 1] == 32 && board[xOfWall-1][yOfWall + 2]  == 32)
                {
                    board[xOfWall-1][yOfWall] = 196;

                    board[xOfWall-1][yOfWall + 1] = 196;

                    board[xOfWall-1][yOfWall + 2] = 196;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
                    }
                    // break;
                }
                else if (wallDirect=='V' && yOfWall-1>-1 && yOfWall<2*n-1 && xOfWall-2>-1 && xOfWall<2*n-1 && board[xOfWall][yOfWall-1] == 32 && board[xOfWall-1][yOfWall-1]  == 32 && board[xOfWall-2][yOfWall-1] == 32)
                {
                    board[xOfWall][yOfWall-1] = 179;

                    board[xOfWall-1][yOfWall-1] = 179;

                    board[xOfWall-2][yOfWall-1] = 179;

                    if (counter%2==0 && p1Walls<4)
                    {
                        RemainingWalls(p1Walls,swOfPlayerType);
                    }
                    else if (counter%2!=0 && p2Walls<4)
                    {
                        RemainingWalls(p2Walls,swOfPlayerType);
                    }
                    // break;
                }       //end of putting walls in the board
                else
                {
                    if (swOfPlayerType)
                    {
                        setTextColor(4,0);
                        printf("you can't place your wall here\n");
                        setTextColor(7,0);
                    }
                }



                if (counter==0)
                {
                    if (paint(n,2*x2,2*y2,counter,x1Saver,x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p1Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }


                }
                else if(counter==1)
                {
                    if (paint(n,2*x1,2*y1,counter,x1Saver,x2Saver))
                    {
                        break;
                    }
                    else
                    {
                        stuckError();
                        p2Walls++;
                        if (wallDirect=='H')
                        {
                            board[xOfWall-1][yOfWall] = 32;

                            board[xOfWall-1][yOfWall + 1] = 32;

                            board[xOfWall-1][yOfWall + 2] = 32;
                        }
                        else
                        {
                            board[xOfWall][yOfWall-1] = 32;

                            board[xOfWall-1][yOfWall-1] = 32;

                            board[xOfWall-2][yOfWall-1] = 32;
                        }


                    }
                }

                



            }

        }


        //clearscreen();      //clear terminal

        for (int i = 0; i < 2*n-1; i++)     //print the updated board
        {
            for (int j = 0; j < 2*n-1; j++)
            {
                if (board[i][j]=='1')
                {
                    if (j!=2*n-2)
                    {
                        setTextColor(10,0);
                        printf("%c",board[i][j]);
                        setTextColor(7,0);
                    }
                    else
                    {
                        setTextColor(10,0);
                        printf("%c\n",board[i][j]);
                        setTextColor(7,0);
                    }


                }
                else if (board[i][j]=='2')
                {
                    if (j!=2*n-2)
                    {
                        setTextColor(12,0);
                        printf("%c",board[i][j]);
                        setTextColor(7,0);
                    }
                    else
                    {
                        setTextColor(12,0);
                        printf("%c\n",board[i][j]);
                        setTextColor(7,0);
                    }
                }
                else if (j!=2*n-2)
                {
                    setTextColor(11,0);
                    printf("%c",board[i][j]);
                    setTextColor(7,0);
                }
                else
                {
                    setTextColor(11,0);
                    printf("%c\n",board[i][j]);
                    setTextColor(7,0);
                }

            }

        }
        if(!swOfPlayerType && counter%2!=0){
            mORwPrint();
        }

        counter++;      //this can tell the computer that the turn of current player finished

        open_file_board(n);
        open_file_info(n, x1, y1, x2, y2, x1Saver, x2Saver, p1Walls, p2Walls, player, swOfPlayerType, counter);
    }
    //end of geme
    if (x2==x1Saver)
    {
        if (swOfPlayerType)
        {
            setTextColor(10,0);
            printf("Hey player 2\nYou won\n");
            setTextColor(7,0);
        }
        else
        {
            setTextColor(10,0);
            printf("Game over\n");
            setTextColor(7,0);
        }
    }

    else
    {
        setTextColor(10,0);
        printf("Hey player 1\nYou won\n");
        setTextColor(7,0);
    }
    if (!(x2==x1Saver && swOfPlayerType==0))
    {
        PrizeOfWinner();
    }
    else printf("nooobe-h sag");

    return 0;
}
