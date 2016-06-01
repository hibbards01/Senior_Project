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

        }

        virtual ~NodeTest()
        {

        }

        virtual void SetUp()
        {

        }

        virtual void TearDown()
        {

        }
    };
}

//     // Tests that the Foo::Bar() method does Abc.
//     TEST_F(FooTest, MethodBarDoesAbc) {
//       const string input_filepath = "this/package/testdata/myinputfile.dat";
//       const string output_filepath = "this/package/testdata/myoutputfile.dat";
//       Foo f;
//       EXPECT_EQ(1, f.Bar(input_filepath, output_filepath)) << "This did not work";
//     }

//     // Tests that Foo does Xyz.
//     TEST_F(FooTest, DoesXyz) {
//       // Exercises the Xyz feature of Foo.
//     }

// }  // namespace