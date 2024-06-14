/*
TITLE: CO222 PROJECT MILESTONE 02 /Task 01
AUTHOR: RANASINGHE R.A.W.L (E/20/316)
 */

#include <stdio.h>
#include <stdbool.h>

bool fibonacciChecker(int number_1, int number_2, int number_3);

int main(){
    // Getting the three numbers from the user
    int num1, num2, num3;
    scanf("%d %d %d", &num1, &num2, &num3);

    //printing "TRUE" if fibonacci number of the first number is present and "FALSE" if it is not present
    if (fibonacciChecker(num1, num2, num3)){
        printf("TRUE");
    } else {
        printf("FALSE");
    }

    return 0;
}

bool fibonacciChecker(int number_1, int number_2, int number_3){
    //finding the fibonacci number of the first number
     int previous1 = 1, previous2 = 0, fibonacciNumber;

    if (number_1 < 2){
        fibonacciNumber = number_1;
    }
    for (; number_1 > 1; number_1--){
        fibonacciNumber = previous1 + previous2;
        previous2 = previous1;
        previous1 = fibonacciNumber;
    }
    
    //checking if the second number and the third number matches the fibonacci number
    if (fibonacciNumber == number_2 || fibonacciNumber == number_3){
        return true;
    } else {
        return false;
    }
     
}