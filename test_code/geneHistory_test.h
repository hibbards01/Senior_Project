/***********************************************************************
* Program:
*   geneHistory_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will test the class GENEHISTORY.
***********************************************************************/

#ifndef GENEHISTORY_TEST_H
#define GENEHISTORY_TEST_H

GeneHistory & history = GeneHistory::getInstance();

namespace {
    /****************************************************
    * GeneHistoryTest
    *   This will test the class GENOME.
    ****************************************************/
    class GeneHistoryTest : public ::testing::Test
    {
    protected:
    };

    TEST_F(GeneHistoryTest, Constructor)
    {
        history.getInnovations().clear();
        EXPECT_EQ(0, history.getInnovations().size());
    }

    TEST_F(GeneHistoryTest, AddNewNeuron)
    {
        history.addNewNeuron(0, 0);

        EXPECT_EQ(1, history.getInnovations().size());

        history.addNewNeuron(0, 0);

        EXPECT_EQ(1, history.getInnovations().size());
    }

    TEST_F(GeneHistoryTest, AddNewLink)
    {
        EXPECT_EQ(1, history.getInnovations().size());

        history.addNewLink(1, 0);

        EXPECT_EQ(2, history.getInnovations().size());

        history.addNewLink(1, 0);

        EXPECT_EQ(2, history.getInnovations().size());
    }
}

#endif // GENEHISTORY_TEST_H