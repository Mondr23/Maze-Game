
**Maze Game Project (COMP1921 - Programming Project)**

**Project Overview**

This project was part of the COMP1921 module, designed to showcase my ability to apply professional programming practices in a real-world problem scenario. The task involved implementing a Maze Game using C with an emphasis on test-driven development, modular design, and defensive programming techniques. The project required the use of dynamic memory allocation and struct usage to create an efficient, maintainable, and well-documented solution.

**Key Features**

Implemented a game where players navigate through a maze, with movement controlled by WASD keys.
The maze was dynamically loaded from a file and followed a strict specification:
Mazes were composed of walls (#), paths ( ), a start (S), and an exit (E).
The player could view their current position in the maze using the M key, with the player’s position marked by X.
The player starts at the starting point and must reach the exit to win the game.
Comprehensive error handling for invalid maze formats, file errors, and argument errors.
Clear and structured output formats for both the gameplay and error handling.
Modular code breakdown with distinct functionalities to support easy maintenance and scalability.

**Highlights of the Assessment**

Defensive Design: Incorporated robust error handling to ensure that invalid inputs, files, and edge cases were properly managed.
Modularity: Code was broken down into manageable, independent modules to enhance readability and maintainability.
Memory Management: Ensured efficient dynamic memory allocation and deallocation, minimizing memory leaks and ensuring optimal performance.
Documentation: Thoroughly documented code, explaining key logic and decision-making processes, promoting clarity for future maintenance.


**Achievement**
I received a 65.5 out of 70 for this project, reflecting strong performance in functionality, error handling, and code quality. I demonstrated the ability to:

Apply professional programming practices effectively.
Design and implement a robust, modular solution to a complex problem.
Debug and test the solution thoroughly to ensure all requirements were met.


**How to Run the Project**
1. Compile the project using the provided makefile.
2. Run the game with a maze file:
    ./maze <mazefile>