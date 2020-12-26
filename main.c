#include <stdio.h>
#include <string.h>
#include <stdlib.h> // для atoi
#include <math.h>

#define and &&
#define or ||


int main(int argc, char **argv)
{
    if (strcmp(&argv[1][1], "q") == 0 and argc == 5)
    {
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        int c = atoi(argv[4]); // a, b, c - coefficient's
        if (!a)
        {
            puts("First coefficient is 0");
            return 0;
        }
        double D = b * b - 4 * a * c;
        printf("a = %d, b = %d, c = %d\n", a, b, c);
        printf("D = %1.0f\n", D);
        if (D > 0) // 2 solution
        {
            printf("x1 = %f x2 = %f\n", ((-b + sqrt(D)) / (2 * a)), ((-b - sqrt(D)) / (2 * a)));
        }
        else if (D == 0) // 1 solution // const double eps = 1e-10; if (fabs(D) < eps) { ... /* equals to zero */ }
        {
            printf("x1 = x2 = %d\n", -b / (2 * a));
        }
        else
        {
            b > 0 ? printf("x1 = %d + %f * i / %d\nx1 = %d - %f * i / %d\n", -b, sqrt(abs(D)), (2 * a), -b,
                   sqrt(abs(D)), (2 * a)) :
                   printf("x1 = %f * i / %d\nx1 = - %f * i / %d\n", sqrt(abs(D)), (2 * a),sqrt(abs(D)), (2 * a));
        }
        return 0;
    }
    else if (strcmp(&argv[1][1], "m") == 0 and argc == 4)
    {
        int first = atoi(argv[2]);
        int second = atoi(argv[3]);
        if (!first or !second)
        {
            puts("Number must be non-zero");
            return 0;
        }
        else
        {
            first % second ? puts("Not aliquot") : puts("Aliquot");
        }
    }
    else if (strcmp(&argv[1][1], "t") == 0 and argc == 5)
    {
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        int c = atoi(argv[4]); // a, b, c - side
        return ((a + b > c) and (a + c > b) and (b + c > a)) ? puts("Triangle exists") :
        puts("Triangle doesn't exists");
    }
    else
    {
        puts("Wrong number of parameters");
    }
}
