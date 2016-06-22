/***********************************************************************
* Program:
*   geneHistory.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold all the innovations for all the genes within the
*       population. This will also hold the variables that will act
*       like a static variables.
***********************************************************************/

#ifndef GENEHISTORY_H
#define GENEHISTORY_H

#include <vector>

static int innovationId = 0; // This will increment every time a new
                             // Innovation is added to the database.

/***********************************************************************
* Innovation
*   This will be the STRUCT that will hold all the innovations. This
*       can either do the nodes or links.
***********************************************************************/
struct Innovation
{
    Innovation(int in, int out, int n, int type)
    {

        id = innovationId++; // Increment the innovation.
        input = in;
        output = out;
        node = n;
        nodeType = type;
    }

    int id;       // The innovation id.
    int input;    // The input and output, this is the link
    int output;   // that will be saved.
    int node;     // The node that we want to save
    int nodeType; // with it's given type.
};

/***********************************************************************
* GeneHistory
*   This will be a singleton class so that any class can use it if
*       needed.
***********************************************************************/
class GeneHistory
{
public:
    //
    // Methods
    //
    void addNewNeuron(int id, int type);         // This will add a new neuron.
    int addNewLink(int source, int destination); // This will add a new link.

    // This will return the GENEHISTORY. It will create a new instance if necessary.
    static GeneHistory & getInstance()
    {
        static GeneHistory inst;
        return inst;
    }

    //
    // Getters
    //
    std::vector<Innovation> & getInnovations() { return innovations;          }
    float getSpeciesCompatibility()      const { return speciesCompatibility; }
    float getLinkRate()                  const { return linkRate;             }
    float getNodeRate()                  const { return nodeRate;             }
    float getWeightRate()                const { return weightRate;           }
    int getKillRate()                    const { return killRate;             }
    float getCrossoverRate()             const { return crossoverRate;        }
    float getC1()                        const { return c1;                   }
    float getC2()                        const { return c2;                   }
    float getC3()                        const { return c3;                   }

    //
    // Setters
    //
    void setSpeciesCompatibility(float sc) { speciesCompatibility = sc; }
    void setLinkRate(float lr)             { linkRate = lr;             }
    void setNodeRate(float nr)             { nodeRate = nr;             }
    void setWeightRate(float wr)           { weightRate = wr;           }
    void setKillRate(int kr)               { killRate = kr;             }
    void setCrossoverRate(float cr)        { crossoverRate = cr;        }
    void setC1(float v)                    { c1 = v;                    }
    void setC2(float v)                    { c2 = v;                    }
    void setC3(float v)                    { c3 = v;                    }
private:
    //
    // Constructors
    //
    GeneHistory() : innovations(), speciesCompatibility(0), linkRate(0), nodeRate(0), weightRate(0),
    killRate(0), crossoverRate(0), c1(0), c2(0), c3(0) {}
    GeneHistory(const GeneHistory & rhs) {}
    ~GeneHistory() {}
    GeneHistory & operator = (const GeneHistory & rhs) { return *this; }

    std::vector<Innovation> innovations; // This will hold all the innovations.
    float speciesCompatibility;  // The species compatibility threshold.
    float linkRate;              // Mutation link rate.
    float nodeRate;              // Mutation neuron rate.
    float weightRate;            // Mutation weight rate.
    int killRate;                // When should the species should be killed?
    float crossoverRate;         // This will be set for the crossover rate.
    float c1, c2, c3;            // These will be used for the computeDistance function.
};

#endif // GENEHISTORY_H