/***********************************************************************
* Program:
*   main.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will be where main is held. This will be the main driver of the
*       whole program.
***********************************************************************/

#include "supervisor.h"
#include "geneHistory.h"
#include "../simulator/sim.h"
#include <fstream>
#include <ctime>
#include <cassert>
#include <map>
using namespace std;

// Define the window size!
float Point::xMin = -700.0;
float Point::xMax = 700.0;
float Point::yMin = -400.0;
float Point::yMax = 400.0;

#define THREADS 8
#define SIZE 200
#define INPUTS 28
#define OUTPUTS 3

static Genome computer;
static bool player;

/***********************************************************************
* displayHelp
*   This will display the options for the command line.
***********************************************************************/
void displayHelp()
{
    cout << "\nOptions:\n"
         << "\t-file [file], The file with the parameters for the Genetic Algorithm.\n"
         << "\t              example.txt and example2.txt is an example of what is needed for [file].\n"
         << "\t-run,  This will run the Genetic Algorithm. -file must be specified. This will\n"
         << "\t       use example.txt.\n"
         << "\t-sim,  This will run the game. If -file is specified then the game will be\n"
         << "\t       controlled by the Genetic Algorithm provided from the file. If not then\n"
         << "\t       the player could play the game. This will use example2.txt.\n"
         << "\tNOTE: -sim and -run cannot be both specified.\n"
         << "\t-help, Display this.\n\n";

    return;
}

/***********************************************************************
* parseCommandLine
*   This will parse the commands that were given from the user. It will
*       also check to make sure that the user gave the right parameters.
***********************************************************************/
bool parseCommandLine(int argc, char *argv[], string & fileName, bool & sim)
{
    bool help = false;
    bool run = false;

    // Loop through the arguments that were given.
    for (int i = 1; i < argc; ++i)
    {
        string word = argv[i]; // Change the argv to a string. So it is easier to compare.

        if (word == "-file")
        {
            if (i + 1 < argc)
            {
                fileName = argv[i + 1]; // Grab the file name.
            }
        }
        else if (word == "-run")
        {
            run = true;
        }
        else if (word == "-sim")
        {
            sim = true;
        }
        else if (word == "-help")
        {
            help = true;
        }
    }

    // Make sure everything was given correctly
    bool error = false;
    if (help)
    {
        displayHelp();
    }
    else if ((sim && run) || (run && fileName.empty()) || argc == 1 || (!sim && !run))
    {
        error = true;
    }

    return error;
}

/***********************************************************************
* setStaticVariables
*   This will set the static variables for the Genetic Algorithm.
***********************************************************************/
void setStaticVariables(string variable, float value) throw (string)
{
    // See which static variable to set
    GeneHistory & db = GeneHistory::getInstance();

    if (variable == "c1")
    {
        db.setC1(value);
    }
    else if (variable == "c2")
    {
        db.setC2(value);
    }
    else if (variable == "c3")
    {
        db.setC3(value);
    }
    else if (variable == "crossoverRate")
    {
        db.setCrossoverRate(value);
    }
    else if (variable == "speciesCompatibility")
    {
        db.setSpeciesCompatibility(value);
    }
    else if (variable == "linkRate")
    {
        db.setLinkRate(value);
    }
    else if (variable == "nodeRate")
    {
        db.setNodeRate(value);
    }
    else if (variable == "weightRate")
    {
        db.setWeightRate(value);
    }
    else if (variable == "killRate")
    {
        db.setKillRate(value);
    }
    else
    {
        throw "Error with file unknown variable: " + variable;
    }

    return;
}

/***********************************************************************
* split
*   This will split the string by a delimiter into a vector.
***********************************************************************/
vector<string> split(string line, char delimiter)
{
    vector<string> result; // This will hold the broken up string.
    stringstream ss(line); // This will do the actual splitting.
    string piece;          // This will save the individual piece.

    // Loop until there is none left.
    while (getline(ss, piece, delimiter))
    {
        result.push_back(piece);
    }

    return result;
}

/***********************************************************************
* saveNodes
*   This will save the nodes for the genome.
***********************************************************************/
void saveNodes(vector<NodeGene> & nodes, string line)
{
    if (!line.empty())
    {
        vector<string> pieces = split(line, ' ');

        if (pieces[0] == "Id:")
        {
            vector<string> ids = split(pieces[1], ',');
            for (int i = 0; i < ids.size(); ++i)
            {
                NodeGene node;
                node.id = stoi(ids[i]);
                nodes.push_back(node);
            }
        }
        else if (pieces[0] == "Type:")
        {
            vector<string> types = split(pieces[1], ',');
            map<string, int> values;
            values["Sensor"] = 0;
            values["Hidden"] = 1;
            values["Output"] = 2;
            values["Bias"] = 3;
            for (int t = 0; t < types.size(); ++t)
            {
                nodes[t].type = values[types[t]];
            }
        }
        else if (pieces[0] == "Recurrent:")
        {
            vector<string> recurrents = split(pieces[1], ',');
            map<string, bool> values;
            values["True"] = true;
            values["False"] = false;
            for (int r = 0; r < recurrents.size(); ++r)
            {
                nodes[r].recurrent = values[recurrents[r]];
            }
        }
    }

    return;
}

/***********************************************************************
* saveLinks
*   This will save the links for the genome.
***********************************************************************/
void saveLinks(vector<LinkGene> & links, string line)
{
    if (!line.empty())
    {
        vector<string> pieces = split(line, ' ');

        if (pieces[0] == "Id:")
        {
            vector<string> ids = split(pieces[1], ',');
            for (int i = 0; i < ids.size(); ++i)
            {
                LinkGene link;
                link.id = stoi(ids[i]);
                links.push_back(link);
            }
        }
        else if (pieces[0] == "Input:")
        {
            vector<string> inputs = split(pieces[1], ',');
            for (int i = 0; i < inputs.size(); ++i)
            {
                links[i].input = stoi(inputs[i]);
            }
        }
        else if (pieces[0] == "Output:")
        {
            vector<string> outputs = split(pieces[1], ',');
            for (int i = 0; i < outputs.size(); ++i)
            {
                links[i].output = stoi(outputs[i]);
            }
        }
        else if (pieces[0] == "Weight:")
        {
            vector<string> weights = split(pieces[1], ',');
            for (int i = 0; i < weights.size(); ++i)
            {
                links[i].weight = stof(weights[i]);
            }
        }
        else if (pieces[0] == "Enabled:")
        {
            vector<string> enableds = split(pieces[1], ',');
            map<string, bool> values;
            values["True"] = true;
            values["False"] = false;
            for (int r = 0; r < enableds.size(); ++r)
            {
                links[r].enabled = values[enableds[r]];
            }
        }
    }

    return;
}

/***********************************************************************
* readFile
*   This will read the file from what was given.
***********************************************************************/
void readFile(string fileName, bool sim) throw (string)
{
    ifstream fin(fileName.c_str()); // Start the process of reading the file.
    string error;                   // This will throw the error if there was one.

    if (fin.fail())
    {
        error = "ERROR could not read from file: " + fileName;
    }
    else
    {
        string line;
        bool node = true;
        vector<NodeGene> nodes;
        vector<LinkGene> links;

        // Now see what we should read from the file.
        while (getline(fin, line))
        {
            if (!sim)
            {
                string variable; // This will hold the static variable.
                float value;     // This will hold the value.

                // Parse the strings by space.
                stringstream ss(line);
                ss >> variable >> value;

                setStaticVariables(variable, value);
            }
            else
            {
                // Grab the genome provided and grab all the data it has.
                if (line == "Links:")
                {
                    node = false;
                }

                if (node)
                {
                    saveNodes(nodes, line);
                }
                else
                {
                    saveLinks(links, line);
                }
            }
        }

        if (sim)
        {
            computer.setNodeGenes(nodes);
            computer.setLinkGenes(links);
        }
    }

    fin.close(); // Always close the file

    // See if we need to throw any errors.
    if (!error.empty())
    {
        throw error;
    }

    return;
}

/***********************************************************************
* runSimulation
*   This will run the simulation with the Genome that was given.
***********************************************************************/
float runSimulation(Network & network)
{
    // Create a new simulator
    Simulator simulator;
    int fuel;
    int angle;
    float dx, dy;

    // Run the simulation until done.
    while (simulator.getDone() == 0)
    {
        // Create the array from scratch for the inputs
        int arrayInputs[5][5] = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };

        // Now grab the inputs for the ship.
        simulator.getInputs(arrayInputs, fuel, angle, dx, dy);

        // Convert the inputs to an array
        vector<int> inputs;
        inputs.push_back(fuel);
        inputs.push_back(angle);
        inputs.push_back(dx);
        inputs.push_back(dy);
        for (int r = 0; r < 5; ++r)
        {
            for (int c = 0; c < 5; ++c)
            {
                if (r != 2 || c != 2)
                {
                    inputs.push_back(arrayInputs[r][c]);
                }
            }
        }

        assert(inputs.size() == INPUTS);

        // Give the inputs to the network.
        vector<double> outputs;
        outputs = network.feedForward(inputs);

        // Give the outputs to the game.
        simulator.run(outputs);
    }

    // The game is finished. Grab the score for the genome.
    return simulator.computeScore();
}

/***********************************************************************
* runSolutions
*   This will loop through everyone and run their solutions against the
*       the game and retrieve the score for them.
***********************************************************************/
void runSolutions(Supervisor & supervisor)
{
    cout << "Running Solutions\n";

    // Loop through all the genomes and see how they do against the game.
    int g;
    float score;
    for (int s = 0; s < supervisor.getSpecies().size(); ++s)
    {
        #pragma omp parallel for num_threads(THREADS) shared(supervisor, s) private(g, score)
        for (g = 0; g < supervisor.getSpecies()[s].getGenomes().size(); ++g)
        {
            // Grab the score it got.
            score = runSimulation(supervisor.getSpecies()[s].getGenomes()[g].getNetwork());

            // if (score > 2000)
            // {
            //     score = 2000;
            // }

            // Save the score for the genome.
            supervisor.getSpecies()[s].getGenomes()[g].setFitness(score);
        }
    }

    return;
}

/***********************************************************************
* runGeneticAlgorithm
*   This will run the genetic algorithm and start the whole process.
*       This will terminate when the conditions are met.
***********************************************************************/
void runGeneticAlgorithm()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(10);

    Supervisor supervisor(SIZE, OUTPUTS, INPUTS); // Declare the genetic algorithm.
    supervisor.update();                          // Update everything for the first time.

    // Start the whole process, once there is no improvement or we reach
    // the limit for the generation then it is done.
    while (supervisor.getGeneration() < 2001)
    {
        // Run the solutions against the simulator.
        runSolutions(supervisor);

        // Set the overallAverage and adjusted average.
        supervisor.setAverageBeforeEpoch();

        // Output something to show that it is working.
        cout << "Generation: " << supervisor.getGeneration()
             << " Overall Average: " << supervisor.getOverallAverage() << endl;

        // Now do the epoch for the population.
        cout << "Running epoch\n";
        supervisor.epoch();
    }

    return;
}

/***********************************************************************
 * callBack
 *   This will run the simulator and allow the player to control it.
 **********************************************************************/
void callBack(const Interface *pUI, void *p)
{
    // Grab the simulator
    Simulator *sim = (Simulator *) p;

    int fuel;
    int angle;
    float dx, dy;

    // Run the simulation based off of who.
    if (!player)
    {
        if (sim->getDone() == 0)
        {
            // Create the array from scratch for the inputs
            int arrayInputs[5][5] = {
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
            };

            // Now grab the inputs for the ship.
            sim->getInputs(arrayInputs, fuel, angle, dx, dy);

            // Convert the inputs to an array
            vector<int> inputs;
            inputs.push_back(fuel);
            inputs.push_back(angle);
            inputs.push_back(dx);
            inputs.push_back(dy);
            for (int r = 0; r < 5; ++r)
            {
                for (int c = 0; c < 5; ++c)
                {
                    if (r != 2 || c != 2)
                    {
                        inputs.push_back(arrayInputs[r][c]);
                    }
                }
            }

            // Give the inputs to the network!
            vector<double> outputs;
            outputs = computer.getNetwork().feedForward(inputs);

            sim->run(outputs);
        }

        sim->draw();
    }
    else
    {
        sim->runSim(pUI);
    }
}

/***********************************************************************
* runGame
*   This will run the game instead. This will allow the player to play
*       unless the file was specified. If that is the case then it will
*       run the Genome on the game instead.
***********************************************************************/
void runGame(int argc, char *argv[])
{
    // Start the interface
    Interface ui(argc, argv, "Gravity");
    Simulator sim;

    if (!player)
    {
        computer.update();
    }

    // Now do the callback function
    ui.run(callBack, &sim);

    return;
}

/***********************************************************************
* main
*   This will be the main driver of the program.
***********************************************************************/
int main(int argc, char *argv[])
{
    srand(time(0));
    string fileName;  // The file given from the user.
    bool sim = false; // These will determine what should be run.

    // Parse the command line.
    if (parseCommandLine(argc, argv, fileName, sim))
    {
        cout << "\nERROR with command arguments given please type -help for help.\n\n";
    }
    else
    {
        try
        {
            // No errors, lets see if we need to read from the file.
            if (!fileName.empty())
            {
                readFile(fileName, sim);
            }

            // Run what was requested.
            if (sim)
            {
                // See if the player is playing or the computer.
                player = (fileName.empty()) ? true : false;

                // Run the game.
                runGame(argc, argv);
            }
            else
            {
                // Run the genetic algorithm.
                runGeneticAlgorithm();
            }
        }
        catch (string error)
        {
            cout << error << endl;
        }
    }

    return 0;
}
