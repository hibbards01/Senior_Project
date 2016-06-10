###########################################################################
# Program:
#   makefile
# Author:
#   Samuel Hibbard
# Details
#   This will compile all the tests and create an execution file.
###########################################################################

test.out: driver.cpp node_test.h node.o network_test.h genome_test.h network.o genome.o geneHistory.o
	g++ -o test.out driver.cpp node.o network.o genome.o geneHistory.o -lgtest

node.o: ../genetic_algorithm/node.cpp ../genetic_algorithm/node.h
	g++ -c ../genetic_algorithm/node.cpp

network.o: ../genetic_algorithm/network.cpp ../genetic_algorithm/network.h ../genetic_algorithm/node.h ../genetic_algorithm/defines.h ../genetic_algorithm/genes.h
	g++ -c ../genetic_algorithm/network.cpp

genome.o: ../genetic_algorithm/genome.cpp ../genetic_algorithm/genome.h ../genetic_algorithm/genes.h ../genetic_algorithm/network.h ../genetic_algorithm/geneHistory.h ../genetic_algorithm/defines.h
	g++ -c ../genetic_algorithm/genome.cpp

geneHistory.o: ../genetic_algorithm/geneHistory.cpp ../genetic_algorithm/geneHistory.h
	g++ -c ../genetic_algorithm/geneHistory.cpp

node_debug.o: ../genetic_algorithm/node.cpp ../genetic_algorithm/node.h
	g++ -g -c -o node_debug.o ../genetic_algorithm/node.cpp

network_debug.o: ../genetic_algorithm/network.cpp ../genetic_algorithm/network.h ../genetic_algorithm/node.h ../genetic_algorithm/defines.h ../genetic_algorithm/genes.h
	g++ -g -c -o network_debug.o ../genetic_algorithm/network.cpp

debug.out: network_test.cpp network_debug.o ../genetic_algorithm/defines.h node_debug.o
	g++ -g -o debug.out network_test.cpp network_debug.o node_debug.o

clean:
	rm *.o test.out debug.out