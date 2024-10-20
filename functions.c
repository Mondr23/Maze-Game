#include "functions.h"

/** @brief this function is used to allocate memory for maze.
 * @param  this a pointer to maze object to be intialised.
 * @param  height a height of the maze  to allocate.
 * @param  width a width of teh maze  to allocate.
 */
int create_maze(maze *this, int height, int width)
{
    // declare height and width
    this->height = height;
    this->width = width;

    // set memory for the map
    this->map = (char **)malloc(height * sizeof(char *));

    // check memory location
    if (this->map == NULL)
    {
        printf("EROROR memeory  ");
        return EXIT_ARG_ERROR; // seting memory faild
    }
    // loop through each row in the maze
    for (int i = 0; i < height; i++)
    {
        this->map[i] = (char *)malloc(width * sizeof(char));
        if (this->map[i] == NULL)
        {
            printf("EROROR #  ");
            return EXIT_ARG_ERROR; // seting memory faild
        }
    }
    return EXIT_SUCCESS; // success
}
/**
 * @brief  this function is used to deallocate the maze from the memory.
 * @param pointer to maze struct to free it.
 */
void free_maze(maze *this)
{
    // loop through each row of the maze is map.
    for (int i = 0; i < this->height; i++)
    {
        free(this->map[i]);
    }
    // deallocate teh memory of the maze
    free(this->map);
}
/**
 * @brief this function is used to validate the width and return it
 * @param file the file pointer to check width
 * @return return valid width or 0 for error.
 */
int get_width(FILE *file)
{
    fseek(file, 0, SEEK_SET); // Move file pointer to beginning

    int width = 0;
    char chars;

    // read chars from file one by one till end of the file
    while ((chars = fgetc(file)) != EOF)

    {
        if (chars == '\n')
        {

            // Check if width is within permitted dimension
            if (width >= MIN_DIM && width <= MAX_DIM)
            {
                return width;
            }
            else
            {
                printf("ERROR: Width is invalid\n");
                fclose(file);
                return EXIT_MAZE_ERROR;
            }
            width = 0;
        }

        width++;
    }

    return width;
}
/**
 * @brief this function is used to validate the heigh and return it
 * @param file the file pointer to check height
 * @return  return valid height or 0 for error.
 */
int get_height(FILE *file)
{
    fseek(file, 0, SEEK_SET); // Move file pointer to beginning

    int height = 0;
    char chars[MAX_DIM];

    // read chars from file one by one till end of the file
    while (fgets(chars, sizeof(chars), file) != NULL)
    {
        height++;
    }

    // Check if height is within permited dimension
    if (height >= MIN_DIM && height <= MAX_DIM)
    {
        return height;
    }
    else
    {
        printf("ERROR: Height is invalid \n");
        fclose(file);
        return EXIT_MAZE_ERROR; // return error
    }
}
/**
 *  @brief this function is used to read the maze file into struct and validate the startingand end point in it.
 * @param this maze struct
 * @param file pointer of the maze
 * @return 0 on sucess or 0 on fail.
 */
int read_maze(maze *this, FILE *file)
{
    // Get height and width from maze map
    this->height = get_height(file);
    this->width = get_width(file);

    // return zero if height and width are zero.
    if (this->height == 0 || this->width == 0)
    {
        return EXIT_MAZE_ERROR;
    }

    // Rewind the file pointer to the beginning of file
    rewind(file);

    // Allocate memory for the map
    if (create_maze(this, this->height, this->width) != 0)
    {
        return EXIT_MAZE_ERROR;
    }

    // Read the maze from the file
    char mazeChars;
    int row = 0;
    int col = 0;
    char startS = 0;
    char endE = 0;

    // read the chars of the file till the end of it.
    while ((mazeChars = fgetc(file)) != EOF)
    {
        // detrmain the end of the line
        if (mazeChars == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            this->map[row][col] = mazeChars;

            // find the Start point of the maze
            if (mazeChars == 'S')
            {
                this->start.x = col;
                this->start.y = row;
                startS += 1;
            }
            // find the End point of the maze
            else if (mazeChars == 'E')
            {
                this->end.x = col;
                this->end.y = row;
                endE += 1;
            }
            // return error if there is an char apart from allowed chars in maze
            else if (mazeChars != ' ' && mazeChars != '#' && mazeChars != 'S' && mazeChars != 'E') // Validate characters within the rows
            {
                printf("Invalid character found in the maze\n");
                return EXIT_MAZE_ERROR;
            }

            col++;
        }
    }
    // return error if there is no end point or start point in the maze file
    if (startS == 0 || endE == 0)
    {
        printf("The maze does not contain 'S' or 'E.\n");
        return EXIT_MAZE_ERROR;
    }
    // return error if there are more than end point and start point in the maze file
    if (startS >= 2 || endE >= 2)
    {
        printf("The maze contains multiple 'S' or 'E.\n");
        return EXIT_MAZE_ERROR;
    }

    return EXIT_SUCCESS; // Success
}
/**
 * @brief this function is used to check the length of the rows in the maze.
 * @param this maze struct.
 * @param height of the maze to be used to check  length of the rows
 * @return true if all rows have the same length or 0 if the are different.
 */
int check_maze(maze *this, int height)
{
    // Check the first row length
    int f_RowLength = strlen(this->map[0]);

    // loop through each row of the maze
    for (int i = 0; i < height; i++)
    {

        int rowsLength = strlen(this->map[i]);
        // Check if the current row is not empty and its length is different from the length of the first row
        if (rowsLength != 0 && rowsLength != f_RowLength)
        {
            printf("Row %d has a different length\n", i + 1);
            return EXIT_MAZE_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief this function is used to print the maze out
 * @param this maze struct.
 * @param player refers to the current player position.
 */
void print_maze(maze *this, coord *player)
{
    // print new empty line at the beginng
    printf("\n");
    // loop through the maze
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // print X to refer to th eplayer position in the maze
            if (i == player->y && j == player->x)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        // end each row with a new line.
        printf("\n");
    }
}
/**
 * @brief this function is used to  preforme given direction
 * @param this maze struct.
 * @param player refers to the current player position.
 * @param desired direction to move in
 */
void move(maze *this, coord *player, char direction)
{
    // get the row and the coloum position of the playe
    int new_Col = player->x;
    int new_Row = player->y;

    // handle movment direction
    switch (direction)
    {
    case 'W':
    case 'w':
        new_Row--; // move up
        break;
    case 'A':
    case 'a':
        new_Col--; // move left
        break;
    case 'S':
    case 's':
        new_Row++; // move down
        break;
    case 'D':
    case 'd':
        new_Col++; // move right
        break;
    }
    // check if the move is valid
    if (check_move(this, new_Row, new_Col))
    {
        // update palyer is position
        player->x = new_Col;
        player->y = new_Row;
    }
}
/**
 * @brief this function is used to validate the new move of the player
 * @param this maze struct.
 * @param new_row row coordinate of new position
 * @param new_col column coordinate of new position
 * @return 1 on success move or 0 on invalid move
 */
int check_move(maze *this, int new_Row, int new_Col)
{
    // check if new position is within permited boundaraies and the new move is valid
    if (new_Col >= 0 && new_Col < this->width && new_Row >= 0 && new_Row < this->height &&
        this->map[new_Row][new_Col] != '#' && this->map[new_Row][new_Col] != '\n')
    {
        return 1; // return success
    }
    else
    {
        printf("Invalid move. Cannot move into a wall or out of the borders.\n");
        return 0;
    }
}
/**
 * @brief this function is used to check if the player has reached to the end point.
 * @param  this maze struct.
 * @param  player refers to the current player position.
 * @return return 1 if the player reaches the end point E
 */
int has_won(maze *this, coord *player)
{
    return (player->x == this->end.x && player->y == this->end.y);
}
