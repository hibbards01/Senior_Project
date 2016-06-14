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
    NodeGene()
    {
        id = -1;
        type = -1;
        recurrent = false;
    }

    NodeGene(int i, int t)
    {
        id = i;
        type = t;
        recurrent = false;
    }

    NodeGene(int i, int t, bool r)
    {
        id = i;
        type = t;
        recurrent = r;
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
    LinkGene()
    {
        id = -1;
        input = -1;
        output = -1;
        weight = -1;
        enabled = false;
    }

    LinkGene(int i, int in, int out, double w)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = true;
    }

    LinkGene(int i, int in, int out, double w, bool e)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = e;
    }

    int id;        // Innovation id.
    int input;
    int output;
    double weight;
    bool enabled;
};

#endif // GENES_H