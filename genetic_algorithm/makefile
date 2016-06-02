###########################################################################
# Program:
#   makefile
# Author:
#   Samuel Hibbard
# Summary:
#   This compiles all the .cpp in the genetic_algorithm folder.
###########################################################################

node.o: node.cpp node.h
	g++ -c node.cpp

network.o: network.cpp network.h node.h defines.h genes.h
	g++ -c network.cpp

genome.o: genome.cpp genome.h network.h defines.h
	g++ -c genome.cpp

clean:
	rm *.o