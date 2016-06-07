/***********************************************************************
* Program:
*   genome.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class GENOME.
***********************************************************************/

#include "genome.h"
using namespace std;

/***********************************************************************
* Genome
*   The constructor. This will take in the number of outputs and inputs.
*       for what the GENOME needs to build for its starting history.
***********************************************************************/
Genome::Genome(int outputs, int inputs)
{

}

/***********************************************************************
* mutateAddLink
*   This will add a link to the GENOME. Here is how it will do that:
*       1. Select two random neurons.
*           a. Bias can never be a destination.
*           b. Output neurons cannot be a source.
*       2. One neuron will be the source the other a destination.
*       3. Link the two with a small random weight.
***********************************************************************/
void Genome::mutateAddLink()
{
    return;
}

/***********************************************************************
* mutateAddNeuron
*   This one will add a random neuron on a link. Here are the steps for that:
*       1. Remove random link.
*       2. Remove neuron if there is no more links connected to it.
*           a. Only remove a hidden neuron, it cannot be anything else.
***********************************************************************/
void Genome::mutateAddNeuron()
{
    return;
}


/***********************************************************************
* mutateEnableLink
*   This will loop through all the links to find one that is not enabled.
*       Once it finds it, it will then re-enable it.
***********************************************************************/
void Genome::mutateEnableLink()
{
    return;
}

/***********************************************************************
* getLinksString
*   This will grab all the LINKGENES and produce a string. This string
*       be used to write the string to a file.
***********************************************************************/
string Genome::getLinksString()
{
    return "";
}

/***********************************************************************
* getNodesString
*   This does the same exact thing as GETLINKSSTRING function but for the
*       nodes instead.
***********************************************************************/
string Genome::getNodesString()
{
    return "";
}

/***********************************************************************
* produceChild
*   This will use THIS and RHS to produce a child. It will do a crossover
*       from both of the parents.
***********************************************************************/
Genome Genome::produceChild(const Genome & rhs)
{
    return Genome(0, 0);
}

/***********************************************************************
* computeDistance
*   To do speciation you have to compute the distance it is from THIS
*       GENOME to the RHS GENOME. Here is the formula that is given for
*       computing it:
*
*   d = ((c1 * E) / N) + ((c2 * D) / N) + (c3 * W)
*
*   Here is what the variables mean:
*       - d, This is the final distance computed.
*       - E, This is the number of Excess of the Genes.
*       - D, This is the number of disjoint of the Genes.
*       - N, Genome size. Can be set to 1 if small, or set to the longest
*            GENOME.
*       - W, This is where you minus both the weights and add them up to
*            the total.
*       - c1, c2, c3, These adjust the importance of the three. These will
*            static variables set at the beginning of the program.
***********************************************************************/
float Genome::computeDistance(const Genome & rhs)
{
    return 0.0;
}