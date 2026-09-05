#include <iostream>
#include "math.h"
using namespace std;

int plus(int a, int b) {return (int)(a+b);}
int minus(int a, int b) {return (int)(a-b);}

int mu(int a, int n) {
    if(n == 0) return 1;
    return a * mu(a, n -1);
}
