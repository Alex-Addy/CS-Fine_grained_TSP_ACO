#!/bin/bash

g++ -c utils.cpp -pthread
g++ -c utils.hpp 
g++ -c pthread.cpp -pthread
g++ pthread.o utils.o -pthread
rm *.o
