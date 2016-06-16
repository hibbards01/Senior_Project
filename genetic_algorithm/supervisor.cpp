/***********************************************************************
* Program:
*   supervisor.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define all the functions for the class SUPERVISOR.
***********************************************************************/

#include "supervisor.h"

// For debugging purposes.
// To run debug code run in command line: g++ -D DEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

/***********************************************************************
* run
*   This will start the whole process. It will check the NOIMPROVEMENT
*       to see if it is not making any more improvement. Once it doesn't
*       after a certain amount of time it will finally terminate.
***********************************************************************/
void Supervisor::run()
{
    return;
}

/***********************************************************************
* runSimulation
*   This will run the simulation with the network. It will then return
*       the score once it is finished.
***********************************************************************/
float Supervisor::runSimulation()
{
    return 0;
}

/***********************************************************************
* epoch
*   This will determine how many babies that are needed to be made for
*       the next generation.
***********************************************************************/
void Supervisor::epoch()
{
    return;
}

/***********************************************************************
* setOverallAverage
*   This will grab all the averages from the species and compute the
*       final average.
***********************************************************************/
void Supervisor::setOverallAverage()
{
    return;
}

/***********************************************************************
* update
*   Update all the SPECIES.
***********************************************************************/
void Supervisor::update()
{
    return;
}

/***********************************************************************
* mutateOffspring
*   This will mutate the offspring that was created from the EPOCH
*       function.
***********************************************************************/
void Supervisor::mutateOffspring(std::vector<Genome> & genomes)
{
    for (int g = 0; g < genomes.size(); ++g)
    {
        // Now see if this GENOME will get mutated.
        // First see if a link will be added or taken away...
        if (random(0.01, 1.0) < 0.07) // # define this?
        {
            int num = random(0, 2); // Do a random mutation on the link.
            bool done = false;      // Make sure one of the mutations happens.

            if (num == 0)
            {
                done = genomes[g].mutateEnableLink();
            }

            // Enable link did not work so try a different mutation.
            if (!done)
            {
                num = random(1, 2);
                if (num == 1)
                {
                    genomes[g].mutateRemoveLink();
                }
                else
                {
#ifdef DEBUG
                    genomes[g].mutateAddLink(random(0, 2));
#else
                    genomes[g].mutateAddLink();
#endif
                }
            }
        }

        // See if we should add another neuron.
        if (random(0.01, 1.0) < 0.03)
        {
#ifdef DEBUG
            genomes[g].mutateAddNeuron(random(0, 1));
#else
            genomes[g].mutateAddNeuron();
#endif
        }

        // Now see if a mutation on a weight will happen.
        if (random(0.01, 1.0) < 0.2)
        {
            genomes[g].mutateWeight();
        }
    }

    return;
}