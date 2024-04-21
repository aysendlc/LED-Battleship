#include <FastLED.h>

// Define our LED PINS based off each GRID for both PLAYERS
#define NUM_LEDS     9 // Change this to the number of LEDs in your strips
#define BRIGHTNESS  10  // LED brightness

// Player 1 Bottom Screen
// TOP OF SCREEN
#define LEDPLAYER1_BOTTOMPIN1     2
#define LEDPLAYER1_BOTTOMPIN2     3
#define LEDPLAYER1_BOTTOMPIN3     4
#define LEDPLAYER1_BOTTOMPIN4     5
#define LEDPLAYER1_BOTTOMPIN5     6
#define LEDPLAYER1_BOTTOMPIN6     7
#define LEDPLAYER1_BOTTOMPIN7     8
#define LEDPLAYER1_BOTTOMPIN8     9
#define LEDPLAYER1_BOTTOMPIN9     10
// BOTTOM OF SCREEN

// Player 1 Top Screen
// TOP OF SCREEN
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
#define LEDPLAYER1_TOPPIN1     2
// BOTTOM OF SCREEN

// Player 2 Bottom Screen
// TOP OF SCREEN
#define LEDPLAYER2_BOTTOMPIN1     2
#define LEDPLAYER2_BOTTOMPIN2     3
#define LEDPLAYER2_BOTTOMPIN3     4
#define LEDPLAYER2_BOTTOMPIN4     5
#define LEDPLAYER2_BOTTOMPIN5     6
#define LEDPLAYER2_BOTTOMPIN6     7
#define LEDPLAYER2_BOTTOMPIN7     8
#define LEDPLAYER2_BOTTOMPIN8     9
#define LEDPLAYER2_BOTTOMPIN9     10
// BOTTOM OF SCREEN

// Player 2 Top Screen
// TOP OF SCREEN
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
#define LEDPLAYER2_TOPPIN1     2
// BOTTOM OF SCREEN


// Now Define our DPAD and SELECT buttons for each player

// Player 1 Buttons 
#define BUTTON_UP_PLAYER1    0  // Pin for the UP button 
#define BUTTON_DOWN_PLAYER1  1  // Pin for the DOWN button
#define BUTTON_LEFT_PLAYER1  11  // Pin for the LEFT button
#define BUTTON_RIGHT_PLAYER1 12  // Pin for the RIGHT button
#define BUTTON_SELECT_PLAYER1 13 // Pin for the SELECT button

// Player 2 Buttons
#define BUTTON_UP_PLAYER2   0  // Pin for the UP button
#define BUTTON_DOWN_PLAYER2  1  // Pin for the DOWN button
#define BUTTON_LEFT_PLAYER2  11  // Pin for the LEFT button
#define BUTTON_RIGHT_PLAYER2 12  // Pin for the RIGHT button
#define BUTTON_SELECT_PLAYER2 13 // Pin for the SELECT button


#define COLOR_ON    CRGB::White   // Color when LED is ON
#define COLOR_OFF   CRGB::Red   // Color when LED is OFF
#define COLOR_SHIP   CRGB::Blue // Color of LED where ships are
#define COLOR_GREEN CRGB(0, 255, 0) // Full green

// Create enumerations of the different ships
enum Ship { NONE, SHIP1, SHIP2, SHIP3, SHIP4 };

// Create enumerations of the different orentation states
enum Orientation { HORIZONTAL_LEFT,  HORIZONTAL_RIGHT, VERTICAL_UP, VERTICAL_DOWN, ORIENTATION_NONE};

// Create enumerations of the different game states
enum GameState { SELECTING_LOCATION, SELECTING_ORIENTATION, PLACING_SHIP, SHOOTING, ENDGAME };

// Create another enumaration for the different players
enum Player { PLAYER1, PLAYER2 };


// Set the current values of our enumerations for use
// These are global variables so they can be used in functions later
Ship currentShip = SHIP1;
Orientation currentOrientation = HORIZONTAL_LEFT;
GameState currentState = SELECTING_LOCATION;
Player currentPlayer = PLAYER1;


CRGB ledsPLAYER1TOP[9][NUM_LEDS];
CRGB ledsPLAYER1BOTTOM[9][NUM_LEDS];
CRGB ledsPLAYER2TOP[9][NUM_LEDS];
CRGB ledsPLAYER2BOTTOM[9][NUM_LEDS];

int currentRow = 0; // Initial row index
int currentCol = 0; // Initial column index

// 2D arrays representing the ship locations for both players
bool gridShipPLAYER1[9][NUM_LEDS]; 
bool gridShipPLAYER2[9][NUM_LEDS]; 

// 2D arrays representing the locations of hits and misses for both players
bool gridHitsPLAYER1[9][NUM_LEDS];
bool gridHitsPLAYER2[9][NUM_LEDS];



void setup() {
    // Initialize our LED Grids

    // Player 1 Bottom Screen
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN1, GRB>(ledsPLAYER1BOTTOM[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN2, GRB>(ledsPLAYER1BOTTOM[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN3, GRB>(ledsPLAYER1BOTTOM[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN4, GRB>(ledsPLAYER1BOTTOM[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN5, GRB>(ledsPLAYER1BOTTOM[4], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN6, GRB>(ledsPLAYER1BOTTOM[5], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN7, GRB>(ledsPLAYER1BOTTOM[6], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN8, GRB>(ledsPLAYER1BOTTOM[7], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_BOTTOMPIN9, GRB>(ledsPLAYER1BOTTOM[8], NUM_LEDS);
    // Player 1 Top Screen
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN1, GRB>(ledsPLAYER1TOP[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN2, GRB>(ledsPLAYER1TOP[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN3, GRB>(ledsPLAYER1TOP[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN4, GRB>(ledsPLAYER1TOP[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN5, GRB>(ledsPLAYER1TOP[4], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN6, GRB>(ledsPLAYER1TOP[5], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN7, GRB>(ledsPLAYER1TOP[6], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN8, GRB>(ledsPLAYER1TOP[7], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER1_TOPPIN9, GRB>(ledsPLAYER1TOP[8], NUM_LEDS);

    // Player 2 Bottom Screen
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN1, GRB>(ledsPLAYER2BOTTOM[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN2, GRB>(ledsPLAYER2BOTTOM[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN3, GRB>(ledsPLAYER2BOTTOM[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN4, GRB>(ledsPLAYER2BOTTOM[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN5, GRB>(ledsPLAYER2BOTTOM[4], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN6, GRB>(ledsPLAYER2BOTTOM[5], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN7, GRB>(ledsPLAYER2BOTTOM[6], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN8, GRB>(ledsPLAYER2BOTTOM[7], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_BOTTOMPIN9, GRB>(ledsPLAYER2BOTTOM[8], NUM_LEDS);

    // Player 2 Top Screen
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN1, GRB>(ledsPLAYER2TOP[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN2, GRB>(ledsPLAYER2TOP[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN3, GRB>(ledsPLAYER2TOP[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN4, GRB>(ledsPLAYER2TOP[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN5, GRB>(ledsPLAYER2TOP[4], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN6, GRB>(ledsPLAYER2TOP[5], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN7, GRB>(ledsPLAYER2TOP[6], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN8, GRB>(ledsPLAYER2TOP[7], NUM_LEDS);
    FastLED.addLeds<WS2812B, LEDPLAYER2_TOPPIN9, GRB>(ledsPLAYER2TOP[8], NUM_LEDS);


    FastLED.setBrightness(BRIGHTNESS);

    // Initialize button pins as INPUT with pull-up resistors
    pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
    pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_SELECT, INPUT_PULLUP);
    lightUpLED(currentRow, currentCol, currentOrientation); 

    // Initialize grid arrays to false/0
    memset(gridShipPLAYER1, 0, sizeof(gridShipPLAYER1));
    memset(gridShipPLAYER2, 0, sizeof(gridShipPLAYER2)); 
    memset(gridHitsPLAYER1, 0, sizeof(gridHitsPLAYER1));
    memset(gridHitsPLAYER2, 0, sizeof(gridHitsPLAYER2)); 
}

// LEDs begin at 
void loop() {

    // Handle game state transitions and actions
    switch(currentState) {
        case SELECTING_LOCATION:
            handleMovement();
            // Highlight the current LED to indicate potential starting point of the ship
            lightUpLED(currentRow, currentCol, currentOrientation);
            break;

        case SELECTING_ORIENTATION:
            // Change orientation with button presses (left/right can toggle orientation)
            // Implement a function to handle this (not provided in your code)
            handleOrientationChange();
            lightUpLED(currentRow, currentCol, currentOrientation);
            break;

        case PLACING_SHIP:
            // Place the ship on the grid
            placeShip();
            // Go to the next ship or state after placing
            // Implement logic to advance to the next ship or next game phase
            advanceToNextShipOrState();
            break;

        case SHOOTING:
            // now that we are here, we need to call our shooting function to allow players to shoot
            if (currentPlayer == PLAYER1) {
                handleTargetSelection(ledsPLAYER1TOP);
            } else {
                handleTargetSelection(ledsPLAYER2TOP);
            }
            break;
        
        case ENDGAME:
            // since we made it here, now we want to end the game and display the winner

    }

    // Handle select button actions - this might need to be moved or adjusted
    // based on how you want to trigger state transitions
    handleSelection();
}

// Function to light up the LED at given row and column based on game state
void lightUpLED(int row, int col, Orientation orientation) {
    // Clear only the current LED, keeping the state of other LEDs intact
    FastLED.clear();
    updateBottomLEDsBasedOnGrid();

    if (orientation == ORIENTATION_NONE) {
        // Light up the current LED to a different color to show selection
        leds[row][col] = COLOR_ON; 
    } else  {
        // Light up LEDs in a line based on the ship's orientation and length
        int shipLength = getShipLength(currentShip);

        // Handle all four orientations
        switch (orientation) {
            case HORIZONTAL_LEFT:
                for (int i = col; i >= col - shipLength + 1 && i >= 0; i--)
                    leds[row][i] = COLOR_ON;
                break;
            case HORIZONTAL_RIGHT:
                for (int i = col; i < col + shipLength && i < NUM_LEDS; i++)
                    leds[row][i] = COLOR_ON;
                break;
            case VERTICAL_UP:
                for (int i = row; i >= row - shipLength + 1 && i >= 0; i--)
                    leds[i][col] = COLOR_ON;
                break;
            case VERTICAL_DOWN:
                for (int i = row; i < row + shipLength && i < 9; i++)
                    leds[i][col] = COLOR_ON;
                break;
        }
    }
    FastLED.show(); // Update LEDs
}

// Function to handle orientation change
void handleOrientationChange() {
    int shipLength = getShipLength(currentShip);


    // Check if we need to change our orientation in all directions so we dont start in illegal spot
    // Switch our starting orientation to a valid orientation
    if (currentCol + shipLength <= NUM_LEDS) {
        currentOrientation = HORIZONTAL_RIGHT;
    } else if (currentRow + shipLength <= 9) {
        currentOrientation = VERTICAL_DOWN;
    } else if (currentRow - shipLength + 1 >= 0) {
        currentOrientation = VERTICAL_UP;
    } else if (currentCol - shipLength + 1 >= 0) {
        currentOrientation = HORIZONTAL_LEFT;
    }

    // Now change the orientation of our ship and when selected, we place the ship.
    if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
        // Check if ship will go off-grid on the left
        if(currentCol - shipLength + 1 >= 0)
            currentOrientation = HORIZONTAL_LEFT;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
        // Check if ship will go off-grid on the right
        if(currentCol + shipLength <= NUM_LEDS)
            currentOrientation = HORIZONTAL_RIGHT;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_UP_PIN) == LOW) {
        // Check if ship will go off-grid on the top
        if(currentRow - shipLength + 1 >= 0)
            currentOrientation = VERTICAL_UP;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
        // Check if ship will go off-grid on the bottom
        if(currentRow + shipLength <= 9)
            currentOrientation = VERTICAL_DOWN;
        delay(200); // Button debounce delay
    }
}

void handleMovement() {
    // Move the LED based on button presses
    if (digitalRead(BUTTON_UP_PIN) == LOW && currentRow < 8) {
        currentRow++;
        lightUpLED(currentRow, currentCol, currentOrientation); 
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_DOWN_PIN) == LOW && currentRow > 0) {
        currentRow--;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_LEFT_PIN) == LOW && currentCol > 0) {
        currentCol--;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW && currentCol < 8) {
        currentCol++;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    }
}

void handleSelection() {
    if (digitalRead(BUTTON_SELECT) == LOW) {
        delay(200); // Button debounce delay

        if (currentState == SELECTING_LOCATION) {
            currentState = SELECTING_ORIENTATION;
        } else if (currentState == SELECTING_ORIENTATION) {
            currentState = PLACING_SHIP;
        }
    }
}

// Function for selecting where want to attack. we will then call our handleAttack function when attacking
void handleTargetSelection(CRGB leds[9][NUM_LEDS]) {
    // Use button inputs to select the grid cell to attack
    handleMovement();  // Re-use the movement handling for navigation

    // Light up the current selection on the grid
    lightUpLED(currentRow, currentCol, ORIENTATION_NONE);  // Assuming ORIENTATION_NONE is for single cell highlight

    if (digitalRead(BUTTON_SELECT) == LOW) {
        delay(200);  // Debounce delay
        handleAttack(currentRow, currentCol);
        updateShootingDisplays();
    }
}

// Function for handling the shooting phase of the game
void handleAttack(int row, int col) {
    bool *enemyGrid = currentPlayer == PLAYER1 ? gridPLAYER2 : gridPLAYER1;
    bool *hitGrid = currentPlayer == PLAYER1 ? hitsPLAYER2 : hitsPLAYER1;

    if (hitGrid[row][col]) {
        Serial.println("Already attacked this position!");
        return;  // Skip this turn or ask for a new input
    }

    // Mark this position as attacked
    hitGrid[row][col] = true;

    if (enemyGrid[row][col]) {
        // Hit
        leds[row][col] = CRGB::Red; // Indicate hit
        Serial.println("Hit!");
    } else {
        // Miss
        leds[row][col] = CRGB::White; // Indicate miss
        Serial.println("Miss");
    }
    FastLED.show();

    // Check if all ships are sunk by comparing the hitgrids and grids where the ships are
    if (checkAllShipsSunk(enemyGrid, hitGrid)) {
        Serial.println("Game Over! " + String(currentPlayer == PLAYER1 ? "Player 2" : "Player 1") + " wins!");
        currentState == ENDGAME;
    }

    // Switch player unless the game is over
    if (currentState != ENDGAME) {
        currentPlayer = currentPlayer == PLAYER1 ? PLAYER2 : PLAYER1;
    }
}

bool checkAllShipsSunk(const bool enemyGrid[9][NUM_LEDS], const bool hitGrid[9][NUM_LEDS]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < NUM_LEDS; j++) {
            // Check each cell and compare if there is a TRUE and a FALSE, then that means the game is still going
            if (enemyGrid[i][j] && !hitGrid[i][j]) {
                // return false because the game is not over yet
                return false; 
            }
        }
    }
    // If here, then all hits represent each ship placed, which means the game is over!
    // Return true and lets end the game
    return true; 
}

int getShipLength(Ship ship) {
    // Use a switch statement to return the length of our ship depending which one it is
    switch (ship) {
        case SHIP1: return 4;
        case SHIP2: return 3;
        case SHIP3: return 3;
        case SHIP4: return 2;
        default: return 0;
    }
}

void placeShip() {
    int shipLength = getShipLength(currentShip);

    // Place the ship on the grid based on the current orientation and player
    if (currentPlayer == PLAYER1) {
        switch (currentOrientation) {
            case HORIZONTAL_LEFT:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER1[currentRow][currentCol - i] = true;
                }
                break;
            case HORIZONTAL_RIGHT:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER1[currentRow][currentCol + i] = true;
                }
                break;
            case VERTICAL_UP:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER1[currentRow - i][currentCol] = true;
                }
                break;
            case VERTICAL_DOWN:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER1[currentRow + i][currentCol] = true;
                }
                break;
        }
    }
    else if (currentPlayer == PLAYER2) {
        switch (currentOrientation) {
            case HORIZONTAL_LEFT:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER2[currentRow][currentCol - i] = true;
                }
                break;
            case HORIZONTAL_RIGHT:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER2[currentRow][currentCol + i] = true;
                }
                break;
            case VERTICAL_UP:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER2[currentRow - i][currentCol] = true;
                }
                break;
            case VERTICAL_DOWN:
                for (int i = 0; i < shipLength; ++i) {
                    gridPLAYER2[currentRow + i][currentCol] = true;
                }
                break;
        }
    }
    
    // Optionally, update LED display here or elsewhere after placement
    updateBottomLEDsBasedOnGrid();
}

void updateBottomPlayerScreen(CRGB leds[9][NUM_LEDS], const bool grid[9][NUM_LEDS]) {
    // First clear all the LEDs so the display will be correct
    FastLED.clear();

    // Now update our bottom grids based on where the ships are
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < NUM_LEDS; ++j) {
            leds[i][j] = grid[i][j] ? COLOR_SHIP : COLOR_OFF;
        }
    }
    // Finally show the LEDs
    FastLED.show();
}

void updateBottomLEDsBasedOnGrid() {
    // Update the bottom Screens of each player to display ships
    updatePlayerScreen(ledsPLAYER1BOTTOM, gridShipPLAYER1);
    updatePlayerScreen(ledsPLAYER2BOTTOM, gridShipPLAYER2);   
}

void updateShootingDisplays() {
    // Update our top screens when our currentState is SHOOTING to show player misses and hits
    if (currentState == SHOOTING) {
        updatePlayerScreen(ledsPLAYER1TOP, gridHitsPLAYER1);
        updatePlayerScreen(ledsPLAYER2TOP, gridHitsPLAYER2);
    }
}

void advanceToNextShipOrState() {
    // Check if the current ship is the last one
    if (currentShip == SHIP4 && currentPlayer == PLAYER1) {
        // If it is the last ship, transition to the next phase of the game

        // Reset to the initial state for PLAYER2
        currentState = SELECTING_LOCATION;
        currentShip = SHIP1; // Reset to first ship for next player or next round
        currentPlayer = PLAYER2;


    } else if (currentShip == SHIP4 && currentPlayer == PLAYER2) {

        // Now since PLAYER2 placed their ships, we want to go to the SHOOTING phase
        currentState = SHOOTING;
        currentShip = NONE;

        // Now go back to PLAYER1
        currentPlayer = PLAYER1;
    
    } else {
        // If it is not the last ship, move to the next ship
        currentShip = static_cast<Ship>(static_cast<int>(currentShip) + 1);
        // Reset to SELECTING_LOCATION state for the next ship
        currentState = SELECTING_LOCATION;
    }

    // Reset row and column index to start position for next ship placement
    currentRow = 0;
    currentCol = 0;
}