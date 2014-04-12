#ifndef MOON_H
#define MOON_H

#include <vector>
#include <math.h>

#define pi 3.141592654

class Moon
{
public:
    Moon();
    static double jde(int month, double year, double phase);
    static void j2g(double jd, int *tab);
    static double a2i(double a);
    static double d2r(double d);
};

#endif // MOON_H
