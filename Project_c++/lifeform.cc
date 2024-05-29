#include "shape.h"
#include <cmath>
#include "lifeform.h"
#include "message.h"

#define MAX 5

using namespace std;

lifeform::lifeform() {}
lifeform::lifeform(double xx, double yy, int age) : x(xx), y(yy), age(age) {}

double lifeform::get_x()  { return x; }
double lifeform::get_y()  { return y; }
int lifeform::get_age()  { return age; }

void lifeform::set_x(double xx) { x = xx; }
void lifeform::set_y(double yy) { y = yy; }
void lifeform::set_age(int age) { this->age = age; }

void lifeform::age_verification() {
    if (!(age > 0)) {
        cout << message::lifeform_age(age) << endl;
        exit(EXIT_FAILURE);
    }
}

void lifeform::position_verification() {
    if (!(x >= 1 && x <= dmax - 1 && y >= 1 && y <= dmax - 1)) {
        cout <<  message::lifeform_center_outside(x, y) << endl;
        exit(EXIT_FAILURE);
    }
}

Algue::Algue() {}
Algue::Algue(double x, double y, int age) : lifeform(x, y, age) {}
void Algue::setX(double xx) { lifeform::set_x(xx); }
void Algue::setY(double yy) { lifeform::set_y(yy); }
void Algue::setAge(int age) { lifeform::set_age(age); }

double Algue::getX()  { return lifeform::get_x(); }
double Algue::getY()  { return lifeform::get_y(); }
int Algue::getAge()  { return lifeform::get_age(); }

Corail::Corail() {}
Corail::Corail(double xx, double yy, int age, int identifier, int stat, int dir, int dev, int segments)
    : lifeform(xx, yy, age), id(identifier), nombreSegments(segments) {
    Segm = new segment[nombreSegments];
    tabId[idCorail] = id;
    idCorail++;

    statut = (stat == 0) ? Status_cor::DEAD : Status_cor::ALIVE;
    direction = (dir == 0) ? Dir_rot_cor::TRIGO : Dir_rot_cor::TRIGO; // should this be Dir_rot_cor::TRIGO or something else?
    developpement = (dev == 0) ? Status_dev::EXTEND : Status_dev::REPRO;
}

void Corail::setId(int identifier) { id = identifier; }
void Corail::setStatut(Status_cor stat) { statut = stat; }
void Corail::setDirection(Dir_rot_cor dir) { direction = dir; }
void Corail::setDeveloppement(Status_dev dev) { developpement = dev; }
void Corail::setNombreSegments(int segments) { nombreSegments = segments; }

void Corail::setTabseg(segment* tab) {
    delete[] Segm; // free the old memory if any
    Segm = tab;
}
segment* Corail::getTabsegment() { return Segm; }
int* Corail::getTabId() { return tabId; }
int Corail::getIdCorail() { return idCorail; }
Corail::~Corail() {
    delete[] Segm;
}

void Corail::setSegment(int index, double longueur, double ang) {
    Segm[index].longueur = longueur;
    Segm[index].ang = ang;
}

double Corail::getX() { return lifeform::get_x(); }
double Corail::getY() { return lifeform::get_y(); }
int Corail::getId() { return id; }
int Corail::getNombreSegments() { return nombreSegments; }

void Corail::longueur_verification() {
    for (int i = 0; i < nombreSegments; i++) {
        if (!(Segm[i].longueur >= (l_repro - l_seg_interne) && Segm[i].longueur < l_repro)) {
            cout << message::segment_length_outside(id, Segm[i].longueur);
            exit(EXIT_FAILURE);
        }
    }
}

void Corail::angle_verification() {
    for (int i = 0; i < nombreSegments; i++) {
        if (!(Segm[i].ang >= -pi && Segm[i].ang <= pi)) {
            cout << message::segment_angle_outside(id, Segm[i].ang);
            exit(EXIT_FAILURE);
        }
    }
}

void Corail::position_verification() {
    double x = getX();
    double y = getY();
    if (x <= 0 || x >= dmax || y <= 0 || y >= dmax) {
        cout << message::lifeform_computed_outside(id, x, y) << endl;
        exit(EXIT_FAILURE);
    }
}

void Corail::checkCoralUniqueness() {
    for (int i = 0; i < idCorail - 1; ++i) {
        for (int j = i + 1; j < idCorail; ++j) {
            if (tabId[i] == tabId[j]) {
                cout << message::lifeform_duplicated_id(tabId[i]) << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

int* Corail::tabId = new int[MAX];
int Corail::idCorail = 0;

//SCAVENGER/

Scavenger::Scavenger(double posX, double posY, int age, double initialRadius, int statt, int e)
    : lifeform(posX, posY, age), radius(initialRadius), eatingCorailId(e) {
    stat = (statt == 0) ? Status_sca::FREE : Status_sca::EATING;
}

Scavenger::Scavenger() {}

void Scavenger::radius_verification() {
    if (!(radius >= r_sca && radius < r_sca_repro)) {
        cout << message::scavenger_radius_outside(radius) << endl;
        exit(EXIT_FAILURE);
    }
}

void Scavenger::setRadius(double r) { radius = r; }
void Scavenger::setStatus(int s) {
    stat = (s == 0) ? Status_sca::FREE : Status_sca::EATING;
}

double Scavenger::getX() { return lifeform::get_x(); }
double Scavenger::getY() { return lifeform::get_y(); }
double Scavenger::getRadius() { return radius; }
int Scavenger::getEatingCorailId() { return eatingCorailId; }

void Scavenger::isValidCorailId(int id) {
    int k = 0;
    Corail a;
    int* t = a.getTabId();
    int index = a.getIdCorail();

    for (int i = 0; i < index; i++) {
        if (t[i] == id) {
            k++;
        }
    }
    if (k == 0 && id != -1) {
        cout << message::lifeform_invalid_id(id) << endl;
        exit(EXIT_FAILURE);
    }
}
