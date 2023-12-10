#!/bin/bash

RESOURCE_PATH="$(dirname "$0")/assets/sprites/mushroom.png"

g++ -o main src/main.cpp -lraylib -ldl -lpthread -lm -lX11
./main "$RESOURCE_PATH"
