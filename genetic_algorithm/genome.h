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
#include "defines.h"
#include <iostream>

// For debugging purposes.
// To run debug code run in command line: g++ -D DEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

static int genomeId = 0; // This will assign an ID to every GENOME.
                         // This will help to know what happens to what GENOME
                         // in the future.

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
    Genome() : nodeGenes(), linkGenes(), inputs(0), outputs(0), fitness(0), adjustedFitness(0),
    age(0), network()
    {
        id = genomeId++;
    }
    Genome(int outputs, int inputs);
    Genome(std::vector<NodeGene> nodes, std::vector<LinkGene> links, int in, int out) :
    nodeGenes(nodes), linkGenes(links), inputs(in), outputs(out), fitness(0), adjustedFitness(0),
    age(0), network()
    {
        id = genomeId++;
    }
    Genome(const Genome & rhs) { *this = rhs; }
    ~Genome() { network.deleteNetwork(); }

    //
    // Methods
    //
#ifdef DEBUG
    // All of these are for debugging purposes.
    void mutateAddLink(int num);
    void mutateAddNeuron(int num);
#else
    void mutateAddLink();               // These are all the mutations that can be
    void mutateAddNeuron();             // done for one genome. Three things can be
#endif
    bool mutateEnableLink();            // mutated the neurons, links, and weights.
    std::string getLinksString() const; // This will get the link history for writing to a file.
    std::string getNodesString()const ; // This will grab all the nodes for writing to a file.
    Genome produceChild(const Genome & rhs) const;   // This will produce a child based off
                                                     // the two parents.
    float computeDistance(const Genome & rhs) const; // This will compute the distance
                                                     // between two genomes.
    void mutateRemoveLink(); // Remove a random link.
    void mutateWeight();     // Mutate a weight.

    // Update the genome. This will update the age and the NETWORK of the GENOME.
    void update();

    bool operator > (const Genome & rhs) const
    {
        return adjustedFitness > rhs.adjustedFitness;
    }

    bool operator < (const Genome & rhs) const
    {
        return adjustedFitness > rhs.adjustedFitness;
    }

    Genome & operator = (const Genome & rhs);
    friend std::ostream & operator << (std::ostream & out, const Genome & genome);

    //
    // Getters
    //
    Network & getNetwork()                     { return network;         }
    int getAge()                         const { return age;             }
    float getFitness()                   const { return fitness;         }
    float getAdjustedFitness()           const { return adjustedFitness; }
    std::vector<NodeGene> getNodeGenes() const { return nodeGenes;       }
    std::vector<LinkGene> getLinkGenes() const { return linkGenes;       }
    int getInputs()                      const { return inputs;          }
    int getOutputs()                     const { return outputs;         }
    int getId()                          const { return id;              }

    //
    // Setters
    //
    void setFitness(float f)         { fitness = f;         }
    void setAdjustedFitness(float f) { adjustedFitness = f; }
private:
    std::vector<NodeGene> nodeGenes; // This will hold all it's nodes
    std::vector<LinkGene> linkGenes; // This will hold all it's links to and from nodes.
    Network network;                 // This is the network that it will use.
    int age;                         // How old the GENOME is.
    float fitness;                   // The score that it got from the game.
    float adjustedFitness;           // The adjusted fitness based off the species.
    int inputs;                      // This will keep track how many inputs it has.
    int outputs;                     // Same thing as inputs.
    int id;                          // The id of the genome.
};

#endif // GENOME_H