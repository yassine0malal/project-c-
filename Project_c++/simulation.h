#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "constantes.h"
#include "shape.h"
#include "message.h"
#include "lifeform.h"

class simulation {
protected:
    int nb_co;
    int nb_sca;
    int nb_alg;
public:
    simulation();
   // ~simulation();

    void set_co(int co);
    void set_sca(int sca);
    void set_alg(int alg);

    int get_co() ;
    int get_sca() ;
    int get_alg() ;

void lecture(std::ifstream &) ;   
};

#endif // SIMULATION_H
