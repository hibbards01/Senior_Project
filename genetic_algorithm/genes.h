/***********************************************************************
* Program:
*   genes.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold two STRUCTS that are needed by GENOME and NETWORK.
***********************************************************************/

#ifndef GENES_H
#define GENES_H

/***********************************************************************
* NodeGene
*   This holds all the nodes that the GENOME will hold currently. This
*       holds the id, type, and if it is recurrent or not.
***********************************************************************/
struct NodeGene
{
    NodeGene(int i, int t)
    {
        id = i;
        type = t;
        recurrent = false;
    }

    int id;
    int type;
    bool recurrent;
};

/***********************************************************************
* LinkGene
*   This holds the link gene for the GENOME. This is the core of the
*       NETWORK. This tells how everything is going to be connected.
*       This holds the input, output, weight, and if the link is enabled
*       or not. It will also hold an id which will be given by the class
*       GENEHISTORY. This helps the GENOME to know it's history based off
*       the id.
***********************************************************************/
struct LinkGene
{
    LinkGene(int i, int in, int out, double w)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = true;
    }

    int id;
    int input;
    int output;
    double weight;
    bool enabled;
};

#endif // GENES_H