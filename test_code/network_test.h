/***********************************************************************
* Program:
*   network_test.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will test all the functions within the NETWORK class.
***********************************************************************/

#ifndef NETWORK_TEST_H
#define NETWORK_TEST_H

#include "../genetic_algorithm/network.h"
#include "../genetic_algorithm/defines.h"
#include <stdlib.h>
#include <fstream>
#include <math.h>
using namespace std;

namespace
{
    /****************************************************
    * NetworkTest
    *   This will test all the functions for the class
    *       NETWORK. This class will build a network
    *       and then delete the network once it is finished.
    ****************************************************/
    class NetworkTest : public ::testing::Test
    {
    protected:
        virtual ~NetworkTest()
        {
            network.deleteNetwork();
        }

        // This will help build the network.
        void buildNetwork()
        {
            // First build all the nodes.
            vector<NodeGene> nodes;
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
            vector<LinkGene> links;

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
        }

        Network network; // This will be used for all the tests.
    };

    TEST_F(NetworkTest, Constructor)
    {
        EXPECT_EQ(0, network.getSensors().size());
        EXPECT_EQ(0, network.getHiddenNodes().size());
        EXPECT_EQ(0, network.getOutputNodes().size());
    }

    TEST_F(NetworkTest, Update)
    {
        buildNetwork(); // Test the update!

        EXPECT_EQ(5, network.getSensors().size());
        EXPECT_EQ(7, network.getHiddenNodes().size());
        EXPECT_EQ(2, network.getOutputNodes().size());

        // Now test all the links and their input sizes!
        for (int i = 0; i < network.getSensors().size(); ++i)
        {
            Node * node = network.getSensors()[i];

            EXPECT_EQ(0, node->getInputs().size());
        }

        for (int i = 0; i < network.getHiddenNodes().size(); ++i)
        {
            Node * node = network.getHiddenNodes()[i];

            // I only have to do this because there are two layers saved
            // and some nodes of a recurrent link.
            int size = 5;
            if (i == 1)
            {
                size = 6;
            }
            else if (i == 6)
            {
                size = 5;
            }
            else if (i > 3)
            {
                size = 4;
            }

            EXPECT_EQ(size, node->getInputs().size());

            int id = 7;
            if (i < 4)
            {
                id = 2;
            }
            for (int l = 0; l < node->getInputs().size(); ++l, ++id)
            {
                // These are for the recurrent links.
                if (l == 5)
                {
                    id = 11;
                }
                else if (i == 6 && l == 4)
                {
                    id = 13;
                }

                EXPECT_EQ(id, node->getInputs()[l].input->getId());
            }
        }

        for (int i = 0; i < network.getOutputNodes().size(); ++i)
        {
            Node * node = network.getOutputNodes()[i];

            EXPECT_EQ(3, node->getInputs().size());

            int id = 11;
            for (int l = 0; l < node->getInputs().size(); ++l, ++id)
            {
                EXPECT_EQ(id, node->getInputs()[l].input->getId());
            }
        }
    }

    TEST_F(NetworkTest, DeleteNetwork)
    {
        buildNetwork(); // Test the update!

        EXPECT_EQ(5, network.getSensors().size());
        EXPECT_EQ(7, network.getHiddenNodes().size());
        EXPECT_EQ(2, network.getOutputNodes().size());

        network.deleteNetwork(); // Delete the network.

        EXPECT_EQ(0, network.getSensors().size());
        EXPECT_EQ(0, network.getHiddenNodes().size());
        EXPECT_EQ(0, network.getOutputNodes().size());
    }

    TEST_F(NetworkTest, FeedForward)
    {
        buildNetwork(); // Build the network.

        // Create the inputs and add it to the vector.
        vector<double> inputs;
        for (int i = 0; i < 5; ++i)
        {
            inputs.push_back(1);
        }

        // Now feed forward the inputs
        vector<double> results;
        results = network.feedForward(inputs);

        // Check all the outputs the nodes are giving...
        // First the Sensors
        for (int i = 0; i < network.getSensors().size(); ++i)
        {
            EXPECT_EQ(1, network.getSensors()[i]->getOutput());
        }

        // Now for the hidden nodes.
        double outputs[7] = {0, 0, 0, 0, 0, 0, 0};
        double weights[7] = {0.5, 0.25, 0.3, 0.75, 0.35, 0.45, 0.67};

        for (int i = 0; i < network.getHiddenNodes().size(); ++i)
        {
            double summation = 0;
            if (i < 4)
            {
                summation = (1 * weights[i]) + (1 * weights[i]) + (1 * weights[i]) + (1 * weights[i]) + (1 * weights[i]);
            }
            else
            {
                summation = (outputs[0] * weights[i]) + (outputs[1] * weights[i]) + (outputs[2] * weights[i]) + (outputs[3] * weights[i]);
            }

            double output = 1 / (1 + exp(-summation));
            outputs[i] = output;

            // Had to do this because of precision problems.
            output = floor(output * pow(10, 6)) / pow(10, 6);
            double networkOutput = floor(network.getHiddenNodes()[i]->getOutput() * pow(10, 6)) / pow(10, 6);

            EXPECT_EQ(output, networkOutput);
        }

        // Finally the outputs!
        weights[0] = 1;
        weights[1] = 0.86;

        EXPECT_EQ(2, results.size());

        for (int i = 0; i < results.size(); ++i)
        {
            double summation = (outputs[4] * weights[i]) + (outputs[5] * weights[i]) + (outputs[6] * weights[i]);
            double output = 1 / (1 + exp(-summation));

            // Had to do this because of precision problems.
            output = floor(output * pow(10, 6)) / pow(10, 6);
            double networkOutput = floor(results[i] * pow(10, 6)) / pow(10, 6);

            EXPECT_EQ(output, networkOutput);
        }
    }

    TEST_F(NetworkTest, FeedForward2Time)
    {
        buildNetwork(); // Build the network.

        // Create the inputs and add it to the vector.
        vector<double> inputs;
        for (int i = 0; i < 5; ++i)
        {
            inputs.push_back(1);
        }

        // Now feed forward the inputs
        vector<double> results;
        results = network.feedForward(inputs);

        // Hurry and save two outputs. These ones are the recursive ones.
        double recursiveOutputs[2];

        Node * node = network.getHiddenNodes()[4];
        EXPECT_EQ(11, node->getId());
        recursiveOutputs[0] = node->getOutput();

        node = network.getHiddenNodes()[6];
        EXPECT_EQ(13, node->getId());
        recursiveOutputs[1] = node->getOutput();

        // Feed forward one more time!
        for (int i = 0; i < 5; ++i)
        {
            inputs[i] = 0.5;
        }
        results = network.feedForward(inputs);

        // Finally check all the outputs again!
        // First the Sensors
        for (int i = 0; i < network.getSensors().size(); ++i)
        {
            EXPECT_EQ(0.5, network.getSensors()[i]->getOutput());
        }

        // Now for the hidden nodes.
        double outputs[7] = {0, 0, 0, 0, 0, 0, 0};
        double weights[7] = {0.5, 0.25, 0.3, 0.75, 0.35, 0.45, 0.67};

        for (int i = 0; i < network.getHiddenNodes().size(); ++i)
        {
            // Now to see if it has a recursive node
            double recursive = 0;
            if (i == 1)
            {
                recursive = recursiveOutputs[0];
            }
            else if (i == 6)
            {
                recursive = recursiveOutputs[1];
            }

            double summation = 0;
            if (i < 4)
            {
                summation = (0.5 * weights[i]) + (0.5 * weights[i]) + (0.5 * weights[i]) + (0.5 * weights[i]) + (0.5 * weights[i]) + (recursive * 0.15);
            }
            else
            {
                summation = (outputs[0] * weights[i]) + (outputs[1] * weights[i]) + (outputs[2] * weights[i]) + (outputs[3] * weights[i]) + (recursive * 0.8);
            }

            double output = 1 / (1 + exp(-summation));
            outputs[i] = output;

            // Had to do this because of precision problems.
            output = floor(output * pow(10, 6)) / pow(10, 6);
            double networkOutput = floor(network.getHiddenNodes()[i]->getOutput() * pow(10, 6)) / pow(10, 6);

            EXPECT_EQ(output, networkOutput);
        }

        // Finally the outputs!
        weights[0] = 1;
        weights[1] = 0.86;

        EXPECT_EQ(2, results.size());

        for (int i = 0; i < results.size(); ++i)
        {
            double summation = (outputs[4] * weights[i]) + (outputs[5] * weights[i]) + (outputs[6] * weights[i]);
            double output = 1 / (1 + exp(-summation));

            // Had to do this because of precision problems.
            output = floor(output * pow(10, 6)) / pow(10, 6);
            double networkOutput = floor(results[i] * pow(10, 6)) / pow(10, 6);

            EXPECT_EQ(output, networkOutput);
        }
    }

    TEST_F(NetworkTest, GetNode)
    {
        buildNetwork(); // Build the network!

        // Now see that the GETNODE function is working.
        for (int i = 0; i < 14; ++i)
        {
            Node * node = network.getNode(i);
            EXPECT_EQ(i, node->getId());
        }

        // Now make sure it returns null when there is an invalid id.
        EXPECT_EQ(NULL, network.getNode(14));
        EXPECT_EQ(NULL, network.getNode(-1));
    }

    TEST_F(NetworkTest, WriteNetworkToFile)
    {
        buildNetwork(); // Build the network.

        system("mkdir ../data/gen1");
        system("mkdir ../data/gen1/network");

        // Now write it to a file.
        network.writeNetworkToFile(1, 1);

        ifstream fin("../data/gen1/network/network1.txt");

        ASSERT_TRUE(fin.good());

        fin.close();

        // Now clean up the system
        system("rm -rf ../data/gen1");
    }

    TEST_F(NetworkTest, GetShortestPath)
    {
        buildNetwork(); // Build the network!

        // Finally test the function.
        EXPECT_EQ(3, network.getShortestPath(0));
        EXPECT_EQ(2, network.getShortestPath(13));
        EXPECT_EQ(1, network.getShortestPath(8));
        EXPECT_EQ(0, network.getShortestPath(2));
        EXPECT_EQ(-1, network.getShortestPath(14));
        EXPECT_EQ(-1, network.getShortestPath(-1));
    }

    TEST_F(NetworkTest, Bias)
    {
        // Create nodes
        vector<NodeGene> nodes;
        nodes.push_back(NodeGene(0, OUTPUT));
        nodes.push_back(NodeGene(1, SENSOR));
        nodes.push_back(NodeGene(2, SENSOR));
        nodes.push_back(NodeGene(3, HIDDEN));
        nodes.push_back(NodeGene(4, BIAS));

        // Now links
        vector<LinkGene> links;
        links.push_back(LinkGene(0, 1, 3, 0.5));
        links.push_back(LinkGene(1, 2, 3, 0.25));
        links.push_back(LinkGene(2, 4, 3, 0.98));
        links.push_back(LinkGene(3, 3, 0, 0.1));

        // Now build the network
        network.update(nodes, links);

        // Create the inputs
        vector<double> inputs;
        inputs.push_back(1);
        inputs.push_back(1);

        // Now do the feedForward
        vector<double> results = network.feedForward(inputs);

        // Finally test the output
        EXPECT_EQ(1, results.size());

        // Do the hidden summation
        double summation = (1 * 0.5) + (1 * 0.25) + (-1.0 * 0.98);
        double output = 1 / (1 + exp(-summation));

        // Now the output summation
        summation = output * 0.1;
        output = 1 / (1 + exp(-summation));

        // Had to do this because of precision problems.
        output = floor(output * pow(10, 6)) / pow(10, 6);
        double networkOutput = floor(results[0] * pow(10, 6)) / pow(10, 6);

        EXPECT_EQ(output, networkOutput);
    }
}

#endif // NETWORK_TEST_H