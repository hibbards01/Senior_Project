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

#include <iostream>

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

inline std::ostream & operator << (std::ostream & out, const NodeGene & rhs)
{
    out << rhs.id << " " << rhs.type << " " << rhs.recurrent;

    return out;
}

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
        mutate = -1;
    }

    LinkGene(int i, int in, int out, double w)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = true;
        mutate = -1;
    }

    LinkGene(int i, int in, int out, double w, bool e)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = e;
        mutate = -1;
    }

    LinkGene(int i, int in, int out, double w, bool e, int m)
    {
        id = i;
        input = in;
        output = out;
        weight = w;
        enabled = e;
        mutate = m;
    }

    int id;        // Innovation id.
    int input;
    int output;
    double weight;
    bool enabled;
    int mutate;
};

inline std::ostream & operator << (std::ostream & out, const LinkGene & rhs)
{
    out << rhs.id << " " << rhs.input << " " << rhs.output << " " << rhs.weight << " " << rhs.enabled;

    return out;
}

#endif // GENES_H