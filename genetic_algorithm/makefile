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

network.o: network.cpp network.h node.h defines.h
	g++ -c network.cpp

clean:
	rm *.o