#include <stdio.h>
#include <math.h>

double Radius(double a, double b, double c) {
   
    double s = (a + b + c) / 2.0;
    
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    double r = area/s;
    return r;
}

void tri_sides(double A[2], double B[2], double C[2], double sides[3]) {
    sides[0] = hypot(B[0] - C[0], B[1] - C[1]);
    sides[1] = hypot(C[0] - A[0], C[1] - A[1]);
    sides[2] = hypot(A[0] - B[0], A[1] - B[1]);
}

int main() {
    
    double A[2] = {1, -1};
    double B[2] = {-4, 6};
    double C[2] = {-3, -5};

    double sides[3];

    tri_sides(A, B, C, sides);
    double a,b,c;
    a = sides[2];
    b = sides[0];
    c = sides[1];
    
    printf("Length of sides of a Triangle\n");
    printf("a: %.8f\nb: %.8f\nc: %.8f\n", a, b,c);

    double m,n,p;
    p = (a+c-b)/2;
    m = (a+b-c)/2;
    n = (b+c-a)/2;

    printf("Insides of a Triangle\n");
    printf("m: %.8f\nn: %.8f\np: %.8f\n", m, n, p);
    
    double Dx,Ex,Fx;
    Fx = (m*A[0]+p*B[0])/(m+p);
    Ex = (p*C[0]+n*A[0])/(p+n);
    Dx = (n*B[0]+m*C[0])/(n+m);
    
    double Dy,Ey,Fy;
    Fy = (m*A[1]+p*B[1])/(m+p);
    Ey = (p*C[1]+n*A[1])/(p+n);
    Dy = (n*B[1]+m*C[1])/(n+m);
    
    printf("Print the point D, E and F\n");
    printf("Fx: %.8f\n",Fx);
    printf("Fy: %.8f\n",Fy);
    printf("Ex: %.8f\n",Ex);
    printf("Ey: %.8f\n",Ey);
    printf("Dx: %.8f\n",Dx);
    printf("Dy: %.8f\n",Dy);
    
    
    double Ix = (a*C[0]+b*A[0]+c*B[0])/(a+b+c);
    double Iy = (a*C[1]+b*A[1]+c*B[1])/(a+b+c);
    //ABC, ACB, BAC, BCA, CAB, CBA
    
    printf("Print the circumcentre and circumradius of the triangle DEF\n");
    printf("Ix: %.8f\nIy: %.8f\n", Ix, Iy);
    
    if (a + b > c && a + c > b && b + c > a) {
        double r = Radius(a, b, c);
        printf("Radius: %.8lf\n", r);
    }
}

