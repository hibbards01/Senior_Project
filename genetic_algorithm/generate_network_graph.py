#!/usr/bin/python
import networkx as nx
import sys
import matplotlib.pyplot as plt

# Grab the file name
if len(sys.argv) == 2:
    fileName = sys.argv[1]
    print("\nReading File: %s" % fileName)

    graph = nx.DiGraph()

    # Open the file
    file = open(fileName, 'r')

    # Read the file line by line
    print("\nCreating graph...")
    for line in file:
        edge = line.split(',')

        fr = int(edge[0])
        to = int(edge[1])
        weight = float(edge[2][:-1])

        # Add the edge to the graph
        graph.add_edge(fr, to, weight=weight)

    # Close the file
    file.close()

    # Draw the graph
    # NOTE add weights to graph!!!!!!!!!!
    pos = nx.spring_layout(graph)
    nx.draw(graph, pos, cmap=plt.get_cmap('jet'), with_labels=True)
    nx.draw_networkx_edges(graph, pos, arrows=True)
    plt.show()
else:
    print("\nError you must provide a file to read from.\n\n")