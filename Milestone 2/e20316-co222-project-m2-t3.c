/*
TITLE: CO222 PROJECT MILESTONE 02 /Task 03
AUTHOR: RANASINGHE R.A.W.L (E/20/316)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DIST 2147483647

// Declaring functions
void TwoD_array(char *string,int Height, int Width); // function to create the 2D array
int shortestDistance(int Starting_row, int Starting_column, int Ending_row, int Ending_coumn, int Height, int Width); // Function to find the shortest distance
int fibonacci_number(int number); // function to find the fibonacci number

// Creating Global arrays 
char map_string[250]; // Array to get the string
char map[200][200]; // 2D array to create the map
int door_cells[100][100]; // 2D array to get the door cells
int teleportationDoors[2][2]; // 2D Array to represent teleportation doors

// Defining the new data type, Cell
typedef struct {
    int ROW, COLUMN; // the row number and the column number of the cell
    int distance; // distance to the ending position from the starting position
} Cell;


int main(){
    // Declaring variables
    int H, W, S1, S2, E1, E2, M1, M2, ND, TR1, TC1, TR2, TC2;
    int calculated_number;
    char Starting_Character, Ending_Character;
    int shortest_dist_S_to_E;
    int shortest_dist_TD1_TD2;
    int shortest_dist_TD2_TD1;
    
    // Getting the user inputs
    printf("");
    scanf("%d %d", &H, &W); // Getting the Height and the Width of the map
    printf("");
    scanf("%d %d", &S1, &S2); // Getting the starting points (The starting row number and the column number)
    printf("");
    scanf("%d %d", &E1, &E2); // Getting the ending points (The ending row number and the column number)
    getchar();
    scanf("%s", map_string); // Gettting the string for thecreation of the map
    printf("");
    scanf("%d", &M1); // Getting the first integer for matching the fibonacci number
    printf("");
    scanf("%d", &M2); // Getting the second integer for matching the fibonacci number
    printf("");
    scanf("%d", &ND); // Getting the number of door cells
    
    // Getting integers for each door cell position
    int count;
    for (count = 0; count<ND; count++){
        printf("");
        scanf("%d %d", &door_cells[count][0], &door_cells[count][1]);
    }

    // Creating the 2D array
    TwoD_array(map_string, H, W);

    // Finding the Starting character and the ending character
    Starting_Character = map_string[ S1 * W + S2];
    Ending_Character = map_string[ E1 * W + E2];

    int n = 0;
    for (count = 0; count<ND; count++){
        calculated_number = (door_cells[count][0] * W) + door_cells[count][1];
        int fibonacciNumber = fibonacci_number(calculated_number);
        if ((fibonacciNumber == M1 || fibonacciNumber == M2) && n<2){
            teleportationDoors[n][0] = door_cells[count][0];
            teleportationDoors[n][1] = door_cells[count][1];
            n++;
        }
    }

    shortest_dist_S_to_E = shortestDistance(S1,S2,E1,E2,H,W);
    
    // Using teleportation door 1 first
    int shortest_dist_S_to_TD1 = shortestDistance(S1,S2,teleportationDoors[0][0],teleportationDoors[0][1],
    H,W);
    int shortest_dist_TD2_to_E = shortestDistance(teleportationDoors[1][0],teleportationDoors[1][1],E1,E2,H,W);
    // Shortest distance if I use teleportation door1 first
    shortest_dist_TD1_TD2 = shortest_dist_S_to_TD1 + shortest_dist_TD2_to_E;
    
    // Using teleportation door 2 first
    int shortest_dist_S_to_TD2 = shortestDistance(S1,S2,teleportationDoors[1][0],teleportationDoors[1][1],
    H,W);
    int shortest_dist_TD1_to_E = shortestDistance(teleportationDoors[0][0],teleportationDoors[0][1],E1,E2,H,W);
    
    // Shortest distance if I use teleportation door2 first
    shortest_dist_TD2_TD1 = shortest_dist_S_to_TD2 + shortest_dist_TD1_to_E;
    
    // printing invalid paths
    if (shortest_dist_S_to_E == -1 && (shortest_dist_S_to_TD1 == -1 || shortest_dist_TD2_to_E == -1) &&(shortest_dist_S_to_TD2 == -1 || shortest_dist_TD1_to_E == -1)){
        printf("There is no possible path from %c to %c", Starting_Character, Ending_Character);
        return 0;
    }
    
    // giving large numbers for invalid paths 
    if (shortest_dist_S_to_E == -1){
        shortest_dist_S_to_E = MAX_DIST; 
    } 
    if (shortest_dist_S_to_TD1 == -1 || shortest_dist_TD2_to_E == -1){
        shortest_dist_TD1_TD2 = MAX_DIST;
    } 
    if (shortest_dist_S_to_TD2 == -1 || shortest_dist_TD1_to_E == -1){
        shortest_dist_TD2_TD1 = MAX_DIST;
    }
        
    // Finding the minimum distance path and printing it
    if (shortest_dist_S_to_E <= shortest_dist_TD1_TD2){
        if (shortest_dist_S_to_E <= shortest_dist_TD2_TD1){
            printf("The minimum distance from %c to %c is %d", Starting_Character, 
            Ending_Character, shortest_dist_S_to_E);
        } else {
            printf("The minimum distance from %c to %c is %d", Starting_Character, 
            Ending_Character, shortest_dist_TD2_TD1);
        }
    } else {
        printf("The minimum distance from %c to %c is %d", Starting_Character, 
        Ending_Character, shortest_dist_TD1_TD2);
    }
    return 0;  
}


// Creating a 2D array for a given string
void TwoD_array(char *string,int Height, int Width){
    int i,j;
    int index = 0;
    int len_of_string = strlen(string);

    for (i = 0; i < Height;i++){
        for (j = 0; j < Width; j++){
            if (index < len_of_string){
                map[i][j] = string[index++];  
            }
        }
    }
}

//function to find the fibonacci number of a number
int fibonacci_number(int number){
     int previous1 = 1, previous2 = 0, fibonacciNumber;

    if (number < 2){
        fibonacciNumber = number;
        return fibonacciNumber;
    }
    for (; number > 1; number--){
        fibonacciNumber = previous1 + previous2;
        previous2 = previous1;
        previous1 = fibonacciNumber;
    }
    return fibonacciNumber;
}

// Finding the shortest distance using the Breadth First Search algorithm
int shortestDistance(int Starting_row, int Starting_column, int Ending_row, int Ending_coumn,int Height, int Width){

    // array to check the visited cells
    bool visited[Height][Width];
    memset(visited, false, sizeof(visited));

    // Defining the possible moves
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    // Creating a queue for BFS
    Cell queue[Height * Width];
    int front = 0;
    int rear = 0;

    //Enqueuing the starting cell to the queue
    Cell Starting_cell = {Starting_row, Starting_column, 0};
    queue[rear++] = Starting_cell;
    visited[Starting_cell.ROW][Starting_cell.COLUMN] = true;

    //Using the BFS algorithm to find the shortest distance
    while (front != rear) {
        // Dequing the current cell from the queue
        Cell current_cell = queue[front++];

        // Checking whether we have reached the destination
        if (current_cell.ROW == Ending_row && current_cell.COLUMN == Ending_coumn){
            return current_cell.distance;
        }

        // Checking all the possible moves
        for (int index = 0; index < 4; index++){
            int new_row = current_cell.ROW + rowNum[index];
            int new_column = current_cell.COLUMN + colNum[index];

            // Checking the new Cell whether its visited
            if (!visited[new_row][new_column]){

                // Finding the difference of characters in the new cell and current cell
                int difference = map[new_row][new_column] - map[current_cell.ROW][current_cell.COLUMN];

                // Checking whether we can move forward
                if ((difference > 0 && difference <= 2) || (difference > -4 && difference <= 0)){

                    // Enquing the new cell to the queue
                    Cell new_cell = {new_row, new_column, current_cell.distance + 1};
                    queue[rear++] = new_cell;
                    visited[new_row][new_column] = true;
                }
            }
        }    
    }

    // If there is no possible path for a given input
    return -1;
}