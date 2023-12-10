#!/bin/bash

MUSHROOM_PATH="$(dirname "$0")/assets/sprites/mushroom.png"
SHOOTER_PATH="$(dirname "$0")/assets/sprites/shooter.png"
SHOT_PATH="$(dirname "$0")/assets/sprites/shot.png"

g++ -o main src/main.cpp -lraylib -ldl -lpthread -lm -lX11
./main "$MUSHROOM_PATH" "$SHOOTER_PATH" "$SHOT_PATH"
