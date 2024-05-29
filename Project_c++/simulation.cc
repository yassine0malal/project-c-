#include <iostream>
#include <fstream>
#include "message.h"
#include "shape.h"
#include "lifeform.h"
#include "simulation.h"

using namespace std;

simulation::simulation() : nb_co(0), nb_sca(0), nb_alg(0) {}

void simulation::set_co(int co) { nb_co = co; }
void simulation::set_sca(int sca) { nb_sca = sca; }
void simulation::set_alg(int alg) { nb_alg = alg; }

int simulation::get_co() { return nb_co; }
int simulation::get_sca() { return nb_sca; }
int simulation::get_alg() { return nb_alg; }

void simulation::lecture(ifstream &file) {
    if (!file.is_open()) {
       std:: cout << "Error: File not opened." << endl;
        return;
    }

    double xx, y;
    int age, id, stat, dir, dev, nbseg;

    // Reading Algue data
    file >> nb_alg;
    Algue* tab_alg = new Algue[nb_alg];

    for (int i = 0; i < nb_alg; i++) {
        file >> xx >> y >> age;
        tab_alg[i].setX(xx);
        tab_alg[i].setY(y);
        tab_alg[i].setAge(age);
    }

    // Reading Corail data
    file >> nb_co;
    Corail* tab_cor = new Corail[nb_co];
    
    for (int i = 0; i < nb_co; i++) {
        // Read coral attributes
        file >> xx >> y >> age >> id >> stat >> dir >> dev >> nbseg;
        Corail a(xx, y, age, id, stat, dir, dev, nbseg);

        // Read segments
        segment* t = new segment[nbseg]; // dynamically allocate array for segments
        for (int j = 0; j < nbseg; j++) {
            file >> t[j].ang >> t[j].longueur;
            t[j].index = j;
            if (j == 0) {
                t[j].point.x = xx;
                t[j].point.y = y;
            } else {
                t[j].point.x = t[j - 1].extr.x;
                t[j].point.y = t[j - 1].extr.y;
            }
            t[j].extr = extr(t[j]);
        }
        a.setTabseg(t); // set segments in Corail object
        tab_cor[i] = a;
    }

    // Reading Scavenger data
    file >> nb_sca;
    Scavenger* tab_sca = new Scavenger[nb_sca];

    for (int i = 0; i < nb_sca; i++) {
        double radius;
        int eatingCorailId;
        file >> xx >> y >> age >> radius >> stat;
        if (!(file >> eatingCorailId)) {
            eatingCorailId = -1;
        }
        tab_sca[i] = Scavenger(xx, y, age, radius, stat, eatingCorailId);
    }

    // Performing verification after loading all data
    for (int i = 0; i < nb_alg; i++) {
        tab_alg[i].age_verification();
        tab_alg[i].position_verification();
    }

    for (int i = 0; i < nb_co; i++) {
        //   tab_cor[i].longueur_verification();
        tab_cor[i].angle_verification();
        tab_cor[i].position_verification();
        tab_cor[i].checkCoralUniqueness();

        // Check internal collisions
        for (int j = 0; j < tab_cor[i].getNombreSegments()-2; j++) {
            for (int k = j + 2; k < tab_cor[i].getNombreSegments(); k++) {
                cheskcolision(tab_cor[i].getId(), tab_cor[i].getTabsegment()[j], tab_cor[i].getId(), tab_cor[i].getTabsegment()[k]);
            }
        }

        // Check external collisions
        for (int l = 0; l < tab_cor[i].getNombreSegments(); l++) {
            for (int j = 0; j < nb_co; j++) {
                if (i == j) continue; // Prevent self-comparison
                for (int k = 0; k < tab_cor[j].getNombreSegments(); k++) {
                    cheskcolision(tab_cor[i].getId(), tab_cor[i].getTabsegment()[l], tab_cor[j].getId(), tab_cor[j].getTabsegment()[k]);
                }
            }
        }
     }

    // Check for segment superposition
    for (int i = 0; i < nb_co; i++) {
        for (int j = 0; j < tab_cor[i].getNombreSegments() - 1; j++) {
            superposition(tab_cor[i].getTabsegment()[j], tab_cor[i].getTabsegment()[j + 1], tab_cor[i].getId());
        }
    }

    for (int i = 0; i < nb_sca; i++) {
        tab_sca[i].age_verification();
        tab_sca[i].radius_verification();
        tab_sca[i].isValidCorailId(tab_sca[i].getEatingCorailId());
        tab_sca[i].position_verification();
        tab_sca[i].isValidCorailId(tab_sca[i].getEatingCorailId());
    }

    // Clean up dynamically allocated memory
    delete[] tab_alg;
    delete[] tab_cor;
    delete[] tab_sca;
    cout << message::success() << endl;
    file.close();
}
