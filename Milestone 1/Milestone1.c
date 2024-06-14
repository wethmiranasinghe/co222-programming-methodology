/*
TITLE: CO222 PROJECT MILESTONE 01
AUTHOR: RANASINGHE R.A.W.L (E/20/316)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Declaring functions
void TwoD_array(char *string,int Height, int Width); // function to create the 2D array
int shortestDistance(int Starting_row, int Starting_column, int Ending_row, int Ending_coumn, int Height, int Width, char starting_char, char ending_char); // Function to find the shortest distance

//Creating Global arrays 
char map_string[250]; // Array to get the string
char map[200][200]; // 2D array to create the map

// Defining a Cell in  the map
typedef struct {
    int ROW, COLUMN; // the row number and the column number of the cell
    int distance; // distance to the ending position from the starting position
} Cell;


int main(){
    // Declaring variables
    int H, W, S1, S2, E1, E2;
    char Starting_Character, Ending_Character;
    int shortest_distance;
    
    // Getting the user inputs
    printf("");
    scanf("%d %d", &H, &W); // Getting the Height and the Width of the map
    printf("");
    scanf("%d %d", &S1, &S2); // Getting the starting points (The starting row number and the column number)
    printf("");
    scanf("%d %d", &E1, &E2); // Getting the ending points (The ending row number and the column number)
    getchar();
    scanf("%s", map_string); // Gettting the string for thecreation of the map

    // Finding the Starting character and the ending character
    Starting_Character = map_string[ S1 * W + S2];
    Ending_Character = map_string[ E1 * W + E2];

    // Creating the 2D array
    TwoD_array(map_string, H, W);

    // printing the 2D arrray
    int i,j;
    for (i = 0; i < H; i++ ){
        for (j = 0; j < W; j++){
                printf("%c ", map[i][j]);
            }
            printf("\n");
        }

    // Getting the shortest distance
    shortest_distance = shortestDistance(S1, S2, E1, E2, H, W, Starting_Character, Ending_Character);
    if (shortest_distance != -1){
        printf("The minimum distance from %c to %c is %d\n", Starting_Character, Ending_Character, shortest_distance);
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


// Finding the shortest distance using the Breadth First Search algorithm
int shortestDistance(int Starting_row, int Starting_column, int Ending_row, int Ending_coumn,int Height, int Width, char starting_char, char ending_char){

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

    //Using the BFS algorithm to find the shoortest distance
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
    printf("There is no possible path from %c to %c", starting_char, ending_char);
    return -1;
}