#!/bin/bash
g++ `pkg-config --cflags opencv` -std=c++11 -O3 -I.. ../main.cpp `pkg-config --libs opencv` -o Executable.app -lpthread -lX11 -lstdc++ -ldl

