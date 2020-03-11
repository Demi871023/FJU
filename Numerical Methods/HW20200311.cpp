#include <cstdlib>
#include <cstdio>
#include <cmath>

/* f(x) = e^x + xcos2x + 3 */

/*
Algorithm：Bisection Method

1. Find a and b that f(a)f(b) < 0 and k = 10^-8
2. c = (a + b) / 2
3. if(f(a)f(c) < 0) b = c
   else a = c
4. if(|a - b| < 2k) goto step 2
5. output set (a + b) / 2
*/

#define k 1e-8
#define init_a -7
#define init_b -6

double a = init_a, b = init_b, c;

double absd(double x)
{
    if(x >= 0)   return x;
    else    return -x;
}

double FxAnswer(double x)
{
    return exp(x) + x * cos(2 * x) + 3;
}

double BisectionMethod()
{
    while(absd(a - b) >= (2 * k))
    {
        c = (a + b) / 2;
        // print temp ans
        printf("\n----------------------\n c is：%lf \n f(c) is：%lf \n----------------------\n", c, FxAnswer(c));
        if(FxAnswer(a) * FxAnswer(c) < 0)   b = c;
        else    a = c;
    }

    return (a + b) / 2;
}

int main()
{
    printf("==================\n\nOutput %lf\n\n==================\n", BisectionMethod());
}
