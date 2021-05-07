#include <iostream>
#include "matrix.h"
#include "monom.h"
#include "polynom.h"

int main(int argc, char** argv)
{
    char cString[] = "-5 z^3*m";
    char cString1[] = "3 a*b^2*c^3";
    char polynom[] = "[-5 a*b^2*c^3]-[-3 a*b*c^4]";
    Monom kek(cString);
    Monom KKE(cString1);
//    KKE *= kek;
    Monom KEKE;
    Polynom lololo(polynom);
    Polynom kokoko(lololo);
    kokoko += kek;
//    kokoko += KKE;
//    std::cout << kokoko * kokoko << std::endl;
    return 0;
}
