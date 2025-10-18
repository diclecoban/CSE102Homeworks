#include <stdio.h>
#include "util.h"

int GCD_Euclids_Algorithm(int m, int n)
{
    
    int remainder;
    
    /* It keeps going until remainder will become zero. */
    while (n != 0)
    {
        remainder = m % n;
        m = n;
        n = remainder;
    }
    /* In the end of the While code , m becomes the gcd. */
    
    return m;
}


void Addition(int n1,int n2)
{
    int newNumber;
    
    newNumber = n1 + n2;
    
    printf("   %4d \n   %4d \n + \n ------- \n   %4d \n", n1, n2, newNumber);
}

int firstDigit(int x)
{
    
    // The function is to find the units digit.
    
   int lastDigit;

   lastDigit = x % 10;

   return lastDigit;

}


int secondDigit(int c)
{
    
    // The function is to find the tens digit.
    
    int secondDigit;
    
    secondDigit = c / 10;
    
    if(secondDigit>=10) // in case if the multinumber2 is more or equal than 100 and less than 1000.
    {
        secondDigit = secondDigit % 10;
    }
    
    
    return secondDigit;
}

int thirdDigit(int d)
{
    
// The function is to find the hundreds digit.
    
    int thirdDigit;
    
    thirdDigit = d / 100;
    
    return thirdDigit;
}

void part4(int number4)
{
    if(number4>5 && number4<=10)
    {
        printf("The integer you entered is greater than 5.\n");
    }
    
    if(number4<=5 && number4>=1)
    {
        printf("The integer you entered is less than or equal to 5.\n");
    }
    
    if(number4<1 || number4>10)
    {
        printf("Invalid input.\n");
    }
}
