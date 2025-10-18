#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define STUDENT_NO 220104004088
#define VAT 0.18

int list();
int choice(FILE *fis, char p);
void Date(FILE *fis);
int Receipt(FILE *fis, char p);
int RockPaperScissors();

int main()
{
    FILE *fis;
    char p;
    
    list();
    choice(fis,p);
    RockPaperScissors();
    
    return 0;
}

int list()
{
    // opens the menu.txt file to read
    FILE *menu;
    menu = fopen("menu.txt", "r");

    if (menu == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Menu:\n");
    // Skip the first line (Product and Price part)
    
    int c = fgetc(menu);
    while (c != EOF && c != '\n') {
        c = fgetc(menu);
    }

    // Print the remaining lines with numbers to make it seem like a list of menu
    int line_num = 1;
    printf("%d. ", line_num);
    while (!feof(menu)) {
        c = fgetc(menu);
        if (c == EOF) {
            break;
        }
        if(c<45 || c>57) // doesn't read the prices
        {
            putchar(c);
        }
        if (c == '\n')
        {
            line_num++;
            printf("%d. ", line_num);
        }
    }

    fclose(menu);
    return 0;
}

int choice(FILE *fis, char p)
{

    fis = fopen("fis.txt", "w");
    
    // print my school number and the current time on the receipt
    
    fprintf(fis, "\n");
    fprintf(fis, "%ld  ", STUDENT_NO);
    Date(fis);
    
    fprintf(fis, "\n-----------------------------------\n");
    
    fprintf(fis, "PRODUCT               PRICE(TL)");
    
    fprintf(fis, "\n-----------------------------------\n");
    fprintf(fis, "\n");
    
    int food,serving,flag=0, ch, count=0;
    double totalprice=0, price;
    char YorN;
    double student_discount = 0.125, money_discount = 0.1;
    
    while(flag == 0) //while flag equals to zero it keeps asking which food do they want to eat
    {
        printf("\nPlease enter your choice(1-10): ");
        scanf("%d", &food);
        
        while(food<0 || food>10)
        {
            printf("Warning! You can't enter that value. Please try again.\n");
            printf("Please enter your choice(1-10): ");
            scanf("%d", &food);
        }
        
        switch(food)
        {
            case 1:
                
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                   price = (75.99)*serving;
                fprintf(fis, "%d*Kebap\t\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price; // keeps noting the current price
                break;
            case 2:
                
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (21.50)*serving;
                
                fprintf(fis, "%d*Lahmacun\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 3:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (40.00)*serving;
                
                fprintf(fis, "%d*Pide\t\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 4:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (55.60)*serving;
                
                fprintf(fis, "%d*Döner\t\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 5:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (15.00)*serving;
                
                fprintf(fis, "%d*Kola\t\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 6:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (5.00)*serving;
                
                fprintf(fis, "%d*Su \t\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 7:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (60.00)*serving;
                
                fprintf(fis, "%d*Künefe\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 8:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (32.50)*serving;
                
                fprintf(fis, "%d*Sütlaç\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 9:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (45.00)*serving;
                
                fprintf(fis, "%d*Karnıyarık\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 10:
                printf("How much servings do you want?: ");
                scanf("%d", &serving);
                
                while(serving<0)
                {
                    printf("Warning! You can't enter that value. Please try again.\n");
                    printf("How much servings do you want?: ");
                    scanf("%d", &serving);
                }
                
                price = (70.00)*serving;
                
                fprintf(fis, "%d*Baklava\t\t%6.2lf\n", serving, price);
                totalprice = totalprice + price;
                break;
            case 0: // it helps to leave the while(flag ==0) loop
                flag=1;
                break;
        }
        printf("\n");
    }
    
    printf("Are you a student? ");
    scanf(" %c", &YorN);
    
    //checks if it isn't one of these character it keeps printing warning
    
    while(YorN != 'Y' && YorN != 'N' && YorN != 'y' && YorN != 'n')
    {
        printf("Invalid answer. Please try again!\n");
        printf("Are you a student? ");
        scanf(" %c", &YorN);
    }
    
    if(flag == 1)
    {
        
        fprintf(fis, "Total:\t\t\t%6.2lf\n", totalprice);
        
        
        if(totalprice>= 150) //discounts are applying on the totalprice individually
        {
            fprintf(fis, "Additional Discount:\t-%5.2lf\n", (totalprice * money_discount));
        }
        else
        {
            money_discount = 0;
        }
        if(YorN == 'Y' || YorN == 'y') //discounts are applying on the totalprice individually
        {
            fprintf(fis, "Student Discount:\t-%5.2lf\n", (totalprice * student_discount) );
        }
        else
        {
            student_discount = 0;
        }
        
        totalprice = totalprice - (totalprice * (money_discount + student_discount)); // Thats the payable price
        
        fprintf(fis, "\n-----------------------------------\n");
        fprintf(fis, "Price:\t\t\t%6.2lf\n", totalprice);
        
        totalprice = totalprice + (totalprice * VAT);
        
        // Applying the VAT to the payable price
        
        fprintf(fis, "Price + VAT:\t\t%6.2lf\n", totalprice);
    }
    
    fprintf(fis,"\n");
    
    fclose(fis); // finishing writing the fis.txt
    
    Receipt(fis,p); // calling the printing fis.txt file function
    
    return 0;
}

void Date(FILE *fis)
{
    // prints the current time and date on the receipt
    
    time_t cur_time;
    struct tm *local_time;


    cur_time = time(NULL);
    local_time = localtime(&cur_time);

   fprintf(fis, "%s", asctime(local_time));
    

}

int Receipt(FILE *fis, char p)
{
    // prints the final version of the receipt on terminal
    
    fis = fopen("fis.txt", "r");

    if (fis == NULL)
    {
        printf("Warning. The file is empty.\n");
    }
    else
    {
        int p;
        while (!feof(fis))
        {
            p = fgetc(fis);
            if (p != EOF)
            {
                putchar(p);
            }
        }
        fclose(fis);
    }
    
    return 0;
}

int RockPaperScissors()
{
    srand(time(NULL));
    int player, computer;
    char choice;
    
    printf("\nWelcome to Rock-Paper-Scissors Game!\n");
    
    printf(" 1- Rock\n 2- Paper\n 3- Scissors\n");
    printf("Please make a choice(1-3): ");
    scanf("%d", &player);
    
    while(player > 3 || player < 1)
    {
        printf("Invalid choice. Please try again!\n");
        printf("Please make a choice(1-3): ");
        scanf("%d", &player);
    }
    
    switch(player)
    {
        case 1:
            computer = rand() % 3 + 1; //chooses random number of 1,2,3
            
            if(computer ==1)
            {
                printf("You chose Rock. I chose Rock. It's a tie!\n");
            }
            else if(computer == 2)
            {
                printf("You chose Rock. I chose Paper. I win!\n");
            }
            else
            {
                printf("You chose Rock. I chose Scissors. You win!\n");
            }
            
            printf("Do you want to play again?: ");
            scanf(" %c", &choice);
            
            // Keeps printing the warning message until the character would be one of them
            
            while(choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n')
            {
                printf("Invalid answer. Please try again!\n");
                printf("Do you want to play again?: ");
                scanf(" %c", &choice);
                
            }
            
            if(choice == 'Y' || choice == 'y')
            {
                RockPaperScissors();
            }
            else
            {
                exit(0); //ends the execution
            }
            
            break;
        case 2:
            computer = rand() % 3 + 1;
            
            if(computer ==1)
            {
                printf("You chose Paper. I chose Rock. You win!\n");
            }
            else if(computer == 2)
            {
                printf("You chose Paper. I chose Paper. It's a tie!\n");
            }
            else
            {
                printf("You chose Paper. I chose Scissors. I win!\n");
            }
            
            printf("Do you want to play again?: ");
            scanf(" %c", &choice);
            
            while(choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n')
            {
                printf("Invalid answer. Please try again!\n");
                printf("Do you want to play again?: ");
                scanf(" %c", &choice);
                
            }
            
            if(choice == 'Y' || choice == 'y')
            {
                RockPaperScissors();
            }
            else
            {
                exit(0);
            }
            break;
        case 3:
            computer = rand() % 3 + 1;
            
            if(computer ==1)
            {
                printf("You chose Scissors. I chose Rock. I win!\n");
            }
            else if(computer == 2)
            {
                printf("You chose Scissors. I chose Paper. You win!\n");
            }
            else
            {
                printf("You chose Scissors. I chose Scissors. It's a tie!\n");
            }
            
            printf("Do you want to play again?: ");
            scanf(" %c", &choice);
            
            while(choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n')
            {
                printf("Invalid answer. Please try again!\n");
                printf("Do you want to play again?: ");
                scanf(" %c", &choice);
                
            }
            
            if(choice == 'Y' || choice == 'y')
            {
                RockPaperScissors();
            }
            else
            {
                exit(0);
            }
            
            break;
    }
    
    return 0;
}

