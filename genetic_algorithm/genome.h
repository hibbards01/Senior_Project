/***********************************************************************
* Program:
*   genome.h
* Author:
*   Samuel Hibbard
* Summary:
*   This holds one solution of the population. This also holds the
*       NETWORK that controls the ship. This class will be the one that
*       does random mutations or creating offspring based off another
*       GENOME.
***********************************************************************/

#ifndef GENOME_H
#define GENOME_H

#include "network.h"
#include "genes.h"
#include <vector>

/***********************************************************************
* Genome
*   This holds the NETWORK, LINKGENEs, and NODEGENEs for one solution.
*       This is the one that governs when to build the NETWORK and when
*       to do changes to it's history of NODE and LINK genes.
***********************************************************************/
class Genome
{
public:
    //
    // Constructors
    //
    Genome(int outputs, int inputs);
    ~Genome();

    //
    // Methods
    //


    //
    // Getters
    //


    //
    // Setters
    //

private:
    std::vector<NodeGene> nodeGenes; // This will hold all it's nodes
    std::vector<LinkGene> linkGenes; // This will hold all it's links to and from nodes.
    Network network;                 // This is the network that it will use.
    int age;                         // How old the GENOME is.
    float fitness;                   // The score that it got from the game.
    float adjustedFitness;           // The adjusted fitness based off the species.
};

#endif // GENOME_H