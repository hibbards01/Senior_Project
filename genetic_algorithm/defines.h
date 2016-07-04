/***********************************************************************
* Program:
*   defines.h
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the pound defines and ENUMS that are needed for
*       the files that use them.
***********************************************************************/

#ifndef GENETIC_DEFINES_H
#define GENETIC_DEFINES_H

#include <cassert>
#include <math.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

// This holds the value types.
enum {SENSOR, HIDDEN, OUTPUT, BIAS, MUTATE_NEURON1, MUTATE_NEURON2, MUTATE_NEURON3, MUTATE_LINK};

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
inline double random(double min, double max)
{
    assert(min <= max);
    double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

    assert(min <= num && num <= max);

    return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
inline int random(int min, int max)
{
    assert(min <= max);
    int num = (rand() % (max - min)) + min;
    assert(min <= num && num <= max);

    return num;
}

/***********************************************************************
* toString
*   This will convert any T to a string.
***********************************************************************/
template <class T>
inline std::string toString(const T & t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // GENETIC_DEFINES_H