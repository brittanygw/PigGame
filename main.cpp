// Header
// CISP400 16631
// 2/2/2020
// Brittany Wilson (W1811883)
// piggame.cpp

#include <iostream>		
using namespace std;

// The class below will create a scorekeeper for each object created
// This is the overall score, not the points for turn/round
// Program will create one scorekeeper per player (2 objects)

class Scores 
{

   // Access specifier 
    public: 
  
    // Data Members 
    int score = 0; 
    string name = "Computer Jones";  // Default name, computer will keep this one.
  
    // Member Functions

    // This method will add points to the new score
    void AdjustScore(int points) {
      score = score + points;
    }
    
    // This method returns the player's current score
    int PrintScore() {
      return score;
    }

    // This method will change the name from default; only human player will use 
    void ChangeName(string userInput) {
      name = userInput;
    }

};

// The TurnCounter below will create a turnkeeper object
// The flag will keep track of whether the game is continuing 
// Flag flipping to 1 means game is over

class TurnCounter
{
  // Access specifier 
    public: 
  
    // Data Members 
    int turn = 1; 
    int flag = 0;
  
    // Member Functions

    // Increments the turn counter
    void AddTurn() {
      turn++;
    } 

    // Returns what the current turn is 
    int WhatTurn() {
      return turn;
    }

};

// The class below will create an object that keeps track of turn information
// Program will create one per player (2 objects)

class TurnPoints
{

// Access specifier 
    public: 
  
    // Data Members 
    int points = 0;     // Points earned this round
    int roll = 0;       // Player's most recent roll
    int flag = 0;       // Flag set to 0 means player's turn continues, 1 means turn is over
    int move = 0;       // Player's most recent move suggestion 
  
    // Member Functions
    void TurnOver() {
      flag = 1;
    }

    // This method will reset everything to 0 at the end of each turn
    void TurnReset() {
      points = 0;
      roll = 0;
      flag = 0;
      move = 0;
    }
};

// Function Prototypes
void ProgramGreeting();		
  // Introduces user to the game, shows title screen 
  // Also programmer information, contact information, course information 
  // Displays where the rules for the game can be found on Wikipedia 

void Unittest();	

void DisplayInstructions();		
  // Displays how to play the game
  // Runs once at beginning of the game and can be called from the menu if needed again

string PlayerName();
  // Prompts user to enter their full name, returns name as string

int RollDice();
  // Returns a random number from 1 through 6

int OptionMenu();
  // Displays the option menu, prompts user to enter their choice 
  // Returns user input as int

void DisplayScore(string a, string b, int x, int y, int z);
  // Displays the overall game score 
  // Takes arguments for dispslay names and current score 
  // Runs at the end of each turn, and at the end of the game

//----------------------------------------------------------------------

int main() {

  ProgramGreeting();

	Unittest();

  // Specification C1 - Fixed Seed
  srand(1);

  Scores humanScore;
  Scores computerScore;
  TurnCounter gameTurn;
  TurnPoints humanTurnInformation;
  TurnPoints computerTurnInformation;

  // Below will change the human's name to whatever the player inputs.
  // Computer player will keep the default name: Computer Jones.
  humanScore.ChangeName(PlayerName());

  DisplayInstructions(); 

  // Below will display the current overall score of the game.
  // Will display at the beginning by default, and after each turn.
  
  DisplayScore(humanScore.name, computerScore.name, gameTurn.WhatTurn(), humanScore.score, computerScore.score);

while (gameTurn.flag != 1) {
  gameTurn.AddTurn();

  // BEGIN TURN LOOP, runs while both players have moves remaining.

  while (humanTurnInformation.flag == 0 || computerTurnInformation.flag == 0) {

    // Human turn begins here, loops until turn ends.

    while (humanTurnInformation.flag == 0) {
      cout << "Your move." << endl;
      cout << endl;

      // Human can enter their move below.

      humanTurnInformation.move = OptionMenu();

      // Interpret human's move below:

      // Human holds
      if (humanTurnInformation.move == 2) {
      humanTurnInformation.flag = 1;
      // Ends human turn

     } 
      // Human rolls
      else if (humanTurnInformation.move == 1) {
       humanTurnInformation.roll = RollDice();
       cout << "You roll a " << humanTurnInformation.roll << "." << endl; 

        // Rolling a 1 ends the turn and zeroes out points 
        if (humanTurnInformation.roll == 1) {
          cout << "BZZZT! End of turn." << endl;
          humanTurnInformation.flag = 1;
          humanTurnInformation.points = 0;
        } 
        
        // Otherwise, points are added to score
        else {
          humanTurnInformation.points = humanTurnInformation.points + humanTurnInformation.roll;
        }

       cout << "You have " << humanTurnInformation.points << " points." << endl;
       cout << endl;
     } 
     
     // Player can also request to view rules again 
     else if (humanTurnInformation.move == 3) {

       DisplayInstructions();

       // Prompts player to make move again 
       humanTurnInformation.move = OptionMenu();
     }

     // If human quits the game, ends everything 
     else if (humanTurnInformation.move == 4) {
       humanTurnInformation.flag = 1;
       computerTurnInformation.flag = 1;
       gameTurn.flag = 1;
     }

    }

    // End human turn


    // Computer turn, loops until computer turn ends.

    while (computerTurnInformation.flag == 0) {
      cout << "Computer move." << endl;

      // Computer's move determined by dice roll, below
      computerTurnInformation.move = RollDice();

      // Interpret computer's move

      // If computer rolls a 1, 2, or 3 it will hold
      // If computer rolls a 4, 5, or 6, will roll again for score

      // Computer holds
      if (computerTurnInformation.move < 4) {
        cout << "Computer holds." << endl;
        computerTurnInformation.flag = 1;
      } 

      // Otherwise, the computer rolls for its turn
        else {
        computerTurnInformation.roll = RollDice();
        cout << "Computer rolls a " << computerTurnInformation.roll << "." << endl;

        // Rolling a 1 ends the turn and zeroes out points 

        if (computerTurnInformation.roll == 1) {
          cout << "BZZT! End of turn." << endl;
          computerTurnInformation.points = 0;
          computerTurnInformation.flag = 1;
        } 
        
        // Otherwise, points are added to round score
        else {
          computerTurnInformation.points = computerTurnInformation.points + computerTurnInformation.roll;
        }
        
        cout << "Computer has " << computerTurnInformation.points << " points." << endl;
        cout << endl;
      }

    }
    
  }  

  // Add points to total game score.

  humanScore.AdjustScore(humanTurnInformation.points);
  computerScore.AdjustScore(computerTurnInformation.points);

  cout << endl;
  cout << "End of round." << endl;

  //Loop below extracts the first name only from the player's name
  for (int i = 0; i < humanScore.name.find(" " , 0); ++i) {
    cout << humanScore.name.at(i);
    }

  // Specification B1 - Display Turn Stats
  cout << " earned " << humanTurnInformation.points << " points, ";
  cout << "Computer earned " << computerTurnInformation.points << " points." << endl;

  // Turn is over, clean up after the turn below:
  humanTurnInformation.TurnReset();
  computerTurnInformation.TurnReset();

 DisplayScore(humanScore.name, computerScore.name, gameTurn.WhatTurn(), humanScore.score, computerScore.score);

  // Game ends if either player scores 100 or more
 if (humanScore.score >= 100 || computerScore.score >= 100) {
   gameTurn.flag = 1;
 }

 }

  // End game text
 cout << "GAME OVER." << endl;
 cout << endl;
 cout << "--Final Score--";
 DisplayScore(humanScore.name, computerScore.name, gameTurn.WhatTurn(), humanScore.score, computerScore.score);

  // Determines who won the game 
  // In event of a tie, computer wins 
  // Because the computer is very bad at this game

 if (computerScore.score >= humanScore.score) {
   cout << "The winner is: " << computerScore.name << "!!!" << endl;
 } else {
   cout << "The winner is: " << humanScore.name << "!!!" << endl;
 }
 
}

// -------------------------------------------------------------------------------------

void ProgramGreeting() {

// Title   
cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|" << endl;
cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|" << endl;
cout << "|-|-|-|  PIG (the game) |-|-|-|" << endl;
cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|" << endl;
cout << "|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|" << endl;

cout << endl;

cout << "by  : Brittany Wilson (brittany.inbox@gmail.com)" << endl;

cout << "for : Folsom City College - CISP 400" << endl;

// Specification B2 - Display Due Date 
cout << "date: 2/2/2020" << endl;

cout << endl;

cout << "for more information about the rules, please" << endl;
cout << "visit: https://en.wikipedia.org/wiki/Pig_(dice_game)" << endl;

cout << endl;
}

void Unittest() {
// All test code here
}

string PlayerName() {
// Specification C2 - Student Name

  string userDefinedName;   // Reads the whole line, user's full name.
  string userFun;           // Determines if the user is prepared to enjoy themselves. 

  cout << "What is your full name?" << endl;

  getline(cin, userDefinedName);

  // Bug fix: if user does not enter their full name, program encounters a fatal bug. Below checks for space in the name.
  // I suspect this might not be the best way to fix that bug. 

  while (userDefinedName.find(" ", 0) > 1000) {

    cout << "Please enter both your first and last name." << endl;
    
    getline(cin, userDefinedName);

  }

  // Code below has no functionality, this question is just for fun.

  cout << "Are you ready to have fun? (Yes/No)" << endl;
  cin >> userFun; 

  if (userFun == "no" || userFun == "No") {
    cout << "Too bad, ";
    
    // Extract first name from userDefinedName
    for (int i = 0; i < userDefinedName.find(" " , 0); ++i) {
    cout << userDefinedName.at(i);
    } 
  cout << ". You can't turn back now!" << endl;
  } 

  if (userFun == "yes" || userFun == "Yes") {
    cout << "Welcome aboard, ";
    
     // Extract first name from userDefinedName
    for (int i = 0; i < userDefinedName.find(" " , 0); ++i) {
    cout << userDefinedName.at(i);
    } 

  cout << ". Let's go!" << endl;
  }  
  cout << endl;
  return userDefinedName;
}

void DisplayInstructions() {

  // Explains the rules to the game
  // Runs at the beginning of the game 
  //  and can be called up from menu
  
cout << "PIG Rules" << endl;
cout << "---------" << endl;
cout << endl;
cout << "This is a single dice game." << endl;
cout << endl;
cout << "Each round, you can roll or hold." << endl;
cout << endl;
cout << "Every dice roll will add points to your turn score." << endl;
cout << endl;
cout << "The round ends when both players hold." << endl;
cout << endl;
cout << "WATCH OUT! If you roll a 1, you lose all points for the round." << endl;
cout << endl;
cout << "After each round, points are added to players' total score." << endl;
cout << endl;
cout << "First player to 100 points wins the game." << endl;
cout << endl;
cout << "---------" << endl;
}

int RollDice() {

  // Generates a random number 1 through 6

  int dice = rand () % 6 + 1;

  return dice;

}

int OptionMenu() {

  // Specification C3 - Numeric Menu

  int playerMove = 0;

  cout << "Menu Options" << endl;
  cout << "------------" << endl;
  cout << "1. Roll" << endl;
  cout << "2. Hold" << endl;
  cout << "3. Rules" << endl;
  cout << "4. Quit" << endl;

  cin >> playerMove;

  //Specification C4 - Bulletproof Menu

  while (playerMove > 4 || playerMove < 1) {
    cout << "Invalid entry. Please choose an option from the menu." << endl;
    cin >> playerMove;
  }

  // If the user enters a non-number, the program goes into an infite loop and crashes
  // TO DO: fix for that

  if (playerMove == 1) {
    cout << "You roll!" << endl;
  } else if (playerMove == 2) {
    cout << "You hold!" << endl;
  } else if (playerMove == 3) {
    cout << "You would like to reread the rules." << endl;
  } else if (playerMove == 4) {
    cout << "You quit." << endl;
  }

  return playerMove;

}

void DisplayScore(string a, string b, int x, int y, int z) {

  string player1Name = a;
  string player2Name = b;

  int turnCount = x;
  int player1Score = y;
  int player2Score = z;

  cout << endl;
  cout << "TURN: " << turnCount << endl;
  cout << player1Name << ": " << player1Score << endl;
  cout << player2Name << ": " << player2Score << endl;
  cout << endl;

}