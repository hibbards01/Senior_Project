/***********************************************************************
* Program:
*   node.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class NODE.
***********************************************************************/

#include "node.h"
#include "defines.h"
#include <math.h>
#include <iostream>
using namespace std;

/***********************************************************************
* update
*   This does the feed forward for this particular node and sets the
*       output that this node will give.
***********************************************************************/
void Node::update()
{
    if (type != BIAS)
    {
        double sum = 0; // This will sum all the values from the inputs

        // Loop through all the inputs and grab their values
        for (int i = 0; i < inputs.size(); ++i)
        {
            // Have the weight times the output of the input and sum it up
            sum += inputs[i].weight * inputs[i].input->output;
        }

        // Finally set the output for this node
        output = 1 / (1 + exp(-sum));
    }

    return;
}