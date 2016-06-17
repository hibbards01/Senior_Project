/***********************************************************************
* Program:
*   supervisor.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will be the main controller of the whole Genetic process. This
*       class will tell the other classes when to do what. This will
*       also control the simulation and have the networks run it.
***********************************************************************/

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "species.h"

/***********************************************************************
* Supervisor
*   This will have the functions that will invoke everything that the
*       species will do.
***********************************************************************/
class Supervisor
{
public:
    //
    // Constructors
    //
    Supervisor(int population, int outputs, int inputs);
    ~Supervisor() { species.clear(); }

    //
    // Methods
    //
    void epoch();                  // This is the main driver for what happens
                                   // to the population.
    void setOverallAverage();      // Grab the overall average of the population.
    void update();                 // Update everything!
    void run();                    // This will run the everything.
    float runSimulation();         // This will take the network and run the simulation.
    void writePopulationToFile();  // Write the population to a file.

    //
    // Getters
    //
    int getOverallAverage()       const { return overallAverage; }
    int getGeneration()           const { return generation;     }
    int getNoImprovement()        const { return noImprovement;  }
    int getPopulation()           const { return population;     }
    std::vector<Species> & getSpecies() { return species;        }
private:
    std::vector<Species> species; // Confusing, right? ;)
    int generation;               // What generation are we in? This will
                                  // keep track of that.
    float overallAverage;         // What is the overall average of the species.
    int noImprovement;            // This will be the tracker of when this
                                  // algorithm is done.
    int population;               // This will hold how many of population we shall create.

    // This will calculate where the babies go to
    // which species in the population.
    void giveOffspringToSpecies(std::vector<Genome> & genomes);

    // This will mutate the offspring that was made by the population.
    void mutateOffspring(std::vector<Genome> & genomes);
};

#endif // SUPERVISOR_H