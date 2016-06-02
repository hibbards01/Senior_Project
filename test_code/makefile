###########################################################################
# Program:
#   makefile
# Author:
#   Samuel Hibbard
# Details
#   This will compile all the tests and create an execution file.
###########################################################################

test.out: driver.cpp node_test.h node.o
	g++ -o test.out driver.cpp node.o -lgtest

node.o: ../genetic_algorithm/node.cpp ../genetic_algorithm/node.h
	g++ -c ../genetic_algorithm/node.cpp