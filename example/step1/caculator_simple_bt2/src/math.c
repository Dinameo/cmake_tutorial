#include <stdio.h>
#include <math.h>
int str2int(char *str)
{
    int a = 0;
    while(*str != '\0')
    {
        if(*str >= '0' && *str <= '9')
        {
            a *= 10;
            a += (*str - '0');
            str++;
        }
    }
    return a;
}
int sum(int a, int b)
{
    return (int)(a + b);
}
