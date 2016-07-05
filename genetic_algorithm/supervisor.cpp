/***********************************************************************
* Program:
*   supervisor.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define all the functions for the class SUPERVISOR.
***********************************************************************/

#include "supervisor.h"
#include "defines.h"
#include "geneHistory.h"
#include <sys/stat.h>
#include <fstream>
#include <math.h>
#include <cassert>
using namespace std;

// For debugging purposes.
// To run debug code run in command line: g++ -D DEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

/***********************************************************************
* Supervisor
*   This will initialize everything. The population will start with one
*       species and 100 GENOMES.
***********************************************************************/
Supervisor::Supervisor(int population, int outputs, int inputs) : noImprovement(0),
overallAverage(2000), generation(0), population(population)
{
    species.push_back(Species(population, outputs, inputs));
}

/***********************************************************************
* setAverageBeforeEpoch
*   This will set the overall average, adjusted average, and write to the
*       file every 5 generations.
***********************************************************************/
void Supervisor::setAverageBeforeEpoch()
{
    // First we need to adjust all the species fitnesses'.
    for (int s = 0; s < species.size(); ++s)
    {
        species[s].adjustFitness();
    }

    // Now set the overall average of the species.
    setOverallAverage();

    // Write what happened every 5 generations.
    if (generation % 5 == 0)
    {
        writePopulationToFile();
    }

    return;
}

/***********************************************************************
* epoch
*   This will determine how many babies that are needed to be made for
*       the next generation. It will also give the children to the correct
*       species and update everything.
***********************************************************************/
void Supervisor::epoch()
{
    // Run the epoch.
    // Sort the species in descending order of the average fitness for the species.
    // This way the offspring will always be created from the best performing species.
    sort(species.begin(), species.end());

    // Now grab the total of offspring that will be produced.
    // Also produce them and save them in the vector.
    int total = 0;
    vector<Genome> offspring;

    // Now loop through the species and grab the offspring. If that offspring
    // did not perform for 10 generations then we will kill of that species.
    GeneHistory & db = GeneHistory::getInstance();
    int killRate = db.getKillRate();
    for (vector<Species>::iterator s = species.begin(); s != species.end();)
    {
        if (s->getNoImprovement() > killRate && species.size() > 1)
        {
            // Kill off the species since it did not perform as well.
            s = species.erase(s);
        }
        else
        {
            // Still performing well, so now we need to produce some offspring.
            // This will be computed by how well the species is performing divided by it's size.
            int babies = (overallAverage > 0) ? ceil(s->getAverageFitness(true) / overallAverage) : 0;

            // Now kill all the genomes that did not perform that well. Also grab how many
            // survived from those species.
            total += s->killGenomes();

            // Now produce the babies that were calculated. Make sure it does not go over
            // POPULATION. This could happen due to the CEIL function call on link 94.
            if (total + babies <= population)
            {
                // Add up the babies.
                total += babies;

                // Now produce the offspring based off of the number BABIES.
                vector<Genome> children = s->produceOffspring(babies);

                // Finally save it to the vector.
                offspring.insert(offspring.end(), children.begin(), children.end());
            }

            ++s; // Increment the iterator.
        }
    }

    // Make sure that the TOTAL; is the same as the POPULATION. If it is less
    // then the population then we need to produce some more offspring.
    int remainigBabies = population - total;

    if (remainigBabies > 0)
    {
        assert(species.size() > 0);
        int babies = ceil(remainigBabies / species.size()) + 1;
        while (total < population)
        {
            for (int s = 0; s < species.size() && total < population; ++s)
            {
                if (total + babies > population)
                {
                    // Make up for the rest of the population.
                    babies = population - total;
                }

                // Add up the babies
                total += babies;

                // Create the children
                vector<Genome> children = species[s].produceOffspring(babies);

                // Finally save it to the vector.
                offspring.insert(offspring.end(), children.begin(), children.end());
            }
        }
    }

    assert(total == population);
    assert(offspring.size() < population);

    // Mutate the children. See if any mutation occurs.
    mutateOffspring(offspring);

    // Now give the offspring to the correct species
    giveOffspringToSpecies(offspring);

    // Finally update everything!
    update();

    return;
}

/***********************************************************************
* setOverallAverage
*   This will grab all the averages from the species and compute the
*       final average.
***********************************************************************/
void Supervisor::setOverallAverage()
{
    float average = 0; // This will grab all the averages from everyone!

    // Now loop through the species and grab their averages
    int total = 0;
    for (int s = 0; s < species.size(); ++s)
    {
        average += species[s].getAverageFitness();
    }

    assert(species.size() > 0);
    average /= species.size();

    if (average < overallAverage)
    {
        overallAverage = average;
        noImprovement = 0;
    }
    else
    {
        ++noImprovement;
    }

    return;
}

/***********************************************************************
* update
*   Update all the SPECIES.
***********************************************************************/
void Supervisor::update()
{
    // Loop through all the species and update them
    for (int s = 0; s < species.size(); ++s)
    {
        species[s].update();
    }

    ++generation;

    return;
}

/***********************************************************************
* giveOffspringToSpecies
*   This will compute the distance that the offspring is from the species
*       and give that child to that species. If none of them are that
*       close to the child then this will create a new species for the
*       child.
***********************************************************************/
void Supervisor::giveOffspringToSpecies(vector<Genome> & genomes)
{
    GeneHistory & db = GeneHistory::getInstance();
    float speciesCompatibility = db.getSpeciesCompatibility();

    // Loop through all the genomes
    for (int g = 0; g < genomes.size(); ++g)
    {
        bool found = false; // When the genome is added to someone finish
                            // this second for loop
        for (int s = 0; s < species.size() && !found; ++s)
        {
            // Check the compatibility threshold.
            if (genomes[g].computeDistance(species[s].getLeader()) < speciesCompatibility)
            {
                species[s].getGenomes().push_back(genomes[g]);
                found = true;
            }
        }

        // If we did not find anyone then we will create a new species with that Genome
        if (!found)
        {
            species.push_back(Species(genomes[g]));
        }
    }

    return;
}

/***********************************************************************
* mutateOffspring
*   This will mutate the offspring that was created from the EPOCH
*       function.
***********************************************************************/
void Supervisor::mutateOffspring(std::vector<Genome> & genomes)
{
    GeneHistory & db = GeneHistory::getInstance();
    float linkRate = db.getLinkRate();
    float nodeRate = db.getNodeRate();
    float weightRate = db.getWeightRate();

    for (int g = 0; g < genomes.size(); ++g)
    {
        // Now see if this GENOME will get mutated.
        // First see if a link will be added or taken away...
        if (random(0.01, 1.0) < linkRate)
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
                    if (generation == 109)
                    {
                        cout << "HERE!\n";
                    }
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
        if (random(0.01, 1.0) < nodeRate)
        {
#ifdef DEBUG
            genomes[g].mutateAddNeuron(random(0, 1));
#else
            genomes[g].mutateAddNeuron();
#endif
        }

        // Now see if a mutation on a weight will happen.
        if (random(0.01, 1.0) < weightRate)
        {
            genomes[g].mutateWeight();
        }
    }

    return;
}

/***********************************************************************
* writePopulationToFile
*   This will start the whole process of writing the files to the folder.
***********************************************************************/
void Supervisor::writePopulationToFile()
{
    // Create a new folder for the generation!
    string folder = "../data/gen" + toString<int>(generation);
    int error = mkdir(folder.c_str(), ACCESSPERMS);

    string network = folder + "/network";
    int error2 = mkdir(network.c_str(), ACCESSPERMS);

    if (error == -1 || error2 == -1)
    {
        cout << "Error could not create directory.\n"
             << "Folder: " << folder << " Error: " << error << endl
             << "Folder: " << network << " Error: " << error2 << endl;
    }
    else
    {
        // Create the main file that will help show the overall progress of the
        // program.
        string file = folder + "/population_summary.txt";
        ofstream fout(file.c_str());

        if (fout.fail())
        {
            cout << "ERROR could not write to file: " << file << endl;
        }
        else
        {
            // Write the overall progress of the population.
            fout << "Generation: " << generation << endl
                 << "Overall Average: " << overallAverage << endl
                 << "Number of Species: " << species.size() << endl << endl;

            Genome bestGenome;  // Grab the best performer.
            for (int s = 0; s < species.size(); ++s)
            {
                fout << "Species " << s << ": " << species[s].getGenomes().size()
                     << " genomes\n";

                species[s].writeGenomesToFile(generation, s);

                // See which one is the best performer.
                if (species[s].getBestGenome().getFitness() > bestGenome.getFitness())
                {
                    bestGenome = species[s].getBestGenome();
                }
            }

            // Finally write this genome as well to the file.
            fout << endl << "Best Performing Genome\n----------------------\n"
                 << bestGenome << endl;
        }

        fout.close(); // Always close it.
    }

    return;
}