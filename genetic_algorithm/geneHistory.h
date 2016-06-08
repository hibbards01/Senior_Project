/***********************************************************************
* Program:
*   geneHistory.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold all the innovations for all the genes within the
*       population.
***********************************************************************/

#ifndef GENEHISTORY_H
#define GENEHISTORY_H

#include <vector>

static int innovationId = 0; // This will increment every time a new
                             // Innovation is added to the database.

/***********************************************************************
* Innovation
*   This will be the STRUCT that will hold all the innovations. This
*       can either do the nodes or links.
***********************************************************************/
struct Innovation
{
    Innovation(int in, int out, int n, int type)
    {
        id = innovationId++; // Increment the innovation.
        input = in;
        output = out;
        node = n;
        nodeType = type;
    }

    int id;       // The innovation id.
    int input;    // The input and output, this is the link
    int output;   // that will be saved.
    int node;     // The node that we want to save
    int nodeType; // with it's given type.
};

/***********************************************************************
* GeneHistory
*   This will be a singleton class so that any class can use it if
*       needed.
***********************************************************************/
class GeneHistory
{
public:
    //
    // Constructors
    //
    GeneHistory() : innovations() {}
    ~GeneHistory() {}

    //
    // Methods
    //
    void addNewNeuron(int id, int type);         // This will add a new neuron.
    int addNewLink(int source, int destination); // This will add a new link.

    // This will return the GENEHISTORY. It will create a new instance if necessary.
    static GeneHistory * getInstance()
    {
        if (geneHistory == NULL)
        {
            geneHistory = new GeneHistory();
        }

        return geneHistory;
    }
private:
    static GeneHistory * geneHistory;    // This is what makes this class a singleton class.
    std::vector<Innovation> innovations; // This will hold all the innovations.
};

#endif // GENEHISTORY_H