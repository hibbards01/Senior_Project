###########################################################################
# Program:
#   makefile
# Author:
#   Samuel Hibbard
# Details
#   This will compile all the tests and create an execution file.
###########################################################################

test: driver.o node.o network.o genome.o geneHistory.o
	g++ -D DEBUG -o test driver.o node.o network.o genome.o geneHistory.o -lgtest

show: driver_show.o node.o network.o genome.o geneHistory.o
	g++ -D SHOW -D DEBUG -o show driver_show.o node.o network.o genome.o geneHistory.o -lgtest

driver_show.o: driver.cpp node_test.h network_test.h genome_test.h ../genetic_algorithm/geneHistory.h
	g++ -D SHOW -D DEBUG -c driver.cpp -o driver_show.o

driver.o: driver.cpp node_test.h network_test.h genome_test.h geneHistory_test.h
	g++ -D DEBUG -c driver.cpp

node.o: ../genetic_algorithm/node.cpp ../genetic_algorithm/node.h
	g++ -c ../genetic_algorithm/node.cpp

network.o: ../genetic_algorithm/network.cpp ../genetic_algorithm/network.h ../genetic_algorithm/node.h ../genetic_algorithm/defines.h ../genetic_algorithm/genes.h
	g++ -c ../genetic_algorithm/network.cpp

genome.o: ../genetic_algorithm/genome.cpp ../genetic_algorithm/genome.h ../genetic_algorithm/genes.h ../genetic_algorithm/network.h ../genetic_algorithm/defines.h
	g++ -D DEBUG -c ../genetic_algorithm/genome.cpp

geneHistory.o: ../genetic_algorithm/geneHistory.cpp ../genetic_algorithm/geneHistory.h
	g++ -c ../genetic_algorithm/geneHistory.cpp

###########################################################################
# DEBUGGING
#	For debugging purposes.
###########################################################################

debug: driver_debug.o network_debug.o ../genetic_algorithm/defines.h node_debug.o genome_debug.o geneHistory_debug.o
	g++ -g -o debug network_debug.o node_debug.o genome_debug.o geneHistory_debug.o driver_debug.o -lgtest

driver_debug.o: driver.cpp node_test.h network_test.h genome_test.h geneHistory_test.h
	g++ -g -D DEBUG -c -o driver_debug.o driver.cpp

node_debug.o: ../genetic_algorithm/node.cpp ../genetic_algorithm/node.h
	g++ -g -c -o node_debug.o ../genetic_algorithm/node.cpp

network_debug.o: ../genetic_algorithm/network.cpp ../genetic_algorithm/network.h ../genetic_algorithm/node.h ../genetic_algorithm/defines.h ../genetic_algorithm/genes.h
	g++ -g -c -o network_debug.o ../genetic_algorithm/network.cpp

genome_debug.o: ../genetic_algorithm/genome.cpp ../genetic_algorithm/genome.h ../genetic_algorithm/genes.h ../genetic_algorithm/network.h ../genetic_algorithm/defines.h
	g++ -g -D DEBUG -c -o genome_debug.o ../genetic_algorithm/genome.cpp

geneHistory_debug.o: ../genetic_algorithm/geneHistory.cpp ../genetic_algorithm/geneHistory.h
	g++ -g -c -o geneHistory_debug.o ../genetic_algorithm/geneHistory.cpp

clean:
	rm *.o test debug show