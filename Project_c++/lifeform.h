#ifndef LIFEFORM_H
#define LIFEFORM_H

#include "constantes.h"
#include "shape.h"
#define MAX  5

class lifeform {
    double x;
    double y;
    int age;

public:
    lifeform();
    lifeform(double , double , int );

    double get_x() ;
    double get_y() ;
    int get_age() ;

    void set_x(double );
    void set_y(double );
    void set_age(int );
    void age_verification();

        void position_verification();

};

class Algue : public lifeform {
public:
    Algue();
    Algue(double , double y, int );
    void setX(double );
    void setY(double );
    void setAge(int );
    double getX();
    double getY();
    int getAge();
};


class Corail : public lifeform {
private:
    int id;
    Status_cor statut;
    Dir_rot_cor direction;
    Status_dev developpement;
    int nombreSegments;
    segment* Segm;
    static int* tabId;
    static int idCorail;

public:
    Corail();
    Corail(double , double , int , int , int,int,int, int );
    
    void setId(int );
    void setStatut(Status_cor );
    void setDirection(Dir_rot_cor );
    void setDeveloppement(Status_dev );
    void setNombreSegments(int );
    int* getTabId();
    int getIdCorail();
    ~Corail();
void setTabseg(segment*);
    void setSegment(int , double , double );
    double getX();
    double getY();
    int getId();
    // Status_cor getStatut();

    // Dir_rot_cor getDirection();
    // Status_dev getDeveloppement();
    int getNombreSegments();
    
    void longueur_verification();
    void angle_verification();
    void position_verification();
    static void checkCoralUniqueness();
     segment* getTabsegment();

};

class Scavenger : public lifeform {
private:
    double radius;
    Status_sca stat;
    int eatingCorailId;

public:
    Scavenger(double , double , int , double , int,int );
    Scavenger();
    
   
    //void setEatingCorailId(int);
    void radius_verification();
    
    void setRadius(double );
    void setStatus(int );
    double getX();
    double getY();
    double getRadius();
    int getEatingCorailId();
    void isValidCorailId(int );
};


#endif // LIFEFORM_H
