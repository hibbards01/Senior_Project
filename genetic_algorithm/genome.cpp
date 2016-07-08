/***********************************************************************
* Program:
*   genome.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class GENOME.
***********************************************************************/

#include "genome.h"
#include "geneHistory.h"
#include <cmath>
using namespace std;

/***********************************************************************
* Genome
*   The constructor. This will take in the number of outputs and inputs.
*       for what the GENOME needs to build for its starting history.
***********************************************************************/
Genome::Genome(int outputs, int inputs) : fitness(0), adjustedFitness(0), age(0), network()
{
    int nodeId = 0;                                // This will be used for the NODES.
    GeneHistory & db = GeneHistory::getInstance(); // Grab the database.

    // First create all the outputs for the Genome.
    for (int o = 0; o < outputs; ++o, ++nodeId)
    {
        nodeGenes.push_back(NodeGene(nodeId, OUTPUT));

        // Save that node to the main database.
        db.addNewNeuron(nodeId, OUTPUT);
    }

    // Now create all the inputs.
    for (int i = 0; i < inputs; ++i, ++nodeId)
    {
        // First save the object to the vector and the database
        nodeGenes.push_back(NodeGene(nodeId, SENSOR));
        db.addNewNeuron(nodeId, SENSOR);

        // Now create all the links from the sensors to the one output
        for (int o = 0; o < outputs; ++o)
        {
            int source = nodeId;               // Grab the source and
            int destination = nodeGenes[o].id; // the destination.

            // Add it to the database if new.
            int linkId = db.addNewLink(source, destination);

            // Finally save the link
            // Give it a random weight.
            linkGenes.push_back(LinkGene(linkId, source, destination, random(-1.0, 1.0)));
        }
    }

    this->inputs = inputs;
    this->outputs = outputs;
    this->id = genomeId++;
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
#ifdef DEBUG
void Genome::mutateAddLink(int num)
#else
void Genome::mutateAddLink()
#endif
{
    int source;             // As the name applies we need to find two
    int destination;        // Neurons to connect each other.
    bool found = false;     // This will keep track if we have found it yet.
    bool recurrent = false; // Will this be a recurrent link or not?

#ifndef DEBUG
    int num = random(0, 2); // This will decide what will happen to the link.
#endif

    if (num == 0) // Create a recurrent link onto itself
    {
        // Now loop through all the nodes until a node that isn't recurrent is found.
        for (int n = 0; n < nodeGenes.size() && !found; ++n)
        {
            if (nodeGenes[n].type == HIDDEN && !nodeGenes[n].recurrent)
            {
                source = n;
                destination = n;
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

        while (!found && num-- > 0)
        {
            // Grab two random nodes!
            int randNode = random(0, nodeGenes.size() - 1);
            NodeGene sr = nodeGenes[randNode];
            int randNode2 = random(0, nodeGenes.size() - 1);
            NodeGene dest = nodeGenes[randNode2];

            // Now see if everything is correct
            if (sr.type != OUTPUT && dest.type != BIAS
                && sr.id != dest.id)
            {
                found = true;
                source = randNode;
                destination = randNode2;
            }
        }
    }

    // Did we find one?
    if (found)
    {
        assert(source >= 0);
        assert(source < nodeGenes.size());
        assert(destination >= 0);
        assert(destination < nodeGenes.size());

        int srId = nodeGenes[source].id;
        int destId = nodeGenes[destination].id;

        // Let's add the new mutation!
        double weight = random(0.0, 1.0);

        // Now add the link to the new database and grab the id for it.
        GeneHistory & db = GeneHistory::getInstance();
        int id = db.addNewLink(srId, destId);

        if (!recurrent) // This will see if the two nodes are recurrent or not
        {
            int path1 = network.getShortestPath(srId);
            int path2 = network.getShortestPath(destId);

            if (path1 >= path2)
            {
                recurrent = true;
            }
        }

        // Set the source to the recurrent variable
        nodeGenes[source].recurrent = recurrent;

        // Finally add it to the history
        linkGenes.push_back(LinkGene(id, srId, destId, weight, true, MUTATE_LINK));
    }

    return;
}

/***********************************************************************
* mutateAddNeuron
*   This one will add a random neuron on a link. Here are the steps for
*       a HIDDEN node.
*       1. Remove random link.
*       2. Remove neuron if there is no more links connected to it.
*           a. Only remove a hidden neuron, it cannot be anything else.
*   For a BIAS node we will just select a random HIDDEN node and give
*       it an input from the BIAS node.
***********************************************************************/
#ifdef DEBUG
void Genome::mutateAddNeuron(int num)
#else
void Genome::mutateAddNeuron()
#endif
{
    // Create a brand new neuron. Do a random choice for whether it is a
    // BIAS node or a HIDDEN node. It is more biased towards HIDDEN nodes.
    int newId = nodeGenes[nodeGenes.size() - 1].id + 1;
    NodeGene node(newId, -1);
    bool found = false;

    // Grab the database and add node to it.
    GeneHistory & db = GeneHistory::getInstance();

    // Now see which mutation will happen.
#ifdef DEBUG
    if (num == 1)
#else
    if (random(0.0, 1.0) > 0.1)
#endif
    {
        // Create a HIDDEN neuron!
        node.type = HIDDEN;

        // First we need to see how many hidden nodes there are currently.
        int count = 0;
        for (int n = 0; n < nodeGenes.size(); ++n)
        {
            if (nodeGenes[n].type == HIDDEN)
            {
                ++count;
            }
        }

        // If we have less then or equal to five then the network is considered
        // too small. This could result in a repeating of adding multiple nodes
        // to one link causing a chaining effect. We want it to be random. So
        // we bias it towards the older links when it is too small.
        LinkGene link;
        int numTries = 20; // This will be used for only when the count is <= 5.
                           // This will make sure not to loop forever in trying
                           // to find a link.
        int index = 0;
        while (!found && numTries-- > 0)
        {
            int range = linkGenes.size() - 1;

            // Check the count to see if it is too small.
            if (count <= 5)
            {
                range -= sqrt(linkGenes.size());
            }

            // Now grab a random link.
            index = random(0, range);
            assert(index < linkGenes.size() && index > -1);

            link = linkGenes[index];

            // Now see if its an enabled link. It also cannot be a BIAS link or a recurrent link.
            if (link.enabled && nodeGenes[link.input].type != BIAS
                && !nodeGenes[link.input].recurrent)
            {
                found = true;
            }
        }

        if (found)
        {
            // Disable the link.
            linkGenes[index].enabled = false;

            // Now save the links to the VECTOR
            linkGenes.push_back(LinkGene(db.addNewLink(link.input, node.id), link.input, node.id, 1, true, MUTATE_NEURON1));
            linkGenes.push_back(LinkGene(db.addNewLink(node.id, link.output), node.id, link.output, link.weight, true, MUTATE_NEURON2));
        }
    }
    else
    {
        // Create a BIAS node!
        node.type = BIAS;
        int numTries = 10;

        // Loop until we find a node with no BIAS attached to it.
        NodeGene toNode;
        while (!found && numTries-- > 0)
        {
            // Grab the min and max.
            int min = (outputs + inputs) - 1;
            int max = nodeGenes.size() - 1;

            // If there are only inputs and outputs then we will grab a random output.
            if (min == max)
            {
                min = 0;
                max = outputs - 1;
            }

            // Grab a random hidden node
            int index = random(min, max);
            assert(index < nodeGenes.size() && index > -1);

            // Search through the LINKGENES to make sure that this node doesn't
            // already have a bias connected already.
            bool good = true;
            for (int l = 0; l < linkGenes.size() && good; ++l)
            {
                if (nodeGenes[index].id == linkGenes[l].output
                    && nodeGenes[linkGenes[l].input].type == BIAS)
                {
                    good = false;
                }
            }

            // We found a node with no BIAS.
            if (good)
            {
                found = true;
                toNode = nodeGenes[index];
            }
        }

        if (found)
        {
            linkGenes.push_back(LinkGene(db.addNewLink(node.id, toNode.id), node.id, toNode.id, random(0.0, 1.0), true, MUTATE_NEURON3));
        }
    }

    if (found) // We have found a link!
    {
        // Add the neuron to the database!
        db.addNewNeuron(node.id, node.type);

        // Finally save the new node to the VECTOR.
        nodeGenes.push_back(node);
    }

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
    int index = (linkGenes.size() == 1) ? 0 : random(0, linkGenes.size() - 1);

    // Now see if we need to remove the nodes that were connected by this link.
    int removeNode = linkGenes[index].input;
    int removeNode2 = linkGenes[index].output;

    // Remove the link.
    linkGenes.erase(linkGenes.begin() + index);

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
    for (int n = 0; n < nodeGenes.size(); ++n)
    {
        if ((nodeGenes[n].id == removeNode || nodeGenes[n].id == removeNode2) &&
            (nodeGenes[n].type == HIDDEN || nodeGenes[n].type == BIAS))
        {
            nodeGenes.erase(nodeGenes.begin() + n);
        }
    }

    return;
}

/***********************************************************************
* getLinksString
*   This will grab all the LINKGENES and produce a string. This string
*       be used to write the string to a file.
***********************************************************************/
string Genome::getLinksString() const
{
    string ids;     //
    string inputs;  //
    string outputs; // All these strings save an aspect of the GENOME.
    string weights; //
    string enables; //

    // Grab all the links and save them in the strings.
    for (int l = 0; l < linkGenes.size(); ++l)
    {
        ids += "Id: " + toString<int>(linkGenes[l].id) + " | ";
        inputs += "Input: " + toString<int>(linkGenes[l].input) + " | ";
        outputs += "Output: " + toString<int>(linkGenes[l].output) + " | ";
        weights += "Weight: " + toString<double>(linkGenes[l].weight) + " | ";

        string boolean = (linkGenes[l].enabled) ? "True" : "False";

        enables += "Enabled: " + boolean + " | ";
    }

    return ids + "\n" + inputs + "\n" + outputs + "\n" + weights + "\n" + enables + "\n";
}

/***********************************************************************
* getNodesString
*   This does the same exact thing as GETLINKSSTRING function but for the
*       nodes instead.
***********************************************************************/
string Genome::getNodesString() const
{
    string ids;        //
    string types;      // All these strings save an aspect of the GENOME.
    string recurrents; //
    string arrayType[4] = {"Sensor", "Hidden", "Output", "Bias"};

    for (int n = 0; n < nodeGenes.size(); ++n)
    {
        ids += "Id: " + toString<int>(nodeGenes[n].id) + " | ";
        types += "Type: " + arrayType[nodeGenes[n].type] + " | ";

        string boolean = (nodeGenes[n].recurrent) ? "True" : "False";

        recurrents += "Recurrent: " + boolean + " | ";
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
    while (lhsIter != linkGenes.end() || rhsIter != rhs.linkGenes.end())
    {
        LinkGene newLinkGene; // Create a gene.

        // First two conditions check if there is an excess or disjoint history
        // between the GENOMES. It will then grab that LINKGEN from them.
        if ((rhsIter == rhs.linkGenes.end() || lhsIter->id < rhsIter->id)
            && lhsIter != linkGenes.end())
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
    vector<NodeGene> childNodeGenes;
    vector<NodeGene> :: const_iterator iterLhs = nodeGenes.begin();
    vector<NodeGene> :: const_iterator iterRhs = rhs.nodeGenes.begin();

    while (iterLhs != nodeGenes.end() || iterRhs != rhs.nodeGenes.end())
    {
        NodeGene node;

        if ((iterRhs == rhs.nodeGenes.end() || iterLhs->id < iterRhs->id)
            && iterLhs != nodeGenes.end())
        {
            node = *iterLhs;
            ++iterLhs;
        }
        else if (iterLhs == nodeGenes.end() || iterRhs->id < iterLhs->id)
        {
            node = *iterRhs;
            ++iterRhs;
        }
        else
        {
            node = *iterLhs;

            if (iterRhs->recurrent || iterLhs->recurrent)
            {
                node.recurrent = true;
            }

            ++iterLhs;
            ++iterRhs;
        }

        childNodeGenes.push_back(node);
    }

    return Genome(childNodeGenes, childLinkGenes, inputs, outputs);
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
        if (rhsIter == rhs.linkGenes.end() && lhsIter != linkGenes.end()) // If one is done then we have excess.
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

    GeneHistory & db = GeneHistory::getInstance();

    assert(size > 0);
    // Finally compute the distance between the GENOMES.
    float distance = ((db.getC1() * excess) / size) + ((db.getC2() * disjoints) / size) + (db.getC3() * (weightDifference / matched));

    return distance;
}

/***********************************************************************
* mutateWeight
*   This will mutate the weights.
***********************************************************************/
void Genome::mutateWeight()
{
    for (int l = 0; l < linkGenes.size(); ++l)
    {
        float newWeight = linkGenes[l].weight * random(0.5, 1.5);

        if (newWeight > 8.0)
        {
            newWeight = 8.0;
        }
        else if (newWeight < -8.0)
        {
            newWeight = -8.0;
        }

        linkGenes[l].weight = newWeight;
    }

    return;
}

/***********************************************************************
* update
*   This will update the genome. It will also make sure that there are
*       no dead links that should not be there.
***********************************************************************/
void Genome::update()
{
    network.update(nodeGenes, linkGenes);
    ++age;

    return;
}

/***********************************************************************
* Operator =
*   This is the assignment operator.
***********************************************************************/
Genome & Genome::operator = (const Genome & rhs)
{
    nodeGenes = rhs.nodeGenes;
    linkGenes = rhs.linkGenes;
    age = rhs.age;
    fitness = rhs.fitness;
    adjustedFitness = rhs.adjustedFitness;
    inputs = rhs.inputs;
    outputs = rhs.outputs;
    id = rhs.id;

    return *this;
}

/***********************************************************************
* Operator <<
*   This will define the insertion operator.
***********************************************************************/
ostream & operator << (ostream & out, const Genome & genome)
{
    out << "Genome ID: " << genome.id << endl
        << "Fitness Score: " << genome.getFitness() << endl << endl
        << "Nodes:\n" << genome.getNodesString() << endl
        << "Links:\n" << genome.getLinksString() << endl;

    return out;
}