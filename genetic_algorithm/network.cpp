/***********************************************************************
* Program:
*   network.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class NETWORK.
***********************************************************************/

#include "network.h"
#include "defines.h"
#include <execinfo.h>
#include <limits>
using namespace std;

/***********************************************************************
* feedForward
*   This will do the summations for all the nodes. The inputs will be
*       given by the simulator. After the feedForward is done it will
*       return the output for the SHIP.
***********************************************************************/
vector<double> Network::feedForward(const vector<int> & inputs)
{
    assert(inputs.size() == sensors.size()); // This better be the same.

    // First set all the sensor outputs to what was given by the params.
    for (int i = 0; i < sensors.size(); ++i)
    {
        sensors[i]->setOutput(inputs[i]);
    }

    // Now update all the hidden node's outputs.
    for (int i = 0; i < hiddenNodes.size(); ++i)
    {
        hiddenNodes[i]->update();
    }

    // Now grab all the outputs that are given from the network.
    vector<double> outputs;

    for (int i = 0; i < outputNodes.size(); ++i)
    {
        outputNodes[i]->update(); // First do the update.

        outputs.push_back(outputNodes[i]->getOutput()); // Now grab the output.
    }

    return outputs;
}

/***********************************************************************
* getNode
*   This will grab the node from the id that is given to it. This
*       function will search all the vectors until it has found the NODE.
*       If it gives an invalid id then it will return NULL.
***********************************************************************/
Node * Network::getNode(const int id)
{
    Node * node = NULL; // Initialize it to NULL. If not found then it will
                        // return a NULL.

    // Now loop through all the VECTORS and find the NODE.
    for (int i = 0; i < sensors.size() && node == NULL; ++i)
    {
        if (sensors[i]->getId() == id)
        {
            node = sensors[i];
        }
    }

    for (int i = 0; i < hiddenNodes.size() && node == NULL; ++i)
    {
        if (hiddenNodes[i]->getId() == id)
        {
            node = hiddenNodes[i];
        }
    }

    for (int i = 0; i < outputNodes.size() && node == NULL; ++i)
    {
        if (outputNodes[i]->getId() == id)
        {
            node = outputNodes[i];
        }
    }

    return node;
}

/***********************************************************************
* update
*   This will be given the NODES and LINKS that are needed for the
*       NETWORK from the class GENOME. It will delete the old NETWORK
*       and then rebuild everything based off what it is given.
***********************************************************************/
void Network::update(const vector<NodeGene> & nodeGenes, const vector<LinkGene> & linkGenes)
{
    deleteNetwork(); // Erase everything and rebuild everything.

    // First create all the nodes.
    for (int i = 0; i < nodeGenes.size(); ++i)
    {
        int type = nodeGenes[i].type;
        assert(type < 4); // We only have three types so this better pass.

        Node * node = new Node(nodeGenes[i].id, type); // Now create a new node

        // Now insert the node in the proper vector
        if (type == SENSOR)
        {
            sensors.push_back(node);
        }
        else if (type == HIDDEN || type == BIAS)
        {
            // Set the output for bias nodes to -1
            if (type == BIAS)
            {
                node->setOutput(-1);
            }

            hiddenNodes.push_back(node);
        }
        else
        {
            outputNodes.push_back(node);
        }
    }

    // Now link all the nodes together.
    for (int i = 0; i < linkGenes.size(); ++i)
    {
        // First check to see if the link is enabled, if not don't add it.
        if (linkGenes[i].enabled)
        {
            // Now grab both the from and to nodes
            Node * from = getNode(linkGenes[i].input);
            Node * to   = getNode(linkGenes[i].output);

            // Either of them better not be NULL
            assert(from != NULL);
            assert(to != NULL);


            // Finally link them together with the weight.
            to->addInput(from, linkGenes[i].weight);
        }
    }

    return;
}

/***********************************************************************
* deleteNetwork
*   This will delete all the nodes that have been allocated.
***********************************************************************/
void Network::deleteNetwork()
{
    // First delete all the node pointers.
    for (int i = 0; i < sensors.size(); ++i)
    {
        delete sensors[i];
    }

    for (int i = 0; i < hiddenNodes.size(); ++i)
    {
        delete hiddenNodes[i];
    }

    for (int i = 0; i < outputNodes.size(); ++i)
    {
        delete outputNodes[i];
    }

    // Finally clear them from the VECTORS
    sensors.clear();
    hiddenNodes.clear();
    outputNodes.clear();

    return;
}

/***********************************************************************
* writeNodes
*   This will write the nodes to the file.
***********************************************************************/
void Network::writeNodes(ofstream & fout, Node * node)
{
    for (int i = 0; i < node->getInputs().size(); ++i)
    {
        // Now write the links to the file with their weight
        fout << node->getInputs()[i].input->getId() << ","
             << node->getId() << ","
             << node->getInputs()[i].weight << endl;
    }

    return;
}

/***********************************************************************
* writeNetworkToFile
*   This will be given a generation and it will save the network to a
*       that will be saved in the data/ folder.
***********************************************************************/
void Network::writeNetworkToFile(const int id, const int gen)
{
    // Create the file name
    string file = "../data/gen" + toString<int>(gen) + "/network/network" + toString<int>(id) + ".txt";

    // Start the process of writing to a file.
    ofstream fout(file.c_str());

    // Make sure it was able to create a new file
    if (fout.fail())
    {
        // If not output an error
        cout << "ERROR Could not write network to file: " << file << endl;
    }
    else
    {
        // Write the title.
        fout << "Genome Network: " << id << endl;

        // Now write all the nodes to the file.
        for (int n = 0; n < hiddenNodes.size(); ++n)
        {
            writeNodes(fout, hiddenNodes[n]);
        }

        for (int n = 0; n < outputNodes.size(); ++n)
        {
            writeNodes(fout, outputNodes[n]);
        }
    }

    fout.close(); // Always close the file.

    return;
}

/***********************************************************************
* getShortestPath
*   This will find the shortest path that will be given from the ID. It
*       will use the function FINDPATHS to grab all the paths for that
*       node and will then find which one is the shortest path from
*       SENSORS to this NODE.
***********************************************************************/
int Network::getShortestPath(int id)
{
    vector<int> paths; // This will hold all the paths that the node can have.
    vector<int> ids;   // This will hold all the ids that we have done. This
                       // mainly makes sure that we don't do a recurrent link.
                       // and have an infinite loop.

    Node * node = getNode(id); // Grab the node that we want to grab the
                               // shortest path for.

    int shortest = -1;
    if (node != NULL)
    {
        findPaths(node, ids, 0, paths); // Now find all the paths!

        // Make this the highest value.
        shortest = (paths.size() == 0) ? 0 : numeric_limits<int>::max();

        // Finally grab the shortest distance.
        for (int i = 0; i < paths.size(); ++i)
        {
            if (paths[i] < shortest)
            {
                shortest = paths[i];
            }
        }
    }

    return shortest;
}

/***********************************************************************
* findPaths
*   This one will grab all the number of counts it takes to reach a
*       SENSOR for any path it can take from the node that is given. Once
*       all paths are found it will then quit. The variable PATHS is
*       what the function GETSHORTESTPATH will use to find the path that
*       is shortest.
***********************************************************************/
int Network::findPaths(Node * node, vector<int> ids, int count, vector<int> & paths)
{
    ids.push_back(node->getId()); // Insert the id into the vector.

    if (node->getType() != SENSOR && node->getType() != BIAS)
    {
        // Now loop through that node's inputs.
        for (int i = 0; i < node->getInputs().size(); ++i)
        {
            Node * input = node->getInputs()[i].input;

            // See if this input has been done before
            bool found = false;
            for (int id = 0; id < ids.size() && !found; ++id)
            {
                // If so then set found to true.
                if (ids[id] == input->getId())
                {
                    found = true;
                }
            }

            int finalCount = count; // This will grab the count when a path
                                    // is finished.

            // Only do the inputs that we have not done before. This makes
            // sure that recurrent links will not cause an infinite recursive loop.
            if (!found)
            {
                finalCount = findPaths(input, ids, count + 1, paths);
            }

            // Now see if the input is a sensor, if so then save the count. A path
            // has been found for one route.
            if (input->getType() == SENSOR || input->getType() == BIAS)
            {
                paths.push_back(finalCount);
            }
        }
    }

    return count;
}