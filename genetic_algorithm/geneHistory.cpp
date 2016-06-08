/***********************************************************************
* Program:
*   geneHistory.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define all the functions for the class GENEHISTORY.
***********************************************************************/

#include "geneHistory.h"

/***********************************************************************
* addNewNeuron
*   This will search through the neurons to see if it needs to add this
*       to the innovations.
***********************************************************************/
void GeneHistory::addNewNeuron(int id, int type)
{
    bool found = false; // Try to find the neuron

    // Loop through all the innovations until found.
    for (int i = 0; i < innovations.size() && !found; ++i)
    {
        if (innovations[i].id == id && innovations[i].nodeType == type)
        {
            found = true;
        }
    }

    // Did we find it?
    // If not add it to the innovations
    if (!found)
    {
        innovations.push_back(Innovation(-1, -1, id, type));
    }

    return;
}

/***********************************************************************
* addNewLink
*   This will check to see if it needs to add a new link to the history.
*       If it already has one then it will return the id.
***********************************************************************/
int GeneHistory::addNewLink(int source, int destination)
{
    int found = -1; // Try to find the links in the database.

    for (int i = 0; i < innovations.size() && found == -1; ++i)
    {
        if (innovations[i].input == source &&
            innovations[i].output == destination)
        {
            found = innovations[i].id;
        }
    }

    // If found is still -1 then add the new link to the database.
    // Grab the id as well from the innovation.
    if (found == -1)
    {
        Innovation inn(source, destination, -1, -1);
        found = inn.id;

        innovations.push_back(inn);
    }

    return found;
}