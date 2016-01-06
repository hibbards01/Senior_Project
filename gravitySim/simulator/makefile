##############################################################
# Program:
#		Gravity Simulator
# Author:
#		Samuel Hibbard
# Summary:
#		This will compile all the sources.
##############################################################

sim : gravity.o object.o point.o runSim.o sim.o uiDraw.o uiInteract.o vector.o
	g++ -o sim gravity.o object.o point.o runSim.o sim.o uiDraw.o uiInteract.o vector.o -lglut -lGL -lGLU

###################################################
# Compile individual files
###################################################

gravity.o : gravity.cpp gravity.h object.h
	g++ -c gravity.cpp

object.o : object.cpp object.h vector.h uiDraw.h
	g++ -c object.cpp

point.o : point.cpp point.h
	g++ -c point.cpp

runSim.o : runSim.cpp sim.h uiInteract.h
	g++ -c runSim.cpp

sim.o : sim.cpp sim.h gravity.h uiDraw.h
	g++ -c sim.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

vector.o : vector.cpp vector.h point.h 
	g++ -c vector.cpp

####################################
# Useful commands
####################################
clean : 
	rm sim *.o *~
