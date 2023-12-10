#!/bin/bash

RESOURCE_PATH="$HOME/Pictures/Sprites/mushroom.png"

g++ -o main src/main.cpp -lraylib -ldl -lpthread -lm -lX11
./main "$RESOURCE_PATH"
