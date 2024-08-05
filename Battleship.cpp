// This program is a Console-Based Player VS AI Battleship game.
// Language: C++
// Sources Used : ChatGPT for error correction/troubleshooting, and cplusplus.com for concepts such as rand and fixing instances of switch cases not working correctly using functions from <limits>
// A lot of the code here is also sourced from the Tic Tac Toe Game I had created, it was helpful in recreating the game while loop with switching turns along with help rebuilding the board matrix
// This code was created as a submittable project for my Object-Oriented Programming class and was made using knowledge and concepts explored in the class along with outside help from the sources specified above

#include <iostream>
#include <cstdlib> // Needed for operation of rand()
#include <limits> // Needed for operation to which clears buffer (Sourced from ChatGPT to solve issues with switch statement, more information about the fix below)

using namespace std;

// Function Prototypes
void printboard(char[][5], int, int);
bool checkloss(int);

int main(){

    // Bool Variables which will help decide the while loop which alternates between the player's and the computer's turn
    bool proceed = true;
    bool done = false;
    int play_again = 1;
    bool menu_exit = false;

    while(menu_exit == false){ // main loop which will run unless user chooses 3 in the switch statement below which will stop the program)

        cout << "************************************************* \n";
        cout << " \n";
        cout << "              Welcome to Battleship! \n";
        cout << " \n";
        cout << "Please choose a number from the following options: \n";
        cout << " \n";
        cout << "1. Play \n";
        cout << "2. How To Play \n";
        cout << "3. Exit \n";
        cout << " \n";
        cout << "************************************************* \n";
        cout << " \n";

        cin >> play_again;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Sourced from chatGPT as I was getting errors with my switch statement where even if I inputted '2' it would go down to case 3 despite me putting a break statement after case 2's code, this solved the issue as it is said to clear the input buffer.

        switch(play_again){
            case 1: { // Code for Battleship game will go here

                cout << " " << endl;
                cout << "Starting Battleship..." << endl;
                cout << " " << endl;
                
                done = false;

                int cmp_ship_count = 0; // Will keep track of amount of ships which the computer has which comes into play for checking loss conditions
                int player_ship_count = 0; // Will keep track of amount of ships which the player has which comes into play for checking loss conditions

                 char board[5][5] = { // The board in which the player will see
                    
                            /* 0    1    2    3    4  */
                    /* 0 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 1 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 2 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 3 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 4 */  {'-' ,'-' ,'-' ,'-' ,'-'}
                    
                };
                
                int user_input_row = 0, user_input_col = 0;
                
                printboard(board, 5, 5);
                
                // For loop which will ask player to input their 5 ship locations
                for (int i = 0; i < 5; i++) {
                    cout << " " << endl;
                    cout << "Enter the row and column number in which you'd like to place a ship (0-4 for each row and column): " << endl;
                    cin >> user_input_row >> user_input_col;
                        if (board[user_input_row][user_input_col] == 'O'){ // If statement checks if spot is already taken by a user's previously inputted coordinates.
                            cout << " " << endl;
                            cout << "Invalid input(s), please choose a coordinate which is not already taken by one of your previous ships." << endl;
                            --i; // if an error occurs we make sure that this does not impact the loop count
                        }
                        else if (user_input_row >= 0 and user_input_row <= 4 and user_input_col >= 0 and user_input_col <= 4){
                            board[user_input_row][user_input_col] = 'O';
                            player_ship_count += 1;
                            cout << " " << endl;
                            printboard(board, 5, 5);
                            cout << " " << endl;
                        }
                        else {
                            // Will run if inputs are outside of the scope of the matrix
                            cout << " " << endl;
                            cout << "Invalid input(s), please be sure that your inputs are between 0 - 4" << endl;
                            --i; // if an error occurs we make sure that this does not impact the loop count
                        }
                    }
                
                cout << " " << endl;
                cout << "Generating locations for opponent's ships..." << endl;

                char cmpboard[5][5] = { // computer's matrix for it's generated random ship coordinates and use later on
                    
                            /* 0    1    2    3    4  */
                    /* 0 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 1 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 2 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 3 */  {'-' ,'-' ,'-' ,'-' ,'-'},
                    /* 4 */  {'-' ,'-' ,'-' ,'-' ,'-'}
                
                };

                // For loop which will generate the locations of the computer's ships.
                for (int i = 0; i < 5; i++) {
                    
                    int rndm_row = rand() % 5; // Generates random number between 0-4 for rows and inputs it into this variable
                    int rndm_col = rand() % 5; // Generates random number between 0-4 for columns and inputs it into this variable
                    
                    // Checks if spot is already taken by player inputted spots
                    if (cmpboard[rndm_row][rndm_col] == 'O' or board[rndm_row][rndm_col] == 'O'){
                        --i;} // This will help to prevent instances of O being called onto a spot with another O in the spot whether it be the own computer's or the players
                    else {
                        cmpboard[rndm_row][rndm_col] = 'O';
                        cmp_ship_count += 1;
                    } // If there is nothing in the way of the generated spot that will be inputted with O
                }
                
                /* cout << " " << endl;
                printboard(cmpboard, 5, 5); // remove before uploading as this is merely for testing purposes */
                cout << " " << endl;
                cout << "The opponent's ships have been positioned. Get ready for battle!" << endl;
                cout << " " << endl;
                
                while (done == false){
                    
                    proceed = true;
                    
                    cout << " " << endl;
                    cout << "Your ship count: " << player_ship_count << endl; // After each attack from both the player and computer we will print out the ship counts of both players to give a sense of score.
                    cout << "Opponent ship count: " << cmp_ship_count << endl;
                    cout << " " << endl;
                    
                    
                    printboard(board, 5, 5);
                    
                    if (checkloss(player_ship_count) == true){ // checks if player has lost right after computer turn
                        cout << " " << endl;
                        cout << "The opponent has won by destroying all of your ships!" << endl;
                        cout << " " << endl;
                        done = true; // After the win condition is met,done = true and the loop will break
                        break;
                    }
                    
                    while (proceed == true){ // While loop also makes sure inputs are not previously checked spots or player's own ship
                        cout << " " << endl;
                        cout << "Choose a row and column to strike on the board: " << endl;
                        cin >> user_input_row >> user_input_col;
                        if (board[user_input_row][user_input_col] == 'O' or board[user_input_row][user_input_col] == 'X' or board[user_input_row][user_input_col] == '~' or board[user_input_row][user_input_col] == 'V'){ // If statement checks if spot on the board is already taken by the player's ships, was previous hit spot by the player, or if it is already a destroyed ship.
                            cout << " " << endl;
                            cout << "Invalid input(s), please choose coordinates which are NOT your own ship(s) or previously attacked spots/ships." << endl;
                        }
                        else if (user_input_row >= 0 and user_input_row <= 4 and user_input_col >= 0 and user_input_col <= 4){
                            proceed = false; // If statement checks if the inputs are inside of the dimensions of the board
                        }
                        else { // will run if inputs are outside of the scope of the board
                            cout << " " << endl;
                            cout << "Invalid input(s), please be sure that your inputs are between 0 - 4" << endl;
                        }
                    }
                    
                    proceed = true; // setting proceed back to true for when the loop returns back to the player's turn
                    
                    if (cmpboard[user_input_row][user_input_col] == 'O'){
                        cout << " " << endl;
                        cout << "You've made a direct hit on an enemy ship!" << endl;
                        cout << " " << endl;
                        cmp_ship_count -= 1; // Removing 1 from ship count as it means that the player has destroyed one of the computer's ships
                        board[user_input_row][user_input_col] = 'V'; // Changes the spot hit to a 'V' to show that they've hit an enemy ship
                        cmpboard[user_input_row][user_input_col] = 'X'; // Changes spot to 'X' on computer board to show it's ship was destroyed
                    }
                    else if (cmpboard[user_input_row][user_input_col] == '-' or cmpboard[user_input_row][user_input_col] == '~'){ // else if you miss an enemy ship
                        cout << " " << endl;
                        cout << "Your strike did not hit any enemy ships." << endl;
                        cout << " " << endl;
                        board[user_input_row][user_input_col] = '~';
                    }
                    
                    printboard(board, 5, 5);
                    
                    if (checkloss(cmp_ship_count) == true){ // checks if computer has lost right after player turn
                        cout << " " << endl;
                        cout << "You have destroyed all of the opponent's ships. You win!" << endl;
                        cout << " " << endl;
                        done = true;
                        break;
                    }
                    
                    cout << " " << endl;
                    cout << "Your ship count: " << player_ship_count << endl; // After each attack from both the player and computer we will print out the ship counts of both players to give a sense of score.
                    cout << "Opponent ship count: " << cmp_ship_count << endl;
                    cout << " " << endl;
                    
                    cout << "The opponent is launching their attack!" << endl;
                    
                    int rndm_row = 0, rndm_col = 0; // putting this here so the variable works for the while loop below and the if statement below it
                    
                    while (proceed == true){ // Another while loop which will make sure the random generated coordinates by the computer don't conflict with already existing entities in the same way as for the player while loop above does
                        
                        rndm_row = rand() % 5; // Generates random number between 0-4 for rows and inputs it into this variable
                        rndm_col = rand() % 5; // Generates random number between 0-4 for columns and inputs it into this variable
                        
                        if (cmpboard[rndm_row][rndm_col] == 'O' or cmpboard[rndm_row][rndm_col] == 'X' or cmpboard[rndm_row][rndm_col] == '~' or cmpboard[rndm_row][rndm_col] == 'V'){ // If statement checks if spot on the board is already taken by the computer's ships, a previous hit spot by the computer, or if it is already a destroyed player ship.
                            continue; // This will go back to the beginning of the loop and regenerate new row and columns in case the if statement above is true, sourced from cplusplus.com
                        }
                        else {
                            proceed = false; // breaking out of the proceed loop if the computer coordinates are in an empty not hit before spot
                        }
                    }
                    
                    if (board[rndm_row][rndm_col] == 'O'){ // If the generated coordinates on the player board show a ship, it will hit said ship
                        cout << " " << endl;
                        cout << "Your ship has been hit by the opponent's attack!" << endl;
                        player_ship_count -= 1; // Removing 1 from player ship count as it means that the computer has destroyed one of the player's ships
                        cmpboard[rndm_row][rndm_col]  = 'V'; // Changes the spot hit to a 'V' to show that they've hit the player's ship
                        board[rndm_row][rndm_col]  = 'X'; // Changes spot to 'X' on player board to show their ship was destroyed
                    }
                        
                    else if (board[rndm_row][rndm_col] == '-' or board[rndm_row][rndm_col] == 'V' or board[rndm_row][rndm_col] == '~'){ // Else if in case the computer hits none of your active ships
                        cout << " " << endl;
                        cout << "The opponent's attack did not hit any of your ships." << endl;
                        cmpboard[rndm_row][rndm_col] = '~';
                        
                    }
                    
                }
                
                break;
            }
                
            case 2: { // Instructions
                cout << " " << endl;
                cout << "In this game, you and a computer will takes turns in trying to destroy eachother's fleet of 5 ships by guessing the coordinates of the opponent's ships on a 5x5 board as shown below." << endl;
                cout << " " << endl;
                cout << "- - - - -" << endl;
                cout << "- - - - -" << endl;
                cout << "- - - - -" << endl;
                cout << "- - - - -" << endl;
                cout << "- - - - -" << endl;
                cout << " " << endl;
                cout << "If you make a wrong guess, you can see '~' where you striked to cross it off as a potential location for the enemy's ships." << endl;
                cout << " " << endl;
                cout << "After inputting your ships, they will appear as 'O'. Once your ships are hit by the opponent they will appear as X. Enemy ships successfully hit by you will appear on your board as 'V'." << endl;
                cout << " " << endl;
                cout << "- V - ~ O" << endl;
                cout << "O - V - -" << endl;
                cout << "- ~ - ~ ~" << endl;
                cout << "- X - ~ O" << endl;
                cout << "O - O - V" << endl;
                cout << " " << endl;
                cout << "Destroy all of the opposing side's ships in order to win!" << endl;
                cout << " " << endl;
                break;
            }
            case 3: { // Exiting Program
                cout << " " << endl;
                cout << "Thank you for playing!" << endl;
                cout << " " << endl;
                menu_exit = true;
                break;
            }
            default: { // Default, user inputs something other than 1, 2, or 3
                cout << " " << endl;
                cout << "Invalid option, please try again!" << endl;
                cout << " " << endl;
                break;
            }
        }
    }
    

   return 0;
}

void printboard(char matrix[][5], int rows, int cols){
    // Nested for loops will run and print out the column and row values within the matrix in a gridlike format to simulate a battleship board
    for(int i = 0; i < rows; i++){ // For loop through the rows
        for(int j = 0; j < cols; j++) // For loop through the cols
        {
            cout << matrix[i][j] << " "; // Printing each instance of the nested for loops before in order to visualize the board in terminal
        }
    cout << endl; // End line after the end of each row in order to better visualize the board.
    }
}

bool checkloss(int ships){ // Function which will check for a loss of either the player or computer and return the appropriate boolean value of true if yes, and false if no.
    if (ships == 0) {
        return true;
    }
    else
    return false;
}

