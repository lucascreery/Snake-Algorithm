# Snake Algorithm

## About

This is a computer algorithm that will play the perfect game of snake. It utilizes Hamilton cycles to reach every square and optimizes the algorithm by skipping empty regions of the Hamilton cycle.

1 file:
  * main.cpp

## Prerequisites

  * SFML (Simple Fast Multimedia Library) for C++

## Compiling

```batch
g++ -o snake main.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

## Running

The program can be run through PowerShell:

```batch
./snake [width] [height]
```
[width] is and integer representing the desired width of the snake game measured in blocks, and likewise [height] is the desired height of the snake game.
