##############################################################
# Program:
#		Gravity Simulator
# Author:
#		Samuel Hibbard
# Summary:
#		This will compile all the sources.
##############################################################

sim : object.o point.o driver.o sim.o uiDraw.o uiInteract.o vector.o
	g++ -o sim object.o point.o driver.o sim.o uiDraw.o uiInteract.o vector.o -lglut -lGL -lGLU

###################################################
# Compile individual files
###################################################
object.o : object.cpp object.h vector.h uiDraw.h
	g++ -c object.cpp

point.o : point.cpp point.h
	g++ -c point.cpp

driver.o : driver.cpp sim.h uiInteract.h
	g++ -c driver.cpp

sim.o : sim.cpp sim.h defines.h
	g++ -c sim.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

vector.o : vector.cpp vector.h point.h
	g++ -c vector.cpp

###################################################
# Compile the files in debug mode. This will add
#		all the code that is needed for debugging the
#		code.
###################################################
debug : object.o point.o driver.o simDebug.o uiDraw.o uiInteract.o vector.o
	g++ -o simDebug object.o point.o driver.o simDebug.o uiDraw.o uiInteract.o vector.o -lglut -lGL -lGLU

simDebug.o : sim.cpp sim.h defines.h
	g++ -c -DDEBUG -o simDebug.o sim.cpp

####################################
# Useful commands
####################################
clean :
	rm sim *.o simDebug