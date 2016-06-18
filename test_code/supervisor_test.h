/***********************************************************************
* Program:
*   supervisor_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will test the class SUPERVISOR
***********************************************************************/

#ifndef SUPERVISOR_TEST_H
#define SUPERVISOR_TEST_H

#include "../genetic_algorithm/supervisor.h"
#include <stdlib.h>
#include <fstream>

namespace {
    /****************************************************
    * SupervisorTest
    *   This class will test SUPERVISOR class.
    ****************************************************/
    class SupervisorTest : public ::testing::Test
    {
    protected:
    };

    TEST_F(SupervisorTest, Constructor)
    {
        Supervisor spv(100, 3, 5);
        EXPECT_EQ(1, spv.getSpecies().size());
        EXPECT_EQ(0, spv.getGeneration());
        EXPECT_EQ(0, spv.getNoImprovement());
        EXPECT_EQ(100, spv.getPopulation());
        EXPECT_EQ(0, spv.getOverallAverage());
    }

    TEST_F(SupervisorTest, WritePopulationToFile)
    {
        Supervisor spv(100, 3, 5);
        spv.writePopulationToFile();

        ifstream fin("../data/gen0/population_summary.txt");

        EXPECT_EQ(true, fin.good());

        fin.close();

        system("rm -rf ../data/gen0");
    }

    TEST_F(SupervisorTest, Update)
    {
        Supervisor spv(100, 3, 5);
        spv.update();

        EXPECT_EQ(1, spv.getGeneration());

        system("rm -rf ../data/gen0");
    }

    TEST_F(SupervisorTest, SetOverallAverage)
    {
        Supervisor spv(100, 3, 5);
        spv.setOverallAverage();

        EXPECT_EQ(0, spv.getOverallAverage());
        EXPECT_EQ(1, spv.getNoImprovement());
    }

    TEST_F(SupervisorTest, Epoch)
    {
        Supervisor spv(100, 3, 5);
        spv.epoch();               // This is the big function!

        EXPECT_EQ(1, spv.getGeneration());
        EXPECT_EQ(1, spv.getNoImprovement());
        EXPECT_EQ(0, spv.getOverallAverage());

        int total = 0;

        for (int s = 0; s < spv.getSpecies().size(); ++s)
        {
            total += spv.getSpecies()[s].getGenomes().size();
        }

        EXPECT_EQ(100, total);

        system("rm -rf ../data/gen0");

        // Run one more time to see if it still works!
        spv.epoch();

        EXPECT_EQ(2, spv.getGeneration());
        EXPECT_EQ(2, spv.getNoImprovement());
        EXPECT_EQ(0, spv.getOverallAverage());

        total = 0;

        for (int s = 0; s < spv.getSpecies().size(); ++s)
        {
            total += spv.getSpecies()[s].getGenomes().size();
        }

        EXPECT_EQ(100, total);

        system("rm -rf ../data/gen0");
    }
}

#endif // SUPERVISOR_TEST_H