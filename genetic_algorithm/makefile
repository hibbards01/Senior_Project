###########################################################################
# Program:
#   makefile
# Author:
#   Samuel Hibbard
# Summary:
#   This compiles all the .cpp in the genetic_algorithm folder.
###########################################################################

###########################################################################
# All the Genetic Algorithm compilations.
###########################################################################

node.o: node.cpp node.h
	g++ -c node.cpp

network.o: network.cpp network.h node.h defines.h genes.h
	g++ -c network.cpp

genome.o: genome.cpp genome.h network.h genes.h defines.h geneHistory.h
	g++ -c genome.cpp

geneHistory.o: geneHistory.cpp geneHistory.h
	g++ -c geneHistory.cpp

species.o: species.cpp species.h genome.h
	g++ -c species.cpp

supervisor.o: supervisor.cpp supervisor.h species.h
	g++ -c supervisor.cpp

###########################################################################
# All the simulation compilations.
###########################################################################



###########################################################################
# Tools that I can use
###########################################################################

clean:
	rm *.o