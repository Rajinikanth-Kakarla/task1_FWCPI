#ifndef LIBR_H
#define LIBR_H

#include <cmath>

double Radius(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));
    double r = area / s;
    return r;
}

void tri_sides(double A[2], double B[2], double C[2], double sides[3]) {
    sides[0] = std::hypot(B[0] - C[0], B[1] - C[1]);
    sides[1] = std::hypot(C[0] - A[0], C[1] - A[1]);
    sides[2] = std::hypot(A[0] - B[0], A[1] - B[1]);
}

#endif // LIBR_H

