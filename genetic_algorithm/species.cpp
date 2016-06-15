/***********************************************************************
* Program:
*   species.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This holds all the functions that are defined for the class SPECIES.
***********************************************************************/

#include "species.h"
#include "defines.h"
#include <fstream>
#include <cassert>
using namespace std;

/***********************************************************************
* getAverageFitness
*   This will grab all the GENOME fitnesses and compute the average.
***********************************************************************/
float Species::getAverageFitness()
{
    float average = 0;

    // Grab all the fitnesses.
    for (int g = 0; g < genomes.size(); ++g)
    {
        average += genomes[g].getFitness();
    }

    // Now compute the average
    average /= genomes.size();

    // Check to see if there was an improvement for the overall species.
    // If not then increment the variable NOIMPROVEMENT
    if (averageFitness < average)
    {
        averageFitness = average;
        noImprovement = 0;
    }
    else
    {
        ++noImprovement;
    }

    return averageFitness;
}

/***********************************************************************
* writeGenomesToFile
*   This will grab all the GENOME's history and write it to a file.
***********************************************************************/
void Species::writeGenomesToFile(int gen, int speciesId)
{
    // Create the file name based off the numbers.
    string file = "gen" + toString<int>(gen) + "/species" + toString<int>(speciesId) + ".txt";
    ofstream fout(file.c_str());

    // Make sure it was able to do it. If not then output an error message.
    if (fout.fail())
    {
        cout << "Error could not write species" + toString<int>(speciesId) + " to file: " << file << endl;
    }
    else
    {
        for (int g = 0; g < genomes.size(); ++g)
        {
            // Output the genome.
            fout << "Genome " << genomes[g].getId() << "\n----------\n"
                 << "Nodes:\n" << genomes[g].getNodesString() << endl
                 << "Links:\n" << genomes[g].getLinksString() << endl;

            // Now write the network to the file.
            genomes[g].getNetwork().writeNetworkToFile(genomes[g].getId(), gen);
        }
    }

    fout.close(); // Always close the file.

    return;
}

/***********************************************************************
* produceOffspring
*   This will tell the species to produce a certain amount of offspring.
*       It will then return that offspring and the SUPERVISOR will put
*       them in the correct species.
***********************************************************************/
vector<Genome> Species::produceOffspring(int children)
{
    vector<Genome> offspring; // This will hold all the children that will be created.

    // Loop until all the offspring is produced.
    for (int i = 0; i < children; ++i)
    {
        Genome child; // Set the child to be empty for now.

        // Grab a random parent.
        int num = random(0, genomes.size() - 1);
        assert(num >= 0 && num < genomes.size());

        // See if it will pass the crossover rate. If not then it will
        // give a random genome in the species.
        if (random(0, 10) <= 7 && genomes.size() > 1)
        {
            // Now grab another parent that is not the LEFTPARENT.
            int randNum;
            do
            {
                randNum = random(0, genomes.size() - 1);
            }
            while (randNum == num);

            assert(randNum >= 0 && randNum < genomes.size());

            // Finally create the child!
            child = genomes[num].produceChild(genomes[randNum]);
        }
        else
        {
            child = genomes[num];
        }

        offspring.push_back(child);
    }

    return offspring;
}

/***********************************************************************
* mutate
*   This will mutate a genome. It will run the probabilities and see if
*       any of its features are changed.
***********************************************************************/
void Species::mutate(Genome & genome)
{
    // Now see if this GENOME will get mutated.
    // First see if a link will be added or taken away...
    if (random(0.01, 1.0) < 0.07) // # define this?
    {
        int num = random(0, 2); // Do a random mutation on the link.
        bool done = false;      // Make sure one of the mutations happens.

        if (num == 0)
        {
            done = genome.mutateEnableLink();
        }

        // Enable link did not work so try a different mutation.
        if (!done)
        {
            num = random(1, 2);
            if (num == 1)
            {
                genome.mutateRemoveLink();
            }
            else
            {
                genome.mutateAddLink();
            }
        }
    }

    // See if we should add another neuron.
    if (random(0.01, 1.0) < 0.03)
    {
        genome.mutateAddNeuron();
    }

    // Now see if a mutation on a weight will happen.
    if (random(0.01, 1.0) < 0.2)
    {
        genome.mutateWeight();
    }
    return;
}