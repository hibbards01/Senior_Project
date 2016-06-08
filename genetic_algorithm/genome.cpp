/***********************************************************************
* Program:
*   genome.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class GENOME.
***********************************************************************/

#include "genome.h"
#include "defines.h"
#include "geneHistory.h"
#include <cmath>
using namespace std;

/***********************************************************************
* Genome
*   The constructor. This will take in the number of outputs and inputs.
*       for what the GENOME needs to build for its starting history.
***********************************************************************/
Genome::Genome(int outputs, int inputs)
{
    int id;                                        // This will be used for the NODES.
    GeneHistory * db = GeneHistory::getInstance(); // Grab the database.

    // First create all the outputs for the Genome.
    for (int o = 0; o < outputs; ++o, ++id)
    {
        nodeGenes.push_back(NodeGene(id, OUTPUT));

        // Save that node to the main database.
        db->addNewNeuron(id, OUTPUT);
    }

    // Now create all the inputs.
    for (int i = 0; i < inputs; ++i, ++id)
    {
        // First save the object to the vector and the database
        nodeGenes.push_back(NodeGene(id, SENSOR));
        db->addNewNeuron(id, SENSOR);

        // Now create all the links from the sensors to the one output
        for (int o = 0; o < outputs; ++o)
        {
            int source = id;                   // Grab the source and
            int destination = nodeGenes[o].id; // the destination.

            // Add it to the database if new.
            int linkId = db->addNewLink(source, destination);

            // Finally save the link
            // Give it a random weight.
            linkGenes.push_back(LinkGene(linkId, source, destination, random(0.0, 1.0)));
        }
    }
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
    NodeGene * source;      // As the name applies we need to find two
    NodeGene destination;   // Neurons to connect each other.
    bool found = false;     // This will keep track if we have found it yet.
    bool recurrent = false; // Will this be a recurrent link or not?
    int num = random(0, 2); // This will decide what will happen to the link.

    if (num == 0) // Create a recurrent link onto itself
    {
        // Now loop through all the nodes until a node that isn't recurrent is found.
        for (int n = 0; n < nodeGenes.size() && !found; ++n)
        {
            if (nodeGenes[n].type == HIDDEN && !nodeGenes[n].recurrent)
            {
                source = &nodeGenes[n];
                destination = nodeGenes[n];
                found = true;
                recurrent = true;
            }
        }

        // If we did not find anything then we will mutate a different link.
        if (!found)
        {
            num = 1;
        }
    }

    // Create a new link this can either be a recurrent link to another node
    // or be a feed forwarding link,
    if (num > 0)
    {
        num = 10; // Not sure what to set this to?

        while (!found && num--)
        {
            // Grab two random nodes!
            int randNode = random(0, nodeGenes.size() - 1);
            source = &nodeGenes[randNode];
            randNode = random(0, nodeGenes.size() - 1);

            // Now see if everything is correct
            if (source->type != OUTPUT && destination.type != BIAS
                && source->id != destination.id)
            {
                found = true;
            }
        }
    }

    // Did we find one?
    if (found)
    {
        // Let's add the new mutation!
        double weight = random(0.0, 1.0);

        // Now add the link to the new database and grab the id for it.
        GeneHistory * db = GeneHistory::getInstance();
        int id = db->addNewLink(source->id, destination.id);

        if (!recurrent) // This will see if the two nodes are recurrent or not
        {
            if (network.getShortestPath(source->id) <= network.getShortestPath(destination.id))
            {
                recurrent = true;
            }
        }

        // Set the source to the recurrent variable
        source->recurrent = recurrent;

        // Finally add it to the history
        linkGenes.push_back(LinkGene(id, source->id, destination.id, weight));
    }

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
bool Genome::mutateEnableLink()
{
    bool done = false;

    // Find a link that we can re-enable.
    for (int l = 0; l < linkGenes.size() && !done; ++l)
    {
        if (!linkGenes[l].enabled)
        {
            linkGenes[l].enabled = true;
            done = true;
        }
    }

    return done;
}

/***********************************************************************
* mutateRemoveLink
*   This will remove a link. Here are the steps for it:
*       1. Remove a random link.
*       2. Remove neuron if there is no more links connected to i.
*           a. Only remove a hidden and bias node. Nothing else.
***********************************************************************/
void Genome::mutateRemoveLink()
{
    // Remove a random link.
    int index = random(0, linkGenes.size() - 1);

    // Now see if we need to remove the nodes that were connected by this link.
    int removeNode = linkGenes[index].input;
    int removeNode2 = linkGenes[index].output;
    for (int l = 0; l < linkGenes.size(); ++l)
    {
        if (removeNode == linkGenes[l].input
            || removeNode == linkGenes[l].output)
        {
            removeNode = -1;
        }

        if (removeNode2 == linkGenes[l].input
            || removeNode2 == linkGenes[l].output)
        {
            removeNode2 = -1;
        }
    }

    // If either of them is -1 then we don't need to remove a node.
    // If they are not then we need to remove it.
    for (vector<NodeGene>::iterator it = nodeGenes.begin(); it != nodeGenes.end(); ++it)
    {
        if ((it->id == removeNode || it->id == removeNode2) &&
            (it->type == HIDDEN || it->type == BIAS))
        {
            it = nodeGenes.erase(it);
        }
    }

    return;
}

/***********************************************************************
* getLinksString
*   This will grab all the LINKGENES and produce a string. This string
*       be used to write the string to a file.
***********************************************************************/
string Genome::getLinksString()
{
    string ids;     //
    string inputs;  //
    string outputs; // All these strings save an aspect of the GENOME.
    string weights; //
    string enables; //

    // Grab all the links and save them in the strings.
    for (int l = 0; l < linkGenes.size(); ++l)
    {
        ids += "Id: " + toString<int>(linkGenes[l].id) + " ";
        inputs += "Input: " + toString<int>(linkGenes[l].input) + " ";
        outputs += "Output: " + toString<int>(linkGenes[l].output) + " ";
        weights += "Weight: " + toString<double>(linkGenes[l].weight) + " ";

        string boolean = (linkGenes[l].enabled) ? "True" : "False";

        enables += "Enabled: " + boolean + " ";
    }

    return ids + "\n" + inputs + "\n" + outputs + "\n" + weights + "\n" + enables + "\n";
}

/***********************************************************************
* getNodesString
*   This does the same exact thing as GETLINKSSTRING function but for the
*       nodes instead.
***********************************************************************/
string Genome::getNodesString()
{
    string ids;        //
    string types;      // All these strings save an aspect of the GENOME.
    string recurrents; //
    string arrayType[3] = {"Sensor", "Hidden", "Output"};

    for (int n = 0; n < nodeGenes.size(); ++n)
    {
        ids += "Id: " + toString<int>(nodeGenes[n].id) + " ";
        types += "Type: " + arrayType[nodeGenes[n].type] + " ";

        string boolean = (nodeGenes[n].recurrent) ? "True" : "False";

        recurrents += "Recurrent: " + boolean + " ";
    }

    return ids + "\n" + types + "\n" + recurrents + "\n";
}

/***********************************************************************
* produceChild
*   This will use THIS and RHS to produce a child. It will do a crossover
*       from both of the parents.
***********************************************************************/
Genome Genome::produceChild(const Genome & rhs) const
{
    // Create the two iterator for THIS and RHS.
    // This will be used to loop through both of their histories.
    vector<LinkGene> :: const_iterator lhsIter = linkGenes.begin();
    vector<LinkGene> :: const_iterator rhsIter = rhs.linkGenes.begin();

    vector<LinkGene> childLinkGenes; // This is where all the links will be
                                     // saved for the new child.
    bool fit = (rhs.fitness < fitness) ? true : false; // Which parent is the more fit one?

    // Now loop through the histories.
    while (lhsIter != linkGenes.begin() || rhsIter != rhs.linkGenes.end())
    {
        LinkGene newLinkGene; // Create a gene.

        // First two conditions check if there is an excess or disjoint history
        // between the GENOMES. It will then grab that LINKGEN from them.
        if (rhsIter == rhs.linkGenes.end() || lhsIter->id < rhsIter->id)
        {
            newLinkGene = *lhsIter;
            ++lhsIter;
        }
        else if (lhsIter == linkGenes.end() || rhsIter->id < lhsIter->id)
        {
            newLinkGene = *rhsIter;
            ++rhsIter;
        }
        else
        {
            // If there is a match then grab from the fittest parent.
            newLinkGene = (fit) ? *lhsIter : *rhsIter;

            ++lhsIter;
            ++rhsIter;
        }

        // Finally insert that link into the vector.
        childLinkGenes.push_back(newLinkGene);
    }

    // Now grab the NEURONS for the child.
    // Grab the biggest vector
    vector<NodeGene> childNodeGenes = nodeGenes;
    vector<NodeGene> otherNodeGenes = rhs.nodeGenes;

    if (rhs.nodeGenes.size() > nodeGenes.size())
    {
        childNodeGenes = rhs.nodeGenes;
        otherNodeGenes = nodeGenes;
    }

    // Now loop through the OTHERNODEGENES to grab all the recurrent links
    for (int i = 0; i < otherNodeGenes.size(); ++i)
    {
        if (otherNodeGenes[i].recurrent)
        {
            childNodeGenes[i].recurrent = true;
        }
    }

    return Genome(childNodeGenes, childLinkGenes);
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
float Genome::computeDistance(const Genome & rhs) const
{
    // Create the two iterator for THIS and RHS.
    // This will be used to loop through both of their histories.
    vector<LinkGene> :: const_iterator lhsIter = linkGenes.begin();
    vector<LinkGene> :: const_iterator rhsIter = rhs.linkGenes.begin();

    int disjoints = 0;          // How many disjoints between the two?
    int excess = 0;             // How many excess between the two?
    int matched = 0;            // How many matches were found?
    float weightDifference = 0; // What is the weight difference between the matches?

    // Now loop through both of there histories.
    while (lhsIter != linkGenes.end() || rhsIter != rhs.linkGenes.end())
    {
        if (rhsIter == rhs.linkGenes.end()) // If one is done then we have excess.
        {
            ++excess;
            ++lhsIter;
        }
        else if (lhsIter == linkGenes.end()) // If one is done then we have excess.
        {
            ++excess;
            ++rhsIter;
        }
        else if (lhsIter->id < rhsIter->id) // If one id is less then the other then we have disjoint.
        {
            ++disjoints;
            ++lhsIter;
        }
        else if (rhsIter->id < lhsIter->id) // If one id is less then the other then we have disjoint.
        {
            ++disjoints;
            ++rhsIter;
        }
        else // We have found a match. Grab their weight difference.
        {
            weightDifference += abs(lhsIter->weight - rhsIter->weight);

            ++matched;
            ++lhsIter;
            ++rhsIter;
        }
    }

    // Grab the the biggest genome size
    int size = (linkGenes.size() >= rhs.linkGenes.size()) ? linkGenes.size() : rhs.linkGenes.size();

    // Finally compute the distance between the GENOMES.
    float distance = ((c1 * excess) / size) + ((c2 * disjoints) / size) + (c3 * (weightDifference / matched));

    return distance;
}