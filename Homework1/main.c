#include <stdio.h>

 int GCD_Euclids_Algorithm(int m, int n);
void Addition(int n1,int n2);
int firstDigit(int x);
int secondDigit(int c);
int thirdDigit(int d);
void part4(int number4); 

int main()
{
    
    printf("**** GTU HOMEWORK 1 ****\n");
    printf("** PART ONE **\n");
    
   int gcdnumber1,gcdnumber2;
    
   printf("Please enter the first number: ");
    scanf("%d", &gcdnumber1);
    
    printf("Please enter the second number: ");
    scanf("%d", &gcdnumber2); 
    
    
    printf("The GCD of %d and %d is %d", gcdnumber1, gcdnumber2, GCD_Euclids_Algorithm(gcdnumber1, gcdnumber2));
    
    printf("\n");
    
    printf("** PART TWO **\n");
    
    int addnumber1, addnumber2;
    
    printf("Please enter the first addition number : ");
    scanf("%d", &addnumber1);
    
    printf("Please enter the second addition number: ");
    scanf("%d", &addnumber2);
    
    Addition(addnumber1, addnumber2);
    
    printf("\n** PART THREE **\n");
    
    int multinumber1, multinumber2;
    int newNumber = multinumber1*multinumber2;
    
    printf("Please enter the first number: ");
    scanf("%d", &multinumber1);
    
    printf("Please enter the second number: ");
    scanf("%d", &multinumber2);
    
    if(multinumber2>=1 && multinumber2<10)
    {
        printf(" %6d \n %6d \n * \n ------- \n %6d\n", multinumber1, multinumber2,
               multinumber1*multinumber2);
    }
    if(multinumber2>=10 && multinumber2<100)
    {
        
        printf(" %6d \n %6d \n * \n ------- \n %6d \n %5d \n + \n ------- \n %6d \n", multinumber1, multinumber2, firstDigit(multinumber2)*multinumber1, secondDigit(multinumber2)*multinumber1, multinumber1*multinumber2);
    }
    
    if(multinumber2>=100 && multinumber2<1000)
    {
        printf(" %6d \n %6d \n * \n ------- \n %6d \n %5d \n %4d \n + \n ------- \n %6d \n", multinumber1, multinumber2, firstDigit(multinumber2)*multinumber1, secondDigit(multinumber2)*multinumber1, thirdDigit(multinumber2)*multinumber1, multinumber1*multinumber2);
        
    }
    
    printf("\n** PART FOUR **\n");
    
    int integer;
    printf("Please enter an integer: ");
    scanf("%d", &integer);
    
    part4(integer);
}
