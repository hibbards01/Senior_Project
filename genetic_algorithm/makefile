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

node.o: node.cpp node.h defines.h
	g++ -c node.cpp

network.o: network.cpp network.h defines.h
	g++ -c network.cpp

genome.o: genome.cpp genome.h geneHistory.h
	g++ -c genome.cpp

geneHistory.o: geneHistory.cpp geneHistory.h
	g++ -c geneHistory.cpp

species.o: species.cpp species.h defines.h
	g++ -c species.cpp

supervisor.o: supervisor.cpp supervisor.h defines.h
	g++ -c supervisor.cpp

###########################################################################
# All the simulation compilations.
###########################################################################



###########################################################################
# Tools that I can use
###########################################################################

clean:
	rm *.o