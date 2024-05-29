#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <cmath>
#define pi 3.14159265358979323846

#define epsil_zero 0.5

struct s2d {
    double x = 0.;
    double y = 0.;
};

struct segment {
    s2d point;
    s2d extr;
    int index;
    double longueur;
    double ang;
};
double normx(s2d );
s2d extr(segment );
s2d calculerVecteur(s2d& , s2d& );
double produit_scalaire(s2d& , s2d& );
double norm(s2d , s2d );
double ecart_angulaire(segment , segment );
bool onSegment(s2d , s2d , s2d );
double orientation(s2d , s2d , s2d );
bool doIntersection(s2d , s2d , s2d , s2d );
void superposition(segment , segment , int );
void cheskcolision(int , segment , int , segment );

#endif // SHAPE_H
