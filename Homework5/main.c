#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef enum Color
{
    RED,    //0
    GREEN,  //1
    BLUE,   //2
    YELLOW, //3
    ORANGE  //4
} Color;

double colors[][3] = {
    {1, 0, 0},   // RED
    {0, 1, 0},   // GREEN
    {0, 0, 1},   // BLUE
    {0.5, 0.5, 0},   // YELLOW
    {0.5, 0.4, 0.2}   // ORANGE
};

char board[3][3] = {
    
    {'_', '_', '_'}, // { '(0,0)' , '(0,1)' , '(0,2)'}
    {'_', '_', '_'}, // { '(1,0)' , '(1,1)' , '(1,2)'}
    {'_', '_', '_'}  // { '(2,0)' , '(2,1)' , '(2,2)'}
    
};

void lowercase(char *letter);
int ReadingFile(char *letter);
Color closest(double colors[][3], double mixed[3]);
Color mixing(double colors[][3], Color x, Color y);
Color colorMixer(Color x, Color y, Color (*mixing)(double colors[][3], Color x, Color y));
void testColorMixer();
void printingBoard();
int theGame();
int checkingWinner(char sign);

int main()
{
    char *letter;
    ReadingFile(letter);
    testColorMixer();
    theGame();
}

/*int ReadingFile(char *letter)
{
    printf("\n*** PART ONE ***\n");
    
    FILE *textfile;
    
    char file[100];
    
    printf("You have three options:\n => example1.txt\n => example2.txt\n => example3.txt\n");
    printf("Please enter the text file: ");
    scanf("%s", file);
    
    textfile = fopen(file, "r");
    
    if (textfile == NULL)
    {
        printf("Warning. The file is empty.");
        return 1;
    }

    int counter[26] = {0}; // initialize all counts to 0
    char x;
    while ((x = fgetc(textfile)) != EOF)
    {
        lowercase(letter); // convert to lowercase
        if (x >= 'a' && x <= 'z')
        {
            ++counter[x - 'a'];
        }
    }

    fclose(textfile);

    printf("Letter Frequency:\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c:\t%d\n", i + 'a', counter[i]);
    }

    return 0;
}

void lowercase(char *letter)
{
    if (*letter >= 'A' && *letter <= 'Z')
    {
        *letter += 'a' - 'A'; // convert uppercase to lowercase
    }
}*/
int ReadingFile(char *letter) {
    printf("\n*** PART ONE ***\n");

    FILE *textfile;
    char file[100];

    printf("You have three options:\n => example1.txt\n => example2.txt\n => example3.txt\n");
    printf("Please enter the text file: ");
    scanf("%s", file);

    textfile = fopen(file, "r");

    if (textfile == NULL) {
        printf("Warning. The file is empty.");
        return 1;
    }

    int counter[26] = {0}; // initialize all counts to 0
    char x;
    while (!feof(textfile)) {
        x = fgetc(textfile);
        lowercase(&x); // convert to lowercase
        if (x >= 'a' && x <= 'z') {
            ++counter[x - 'a'];
        }
    }

    fclose(textfile);

    printf("Letter Frequency:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c:\t%d\n", i + 'a', counter[i]);
    }

    return 0;
}

void lowercase(char *letter) {
    if (*letter >= 'A' && *letter <= 'Z') {
        *letter += 'a' - 'A'; // convert uppercase to lowercase
    }
}


void testColorMixer()
{
    printf("\n *** PART TWO ***\n");
    
    Color (*mixer)(double colors[][3], Color x, Color y) = &mixing;
  
    char color1, color2;
    Color x, y;
    
    printf("Please enter the first color(r,g,b,y,o): ");
    scanf(" %c", &color1);
    
    switch(color1)
    {
        case 'r':
         x = RED;
        break;
        case 'g':
        x = GREEN;
        break;
        case 'b':
            x = BLUE;
        break;
        case 'y':
            x = YELLOW;
        break;
        case 'o':
            x = ORANGE;
        break;
    }
    
    printf("Please enter the second color(r,g,b,y,o): ");
    scanf(" %c", &color2);
    
    switch(color2)
    {
        case 'r':
            y = RED;
        break;
        case 'g':
            y = GREEN;
        break;
        case 'b':
            y = BLUE;
        break;
        case 'y':
            y = YELLOW;
        break;
        case 'o':
            y = ORANGE;
        break;
    }
    
    Color last = colorMixer(x, y, mixer);
    
    switch(last)
    {
        case 0:
            printf("The mix color is Red.\n");
            break;
        case 1:
            printf("The mix color is Green.\n");
            break;
        case 2:
            printf("The mix color is Blue.\n");
            break;
        case 3:
            printf("The mix color is Yellow.\n");
            break;
        case 4:
            printf("The mix color is Orange.\n");
            break;
    }
}

Color closest(double colors[][3], double mixed[3])
{
    double distance;
    double mindistance = 1000;
    int i;
    Color last;
    for(i = 0; i < 5; i++)
    {
        distance = sqrt(pow((colors[i][0] - mixed[0]), 2) + pow((colors[i][1] - mixed[1]), 2) + pow((colors[i][2] - mixed[2]), 2));
        
        if(distance < mindistance)
        {
            mindistance = distance;
            last = i;
        }
    }
    return last;
}

Color mixing(double colors[][3], Color x, Color y)
{
     double mixed[3];
     mixed[0] = (colors[x][0] + colors[y][0]) * 0.5;
     mixed[1] = (colors[x][1] + colors[y][1]) * 0.5;
     mixed[2] = (colors[x][2] + colors[y][2]) * 0.5;
     
     return closest(colors, mixed);
}

Color colorMixer(Color x, Color y, Color (*mixing)(double colors[][3], Color x, Color y))
{
    return mixing(colors, x, y);
}

void printingBoard()
{
    printf("-----------\n");
    for (int i = 0; i < 3; ++i)
    {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
        {
            printf("-----------\n");
        }
    }
    printf("-----------\n");
}

int checkingWinner(char sign)
{
    for (int i = 0; i < 3; i++) // checking horizontal rows
    {
        if (board[i][0] == sign && board[i][1] == sign && board[i][2] == sign)
        {
            return 1;
        }
        if (board[0][i] == sign && board[1][i] == sign && board[2][i] == sign)
        {
            return 1;
        }
    }
    if (board[0][0] == sign && board[1][1] == sign && board[2][2] == sign) // checking cross rows
    {
        return 1;
    }
    if (board[0][2] == sign && board[1][1] == sign && board[2][0] == sign) // checking cross rows
    {
        return 1;
    }
    return 0;
}

int theGame()
{
    
    int row, col, player = 1, moves = 0;
    char sign;
    printf("\n*** PART THREE ***\n");
    printf("Welcome to Tic Tac Toe Game!\n");
    printf("Player 1: X\nPlayer 2: O\n");
    printf("*******************************\n");
    while (1)
    {
        printf("Player %d, enter row and column for your move(row col): ", player);
        scanf("%d %d", &row, &col);
        
        while(row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Invalid move. Try again.\n");
            printf("Player %d, enter row and column for your move(row col): ", player);
            scanf("%d %d", &row, &col);
        }
        if (board[row][col] != '_') // if it isn't empty
        {
            printf("That space is already taken. Try again.\n");
            continue;
        }
        if(player == 1)
        {
            sign = 'X';
        }
        else // player == 2
        {
            sign = 'O';
        }
        
        board[row][col] = sign; // printing the sign
        moves++;
        printingBoard();
        if (checkingWinner(sign))
        {
            printf("Player %d wins!\n", player);
            break;
        }
        if (moves == 9)
        {
            printf("It's a draw!\n");
            break;
        }
        if(player == 1)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }
    }
    
    char a;
    printf("Do you want to play again?(Y or N): ");
    scanf(" %c", &a);
    
    while(a != 'y' && a != 'Y' && a != 'n' && a != 'N')
    {
        printf("Invalid decision. Please try again!\n");
        printf("Do you want to play again?(Y or N): ");
        scanf(" %c", &a);
    }
    
    if(a == 'y' || a == 'Y')
    {
        theGame();
    }
    else if(a == 'n' || a == 'N')
    {
        exit(0);
    }

    return 0;
    
} 

