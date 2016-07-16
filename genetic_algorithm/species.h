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
#include <algorithm>

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
    Species(int population, int outputs, int inputs) : noImprovement(0), age(0), averageFitness(100000), leader(outputs, inputs)
    {
        for (int p = 0; p < population; ++p)
        {
            genomes.push_back(Genome(outputs, inputs));
        }
    }
    Species(Genome & genome) : noImprovement(0), age(0), averageFitness(100000), leader(genome) { genomes.push_back(genome); }
    Species(const Species & s) { *this = s; }
    ~Species() { genomes.clear(); }

    //
    // Methods
    //
    float getAverageFitness(bool secondCall = false);   // This will grab the average fitness.
    void writeGenomesToFile(int gen, int id);           // This will save the GENOMES to a file.
    void update();                                      // This will update the age for the species
                                                        // and for all it's GENOMES.
    std::vector<Genome> produceOffspring(int children) const; // Produce offspring within the species.
    Genome getBestGenome()                                  // Grab the best genome.
    {
        Genome genome;
        genome.setFitness(5000);
        for (int g = 0; g < genomes.size(); ++g)
        {
            if (genomes[g].getFitness() < genome.getFitness())
            {
                genome = genomes[g];
            }
        }

        return genome;
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
    // else will be eliminated. This will return how many is left over.
    int killGenomes()
    {
        // First grab the number of survivors
        int survivors = floor(genomes.size() * 0.2) + 1.0;

        // Sort the GENOMES by adjustedFitness in descending order
        sort(genomes.begin(), genomes.end());

        // Finally erase the GENOMES that didn't survive.
        genomes.erase(genomes.begin() + survivors, genomes.end());

        return genomes.size();
    }

    // This will grab the leader of the group. This will be used by the SUPERVISOR
    // class.
    const Genome & getLeader()                   { return leader;    }

    //
    // Operator methods
    //
    bool operator > (const Species & rhs) const
    {
        return averageFitness > rhs.averageFitness;
    }

    bool operator < (const Species & rhs) const
    {
        return averageFitness < rhs.averageFitness;
    }

    Species & operator = (const Species & rhs);

    //
    // Getters
    //
    int getNoImprovement()            const { return noImprovement; }
    int getAge()                      const { return age;           }
    std::vector<Genome> & getGenomes()      { return genomes;       }
private:
    std::vector<Genome> genomes; // This will hold all the genomes for this species.
    int noImprovement;           // This will keep track how long it has not improved.
    int age;                     // How old this species is.
    float averageFitness;        // The average fitness of the species.
    Genome leader;               // This will be the leader of the group that started the species.
};

#endif // SPECIES_H