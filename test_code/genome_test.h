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
        Genome genome;
    };

}

#endif // GENOME_TEST_H