#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BoardSize 10 // Sonrasında uğraşmamak için define ettim

/* Videos:
 > Hit the wall: https://youtu.be/ubctiE4wqPM
 > Hit the obstacle: https://youtu.be/vawDFLqPa6g
 > Hit its body: https://youtu.be/mMEwJv8iWhw
 
 Video linklerinin açılmama ihtimaline karşı teams'e yükledim. */

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    char type;
    int value;
} Block;

void play(Block*** board);
Block*** initBoard();
void drawBoard(Block*** board, Point* snake, int snakeLength);
int checkStatus(Block*** board, Point* snake, int snakeLength);
void update(Block*** board, Point* snake, int* snakeLength, char move);

int main()
{
    
    printf("\n*** CSE 102 Homework 9 ***\n");
    printf("*** Welcome to the 2D Snake Game in C Programming ***\n");
    
    Block*** board = initBoard();
    play(board);

    for (int row = 0; row < BoardSize; ++row)
    {
        for (int col = 0; col < BoardSize; ++col)
        {
            free(board[row][col]);
        }
        free(board[row]);
    }
    free(board);

    return 0;
}


Block*** initBoard()
{
    Block*** board = (Block***)malloc(BoardSize * sizeof(Block**));
    
    for (int row = 0; row < BoardSize; row++)
    {
        board[row] = (Block**)malloc(BoardSize * sizeof(Block*));
        
        for (int col = 0; col < BoardSize; col++)
        {
            board[row][col] = (Block*)malloc(sizeof(Block));
            board[row][col]->type = 'e';
            board[row][col]->value = 0;
        }
    }

    srand(time(NULL));
    int obstacleRow = rand() % (BoardSize - 1) + 1;
    int obstacleCol = rand() % (BoardSize - 1) + 1;
    board[obstacleRow][obstacleCol]->type = 'o';
    board[obstacleRow][obstacleCol]->value = rand() % 3 + 1;

    int baitRow = rand() % (BoardSize - 1) + 1;
    int baitCol = rand() % (BoardSize - 1) + 1;
    board[baitRow][baitCol]->type = 'b';

    return board;
}

void drawBoard(Block*** board, Point* snake, int snakeLength)
{
    printf("\n");
    
    for (int row = 0; row < BoardSize; ++row)
    {
        for (int col = 0; col < BoardSize; ++col)
        {
            if (row == 0 || row == BoardSize - 1 || col == 0 || col == BoardSize - 1)
            {
                printf("- ");
            }
            else
            {
                char type = board[row][col]->type;
                
                if (type == 'e')
                {
                    int isSnakeBody = 0;
                    
                    for (int i = 0; i < snakeLength; ++i)
                    {
                        if (snake[i].row == row && snake[i].col == col)
                        {
                            isSnakeBody = 1;
                            break;
                        }
                    }
                    if (isSnakeBody)
                    {
                        if (row == snake[0].row && col == snake[0].col)
                        {
                            printf("O ");
                        }
                        else
                        {
                            printf("X ");
                        }
                    }
                    else
                    {
                        printf("  ");
                    }
                }
                else if (type == 'b') {
                    printf(". ");
                }
                else if (type == 'o')
                {
                    if (board[row][col]->value == 0)
                    {
                        printf("  ");
                    }
                    else
                    {
                        printf("%d ", board[row][col]->value);
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void play(Block*** board)
{
    int snakeLength = 1;
    Point* snake = (Point*)malloc(snakeLength * sizeof(Point));
    snake[0] = (Point){.row = 1, .col = 1};

    while (1)
    {
        drawBoard(board, snake, snakeLength);

        if (checkStatus(board, snake, snakeLength))
        {
            printf("Game Over\n");
            break;
        }

        char move;
        
        printf("Please enter next move (w for up/a for left/s for down/d for right): ");
        scanf(" %c", &move);
        
        while (move != 'w' && move != 'a' && move != 's' && move != 'd')
        {
            printf("Invalid move. Please try again.\n");
            printf("Please enter next move (w for up/a for left/s for down/d for right): ");
            scanf(" %c", &move);
        }
        

        update(board, snake, &snakeLength, move);
    }

    free(snake);
}


void update(Block*** board, Point* snake, int* snakeLength, char move)
{
    int prevRow = snake[0].row;
    int prevCol = snake[0].col;

    for (int i = 1; i < *snakeLength; ++i)
    {
        int tempRow = snake[i].row;
        int tempCol = snake[i].col;
        snake[i].row = prevRow;
        snake[i].col = prevCol;
        prevRow = tempRow;
        prevCol = tempCol;
    }

    if (move == 'w' && snake[0].row > 0 && board[snake[0].row - 1][snake[0].col]->type != 'o')
    {
        --snake[0].row;
    }
    else if (move == 'a' && snake[0].col > 0 && board[snake[0].row][snake[0].col - 1]->type != 'o')
    {
        --snake[0].col;
    }
    else if (move == 's' && snake[0].row < BoardSize - 1 && board[snake[0].row + 1][snake[0].col]->type != 'o')
    {
        ++snake[0].row;
    }
    else if (move == 'd' && snake[0].col < BoardSize - 1 && board[snake[0].row][snake[0].col + 1]->type != 'o')
    {
        ++snake[0].col;
    }

    int ateBait = 0;

    if (board[snake[0].row][snake[0].col]->type == 'b')
    {
        ateBait = 1;
    }

    board[snake[0].row][snake[0].col]->type = 'e';

    if (ateBait)
    {
        ++(*snakeLength);
        int baitRow, baitCol;
        do
        {
            baitRow = rand() % (BoardSize - 1) + 1;
            baitCol = rand() % (BoardSize - 1) + 1;
        }
        while (board[baitRow][baitCol]->type != 'e');
        board[baitRow][baitCol]->type = 'b';
    }

    int numObstacles = 0;

    for (int row = 0; row < BoardSize; ++row)
    {
        for (int col = 0; col < BoardSize; ++col)
        {
            if (board[row][col]->type == 'o')
            {
                if (board[row][col]->value < *snakeLength)
                {
                    board[row][col]->type = 'e';
                    board[row][col]->value = 0;
                }
                else
                {
                    numObstacles++;
                }
            }
        }
    }

    if (numObstacles < 3 && *snakeLength % 5 == 0)
    {
        int obstacleRow, obstacleCol;
        do
        {
            obstacleRow = rand() % (BoardSize - 1) + 1;
            obstacleCol = rand() % (BoardSize - 1) + 1;
        }
        while (board[obstacleRow][obstacleCol]->type != 'e');

        board[obstacleRow][obstacleCol]->type = 'o';
        board[obstacleRow][obstacleCol]->value = 3;
    }
}

int checkStatus(Block*** board, Point* snake, int snakeLength)
{
    int headRow = snake[0].row;
    int headCol = snake[0].col;

    for (int i = 1; i < snakeLength; ++i)
    {
        if (headRow == snake[i].row && headCol == snake[i].col)
        {
            return 1;
        }
    }

    if (headRow < 0 || headRow >= BoardSize || headCol < 0 || headCol >= BoardSize)
    {
        return 1;
    }

    if (board[headRow][headCol]->type == 'o' && board[headRow][headCol]->value > snakeLength)
    {
        return 1;
    }

    return 0;
}



