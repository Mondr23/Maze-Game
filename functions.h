#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define maximum and minimum dimensions for the maze
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required autograder exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

typedef struct __Coord
{
    int x;
    int y;
} coord;

typedef struct __Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;

// functions prototypes
int create_maze(maze *this, int height, int width);
void free_maze(maze *this);
int get_width(FILE *file);
int get_height(FILE *file);
int read_maze(maze *this, FILE *file);
int check_maze(maze *this,int height);
void print_maze(maze *this, coord *player);
void move(maze *this, coord *player, char direction);
int check_move(maze *this, int new_Row, int new_Col);
int has_won(maze *this, coord *player);

#endif
