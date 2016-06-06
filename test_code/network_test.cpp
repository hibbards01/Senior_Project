/***********************************************************************
* Program:
*   node_test.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will test the class NODE from the genetic_algorithm folder.
***********************************************************************/
#include <iostream>
#include "../genetic_algorithm/network.h"
#include "../genetic_algorithm/defines.h"
using namespace std;

/***********************************************************************
* buildNetwork
***********************************************************************/
void buildNetwork(Network & network)
{
    // First build all the nodes.
    std::vector<NodeGene> nodes;
    nodes.push_back(NodeGene(0, OUTPUT));
    nodes.push_back(NodeGene(1, OUTPUT));

    nodes.push_back(NodeGene(2, SENSOR));
    nodes.push_back(NodeGene(3, SENSOR));
    nodes.push_back(NodeGene(4, SENSOR));
    nodes.push_back(NodeGene(5, SENSOR));
    nodes.push_back(NodeGene(6, SENSOR));

    nodes.push_back(NodeGene(7, HIDDEN));
    nodes.push_back(NodeGene(8, HIDDEN));
    nodes.push_back(NodeGene(9, HIDDEN));
    nodes.push_back(NodeGene(10, HIDDEN));

    nodes.push_back(NodeGene(11, HIDDEN));
    nodes.push_back(NodeGene(12, HIDDEN));
    nodes.push_back(NodeGene(13, HIDDEN));


    // Now build all the links.
    std::vector<LinkGene> links;

    // Start the first layer...
    links.push_back(LinkGene(0, 2, 7, 0.5));
    links.push_back(LinkGene(1, 3, 7, 0.5));
    links.push_back(LinkGene(2, 4, 7, 0.5));
    links.push_back(LinkGene(3, 5, 7, 0.5));
    links.push_back(LinkGene(4, 6, 7, 0.5));

    links.push_back(LinkGene(5, 2, 8, 0.25));
    links.push_back(LinkGene(6, 3, 8, 0.25));
    links.push_back(LinkGene(7, 4, 8, 0.25));
    links.push_back(LinkGene(8, 5, 8, 0.25));
    links.push_back(LinkGene(9, 6, 8, 0.25));

    links.push_back(LinkGene(10, 2, 9, 0.3));
    links.push_back(LinkGene(11, 3, 9, 0.3));
    links.push_back(LinkGene(12, 4, 9, 0.3));
    links.push_back(LinkGene(13, 5, 9, 0.3));
    links.push_back(LinkGene(14, 6, 9, 0.3));

    links.push_back(LinkGene(15, 2, 10, 0.75));
    links.push_back(LinkGene(16, 3, 10, 0.75));
    links.push_back(LinkGene(17, 4, 10, 0.75));
    links.push_back(LinkGene(18, 5, 10, 0.75));
    links.push_back(LinkGene(19, 6, 10, 0.75));

    // Now the second layer...
    links.push_back(LinkGene(20, 7, 11, 0.35));
    links.push_back(LinkGene(21, 8, 11, 0.35));
    links.push_back(LinkGene(22, 9, 11, 0.35));
    links.push_back(LinkGene(23, 10, 11, 0.35));

    links.push_back(LinkGene(24, 7, 12, 0.45));
    links.push_back(LinkGene(25, 8, 12, 0.45));
    links.push_back(LinkGene(26, 9, 12, 0.45));
    links.push_back(LinkGene(27, 10, 12, 0.45));

    links.push_back(LinkGene(28, 7, 13, 0.67));
    links.push_back(LinkGene(29, 8, 13, 0.67));
    links.push_back(LinkGene(30, 9, 13, 0.67));
    links.push_back(LinkGene(31, 10, 13, 0.67));

    // Finally the last links!!!
    links.push_back(LinkGene(32, 11, 0, 1));
    links.push_back(LinkGene(33, 12, 0, 1));
    links.push_back(LinkGene(34, 13, 0, 1));

    links.push_back(LinkGene(35, 11, 1, 0.86));
    links.push_back(LinkGene(36, 12, 1, 0.86));
    links.push_back(LinkGene(37, 13, 1, 0.86));

    // Recurrent link
    links.push_back(LinkGene(38, 13, 13, 0.8));
    links.push_back(LinkGene(39, 11, 8, 0.15));

    // Finally build the network
    network.update(nodes, links);
    return;
}

int main(int argc, char **argv) {
    Network network;
    buildNetwork(network);

    int num = network.getShortestPath(0);

    return 0;
}