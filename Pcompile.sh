#!/bin/bash

g++ -c utils.cpp
g++ -c pthread.cpp -pthread
g++ psuedo.o utils.o
rm *.o
