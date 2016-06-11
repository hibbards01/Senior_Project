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
#include "../genetic_algorithm/geneHistory.h"
#include "../genetic_algorithm/defines.h"
using namespace std;

namespace {
    /****************************************************
    * NetworkTest
    *   This will test all the functions for the class
    *       NETWORK. This class will build a network
    *       and then delete the network once it is finished.
    ****************************************************/
    class GenomeTest : public ::testing::Test
    {
    protected:
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
            links.push_back(LinkGene(1, 1, 5, 0.8));
            links.push_back(LinkGene(2, 2, 4, 0.8));
            links.push_back(LinkGene(3, 2, 5, 0.8));
            links.push_back(LinkGene(4, 3, 4, 0.8));
            links.push_back(LinkGene(5, 3, 5, 0.8));

            links.push_back(LinkGene(6, 4, 0, 0.5));
            links.push_back(LinkGene(7, 5, 0, 0.5));
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

        // First test out recurrent link on itself.
        genome.mutateAddLink(0);
        EXPECT_EQ(9, genome.getLinkGenes().size());
        EXPECT_EQ(4, genome.getLinkGenes()[8].input);
        EXPECT_EQ(4, genome.getLinkGenes()[8].output);

        // Again!
        genome.mutateAddLink(0);
        EXPECT_EQ(10, genome.getLinkGenes().size());
        EXPECT_EQ(5, genome.getLinkGenes()[9].input);
        EXPECT_EQ(5, genome.getLinkGenes()[9].output);

        // Now test adding a feed forward link or recurrent link.
        buildGenome2(nodes, links);
        Genome test(nodes, links, 5, 2);
        test.update();

        EXPECT_EQ(38, test.getLinkGenes().size());
        EXPECT_EQ(14, test.getNodeGenes().size());

        int linkSize = 38;

        for (int i = 0; i < 10; ++i)
        {
            test.mutateAddLink(1);
            test.update();
            EXPECT_EQ(linkSize + 1, test.getLinkGenes().size());

            LinkGene link = test.getLinkGenes()[linkSize];

            // Make sure it did not fail any of the assumptions.
            bool boolean = (test.getNodeGenes()[link.input].type != 2) ? true : false;
            EXPECT_EQ(true, boolean);
            boolean = (test.getNodeGenes()[link.output].type != 3) ? true : false;
            EXPECT_EQ(true, boolean);
            EXPECT_EQ(true, link.input != link.output);

            ++linkSize;
        }
    }
}

#endif // GENOME_TEST_H