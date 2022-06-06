# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: scene.o tinyxml2.o mesh.o camera.o material.o raytracing.o
	$(CC) $(CFLAGS) -o main scene.o raytracing.o tinyxml2.o mesh.o camera.o material.o
 
# The main.o target can be written more simply
 
scene.o: scene.cpp raytracing.h tinyxml2.h 
	$(CC) $(CFLAGS) -c scene.cpp
 
raytracing.o: raytracing.h mesh.hpp camera.hpp

tinyxml2.o: tinyxml2.h
 
mesh.o: mesh.hpp material.hpp

camera.o: camera.hpp vec3.h

material.o: material.hpp vec3.h

