/***********************************************************************
* Program:
*   network.h
* Author:
*   Samuel Hibbard
* Summary:
*   This holds the network of what the GENOME gives it. This class
*       is the main thing that controls the SHIP within the simulator.
***********************************************************************/

#ifndef NETWORK_H
#define NETWORK_H

#include "node.h"
#include "genes.h"
#include <vector>
#include <fstream>

/***********************************************************************
* Network
*   This class uses the NODE class in order to build the network. It
*       will make sure that the nodes are created and deleted once the
*       network is finished or updated by GENOME.
***********************************************************************/
class Network
{
public:
    //
    // Constructors
    //
    Network() : sensors(), hiddenNodes(), outputNodes() {}
    ~Network() { deleteNetwork(); }

    //
    // Methods
    //

    // FeedForward will be the one that does the summations of all the nodes
    // once it is finished it will then return the outputs that the network gave.
    std::vector<double> feedForward(const std::vector<double> & inputs);

    // This updates the network.
    void update(const std::vector<NodeGene> & nodeGenes, const std::vector<LinkGene> & linkGenes);

    // This writes the network to a file.
    void writeNetworkToFile(const int id, const int gen);

    Node * getNode(const int id);           // This grabs the node with the id given.
    void deleteNetwork();                   // This deletes the nodes.
    int getShortestPath(int id);            // This finds the shortest path from a node.

    //
    // Getters
    //
    std::vector<Node *> getSensors()     const { return sensors;     }
    std::vector<Node *> getHiddenNodes() const { return hiddenNodes; }
    std::vector<Node *> getOutputNodes() const { return outputNodes; }
private:
    std::vector<Node *> sensors;     // This holds the sensors that will be given to
                                     // from the game.
    std::vector<Node *> hiddenNodes; // These are the nodes that are within the network.
    std::vector<Node *> outputNodes; // These nodes are the results after all the nodes
                                     // have given there output.
    void writeNodes(std::ofstream & fout, Node * node); // This will write the nodes to the file.
    int findPaths(Node * node,                          // This finds the paths for a given node.
                std::vector<int> ids,
                int count,
                std::vector<int> & paths);
};

#endif // NETWORK_H