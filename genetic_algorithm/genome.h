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
#include <iostream>

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
    Genome(std::vector<NodeGene> nodes, std::vector<LinkGene> links, int in, int out) :
    nodeGenes(nodes), linkGenes(links), inputs(in), outputs(out) {}
    Genome(const Genome & rhs)
    {
        nodeGenes = rhs.nodeGenes;
        linkGenes = rhs.linkGenes;
        age = rhs.age;
        fitness = rhs.fitness;
        adjustedFitness = rhs.adjustedFitness;
        inputs = rhs.inputs;
        outputs = rhs.outputs;
    }
    ~Genome() { network.deleteNetwork(); }

    //
    // Methods
    //
    void mutateAddLink();         // These are all the mutations that can be
    void mutateAddNeuron();       // done for one genome. Three things can be
    bool mutateEnableLink();      // mutated the neurons, links, and weights.
    std::string getLinksString(); // This will get the link history for writing to a file.
    std::string getNodesString(); // This will grab all the nodes for writing to a file.
    Genome produceChild(const Genome & rhs) const;   // This will produce a child based off
                                                     // the two parents.
    float computeDistance(const Genome & rhs) const; // This will compute the distance
                                                     // between two genomes.
    void mutateRemoveLink(); // Remove a random link.

    // Mutate a weight.
    void mutateWeight()
    {
        return;
    }

    // Update the genome. This will update the age and the NETWORK of the GENOME.
    void update()
    {
        network.update(nodeGenes, linkGenes);
        ++age;

        return;
    }


    //
    // Getters
    //
    Network & getNetwork()           { return network;         }
    int getAge()               const { return age;             }
    float getFitness()         const { return fitness;         }
    float getAdjustedFitness() const { return adjustedFitness; }
private:
    std::vector<NodeGene> nodeGenes; // This will hold all it's nodes
    std::vector<LinkGene> linkGenes; // This will hold all it's links to and from nodes.
    Network network;                 // This is the network that it will use.
    int age;                         // How old the GENOME is.
    float fitness;                   // The score that it got from the game.
    float adjustedFitness;           // The adjusted fitness based off the species.
    int inputs;                      // This will keep track how many inputs it has.
    int outputs;                     // Same thing as inputs.
    static float c1, c2, c3;         // These will be used for the computeDistance function.
};

#endif // GENOME_H