
#include "lifeform.h"
//#include<string>
#include "lifeform.cc"
#include "simulation.h"
#include "simulation.cc"
#include "message.h"
#include "constantes.h"
#include "shape.h"
#include "shape.cc"
// #include "message.cc"
#include <fstream>
#include<iostream>

int main()
{   
    ifstream t("t08.txt");
    simulation sim;
    sim.lecture(t);
    return 0;
}