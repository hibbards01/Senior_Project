/***********************************************************************
* Program:
*   driver.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This is the main driver for the tests on the classes within the
*       the genetic_algorithm folder.
***********************************************************************/

#include "gtest/gtest.h"
#include "node_test.h"
#include "network_test.h"
#include "genome_test.h"
#include "geneHistory_test.h"
#include <ctime>

float Genome::c1 = 1;
float Genome::c2 = 1;
float Genome::c3 = 0.4;

int main(int argc, char **argv)
{
    srand(time(0));

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}