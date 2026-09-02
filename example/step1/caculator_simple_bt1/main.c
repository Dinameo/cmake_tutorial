#include <stdio.h>

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

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("usage: calculator <number1> <number2>\n");
        return -1;
    }
 
    int num1 = str2int(argv[1]);
    int num2 = str2int(argv[2]);
    printf("%d\n", num1 + num2);

    return 0;

}
