#include <stdio.h>
#define ROWS 5
#define COLS 35
#define SIZE 7
char turn = 'u';
/*This function takes the board and the number array as parameters*/
void initializeGame(char board[ROWS][COLS], int arr[SIZE * 2]) /*Function that initialize the game*/
{
    int i, j;

    for (i = 0; i < SIZE * 2; i++) /*For loop to fill the array that hold the numbers of the movement*/
    {
        if (i == 6 || i == 13)
            arr[i] = 0;
        else
            arr[i] = 4;
    }

    for (i = 0; i < ROWS; i++) /*for loop to fill the board*/
    {
        for (j = 0; j < COLS; j++)
        {
            /*Condition for game board designing*/
            if (i == 0 || i == 4)
            {
                if (j != 33 && j != 1 && (j == 0 || j == 34 || ((j - 1) % 4 == 0)))
                    board[i][j] = '+';
                else
                    board[i][j] = '-';
            }
            else if (i == 1 || i == 3)
            {
                if (j != 33 && j != 1 && (j == 0 || j == 34 || ((j - 1) % 4 == 0)))
                    board[i][j] = '|';
                else
                    board[i][j] = ' ';
            }
            else if (i == 2)
            {
                if ((j > 0 && j < 5) || (j > 29 && j < 34))
                    board[i][j] = ' ';

                else if (j != 33 && (j == 0 || j == 34 || ((j - 1) % 4 == 0)))
                    if (j == 0 || j == 5 || j == 29 || j == 34)
                        board[i][j] = '|';
                    else
                        board[i][j] = '+';
                else
                    board[i][j] = '-';
            }
        }
    }
}

/*this function takes the board an the number array as parameters*/
void printBoard(char board[ROWS][COLS], int arr[]) /*function that print the board*/
{
    int i, j;
    for (i = 0; i < ROWS; i++) /*For loop to print the 2D board array*/
    {
        for (j = 0; j < COLS; j++)
        {
            /*conditions for print the number array */
            /*print from the number array*/
            if ((i == 1) && (j == 7 || j == 11 || j == 15 || j == 19 || j == 23 || j == 27))
            {
                if (arr[(SIZE * 2 - 1) - (j / 4)] >= 10)
                {
                    printf("%d", arr[(SIZE * 2 - 1) - (j / 4)]);
                    j++;
                }
                else
                    printf("%d", arr[(SIZE * 2 - 1) - (j / 4)]);
            }
            else if ((i == 3) && (j == 7 || j == 11 || j == 15 || j == 19 || j == 23 || j == 27))
            {
                if (arr[((j - 7) / 4)] >= 10)
                {
                    printf("%d", arr[((j - 7) / 4)]);
                    j++;
                }
                else
                    printf("%d", arr[((j - 7) / 4)]);
            }
            else if (i == 2 && (j == 2 || j == 31))
            {
                if (j == 31)
                {
                    if (arr[0] >= 10)
                    {
                        printf("%d", arr[6]);
                        j++;
                    }
                    else
                        printf("%d", arr[6]);
                }
                else if (j == 2)
                {
                    if (arr[SIZE * 2 - 1] >= 10)
                    {
                        printf("%d", arr[SIZE * 2 - 1]);
                        j++;
                    }
                    else
                        printf("%d", arr[SIZE * 2 - 1]);
                }
            }

            else
                printf("%c", board[i][j]); /*print from the board array*/
        }
        printf("\n");
    }
}

/*this function takes the number array as parameters and calculate best move for computer*/
int bestMove(int arr[SIZE * 2])
{
    /*plays every case and store the minimum sum after the move and return the index for best move*/
    int t = 0;
    int comp_arr[7];
    for (t = 0; t < SIZE * 2; t++)
    {
        if (t >= 7)
            comp_arr[t - 7] = arr[t]; /*fill the array of movement to computer array and we can manipulate it*/
    }

    int index;                   /*variable that catch the best move's index*/
    int min_sum = __INT32_MAX__; /*arramg max vaalue to the min_sum the we can calcaulate the min sum*/
    int sum = 0;                 /*variable that store the sum for each case*/

    int move_num;
    int selected_cup;
    int region;
    int p;
    for (p = 0; p < 6; p++)
    {
        selected_cup = p;
        move_num = comp_arr[selected_cup];
        if (move_num != 1)
        {
            if (p + move_num - 1 == 6) /*Looks whether it can gets another turn or not */
                return p;
        }
        else if (move_num == 1)
        {
            if (p + move_num == 6)
                return p;
        }
    }
    /*for loop to try every case and choose the best move means min sum index*/
    int j;
    for (j = 0; j < 6; j++)
    {
        selected_cup = j;
        move_num = comp_arr[j]; /*number of movement*/
        if (move_num == 1)
        {
            comp_arr[selected_cup] = 0;
            selected_cup++; /*it means move to another index*/
            if (selected_cup == 6)
                return j;
        }

        else if (move_num > 0)
        {
            comp_arr[j] = 1;
            move_num--;
            while (move_num > 0)
            {
                move_num--;
                selected_cup++;
                if (selected_cup == 6 && move_num == 0) /*if we can reach to big cup the return this index;*/
                {
                    return j;
                }
                else if (selected_cup == 6 && move_num > 0)
                {
                    move_num--;
                    while (move_num > 0)
                    {
                        move_num--;
                        selected_cup--;
                        if (selected_cup == 0 && move_num > 0)
                        {
                            comp_arr[selected_cup] += 1;
                            while ((move_num != 0))
                            {
                                move_num--;
                                selected_cup++;
                                comp_arr[selected_cup] += 1;
                            }
                        }
                    }
                }
            }
        }
        else /*if movement is zero return the first index that is not equal to zero*/
        {
            int m = 0;
            while (m < 6)
            {
                if (comp_arr[m] != 0)
                    return m;
                m++;
            }
        }
        int m = 0;
        while (m < 6) /*loop to calculate sum after a move*/
        {
            sum += comp_arr[m];
            m++;
        }
        if (sum < min_sum) /*update minimum sum after a move*/
        {
            sum = min_sum;
            index = j;
        }
    }
    return index; /*return the index*/
}
void move(int arr[SIZE * 2], int selected_cup)
{
    /*+: hareket et*/

    /*+: taşları arttır +: kim oynuyosa büyük haznesine o koyabilir. bittiği yeri kontrol et son yer 0 dan büyükse devam et*/
    /* Boşsa son yer sıra değiş*/
    /* Büyük hazneye gelirse ve son oynayan kimse bidaha oynasın*/
    int i;
    int movement = arr[selected_cup]; /*number of movement*/
    arr[selected_cup] = 0;
    /* i starts minimum from zero because user can select minimum first cup*/
    for (i = selected_cup + 1; movement > 0; i++) /*for loop to move*/
    {
        if (i == SIZE * 2) /*if we are at the end of the array then go to the start point*/
        {
            i = 0;
        }
        if (i == 6) /*case of users big cup*/
        {
            if (turn == 'u') /*move depends on the current turn*/
            {
                arr[i]++;
                movement--;
            }
        }
        else if (i == 13) /*case of computers big cup*/
        {
            if (turn == 'c') /*move depends on the current turn*/
            {
                movement--; /*decrease the movement*/
                arr[i]++;   /*increment the current cup*/
            }
        }
        else /*case for the other possibilities*/
        {
            arr[i]++;   /*increment the current cup*/
            movement--; /*decrease the movement*/
        }
    }

    i--; /*update last cup*/
    /*case for 3 possibilities*/
    /*1: if we are at the big cup*/
    if (i == 13 || i == 6)
    {
        if (turn == 'u')
            turn = 'u';
        else
            turn = 'c';
    }
    /*2: if  last cup was empty update the turn*/
    else if (arr[i] - 1 <= 0) /*eğer son taş boş kutuya gelirse sıra değiş*/
    {
        if (turn == 'u')
            turn = 'c';
        else
            turn = 'u';
    }
    else /*if last cup was not empty then distribution restarts from this cup*/
    {
        move(arr, i); /*call move function again for last cup*/
    }
}

int isContinue(int arr[SIZE * 2]) /*function that checks the game finishsed or not*/
{

    int i;
    int flag = 0; /*variable that checks the cup if is empty or not. if all of the cup is zero flag=0 else flag=1*/
    for (i = 0; i < SIZE - 1; i++)
    {
        if (arr[i] != 0) /*checks it is empty or not */
        {
            flag = 1;
            i = SIZE; /*as a break*/
        }
    }

    if (flag == 0)
        return flag; /*end of game*/
    flag = 0;
    for (i = SIZE; i < SIZE * 2 - 1; i++)
    {
        if (arr[i] != 0) /*checks it is empty or not */
        {
            flag = 1;
            i = SIZE * 2; /*as a break*/
        }
    }
    if (flag == 0)
        return flag; /*end of game*/

    return flag;
}
void gamePlay(char board[ROWS][COLS], int arr[SIZE * 2])
{
    printf("USER STARTS\n");
    turn = 'u';
    int is_playing = 1;
    int cup;

    while (is_playing == 1)
    {
        if (turn == 'u') /*user plays*/
        {
            printf("Select a cup from the bottom\n");
            scanf("%d", &cup);

            if (cup >= 1 && cup <= 6)
            {
                cup--;
                move(arr, cup);
            }
            else
            {
                printf("Wrong choice select again!!\n");
                continue;
            }
        }
        else if (turn == 'c') /*computer plays*/
        {
            printf("Computer is playing\n");

            int comp_move = bestMove(arr); /*getting best move from the function */
            printf("Computer move is: %d\n", comp_move);
            move(arr, comp_move + SIZE); /*comp_move+SIZE is the index of the selected cup in the number array.*/
        }
        printBoard(board, arr); /*print the board*/

        is_playing = isContinue(arr); /*update the loop variables to continue or ending the game*/
    }
}

int main()
{
    char board[ROWS][COLS]; /*game board*/
    int arr[SIZE * 2];      /*array that holds the stones for computer and for the user*/

    initializeGame(board, arr); /*initialize the game*/
    printBoard(board, arr);     /*print the board*/
    gamePlay(board, arr);       /*the game is starting*/

    /*Determine who wins*/
    if (arr[SIZE - 1] > arr[SIZE * 2 - 1])
        printf("USER WINS POINT : %d \n", arr[SIZE - 1]);
    else if (arr[SIZE - 1] < arr[SIZE * 2 - 1])
        printf("COMPUTER WINS POINT : %d \n", arr[SIZE * 2 - 1]);
    else
        printf("!!! DRAW !!!\n");

    return 0;
}
