#include "shape.h"
#include "message.cc"
#include <iostream>
#include <cmath>

using namespace std;

s2d extr(segment A) {
    s2d a;
    a.x = A.point.x + A.longueur * cos(A.ang);
    a.y = A.point.y + A.longueur * sin(A.ang);
    return a;
}

s2d calculerVecteur(s2d& p1, s2d& p2) {
    s2d vecteur;
    vecteur.x = p2.x - p1.x;
    vecteur.y = p2.y - p1.y;
    return vecteur;
}

double produit_scalaire(s2d& u, s2d& v) {
    return (u.x * v.x) + (u.y * v.y);
}

double norm(s2d p1, s2d p2) {
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

double normx(s2d v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double ecart_angulaire(segment seg1, segment seg2) {
    s2d extr1 = extr(seg1);
    s2d extr2 = extr(seg2);

    s2d vect1 = calculerVecteur(seg1.point, extr1);
    s2d vect2 = calculerVecteur(seg2.point, extr2);

    double dot = produit_scalaire(vect1, vect2);
    double norm1 = normx(vect1);
    double norm2 = normx(vect2);

    double cos_angle = dot / (norm1 * norm2);
    if (cos_angle > 1.0) cos_angle = 1.0;
    if (cos_angle < -1.0) cos_angle = -1.0;

    double angle = acos(cos_angle);

    double cross_product = vect1.x * vect2.y - vect1.y * vect2.x;

    if (cross_product < 0) {
        angle = -angle;
    }

    if (angle > pi) {
        angle -= 2 * pi;
    } else if (angle < -pi) {
        angle += 2 * pi;
    }

    return angle;
}

bool onSegment(s2d p, s2d q, s2d r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        s2d u = calculerVecteur(p, r);
        s2d v = calculerVecteur(p, q);
        double p_s = produit_scalaire(u, v);
        double x = p_s / norm(p, r);
        if (x >= -epsil_zero && x <= (norm(p, r) + epsil_zero))
            return true;
        else
            return false;
    }
    return false;
}

double orientation(s2d p, s2d q, s2d r) {
    if (onSegment(p, q, r) == true) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (fabs(val) < epsil_zero) return 0;
        return val;
    }
  //  return 1;
}

bool doIntersection(s2d p1, s2d q1, s2d p2, s2d q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

void superposition(segment s1, segment s2, int id) {
    double angle = ecart_angulaire(s1, s2);

    // // Enhanced Debugging Output
    // cout << "Checking superposition for Coral ID: " << id << endl;
    // cout << "Segment 1 - Index: " << s1.index << ", Point: (" << s1.point.x << ", " << s1.point.y << "), Extr: (" << s1.extr.x << ", " << s1.extr.y << "), Angle: " << s1.ang << endl;
    // cout << "Segment 2 - Index: " << s2.index << ", Point: (" << s2.point.x << ", " << s2.point.y << "), Extr: (" << s2.extr.x << ", " << s2.extr.y << "), Angle: " << s2.ang << endl;
    // cout << "Calculated Angle Difference: " << angle << endl;

   // const double epsilon = 1e-5; // Small epsilon for floating-point comparison
    if (fabs(fabs(angle) - pi) < epsil_zero)
     { 
        cout << message::segment_superposition(id, s1.index, s2.index) << endl;
        exit(EXIT_FAILURE);
    }
}

void cheskcolision(int id1, segment s1, int id2, segment s2) 
{
    s2d extr1 = extr(s1);
    s2d extr2 = extr(s2);
    if (doIntersection(s1.point,extr1, s2.point, extr2) == false) {
        cout << message::segment_collision(id1, s1.index, id2, s2.index) << endl;
        exit(EXIT_FAILURE);
    }
}
