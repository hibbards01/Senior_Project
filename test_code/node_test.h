/***********************************************************************
* Program:
*   node_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This includes all the tests for the class NODE and LINK.
***********************************************************************/

#include "../genetic_algorithm/node.h"
#include <math.h>

namespace {
    /****************************************************
    * NodeTest
    *   This will do all the set up for the tests. It will
    *       also make sure to delete the pointers.
    ****************************************************/
    class NodeTest : public ::testing::Test {
    protected:
        NodeTest()
        {
            node = new Node(0, 0);
        }

        virtual ~NodeTest()
        {
            delete node;
        }

        Node * node; // This will be used for the tests
    };

    TEST_F(NodeTest, Constructor)
    {
        EXPECT_EQ(0, node->getInputs().size());
        EXPECT_EQ(0, node->getId());
        EXPECT_EQ(0, node->getType());
        EXPECT_EQ(0, node->getOutput());
    }

    TEST_F(NodeTest, AddInput)
    {
        // Create a node and add it to the input
        Node * test = new Node(1, 2);
        int * addr = (int *)test;

        node->addInput(test, -1);

        // Make sure that everything worked
        EXPECT_EQ(1, node->getInputs().size());
        EXPECT_EQ(1, node->getInputs()[0].input->getId());
        EXPECT_EQ(2, node->getInputs()[0].input->getType());
        EXPECT_EQ(0, node->getInputs()[0].input->getOutput());
        EXPECT_EQ(-1, node->getInputs()[0].weight);
        EXPECT_EQ(addr, (int *)node->getInputs()[0].input);

        delete test;
    }

    TEST_F(NodeTest, DeleteLinks)
    {
        // Add nodes. Now delete them
        Node * test = new Node(1, 2);
        node->addInput(test, -1);

        node->addInput(node, -1);

        EXPECT_EQ(2, node->getInputs().size());
        EXPECT_EQ(node, node->getInputs()[1].input);

        // Delete the links
        node->deleteLinks();

        EXPECT_EQ(0, node->getInputs().size());

        delete test;
    }

    TEST_F(NodeTest, Update)
    {
        // Add some nodes
        Node * test = new Node(1, 2);
        Node * test2 = new Node(2, 2);
        Node * test3 = new Node(3, 2);
        // Set the outputs
        test->setOutput(0.5);
        test2->setOutput(1);
        test3->setOutput(0.75);
        // Finally add them
        node->addInput(test, 1);
        node->addInput(test2, -1);
        node->addInput(test3, 0.5);

        // Make sure it worked
        EXPECT_EQ(3, node->getInputs().size());

        // Now do the update
        node->update();

        double sum = (.5 * 1) + (1 * -1) + (.75 * 0.5);
        double expected = 1 / (1 + exp(-sum));
        EXPECT_EQ(expected, node->getOutput());

        delete test;
        delete test2;
        delete test3;
    }
}