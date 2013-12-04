#!/bin/bash

g++ -c utils.cpp
g++ -c utils.hpp
g++ -c psuedo.cpp
g++ psuedo.o utils.o
rm *.o