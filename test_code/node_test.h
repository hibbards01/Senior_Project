/***********************************************************************
* Program:
*   node_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This includes all the tests for the class NODE and LINK.
***********************************************************************/

#include "../genetic_algorithm/node.h"

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
}