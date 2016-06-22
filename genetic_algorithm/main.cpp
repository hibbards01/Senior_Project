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
using namespace std;

// Define the window size!
float Point::xMin = -700.0;
float Point::xMax = 700.0;
float Point::yMin = -400.0;
float Point::yMax = 400.0;

const static Simulator sim;

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

            }
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
* main
*   This will be the main driver of the program.
***********************************************************************/
int main(int argc, char *argv[])
{
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
        }
        catch (string error)
        {
            cout << error << endl;
        }
    }

    return 0;
}