#!/bin/bash
g++ `pkg-config --cflags opencv` -std=c++11 -O3 ../main.cpp ../Subject.cpp `pkg-config --libs opencv` -o MegaFaceJson.app