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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}