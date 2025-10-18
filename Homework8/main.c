#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3
#define EMPTY_SPACE '_'

struct Puzzle {
    char board[SIZE][SIZE];
    int empty_row;
    int empty_col;
};

void initializePuzzle(struct Puzzle *puzzle);
void printPuzzle(const struct Puzzle *puzzle);
int isValidMove(const struct Puzzle *puzzle, int number, char direction);
int moveTile(struct Puzzle *puzzle, int number, char direction);
int PuzzleSolved(const struct Puzzle *puzzle);
int menu();
int game(struct Puzzle *puzzle, int number, char direction, const char *filename, int moves);
void savePuzzle(const struct Puzzle *puzzle, const char *filename);
void auto_finish(struct Puzzle *puzzle, const char *filename, int *moves);
int calculateScore(int moves);
void saveBestScore(int score);
void showBestScore(int score);
int countInversions(struct Puzzle *puzzle);
int isSolvable(struct Puzzle *puzzle);



int main()
{
    menu();
    return 0;
}


int menu()
{
    int op;
    struct Puzzle *puzzle;
    int number;
    char direction;
    const char *filename = "board.txt";
    int score;
    int moves;
    
    printf("\n*** Welcome to 8-Puzzle Game! ***\n");
    printf(" 1-Play game as a user\n 2-Finish the game with PC\n 3-Show the best score\n 4-Exit\n");
    printf("Please select your option: ");
    scanf("%d", &op);
    
    switch (op)
    {
        case 1:
            game(&puzzle,number,direction,filename,moves);
            break;
        case 2:
            auto_finish(puzzle,filename,&moves);
            break;
        case 3:
            showBestScore(score);
            break;
        case 4:
            exit(0);
            break;
            
        default:
            printf("Invalid option! Please try again.\n");
            break;
    }
    
    return 0;
    
}



void initializePuzzle(struct Puzzle *puzzle)
{
    int numbers[SIZE * SIZE - 1];
    int count = 0;

    // Generate a random arrangement of numbers
    for (int i = 0; i < SIZE * SIZE - 1; ++i)
    {
        numbers[i] = i + 1;
    }
    srand(time(NULL));
    
    for (int i = SIZE * SIZE - 2; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Fill the puzzle board with numbers and the empty space
    count = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (count < SIZE * SIZE - 1)
            {
                puzzle->board[i][j] = numbers[count] + '0';
                count++;
            }
            else
            {
                puzzle->board[i][j] = EMPTY_SPACE;
                puzzle->empty_row = i;
                puzzle->empty_col = j;
            }
        }
    }
}

void printPuzzle(const struct Puzzle *puzzle)
{
    FILE *board = fopen("board.txt", "a+");
    
    if(board == NULL)
    {
        printf("Warning!\n");
    }
    
    fprintf(board,"\n");
    // writes the board on text file
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            fprintf(board, "%c ", puzzle->board[i][j]);
        }
        fprintf(board,"\n");
    }
    
    printf("\n");
    // prints the board on terminal
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            printf("%c ", puzzle->board[i][j]);
        }
        printf("\n");
    }
    
}

int isValidMove(const struct Puzzle *puzzle, int number, char direction)
{
    int row = -1;
    int col = -1;

    // Find the position of the tile
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (puzzle->board[i][j] == number + '0')
            {
                row = i;
                col = j;
                break;
            }
        }
    }

    // Check if the move is valid in the specified direction
    switch (direction)
    {
        case 'U':
            if (row > 0 && puzzle->board[row - 1][col] == EMPTY_SPACE)
            {
                return 1; // Valid move
            }
            break;
        case 'D':
            if (row < SIZE - 1 && puzzle->board[row + 1][col] == EMPTY_SPACE)
            {
                return 1; // Valid move
            }
            break;
        case 'L':
            if (col > 0 && puzzle->board[row][col - 1] == EMPTY_SPACE)
            {
                return 1; // Valid move
            }
            break;
        case 'R':
            if (col < SIZE - 1 && puzzle->board[row][col + 1] == EMPTY_SPACE)
            {
                return 1; // Valid move
            }
            break;
        default:
            printf("Invalid direction!\n");
            break;
    }

    return 0; // Invalid move
}

int moveTile(struct Puzzle *puzzle, int number, char direction)
{
    int row = -1;
    int col = -1;

    // Find the position of the tile
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (puzzle->board[i][j] == number + '0')
            {
                row = i;
                col = j;
                break;
            }
        }
    }

    // Move the tile in the specified direction
    switch (direction)
    {
        case 'U':

                puzzle->board[row][col] = EMPTY_SPACE;
                puzzle->board[row - 1][col] = number + '0';
                puzzle->empty_row = row;
                puzzle->empty_col = col;
            break;
        case 'D':

                puzzle->board[row][col] = EMPTY_SPACE;
                puzzle->board[row + 1][col] = number + '0';
                puzzle->empty_row = row;
                puzzle->empty_col = col;
            break;
        case 'L':
                puzzle->board[row][col] = EMPTY_SPACE;
                puzzle->board[row][col - 1] = number + '0';
                puzzle->empty_row = row;
                puzzle->empty_col = col;
            break;
        case 'R':
                puzzle->board[row][col] = EMPTY_SPACE;
                puzzle->board[row][col + 1] = number + '0';
                puzzle->empty_row = row;
                puzzle->empty_col = col;
            break;
            
        default:
            printf("Invalid direction!\n");
            break;
    }
    
    return 0;
    
}

void savePuzzle(const struct Puzzle *puzzle, const char *filename) {
    
    FILE *board = fopen(filename, "a+");
    
    if (board == NULL)
    {
        printf("Unable to open file for saving!\n");
        return;
    }

    fprintf(board,"\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            fprintf(board, "%c ", puzzle->board[i][j]);
        }
        fprintf(board, "\n");
    }

    fclose(board);
}

void auto_finish(struct Puzzle *puzzle, const char *filename, int *moves)
{
    
    initializePuzzle(puzzle);
    printPuzzle(puzzle);
    
    if (PuzzleSolved(puzzle))
    {
        return;
    }

    if (isSolvable(puzzle))
    {
        int number, randomIndex;
        char direction;
        const char directions[] = {'U', 'D', 'L', 'R'};
        int score = 0;
        int maxMoves = 900000; // Maximum number of moves to prevent infinite loop

        while (*moves < maxMoves)
        {
            randomIndex = rand() % 4;
            direction = directions[randomIndex];
            number = rand() % 8 + 1;

            if (isValidMove(puzzle, number, direction))
            {
                moveTile(puzzle, number, direction);
                (*moves)++;
                printf("Moves: %d", moves);
                printPuzzle(puzzle);
                savePuzzle(puzzle, filename);

                if (PuzzleSolved(puzzle))
                {
                    printf("Congrats! You finished the game!\n");
                    score = calculateScore(moves);
                    printf("Total moves: %d\n", moves);
                    printf("Score: %d\n", score);
                    saveBestScore(score);
                    menu();
                }
            }
        }
    }

     auto_finish(puzzle, filename, moves);
}

void saveBestScore(int score)
{
    char filename[] = "best_score.txt";
    
    FILE *file = fopen(filename, "r");
    
    if (file != NULL)
    {
        int bestScore;
        
        fscanf(file, "%d", &bestScore);
        fclose(file);

        if (score <= bestScore)
            return; // Current score is not better than the best score, no need to update
    }

    file = fopen(filename, "w");
    
    if (file == NULL)
    {
        printf("Unable to open file for saving best score!\n");
        return;
    }

    fprintf(file, "%d", score);
    fclose(file);
}

int PuzzleSolved(const struct Puzzle *puzzle)
{
    
    char expectedValue = '1';
    
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (puzzle->board[i][j] != expectedValue)
            {
                if (i == SIZE - 1 && j == SIZE - 1 && puzzle->board[i][j] == EMPTY_SPACE)
                {
                    return 1; // Puzzle solved
                }
                else
                {
                    return 0; // Puzzle not solved
                }
            }
            expectedValue++;
        }
    }
    return 0; // Puzzle not solved
}

int calculateScore(int moves)
{
    
    return 1000 - 10 * moves;
    
}

int game(struct Puzzle *puzzle, int number, char direction, const char *filename, int moves)
{
    moves = 0;
    int score = 0;

    initializePuzzle(puzzle);
    printPuzzle(puzzle);
    score = calculateScore(moves);

    while (1)
    {
        printf("Enter number and direction (e.g., 2-R): ");
        scanf("%d-%c", &number, &direction);

        if (number >= 1 && number <= 8 && (direction == 'U' || direction == 'D' || direction == 'L' || direction == 'R'))
        {
            if (isValidMove(puzzle, number, direction))
            {
                
                moveTile(puzzle, number, direction);
                moves++;
                printf("Moves: %d", moves);
                printPuzzle(puzzle);
                savePuzzle(puzzle, filename);
                

                if (PuzzleSolved(puzzle))
                {
                    printf("Congrats! You finished the game!\n");
                    score = calculateScore(moves);
                    printf("Total moves: %d\n", moves);
                    printf("Score: %d\n", score);
                    saveBestScore(score);
                    menu();
                    break;
                }
            }
            else
            {
                printf("Invalid move! Please try again.\n");
            }
        }
        else
        {
            printf("Invalid input! Please try again.\n");
        }
    }

    
    return 0;
}

void showBestScore(int score)
{
    char filename[] = "best_score.txt";
    
    FILE *file = fopen(filename, "r");
    
    if (file == NULL)
    {
        printf("Best score not available.\n");
        return;
    }

    int bestScore;
    fscanf(file, "%d", &bestScore);
    fclose(file);

    printf("Best score: %d\n", bestScore);
}

int countInversions(struct Puzzle *puzzle)
{
    int inv = 0;
    int i, j;
    int number;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            number = puzzle->board[i][j];
            if (number == 0) // Skip the blank tile
                continue;
            
            for (int k = i; k < SIZE; k++)
            {
                for (int l = (k == i) ? j + 1 : 0; l < SIZE; l++)
                {
                    int compare = puzzle->board[k][l];
                    if (compare != 0 && number > compare)
                        inv++;
                }
            }
        }
    }
    return inv;
}

int isSolvable(struct Puzzle *puzzle)
{
    int inversions = countInversions(puzzle);
    int blankRow = 0;

    // Find the row containing the blank tile
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (puzzle->board[i][j] == 0)
            {
                blankRow = SIZE - i;
                break;
            }
        }
    }


    if (SIZE % 2 != 0 && inversions % 2 == 0)
        return 1;

    else if (SIZE % 2 == 0 && ((inversions + blankRow) % 2) != 0)
        return 1;
    else
        return 0;
}
