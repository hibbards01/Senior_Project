/***********************************************************************
* Program:
*   genome_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will test out the class GENOME.
***********************************************************************/

#ifndef GENOME_TEST_H
#define GENOME_TEST_H

#include "../genetic_algorithm/genome.h"
#include "../genetic_algorithm/defines.h"
#include "../genetic_algorithm/geneHistory.h"
#include <cmath>
using namespace std;

// For debugging purposes.
// To run debug code run in command line: g++ -D SHOW <file>
// This will show the results for the professor.
#ifdef SHOW
#define Show(x) x
#else
#define Show(x)
#endif

namespace {
    /****************************************************
    * NetworkTest
    *   This will test all the functions for the class
    *       GENOME.
    ****************************************************/
    class GenomeTest : public ::testing::Test
    {
    protected:
        virtual ~GenomeTest()
        {
            GeneHistory::getInstance().getInnovations().clear();
        }

        void buildGenome(vector<NodeGene> & nodes, vector<LinkGene> & links)
        {
            nodes.clear();
            links.clear();

            // First build all the nodes.
            nodes.push_back(NodeGene(0, OUTPUT));

            nodes.push_back(NodeGene(1, SENSOR));
            nodes.push_back(NodeGene(2, SENSOR));
            nodes.push_back(NodeGene(3, SENSOR));

            nodes.push_back(NodeGene(4, HIDDEN));
            nodes.push_back(NodeGene(5, HIDDEN));

            // Now build all the links.
            links.push_back(LinkGene(0, 1, 4, 0.8));
            links.push_back(LinkGene(2, 1, 5, 0.8, false));
            links.push_back(LinkGene(4, 2, 4, 0.8));
            links.push_back(LinkGene(6, 2, 5, 0.8));
            links.push_back(LinkGene(8, 3, 4, 0.8));
            links.push_back(LinkGene(10, 3, 5, 0.8));

            links.push_back(LinkGene(12, 4, 0, 0.5));
            links.push_back(LinkGene(14, 5, 0, 0.5));
        }

        void buildGenome2(vector<NodeGene> & nodes, vector<LinkGene> & links)
        {
            nodes.clear();
            links.clear();

            // First build all the nodes.
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
        }

        void buildGenome3(vector<NodeGene> & nodes, vector<LinkGene> & links)
        {
            nodes.clear();
            links.clear();

            // First build all the nodes.
            nodes.push_back(NodeGene(0, OUTPUT));

            nodes.push_back(NodeGene(1, SENSOR));
            nodes.push_back(NodeGene(2, SENSOR));
            nodes.push_back(NodeGene(3, SENSOR));

            nodes.push_back(NodeGene(4, HIDDEN, true));
            nodes.push_back(NodeGene(5, HIDDEN, true));
            nodes.push_back(NodeGene(6, HIDDEN));

            // Now build all the links.
            links.push_back(LinkGene(1, 1, 5, 0.8));
            links.push_back(LinkGene(2, 1, 5, 0.5));
            links.push_back(LinkGene(3, 2, 5, 0.8));
            links.push_back(LinkGene(5, 3, 5, 0.8));
            links.push_back(LinkGene(6, 2, 5, 0.5));
            links.push_back(LinkGene(10, 3, 5, 0.5));
            links.push_back(LinkGene(20, 1, 0, 0.8));
            links.push_back(LinkGene(21, 2, 0, 0.8, false));
            links.push_back(LinkGene(22, 3, 0, 0.8));
            links.push_back(LinkGene(26, 4, 2, 0.5));
            links.push_back(LinkGene(27, 5, 5, 0.5));
            links.push_back(LinkGene(28, 6, 0, 0.5));
        }
    };

    TEST_F(GenomeTest, Constructor)
    {
        Genome genome(2, 3);

        // Check the nodes first.
        EXPECT_EQ(5, genome.getNodeGenes().size());
        EXPECT_EQ(2, genome.getNodeGenes()[0].type);
        EXPECT_EQ(2, genome.getNodeGenes()[1].type);
        EXPECT_EQ(0, genome.getNodeGenes()[2].type);

        // Now check the links.
        EXPECT_EQ(6, genome.getLinkGenes().size());
        int index = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int o = 0; o < 2; ++o, ++index)
            {
                EXPECT_EQ(i + 2, genome.getLinkGenes()[index].input);
                EXPECT_EQ(o, genome.getLinkGenes()[index].output);
            }
        }

        EXPECT_EQ(2, genome.getOutputs());
        EXPECT_EQ(3, genome.getInputs());
        EXPECT_EQ(0, genome.getFitness());
        EXPECT_EQ(0, genome.getAdjustedFitness());
        EXPECT_EQ(0, genome.getAge());
    }

    TEST_F(GenomeTest, Constructor2)
    {
        Genome genome(5, 20);

        // Check the nodes first.
        EXPECT_EQ(25, genome.getNodeGenes().size());
        EXPECT_EQ(2, genome.getNodeGenes()[0].type);
        EXPECT_EQ(0, genome.getNodeGenes()[5].type);

        // Now check the links.
        EXPECT_EQ(100, genome.getLinkGenes().size());
        int index = 0;
        for (int i = 0; i < 20; ++i)
        {
            for (int o = 0; o < 5; ++o, ++index)
            {
                EXPECT_EQ(i + 5, genome.getLinkGenes()[index].input);
                EXPECT_EQ(o, genome.getLinkGenes()[index].output);
            }
        }
    }

    TEST_F(GenomeTest, NonDefaultConstructor)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;

        buildGenome(nodes, links);

        Genome genome(nodes, links, 3, 1);

        EXPECT_EQ(6, genome.getNodeGenes().size());
        EXPECT_EQ(8, genome.getLinkGenes().size());
        EXPECT_EQ(3, genome.getInputs());
        EXPECT_EQ(1, genome.getOutputs());
    }

    TEST_F(GenomeTest, MutateAddLink)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;

        buildGenome(nodes, links);

        Genome genome(nodes, links, 3, 1);

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        // First test out recurrent link on itself.
        genome.mutateAddLink(0);
        EXPECT_EQ(9, genome.getLinkGenes().size());
        EXPECT_EQ(4, genome.getLinkGenes()[8].input);
        EXPECT_EQ(4, genome.getLinkGenes()[8].output);

#ifdef SHOW
        cerr << "Added Recurrent Link:\n"
             << genome << endl;
#endif

        // Again!
        genome.mutateAddLink(0);
        EXPECT_EQ(10, genome.getLinkGenes().size());
        EXPECT_EQ(5, genome.getLinkGenes()[9].input);
        EXPECT_EQ(5, genome.getLinkGenes()[9].output);

#ifdef SHOW
        cerr << "Added another Recurrent Link:\n"
             << genome << endl;
#endif

        // Now test adding a feed forward link or recurrent link.
        buildGenome2(nodes, links);
        Genome test(nodes, links, 5, 2);
        test.update();

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        EXPECT_EQ(38, test.getLinkGenes().size());
        EXPECT_EQ(14, test.getNodeGenes().size());

        int linkSize = 38;

        for (int i = 0; i < 10; ++i)
        {
            test.mutateAddLink(1);
            test.update();
            EXPECT_EQ(linkSize + 1, test.getLinkGenes().size());

            LinkGene link = test.getLinkGenes()[linkSize++];

            // Make sure it did not fail any of the assumptions.
            bool boolean = (test.getNodeGenes()[link.input].type != 2) ? true : false;
            EXPECT_EQ(true, boolean);
            boolean = (test.getNodeGenes()[link.output].type != 3) ? true : false;
            EXPECT_EQ(true, boolean);
            EXPECT_EQ(true, link.input != link.output);

#ifdef SHOW
            cerr << "Genome After mutating a link:\n"
                 << genome << endl;
#endif
        }
    }

    TEST_F(GenomeTest, MutateAddNeuron)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;

        buildGenome2(nodes, links);

        Genome genome(nodes, links, 3, 1);

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        // Now test the mutation for a node
        EXPECT_EQ(14, genome.getNodeGenes().size());
        EXPECT_EQ(38, genome.getLinkGenes().size());

        // Test out a new hidden node.
        genome.mutateAddNeuron(1);
        EXPECT_EQ(15, genome.getNodeGenes().size());
        EXPECT_EQ(1, genome.getNodeGenes()[14].type);
        EXPECT_EQ(40, genome.getLinkGenes().size());

#ifdef SHOW
        cerr << "Genome after adding neuron:\n"
             << genome << endl;
#endif

        // Hurry and find the link that was disconnected.
        int input = genome.getLinkGenes()[38].input;
        int output = genome.getLinkGenes()[39].output;
        int found = -1;
        for (int l = 0; l < genome.getLinkGenes().size() && found == -1; ++l)
        {
            if (genome.getLinkGenes()[l].input == input && genome.getLinkGenes()[l].output == output)
            {
                found = l;
            }
        }

        bool good = (!genome.getLinkGenes()[found].enabled) ? true : false;
        EXPECT_EQ(true, good);
        EXPECT_EQ(1, genome.getLinkGenes()[38].weight);
        EXPECT_EQ(genome.getLinkGenes()[found].weight, genome.getLinkGenes()[39].weight);

        // Now try out the BIAS part.
        genome.mutateAddNeuron(0);
        EXPECT_EQ(16, genome.getNodeGenes().size());
        EXPECT_EQ(41, genome.getLinkGenes().size());
        EXPECT_EQ(15, genome.getLinkGenes()[40].input);
        EXPECT_EQ(3, genome.getNodeGenes()[15].type);

#ifdef SHOW
        cerr << "Genome After adding bias neuron:\n"
             << genome << endl;
#endif
    }

    TEST_F(GenomeTest, MutateEnableLink)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        nodes.push_back(NodeGene(0, OUTPUT));
        nodes.push_back(NodeGene(1, SENSOR));
        nodes.push_back(NodeGene(2, SENSOR));
        nodes.push_back(NodeGene(3, HIDDEN));
        links.push_back(LinkGene(0, 1, 3, 0.5));
        links.push_back(LinkGene(0, 2, 3, 0.5));
        links.push_back(LinkGene(0, 3, 0, 0.5));
        links.push_back(LinkGene(0, 1, 0, 0.5));
        links[3].enabled = false;
        Genome genome(nodes, links, 2, 1);

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        // Now test the function
        EXPECT_EQ(true, genome.mutateEnableLink());
        EXPECT_EQ(true, genome.getLinkGenes()[3].enabled);
        EXPECT_EQ(false, genome.mutateEnableLink());

#ifdef SHOW
        cerr << "Genome After enabling link:\n"
             << genome << endl;
#endif
    }

    TEST_F(GenomeTest, MutateRemoveLink)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        nodes.push_back(NodeGene(0, OUTPUT));
        nodes.push_back(NodeGene(1, SENSOR));
        nodes.push_back(NodeGene(2, SENSOR));
        nodes.push_back(NodeGene(3, HIDDEN));
        links.push_back(LinkGene(0, 1, 3, 0.5));
        links.push_back(LinkGene(0, 2, 3, 0.5));
        links.push_back(LinkGene(0, 3, 0, 0.5));
        Genome genome(nodes, links, 2, 1);

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        genome.mutateRemoveLink();
        EXPECT_EQ(2, genome.getLinkGenes().size());
        EXPECT_EQ(4, genome.getNodeGenes().size());

#ifdef SHOW
        cerr << "Genome After removing a link:\n"
             << genome << endl;
#endif

        genome.mutateRemoveLink();
        EXPECT_EQ(1, genome.getLinkGenes().size());
        EXPECT_EQ(4, genome.getNodeGenes().size());

#ifdef SHOW
        cerr << "Genome After removing a link:\n"
             << genome << endl;
#endif

        genome.mutateRemoveLink();
        EXPECT_EQ(0, genome.getLinkGenes().size());
        EXPECT_EQ(3, genome.getNodeGenes().size());

#ifdef SHOW
        cerr << "Genome After removing a link:\n"
             << genome << endl;
#endif
    }

    TEST_F(GenomeTest, MutateWeight)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        buildGenome(nodes, links);

        Genome genome(nodes, links, 3, 1);

#ifdef SHOW
        cerr << "Genome Before:\n"
             << genome << endl;
#endif

        genome.mutateWeight();

#ifdef SHOW
        cerr << "Genome After mutating weight:\n"
             << genome << endl;
#endif

        int count = 0;
        for (int l = 0; l < links.size(); ++l)
        {
            if (genome.getLinkGenes()[l].weight != links[l].weight)
            {
                ++count;
            }
        }

        EXPECT_EQ(1, count);
    }

    TEST_F(GenomeTest, Update)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        buildGenome(nodes, links);

        Genome genome(nodes, links, 3, 1);

        EXPECT_EQ(0, genome.getAge());
        EXPECT_EQ(0, genome.getNetwork().getSensors().size());
        EXPECT_EQ(0, genome.getNetwork().getHiddenNodes().size());
        EXPECT_EQ(0, genome.getNetwork().getOutputNodes().size());

        genome.update();

        EXPECT_EQ(1, genome.getAge());
        EXPECT_EQ(3, genome.getNetwork().getSensors().size());
        EXPECT_EQ(2, genome.getNetwork().getHiddenNodes().size());
        EXPECT_EQ(1, genome.getNetwork().getOutputNodes().size());
    }

    TEST_F(GenomeTest, ProduceChild)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        buildGenome(nodes, links);

        Genome leftParent(nodes, links, 3, 1);
        leftParent.setFitness(1);

#ifdef SHOW
        cerr << "Left Parent:\n"
             << leftParent << endl;
#endif

        buildGenome3(nodes, links);

        Genome rightParent(nodes, links, 3, 1);
        rightParent.setFitness(5);

#ifdef SHOW
        cerr << "Right Parent:\n"
             << rightParent << endl;
#endif

        Genome child = leftParent.produceChild(rightParent);

#ifdef SHOW
        cerr << "Child:\n"
             << child << endl;
#endif

        EXPECT_EQ(7, child.getNodeGenes().size());
        EXPECT_EQ(17, child.getLinkGenes().size());
        EXPECT_EQ(true, child.getNodeGenes()[4].recurrent);
        EXPECT_EQ(true, child.getNodeGenes()[5].recurrent);
        EXPECT_EQ(false, child.getNodeGenes()[6].recurrent);
        EXPECT_EQ(0, child.getLinkGenes()[0].id);
        EXPECT_EQ(28, child.getLinkGenes()[16].id);
        EXPECT_EQ(false, child.getLinkGenes()[12].enabled);
        EXPECT_EQ(true, child.getLinkGenes()[2].enabled);
    }

    TEST_F(GenomeTest, ComputeDistance)
    {
        vector<NodeGene> nodes;
        vector<LinkGene> links;
        buildGenome(nodes, links);

        Genome left(nodes, links, 3, 1);

        buildGenome3(nodes, links);

        Genome right(nodes, links, 3, 1);
        right.setFitness(5);

        float weightDifference = abs(left.getLinkGenes()[1].weight - right.getLinkGenes()[1].weight) +
                                 abs(left.getLinkGenes()[3].weight - right.getLinkGenes()[4].weight) +
                                 abs(left.getLinkGenes()[5].weight - right.getLinkGenes()[5].weight);

        float expected = ((1.0 * 6.0) / 12.0) + ((1.0 * 8.0) / 12.0) + (0.4 * (weightDifference / 3.0));
        float dist = left.computeDistance(right);

        // Precision is a problem to make them equal.
        double e = floor(expected * pow(10, 6)) / pow(10, 6);
        double d = floor(dist * pow(10, 6)) / pow(10, 6);

        EXPECT_EQ(e, d);
    }
}

#endif // GENOME_TEST_H