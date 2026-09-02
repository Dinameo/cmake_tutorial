#include <stdio.h>
#include "math.h"

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("usage: calculator <number1> <number2>\n");
        return -1;
    }
 
    int num1 = str2int(argv[1]);
    int num2 = str2int(argv[2]);
    printf("%d\n", sum(num1, num2));

    return 0;

}
