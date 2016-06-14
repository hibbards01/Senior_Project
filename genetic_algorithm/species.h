/***********************************************************************
* Program:
*   species.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will be the one that holds all the GENOMES that are related to
*       each other.
***********************************************************************/

#ifndef SPECIES_H
#define SPECIES_H

#include "genome.h"
#include <cmath>

/***********************************************************************
* Species
*   This will be the class that will invoke a lot of things for the
*       the GENOMES.
***********************************************************************/
class Species
{
public:
    //
    // Constructors
    //
    Species(int population, int outputs, int inputs) {}
    ~Species() { genomes.clear(); }

    //
    // Methods
    //
    float getAverageFitness();                     // This will grab the average fitness.
    void writeGenomesToFile(int gen, int id);      // This will save the GENOMES to a file.
    std::vector<Genome> produceOffspring(int num); // Produce offspring within the species.
    void mutate(Genome & genome);                  // See if it needs to be mutated.

    // This will update the age for the species and for all it's GENOMES.
    void update()
    {
        for (int g = 0; g < genomes.size(); ++g)
        {
            genomes[g].update();
        }

        ++age;

        return;
    }

    // This will update all the fitnesses so that younger genomes have a
    // better chance for surviving.
    void adjustFitness()
    {
        int size = genomes.size();

        for (int g = 0; g < genomes.size(); ++g)
        {
            genomes[g].setAdjustedFitness(genomes[g].getFitness() / size);
        }

        return;
    }

    // This one will loop through everyone to see who survived this round. Everyone
    // else will be eliminated.
    void killGenomes()
    {
        // First grab the number of survivors
        int survivors = floor(genomes.size() * 0.2) + 1.0;

        // Sort the GENOMES by adjustedFitness in descending order
        sort(genomes.begin(), genomes.end(), std::greater<Genome>());

        // Finally erase the GENOMES that didn't survive.
        genomes.erase(genomes.begin() + survivors, genomes.end());

        return;
    }

    // This will grab the leader of the group. This will be used by the SUPERVISOR
    // class.
    Genome & getLeader()         { return genomes[0];    }

    //
    // Getters
    //
    int getNoImprovement() const { return noImprovement; }
    int getAge()           const { return age;           }
private:
    std::vector<Genome> genomes; // This will hold all the genomes for this species.
    int noImprovement;           // This will keep track how long it has not improved.
    int age;                     // How old this species is.
    float averageFitness;        // The average fitness of the species.
};

#endif // SPECIES_H