#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    // check the number of command-line arguments is provided
    if (argc != 2)
    {
        printf("ERROR Usage: %s <mazefile path>\n", argv[0]);
        return EXIT_ARG_ERROR;
    }

    // Open the maze file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file '%s'\n", argv[1]);
        return EXIT_FILE_ERROR;
    }

    // Initialize a maze object
    maze this_maze;

    // Read the maze data from the file into the maze object
    if (read_maze(&this_maze, file) != 0)
    {
        printf("Error: Invalid maze\n");
        fclose(file);
        return EXIT_MAZE_ERROR;
    }

    // Check if all rows have the same length
    if (check_maze(&this_maze, this_maze.height) != 0)
    {
        free_maze(&this_maze);
        return EXIT_MAZE_ERROR;
    }

    fclose(file);

    // Initialize the player's position
    coord player = this_maze.start;

    // print the maze
    print_maze(&this_maze, &player);

    char input;

    // Main game loop
    while (1)
    {

        printf("Enter your move (W/A/S/D/M(MAP)): ");
        scanf(" %c", &input);

        if (input == 'M' || input == 'm')
        {
            // show map option
            printf("Map:\n");
            print_maze(&this_maze, &player);
        }
        else if (input == 'W' || input == 'w' || input == 'S' || input == 's' || input == 'A' || input == 'a' || input == 'D' || input == 'd')
        {
            // move the player according to its input
            move(&this_maze, &player, input);

            // Check if the player has reached the exit
            if (has_won(&this_maze, &player))
            {
                printf("Congratulations! You have won!!!.\n");
                break;
            }
        }
        else
        {
            printf("INVALID INPUT!!!\n");
        }
    }
    free_maze(&this_maze);

    return EXIT_SUCCESS;
}
