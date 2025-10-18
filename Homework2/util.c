#include <stdio.h>
#include <math.h>
#include "util.h"

int part1()
{
    int flag, year;

    printf("*** PART ONE  ***\n");
    
    printf("Please enter a year: ");
    scanf("%d", &year);
        
    if (year % 4 == 0) // Besides exceptional part, all the leap years are should be divisible by 4.
    {
        if (year % 100 == 0) // checks if it's divisible by 100.
        {
            if (year % 400 == 0) // if it's divisible by 100 then it should be divisible by 400 as well.
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        else
        {
            flag = 1;
        }
    }
    else
    {
        flag = 0;
    }
    
    
    if(flag == 1)
    {
        printf("%d is a leap year.", year);
    }
    else
    {
        printf("%d is not a leap year.", year);
    }
    
    return year;
}
int part2()
{
    
    char format, operation;
    double n1, n2;
    int flag;
    double result;
    float newResult;
    int m, n, j, i;
    
    printf("\n*** PART TWO ***\n");
    
    printf("Please enter the format (S or I): ");
    scanf("%s", &format);
    
    switch(format)
    {
        case 'S': flag = 1;
            break;
        case 'I': flag = 0;
            break;
    }
    
    if(flag == 0)
    {
        printf("Please enter the operation(+,-,/,*,%%,!,^): ");
        scanf("%s", &operation);
        
        switch(operation)
        {
            case '+':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 + n2;
                printf("%lf + %lf = %lf\n", n1, n2, result);
                break;
            case '-':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 - n2;
                printf("%lf - %lf = %lf\n", n1, n2, result);
                break;
            case '/':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 / n2;
                printf("%lf / %lf = %lf\n", n1, n2, result);
                break;
            case '*':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 * n2;
                printf("%lf * %lf = %lf\n", n1, n2, result);
                break;
            case '%':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = fmod(n1,n2);
                printf("%lf %% %lf = %lf\n", n1, n2, result);
                break;
            case '!':
                printf("Please enter the operand: ");
                scanf("%lf", &n1);
                result = tgamma(n1+1);
                printf("Factorial of %lf is %lf.\n", n1, result);
                break;
            case '^':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = pow(n1,n2);
                printf("%lf ^ %lf = %lf\n", n1, n2, result);
        }
    }
    
    if(flag == 1)
    {
        printf("Please enter m and n values: ");
        scanf("%d %d", &m, &n);
        
        while(n>m) // The part after the comma can't be greater than the total digits.
        {
            printf("n can't be bigger than m. Please try again.\n");
            printf("Please enter m and n values: ");
            scanf("%d %d", &m, &n);
        }
        
        
        printf("Please enter the operation(+,-,/,*,%%,!,^): ");
        scanf("%s", &operation);
        
        switch(operation)
        {
            case '+':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 + n2;
                
                float floor_num = floor(result);
                float ceil_num = ceil(result);
                

                if(floor_num == ceil_num) //integer
                {
                j = 0-n; // I multiply ten to the minus n to get the decimal place.
                newResult = result*pow(10,j);
                    
                for(i=0; i<m-n-1; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge%d", newResult, n);
                }
                else // if it's not integer.
                {
                
                newResult = result*pow(10,n);
                    
                for(i=0; i<m-n-2; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge-%d", newResult, n);
                }
                break;
            case '-':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 - n2;

                if(floor_num == ceil_num)
                {
                j = 0-n;
                newResult = result*pow(10,j);
                    
                for(i=0; i<m-n-1; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge%d", newResult, n);
                }
                else
                {
                
                newResult = result*pow(10,n);
                    
                for(i=0; i<m-n-2; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge-%d", newResult, n);
                }
                break;
            case '/':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 / n2;

                if(floor_num == ceil_num)
                {
                //integer
                j = 0-n;
                newResult = result*pow(10,j);
                    
                for(i=0; i<m-n-1; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge%d", newResult, n);
                }
                else
                {
                
                newResult = result*pow(10,n);
                    
                for(i=0; i<m-n-2; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge-%d", newResult, n);
                }
                break;
            case '*':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = n1 * n2;
                j = 0-n;
                newResult = result*pow(10,j);
                
                printf("%0*.*fe%d", (m+1), n, newResult, n);
                
                break;
            case '%':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = fmod(n1,n2);

                if(floor_num == ceil_num)
                {
                //integer
                j = 0-n;
                newResult = result*pow(10,j);
                    
                for(i=0; i<m-n-1; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge%d", newResult, n);
                }
                else
                {
                
                newResult = result*pow(10,n);
                    
                for(i=0; i<m-n-2; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge-%d", newResult, n);
                }
                
                break;
            case '!':
                printf("Please enter the operand: ");
                scanf("%lf", &n1);
                result = factorial(n1);
                
                j = 0-n;
                newResult = result*pow(10,j);
                    
                printf("%0*.*fe%d", (m+1), n, newResult, n);
                break;
            case '^':
                printf("Please enter the first operand: ");
                scanf("%lf", &n1);
                printf("Please enter the second operand: ");
                scanf("%lf", &n2);
                result = pow(n1,n2);
                
                if(floor_num == ceil_num)
                {
                j = 0-n;
                newResult = result*pow(10,j);
                    
                for(i=0; i<m-n-1; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge%d", newResult, n);
                }
                else
                {
                
                newResult = result*pow(10,n);
                    
                for(i=0; i<m-n-2; ++i)
                {
                    printf("0");
                }
                
                    printf("%.5ge-%d", newResult, n);
                }
               
        }
    }
    return newResult;
}
int part3()
{
    printf("\n*** PART THREE ***\n");
    int ex1,ex2,ex3,as1,as2;
    
    printf("Please enter your 3 exam results: ");
    scanf("%d %d %d", &ex1, &ex2, &ex3);
    printf("Please enter your 2 assignment results: ");
    scanf("%d %d", &as1, &as2);
    
    while(ex1 > 100 || ex2 > 100 || ex3 > 100 || as1 > 100 || as2 > 100)
    {
        printf("Invalid values. Please try again.\n");
        printf("Please enter your 3 exam results: ");
        scanf("%d %d %d", &ex1, &ex2, &ex3);
        printf("Please enter your 2 assignment results: ");
        scanf("%d %d", &as1, &as2);
    }
    
    int av1, av2, finalgrade;
    
    av1 = (ex1 + ex2 + ex3)/3;
    av2 = (as1 + as2)/2;
    
    finalgrade = av1*(0.6) + av2*(0.4);
    
    
    if(finalgrade>=60)
    {
        printf("Your final grade is: %d ==> You Passed!\n", finalgrade);
    }
    else
    {
        printf("Your final grade is: %d ==> You Failed.\n", finalgrade);
    }
    
    return finalgrade;
}

int factorial(double n)
{
    int i;
    int factorial = 1;

    for (i = 1; i <= n; i++)
    {
        factorial *= i;
    }
    
    return factorial;
}
