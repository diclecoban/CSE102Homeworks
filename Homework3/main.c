#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

int i, j;
void Menu(int op);
void DrawtheRoom(int room, int Cx, int Cy, int Dx, int Dy);
void Moves(int room, int Cx, int Cy, int Dx, int Dy);
void Help(int op);
int Run(int Cx, int Cy, int Dx, int Dy);
void Game(int Cx, int Cy, int Dx, int Dy, int room);

int main()
{
    // starts with the Menu function
    
    int op;
    Menu(op);
}

void DrawtheRoom(int room, int Cx, int Cy, int Dx, int Dy)
{
    printf("\nPlease enter your room size: ");
    scanf("%d", &room);
    
    while(room<5 || room>10)
    {
        printf("\nInvalid size. Please try again.\n");
        printf("Please enter your room size: ");
        scanf("%d", &room);
    }
    
    srand(time(NULL));
    
     Cx = rand() % room;
     Cy = rand() % room;
     Dx = rand() % room;
     Dy = rand() % room;
       
    if((Cx == Dx) && (Cy == Dy))
    {
        // For not the same C and D coordinates before the game starts.
        
        Cx = rand() % room;
        Cy = rand() % room;
        Dx = rand() % room;
        Dy = rand() % room;
    }
    
    
    for(i=0; i<=room; ++i)
            {
                printf("--");
            }
                printf("\n");
    
              for(i=0; i<=room-1; ++i)
            {
                for(j=0; j<room; ++j)
                {
                    if (i == Cx && j == Cy)
                    {
                        printf("|C");
                    }
                    else if(i == Dx && j == Dy)
                    {
                        printf("|D");
                    }
                    else
                    {
                        printf("| ");
                    }
                }
                
                printf("|\n");
            }
            for(i=0; i<=room; ++i)
            {
                printf("--");
            }
    
    // It calls the Game function to check if the game can run
    
    Game(Cx,Cy,Dx,Dy,room);

}

void Help(int op)
{
    printf("\n** HELP SECTION **\n");
    
    printf("The Rules:\n");
    printf(" ▸ a is for left.\n ▸ d is for right.\n ▸ s is for down.\n ▸ w is for up.\n ");
    printf("The game will be continue until you reach the door.\n If you move through a wall the game will end.\n ");
    
    printf("\nEnter 0 to go back to main menu: ");
    scanf("%d", &op);
    
    while( op != 0 )
    {
        printf("\nInvalid number. Please try again.\n");
        
        printf("Enter 0 to go back to main menu: ");
        scanf("%d", &op);
    }
    
    Menu(op);
}

void Menu(int op)
{
    int Cx, Cy, Dx, Dy, room;

    
    printf("\n** MENU **\n");
    printf("Welcome to the 2D Puzzle Game!\n");
    printf("1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");
    
    printf("Please select an option: ");
    scanf("%d", &op);
    
    switch (op)
    {
        case 1:
            DrawtheRoom(room, Cx, Cy, Dx, Dy);
            break;
        case 2:
            Help(op);
            break;
        case 3:
            exit(0);
            break;
            
    }
}

void Moves(int room, int Cx, int Cy, int Dx, int Dy)
{
    int op;
    char input;
    int move=0,exit=0;
    
    // Every move the coordinates and the amount of move will change. Move will always increase but the coordinates according to the move increase or decrease

    while(exit==0)
    {
        printf("\nPlease enter a move (a=left, d=right, w=up, s=down): ");
        scanf(" %c", &input);
        
        switch (input)
        {
            case LEFT:
                // move left
                if (Cy == 0)
                {
                    printf("WARNING: You can't move through a wall.\n");
                    
                    break;
                    
                    printf("Please enter a move (a=left, d=right, w=up, s=down): ");
                    scanf(" %c", &input);
                }
                
                else
                {
                    --Cy;
                   ++move;
                    
                    for(i=0; i<=room; ++i)
                    {
                        printf("--");
                    }
                    printf("\n");
                    
                    for(i=0; i< room; ++i)
                    {
                        for(j=0; j< room; ++j)
                        {
                            if (i == Cx && j == Cy)
                            {
                                printf("|C");
                            }
                            else if(i == Dx && j == Dy)
                            {
                                printf("|D");
                            }
                            else
                            {
                                printf("| ");
                            }
                        }
                        
                        printf("|\n");
                    }
                    for(i=0; i<=room; ++i)
                    {
                        printf("--");
                    }
                }
                break;
                
            case RIGHT:
                // move right
                if (Cy == (room-1))
                {
                    printf("WARNING: You can't move through a wall.\n");
                    
                    break;
                    
                    printf("Please enter a move (a=left, d=right, w=up, s=down): ");
                    scanf(" %c", &input);
                }
                
                else
                {
                    ++Cy;
                   ++move;
                    
                    for(i=0; i<= room; ++i)
                    {
                        printf("--");
                    }
                    printf("\n");
                    
                    for(i=0; i<room; ++i)
                    {
                        for(j=0; j<room; ++j)
                        {
                            if (i == Cx && j == Cy)
                            {
                                printf("|C");
                            }
                            else if(i == Dx && j == Dy)
                            {
                                printf("|D");
                            }
                            else
                            {
                                printf("| ");
                            }
                        }
                        
                        printf("|\n");
                    }
                    for(i=0; i<= room; ++i)
                    {
                        printf("--");
                    }
                }
                break;
            case UP:
                // move up
                if (Cx == 0)
                {
                    printf("WARNING: You can't move through a wall.\n");
                    
                    break;
                    
                    
                    printf("Please enter a move (a=left, d=right, w=up, s=down): ");
                    scanf(" %c", &input);
                }
                
                
                else
                {
                    --Cx;
                   ++move;
                    
                    for(i=0; i<=room; ++i)
                    {
                        printf("--");
                    }
                    printf("\n");
                    
                    for(i=0; i<room; ++i)
                    {
                        for(j=0; j<room; ++j)
                        {
                            if (i == Cx && j == Cy)
                            {
                                printf("|C");
                            }
                            else if(i == Dx && j == Dy)
                            {
                                printf("|D");
                            }
                            else
                            {
                                printf("| ");
                            }
                        }
                        
                        printf("|\n");
                    }
                    for(i=0; i<=room; ++i)
                    {
                        printf("--");
                    }
                }
                break;
                
            case DOWN:
                // move down
                if (Cx == (room-1))
                {
                    printf("WARNING: You can't move through a wall.\n");
                    
                    break;
                    
                    printf("Please enter a move (a=left, d=right, w=up, s=down):: ");
                    scanf(" %c", &input);
                }
                
                
                else
                {
                    ++Cx;
                   ++move;
                    
                    for(i=0; i<= room; ++i)
                    {
                        printf("--");
                    }
                    printf("\n");
                    
                    for(i=0; i< room; ++i)
                    {
                        for(j=0; j<room; ++j)
                        {
                            if (i == Cx && j == Cy)
                            {
                                printf("|C");
                            }
                            else if(i == Dx && j == Dy)
                            {
                                printf("|D");
                            }
                            else
                            {
                                printf("| ");
                            }
                        }
                        
                        printf("|\n");
                    }
                    for(i=0; i<=room; ++i)
                    {
                        printf("--");
                    }
                }
                break;
                
            default:
                printf("Invalid move!\n");
                break;
    }
        
        // It gets out of the while loop if coordinates are the same
        
        if(Run(Cx, Cy, Dx, Dy) == 1)
        {
            break;
        }
        
    }
    
    printf("\nCongrats! You finished the game with %d moves.", move);
    printf("\nPlease press 1 for menu: ");
    scanf("%d", &op);
    
    while(op != 1)
    {
        printf("Invalid number. Please try again.\n");
        printf("\nPlease press 1 for menu: ");
        scanf("%d", &op);
    }
    
    // When the game ends the function goes to Menu function
    
    Menu(op);
    
    }
int Run(int Cx, int Cy, int Dx, int Dy)
{
    
    // If coordinates are the same it returns 1, else it returns 0
    
    if((Cx == Dx) && (Cy == Dy))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Game(int Cx, int Cy, int Dx, int Dy, int room)
{
    // while coordinates don't same it goes to Moves function
    
    while(Run(Cx, Cy, Dx, Dy) == 0)
    {
        Moves(room, Cx, Cy, Dx, Dy);
    }
}

