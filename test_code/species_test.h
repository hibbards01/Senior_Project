/***********************************************************************
* Program:
*   species_test.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will test the class SPECIES.
***********************************************************************/

#ifndef SPECIES_TEST_H
#define SPECIES_TEST_H

#include "../genetic_algorithm/species.h"
#include <stdlib.h>
#include <fstream>

namespace {
    /****************************************************
    * SpeciesTest
    *   This will be the class that will test the SPECIES
    *       class.
    ****************************************************/
    class SpeciesTest : public ::testing::Test
    {
    protected:
        virtual ~SpeciesTest()
        {
            GeneHistory::getInstance().getInnovations().clear();
        }
    };

    TEST_F(SpeciesTest, Constructor)
    {
        Species species(100, 3, 20);
        EXPECT_EQ(0, species.getAge());
        EXPECT_EQ(0, species.getNoImprovement());
        EXPECT_EQ(0, species.getAverageFitness());
        EXPECT_EQ(100, species.getGenomes().size());
    }

    TEST_F(SpeciesTest, GetAverageFitness)
    {
        Species species(50, 3, 5);

        float average = 0;
        for (int g = 0; g < species.getGenomes().size(); ++g)
        {
            average += 0.5;
            species.getGenomes()[g].setFitness(0.5);
        }

        average /= species.getGenomes().size();

        EXPECT_EQ(average, species.getAverageFitness());
    }

    TEST_F(SpeciesTest, WriteGenomeToFile)
    {
        Species species(50, 3, 5);

        system("mkdir ../data/gen1");
        system("mkdir ../data/gen1/network");

        species.writeGenomesToFile(1, 1);

        ifstream fin("../data/gen1/species1.txt");

        ASSERT_TRUE(fin.good());

        fin.close();

        // Now clean up the system
        system("rm -rf ../data/gen1");
    }

    TEST_F(SpeciesTest, ProduceOffspring)
    {
        Species species(50, 3, 5);

        vector<Genome> children = species.produceOffspring(10);

        EXPECT_EQ(10, children.size());
    }

    TEST_F(SpeciesTest, Update)
    {
        Species species(50, 3, 5);

        species.update();

        EXPECT_EQ(1, species.getAge());
    }

    TEST_F(SpeciesTest, AdjustFitness)
    {
        Species species(10, 3, 5);

        for (int g = 0; g < species.getGenomes().size(); ++g)
        {
            species.getGenomes()[g].setFitness(500);
        }

        species.adjustFitness();

        for (int g = 0; g < species.getGenomes().size(); ++g)
        {
            EXPECT_EQ(50, species.getGenomes()[g].getAdjustedFitness());
        }
    }

    TEST_F(SpeciesTest, KillGenomes)
    {
        Species species(100, 3, 5);

        EXPECT_EQ(100, species.getGenomes().size());

        for (int g = 0; g < species.getGenomes().size(); ++g)
        {
            species.getGenomes()[g].setAdjustedFitness(random(0, 1000));
        }

        EXPECT_EQ(21, species.killGenomes());
    }
}

#endif // SPECIES_TEST_H