/***********************************************************************
* Program:
*   species.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class SPECIES.
***********************************************************************/

#include "species.h"
using namespace std;

/***********************************************************************
* getAverageFitness
*   This will grab all the GENOME fitnesses and compute the average.
***********************************************************************/
float Species::getAverageFitness()
{
    return 0;
}

/***********************************************************************
* writeGenomesToFile
*   This will grab all the GENOME's history and write it to a file.
***********************************************************************/
void Species::writeGenomesToFile(int gen, int id)
{
    return;
}

/***********************************************************************
* produceOffspring
*   This will tell the species to produce a certain amount of offspring.
*       It will then return that offspring and the SUPERVISOR will put
*       them in the correct species.
***********************************************************************/
vector<Genome> Species::produceOffspring(int num)
{
    return vector<Genome>();
}

/***********************************************************************
* mutate
*   This will mutate a child. It will run the probabilities and see if
*       any of its features are changed.
***********************************************************************/
void Species::mutate(Genome & child)
{
    return;
}