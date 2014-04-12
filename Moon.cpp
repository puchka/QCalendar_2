#include "Moon.h"

Moon::Moon()
{
}

double Moon::jde(int month, double year, double phase)
{
    switch (month)
    {
        case 1:
            year+=0.08;
            break;
        case 2:
            year+=0.17;
            break;
        case 3:
            year+=0.25;
            break;
        case 4:
            year+=0.33;
            break;
        case 5:
            year+=0.41;
            break;
        case 6:
            year+=0.5;
            break;
        case 7:
            year+=0.58;
            break;
        case 8:
            year+=0.67;
            break;
        case 9:
            year+=0.75;
            break;
        case 10:
            year+=0.83;
            break;
        case 11:
            year+=0.91;
            break;
        case 12:
            year+=1;
            break;
    }
    int k1 = (year - 2000) * 12.3685;
    double k=k1+phase;
    double t = k/1236.85;
    double e = 1 - 0.002516 * t - 0.0000074 * pow(t, 2);
    // Sun's mean anomaly at time JDE :
    double m = 2.5534 + 29.10535669 * k
                      - 0.0000218 * pow(t, 2)
                      - 0.00000011 * pow(t, 3);
    // Moon's mean anomaly :
    double mp = 201.5643 + 385.81693528 * k
                  + 0.0107438 * pow(t, 2)
                  + 0.00001239 * pow(t, 3)
                  - 0.000000058 * pow(t, 4);
    // Moon's argument of latitude :
    double f = 160.7108 + 390.67050274 * k
                        - 0.0016341 * pow(t, 2)
                        - 0.00000227 * pow(t, 3)
                        + 0.000000011 * pow(t, 4);
    double o = 124.7746 - 1.56375580 * k
                        + 0.0020691 * pow(t, 2)
                        + 0.00000215 * pow(t, 3);
    // Planetary arguments :
    double a1 = 299.77 + 0.107408 * k - 0.009173 * pow(t, 2);
    double a2 = 251.88 + 0.016321 * k;
    double a3 = 251.83 + 26.651886 * k;
    double a4 = 349.42 + 36.412478 * k;
    double a5 = 84.66 + 28.206239 * k;
    double a6 = 141.74 + 53.303771 * k;
    double a7 = 207.14 + 2.453732 * k;
    double a8 = 154.84 + 7.306860 * k;
    double a9 = 34.52 + 27.261239 * k;
    double a10 = 207.19 + 0.121824 * k;
    double a11 = 291.34 + 1.844379 * k;
    double a12 = 161.72 + 24.198154 * k;
    double a13 = 239.56 + 25.513099 * k;
    double a14 = 331.55 + 3.592518 * k;
    // Convert angles to radian
    m = d2r(m);
    mp = d2r(mp);
    f = d2r(f);
    o = d2r(o);
    a1 = d2r(a1);
    a2 = d2r(a2);
    a3 = d2r(a3);
    a4 = d2r(a4);
    a5 = d2r(a5);
    a6 = d2r(a6);
    a7 = d2r(a7);
    a8 = d2r(a8);
    a9 = d2r(a9);
    a10 = d2r(a10);
    a11 = d2r(a11);
    a12 = d2r(a12);
    a13 = d2r(a13);
    a14 = d2r(a14);
    // Corrections
    // New Moon
    double s1 = -0.40720 *     sin(mp)
                +0.17241 * e * sin(m)
                +0.01608 *     sin(2*mp)
                +0.01039     * sin(2*f)
                +0.00739 * e * sin(mp-m)
                -0.00514 * e * sin(mp+m)
                +0.00208 * pow(e, 2) * sin(2*m)
                -0.00111     * sin(mp-2*f)
                -0.00057     * sin(mp+2*f)
                +0.00056 * e * sin(2*mp+m)
                -0.00042     * sin(3*mp)
                +0.00042 * e * sin(m+2*f)
                +0.00038 * e * sin(m-2*f)
                -0.00024 * e * sin(2*mp-m)
                -0.00017     * sin(o)
                -0.00007     * sin(mp+2*m)
                +0.00004     * sin(2*mp-2*f)
                +0.00004     * sin(3*m)
                +0.00003     * sin(mp+m-2*f)
                +0.00003     * sin(2*mp+2*f)
                -0.00003     * sin(mp+m+2*f)
                +0.00003     * sin(mp-m+2*f)
                -0.00002     * sin(mp-m-2*f)
                -0.00002     * sin(3*mp+m)
                +0.00002     * sin(4*mp);
    // Full Moon
    double s3 = -0.40614     * sin(mp)
                +0.17302 * e * sin(m)
                +0.01614     * sin(2*mp)
                +0.01043     * sin(2*f)
                +0.00734 * e * sin(mp-m)
                -0.00515 * e * sin(mp+m)
                +0.00208 * pow(e, 2) * sin(2*m)
                -0.00111     * sin(mp-2*f)
                -0.00057     * sin(mp+2*f)
                +0.00056 * e * sin(2*mp+m)
                -0.00042     * sin(3*mp)
                +0.00042 * e * sin(m+2*f)
                +0.00038 * e * sin(m-2*f)
                -0.00024 * e * sin(2*mp-m)
                -0.00017     * sin(o)
                -0.00007     * sin(mp+2*m)
                +0.00004     * sin(2*mp-2*f)
                +0.00004     * sin(3*m)
                +0.00003     * sin(mp+m-2*f)
                +0.00003     * sin(2*mp+2*f)
                -0.00003     * sin(mp+m+2*f)
                +0.00003     * sin(mp-m+2*f)
                -0.00002     * sin(mp-m-2*f)
                -0.00002     * sin(3*mp+m)
                +0.00002     * sin(4*mp);
    // First and Last Quarters
    double s4 = -0.62801     * sin(mp)
                +0.17172 * e * sin(m)
                -0.01183 * e * sin(mp+m)
                +0.00862     * sin(2*mp)
                +0.00804     * sin(2*f)
                +0.00454 * e * sin(mp-m)
                +0.00204 * pow(e, 2) * sin(2*m)
                -0.00180     * sin(mp-2*f)
                -0.00070     * sin(mp+2*f)
                -0.00040     * sin(3*mp)
                -0.00034     * sin(2*mp-m)
                +0.00032     * sin(m+2*f)
                +0.00032     * sin(m-2*f)
                -0.00028 * pow(e, 2) * sin(mp+2*m)
                +0.00027 * e * sin(2*mp+m)
                -0.00017     * sin(o)
                -0.00005     * sin(mp-m-2*f)
                +0.00004     * sin(mp+2*f)
                -0.00004     * sin(mp+m+2*f)
                +0.00004     * sin(mp-2*m)
                +0.00003     * sin(mp+m-2*f)
                +0.00003     * sin(2*m)
                +0.00002     * sin(2*mp-2*f)
                +0.00002     * sin(mp-m+2*f)
                -0.00002     * sin(3*mp+m);

    double w = 0.00306 - 0.00038 * e * cos(m) + 0.00026 * cos(mp)
               - 0.00002 * cos(mp-m) + 0.00002 * cos (mp+m)
               + 0.00002 * cos(2*f);
    // Additional corrections for all phases
    double s2 = +0.000325 * sin(a1) + 0.000056 * sin(a8)
                +0.000165 * sin(a2) + 0.000047 * sin(a9)
                +0.000164 * sin(a3) + 0.000042 * sin(a10)
                +0.000126 * sin(a4) + 0.000040 * sin(a11)
                +0.000110 * sin(a5) + 0.000037 * sin(a12)
                +0.000062 * sin(a6) + 0.000035 * sin(a13)
                +0.000060 * sin(a7) + 0.000023 * sin(a14);
    // The resulting time expressed in Julian Ephemeris Days
    double jde = 2451550.09765 + 29.530588853 * k
                               + 0.0001337 * pow(t, 2)
                               - 0.000000150 * pow(t, 3)
                               + 0.00000000073 * pow(t, 4);
    jde += s2;
    if (phase==0.0)
        jde+=s1;
    else if (phase==0.25)
        jde=jde+s4+w;
    else if (phase==0.5)
        jde+=s3;
    else if (phase==0.75)
        jde=jde+s4-w;
    return jde;
}

double Moon::a2i(double a)
{
    while (a<0)
        a+=360;
    if (a>360)
        return a-(int)a/360;
    return a;
}

double Moon::d2r(double d)
{
    d = a2i(d);
    return (d/180)*pi;
}

void Moon::j2g(double jd, int *tab)
{
    int z = (int)jd;
    int alpha = (int)((z-1867216.25)/36524.25);
    int s = z+1+alpha-(int)(alpha/4);
    int b = s+1524;
    int c = (int)((b-122.1)/365.25);
    int d = (int)(365.25*c);
    int e = (int)((b-d)/30.6001);
    tab[0] = b-d-(int)(30.6001*e);
    if (e<14)
        tab[1] = e-1;
    else
        tab[1] = e-13;
    if (tab[1]>2)
        tab[2] = c-4716;
    else
        tab[2] = c-4715;
}
