/*Jacob Cassady
3D-Tic-Tac-Toe
Language: C++
Date Created: 10/27/2015
Last Edited: 06/09/2016*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Class for each square
class square {
	protected:
		int pos;
		int mode;
		int val;
		string line1;
		string line2;
		string line3;
		string line4;
	
	public:
		square(int,int); //Constructor
		square();
		~square(); //Destructor
		int getPosition() {return pos;}
			//Function to retrieve position.
			//Postcondition: position = pos;
		int getMode() {return mode;}
			//Function to set mode.
			//Postcondition: mode = mode
		int getValue() {return val;}
			//Function to set value.
			//Postcondition: value = value
		string getLine1() {return line1;}
			//Function to set line1
			//Postcondition: line1 = line1
		string getLine2() {return line2;}
			//Function to set line2
			//Postcondition: line2 = line2
		string getLine3() {return line3;}
			//Function to set line3
			//Postcondition: line3 = line3
		string getLine4() {return line4;}
			//Function to set line4
			//Postcondition: line4 = line4
		void setLines(int);
			//Function to set Lines
			//The lines are set according to its parameter (mode)
			//Postcondition: line1 = line1
			//				 line2 = line2
			//				 line3 = line3
			//				 line4 = line4
			//				 line5 = line5
			//				 line6 = line6
			//				 line7 = line7
			//				 line8 = line8
		void setPosition(int);
			//Function to set position
			//Position is set according to its parameter (an int 1-9)
			//Postcondition: position = int
		void setValue(int);
			//Function to set value.  This is used by the AI to determine its best move
			//Value is set according to its parameter (an int 1-5)
			//Postcondition: value = int
		void setMode(int);
			//Function to set move.  This is used to determine if the square should be an X, O, or blank
			//Mode is set according to its parameter (an int 0-2)
			//Postcondition: mode = int
			//				 line1 = line1
			//				 line2 = line2
			//				 line3 = line3
			//				 line4 = line4
			//				 line5 = line5
			//				 line6 = line6
			//				 line7 = line7
			//				 line8 = line8
};

//////////////////////////////////////////////////////SQUARE CONSTRUCTOR///////////////////////////////////////////////////
square::square(int position, int value){
	pos = position;
	val = value;
	this->setMode(0);
} //End square constructor

square::square(){
	pos = 0;
	val = 0;
	this->setMode(0);
}

//Class for section
class section: protected square {
	protected:
		int level;
		square topLeft;
		square top;
		square topRight;
		square left;
		square middle;
		square right;
		square bottomLeft;
		square bottom;
		square bottomRight;
	public:
		section(int);
		~section();
		int getLevel() {return level;}
		void choose(int,int);
		void display(void);
		void setLevel(int);
		bool checkEmpty(int);
		bool checkUser(int);
		bool checkAI(int);
		bool checkFull(void);
		int checkCorners(void);
		int checkSides(void);
		int stopWin(void);
		int getWin(void);
		void checkSection(int*,int*);
		int storeMode(int);
};

//////////////////////////////////////////////////////SECTION CONSTRUCTOR///////////////////////////////////////////////////
section::section(int num){
	level = (num+1);
	int position = ((num*9)+1);

	topLeft.setPosition(position);
	topLeft.setValue(3);
	position++;
	top.setPosition(position);
	top.setValue(1);
	position++;
	topRight.setPosition(position);
	topRight.setValue(3);
	position++;
	left.setPosition(position);
	left.setValue(1); 
	position++;
	middle.setPosition(position);
	middle.setValue(5);
	position++;
	right.setPosition(position);
	right.setValue(1);
	position++;
	bottomLeft.setPosition(position);
	bottomLeft.setValue(3);
	position++;
	bottom.setPosition(position);
	bottom.setValue(1);
	position++;
	bottomRight.setPosition(position);
	bottomRight.setValue(3);
} //End section concstructor

//Function Prototypes
bool checkFullBoard(section[3]);
void tallyScore(section[3],int*,int*);
int reportScore(section[3],int*,int*);
int combineSelection(int,int);
void generate(section[3]);
	//Function to display the game board
	//PostCondition: The squares are printed in a 3x3x3 fashion
int userInput(section[3]);
	//Function used for user input and mode(1) manipulation.
	//PostCondition: does not return any values
int durzo(section[3]);
	//Function used to determine Jacob's AI's next move.
int stephen(section[3]);
	//Function used to determine Stephen's AI's next move.
		
//////////////////////////////////////////////////// MAIN ///////////////////////////////////////////////////////////
int main(){
	int flip=0,turn=0,winner=0,p1Score=0,p2Score=0,p1Final=0,p2Final=0, selection=0;
	bool full = false;
	char playerName[25];
	
	section top(0);
	section middle(1);
	section bottom(2);

	srand(time(NULL));
	turn = (rand() % 2);
		
	//Initialize and display blank board
	section board[3] = {top,middle,bottom};
	
	cout << "\n\tHello! Welcome to my 3D-Tic-Tac-Toe game.  You will be facing off against our tried and true AI Durzo." << endl;
	cout << "\tBefore we start, do you mind telling me your name? ";
	cin >> playerName;
	
	cout << "\n\tI will toss a coin to see who will go first between you and our AI, Durzo." << endl;
	cout << "\tYou have the option of choosings between heads or tails.  Please enter a 1 for heads or a 0 for tails:";
	cin >> flip;
	
	if (turn == 0){
		cout << "\n\t.... Tails it is!" << endl;
		if(turn == flip){
			cout << "\n\tGood job! It looks like you won the coin toss and now get to go first!" << endl;
		} else {
			cout << "\n\tSorry! You guessed incorrectly and now Durzo gets the first pick." << endl;
			turn = 1;
		}
	} else if (turn == 1){
		cout << "\n\tHeads up!" << endl;
		if(turn == flip){
			cout << "\n\tGood job! It looks like you won the coin toss and now get to go first!" << endl;
			turn = 0;
		} else {
			cout << "\n\tSorry! You guessed incorrectly and now Durzo gets the first pick." << endl;
		}
	}
	
	system("pause");
	system("cls");
	do {
		if (turn == 0){ //Player's Turn
			generate(board);
			cout << playerName << "'s Turn." << endl;
			selection = userInput(board);
			tallyScore(board,&p1Score,&p2Score);
			full = checkFullBoard(board);
			system("pause");
			system("cls");
			if (full == false){
				turn = 1;
			}
		}
		if (turn == 1){ //Jacob's Turn
			cout << "Durzo's Turn." << endl;
			selection = durzo(board);
			cout << "Durzo chose square #" << selection << endl;
			tallyScore(board,&p1Score,&p2Score);
			full = checkFullBoard(board);
			system("pause");
			system("cls");
			if (full == false){
				turn = 0;
			}
		}
		if (full == true) {
			winner = reportScore(board,&p1Final,&p2Final);
			if (winner == 1){
				cout << "Congratulations to " << playerName << ", well played!" << endl;
			} else if (winner == 2) {
				cout << "Congratulations to Durzo, well played!" << endl;
			} else if (winner == 3) {
				cout << "I can't believe it but both of you two are just too darn good! It's a draw." << endl;	
			}
		}
	} while (!full);
} //end main();


///////////////////////////////////////////////////////FUNCTION DEFINTION//////////////////////////////////////////////////
void generate(section board[3]){
	int i;
	
	cout << endl << "\t\t\t3D Tic-Tac-Toe" << endl << endl;
	for (i=0;i<3;i++){
		board[i].display();
	}
}//End breakDown();

///////////////////////////////////////////////////////FUNCTION DEFINTION//////////////////////////////////////////////////
bool checkFullBoard(section board[3]){
	if ((board[0].checkFull()) && (board[1].checkFull()) && (board[2].checkFull())){
		return true;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////FUNCTION DEFINTION//////////////////////////////////////////////////
void tallyScore(section board[3],int* p1Score,int* p2Score){
 	int i=0,j=0,tempTopMode=0,tempMiddleMode=0,tempBottomMode=0,jacobScore=0,stephenScore=0;
 	(*p1Score)=0;
 	(*p2Score)=0;
	board[0].checkSection(p1Score,p2Score);
	board[1].checkSection(p1Score,p2Score);
	board[2].checkSection(p1Score,p2Score);
	
	
	
	//NOTE: ALL OF THESE NOTES DISCLUDE VERTICAL CROSS BOARD WINS.  THESE ARE ADDRESSED IN THE FOLLOWING FOR LOOP
	//Check for cross board wins with an oblique orientation.
		for (i=1;i<3;i++){
			//Check all possible cross board wins at topLeft square on the top section
			if ((board[0].storeMode(1) == board[1].storeMode(2)) && (board[0].storeMode(1) == board[2].storeMode(3)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(1) == board[1].storeMode(5)) && (board[0].storeMode(1) == board[2].storeMode(9)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(1) == board[1].storeMode(4)) && (board[0].storeMode(1) == board[2].storeMode(7)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at top square on the top section
			if ((board[0].storeMode(2) == board[1].storeMode(5)) && (board[0].storeMode(2) == board[2].storeMode(2)) && (board[0].storeMode(2) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at topRight square on the top section
			if ((board[0].storeMode(3) == board[1].storeMode(2)) && (board[0].storeMode(3) == board[2].storeMode(1)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(3) == board[1].storeMode(6)) && (board[0].storeMode(3) == board[2].storeMode(9)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(3) == board[1].storeMode(5)) && (board[0].storeMode(3) == board[2].storeMode(7)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at left square on the top section
			if ((board[0].storeMode(4) == board[1].storeMode(5)) && (board[0].storeMode(4) == board[2].storeMode(6)) && (board[0].storeMode(4) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//THERE ARE NO POSSIBLE CROSS BOARD WINS AT MIDDLE SQUARE
		//Check all possible cross board wins at right square on the top section
			if ((board[0].storeMode(6) == board[1].storeMode(5)) && (board[0].storeMode(6) == board[2].storeMode(4)) && (board[0].storeMode(6) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottomLeft square on the top section
			if ((board[0].storeMode(7) == board[1].storeMode(8)) && (board[0].storeMode(7) == board[2].storeMode(9)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(7) == board[1].storeMode(4)) && (board[0].storeMode(7) == board[2].storeMode(1)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(7) == board[1].storeMode(5)) && (board[0].storeMode(7) == board[2].storeMode(3)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottom square on the top section
			if ((board[0].storeMode(8) == board[1].storeMode(5)) && (board[0].storeMode(8) == board[2].storeMode(2)) && (board[0].storeMode(8) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottomRight square on the top section
			if ((board[0].storeMode(9) == board[1].storeMode(6)) && (board[0].storeMode(9) == board[2].storeMode(3)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(9) == board[1].storeMode(8)) && (board[0].storeMode(9) == board[2].storeMode(7)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(9) == board[1].storeMode(5)) && (board[0].storeMode(9) == board[2].storeMode(1)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
		}
	}
	
	//Check for all possible cross boards wins with a vertical orientation
	for (i=1;i<10;i++){
		tempTopMode = board[0].storeMode(i);
		tempMiddleMode = board[1].storeMode(i);
		tempBottomMode = board[2].storeMode(i);

//		cout << i << ": tempTopMode: " << tempTopMode << endl;
//		cout << i << ": tempMiddleMode: " << tempMiddleMode << endl;
//		cout << i << ": tempBottomMode: " << tempBottomMode << endl;
		for (j=1;j<3;j++){
//			cout << "i: " << i << "j: " << j << endl;
			if ((tempTopMode == tempMiddleMode) && (tempTopMode == tempBottomMode) && (tempMiddleMode == tempBottomMode) && (tempTopMode == j)){
				if(j==1){
					(*p1Score)++;
				}
				if(j==2){
					(*p2Score)++;
				}
			}
		}
	}
	
	cout << "Current Score: " << endl << "Player : X : " << *p1Score << endl << "Durzo : O : " << *p2Score << endl;
} // End tallyScore

///////////////////////////////////////////////////////FUNCTION DEFINTION//////////////////////////////////////////////////
int reportScore(section board[3],int* p1Score,int* p2Score){
 	int i=0,j=0,tempTopMode=0,tempMiddleMode=0,tempBottomMode=0;
 		
	board[0].checkSection(p1Score,p2Score);
	board[1].checkSection(p1Score,p2Score);
	board[2].checkSection(p1Score,p2Score);
	
	
	
	//NOTE: ALL OF THESE NOTES DISCLUDE VERTICAL CROSS BOARD WINS.  THESE ARE ADDRESSED IN THE FOLLOWING FOR LOOP
	//Check for cross board wins with an oblique orientation.
		for (i=1;i<3;i++){
			//Check all possible cross board wins at topLeft square on the top section
			if ((board[0].storeMode(1) == board[1].storeMode(2)) && (board[0].storeMode(1) == board[2].storeMode(3)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(1) == board[1].storeMode(5)) && (board[0].storeMode(1) == board[2].storeMode(9)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(1) == board[1].storeMode(4)) && (board[0].storeMode(1) == board[2].storeMode(7)) && (board[0].storeMode(1) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at top square on the top section
			if ((board[0].storeMode(2) == board[1].storeMode(5)) && (board[0].storeMode(2) == board[2].storeMode(2)) && (board[0].storeMode(2) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at topRight square on the top section
			if ((board[0].storeMode(3) == board[1].storeMode(2)) && (board[0].storeMode(3) == board[2].storeMode(1)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(3) == board[1].storeMode(6)) && (board[0].storeMode(3) == board[2].storeMode(9)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(3) == board[1].storeMode(5)) && (board[0].storeMode(3) == board[2].storeMode(7)) && (board[0].storeMode(3) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at left square on the top section
			if ((board[0].storeMode(4) == board[1].storeMode(5)) && (board[0].storeMode(4) == board[2].storeMode(6)) && (board[0].storeMode(4) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//THERE ARE NO POSSIBLE CROSS BOARD WINS AT MIDDLE SQUARE
		//Check all possible cross board wins at right square on the top section
			if ((board[0].storeMode(6) == board[1].storeMode(5)) && (board[0].storeMode(6) == board[2].storeMode(4)) && (board[0].storeMode(6) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottomLeft square on the top section
			if ((board[0].storeMode(7) == board[1].storeMode(8)) && (board[0].storeMode(7) == board[2].storeMode(9)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(7) == board[1].storeMode(4)) && (board[0].storeMode(7) == board[2].storeMode(1)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(7) == board[1].storeMode(5)) && (board[0].storeMode(7) == board[2].storeMode(3)) && (board[0].storeMode(7) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottom square on the top section
			if ((board[0].storeMode(8) == board[1].storeMode(5)) && (board[0].storeMode(8) == board[2].storeMode(2)) && (board[0].storeMode(8) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
		//Check all possible cross board wins at bottomRight square on the top section
			if ((board[0].storeMode(9) == board[1].storeMode(6)) && (board[0].storeMode(9) == board[2].storeMode(3)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(9) == board[1].storeMode(8)) && (board[0].storeMode(9) == board[2].storeMode(7)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
			}
			if ((board[0].storeMode(9) == board[1].storeMode(5)) && (board[0].storeMode(9) == board[2].storeMode(1)) && (board[0].storeMode(9) == i)) {
				if(i==1){
					(*p1Score)++;
				}
				if(i==2){
					(*p2Score)++;
				}
		}
	}
	
	//Check for all possible cross boards wins with a vertical orientation
	for (i=1;i<10;i++){
		tempTopMode = board[0].storeMode(i);
		tempMiddleMode = board[1].storeMode(i);
		tempBottomMode = board[2].storeMode(i);

//		cout << i << ": tempTopMode: " << tempTopMode << endl;
//		cout << i << ": tempMiddleMode: " << tempMiddleMode << endl;
//		cout << i << ": tempBottomMode: " << tempBottomMode << endl;
		for (j=1;j<3;j++){
//			cout << "i: " << i << "j: " << j << endl;
			if ((tempTopMode == tempMiddleMode) && (tempTopMode == tempBottomMode) && (tempMiddleMode == tempBottomMode) && (tempTopMode == j)){
				if(j==1){
					(*p1Score)++;
				}
				if(j==2){
					(*p2Score)++;
				}
			}
		}
	}
	
	cout << "Current Score: " << endl << "Player : X : " << *p1Score << endl << "Durzo : O : " << *p2Score << endl;

	if (*p1Score > *p2Score){
		return 1;
	} else if (*p1Score < *p2Score) {
		return 2;
	} else if (*p1Score == *p2Score) {
		return 3;
	}
} // End reportScore

///////////////////////////////////////////////////////FUNCTION DEFINTION//////////////////////////////////////////////////
int userInput(section board[3]) {
	int selection = 0;
	int i=0;
	int temp = 0;
	
	reselect:
	cout << "Please choose your move: ";
	cin >> selection;
	
	
	if (selection < 10){
		i=0;
	} else if (selection <19){
		selection-=9;
		i=1;
	} else {
		selection-=18;
		i=2;
	}
	
	if (board[i].checkEmpty(selection)){
		board[i].choose(selection,1);
	} else {
		cout << "Please choose one of the left over squares! Try again." << endl << endl;
		goto reselect;
	}
	generate(board);
	return combineSelection(i,selection);
} //End userInput()

///////////////////////////////////////////////////////FUNCTION DEFINTION/////////////////////////////////////////////////
int durzo(section board[3]){
	int selection=0, i=0, blockMove = 0,j=0, tempTopMode=0,tempMiddleMode=0,tempBottomMode=0;
	
	for (i=0;i<3;i++){ //Check each board for a possible chance to a win.  If no win is found, check the next board.
		if(board[i].getWin() > 0){ //Remember that .getWin() does not account for cross board wins.
			selection = board[i].getWin();
			j=i;
			i=3;
		}
	}
	
	if (selection == 0) {
	//Check possible win stops on a cross board basis
		//Check for all possible cross boards wins with a vertical orientation
		for (i=1;i<10;i++){
			tempTopMode = board[0].storeMode(i);
			tempMiddleMode = board[1].storeMode(i);
			tempBottomMode = board[2].storeMode(i);

			//Check if true when all but top square is missing
			if ((tempBottomMode == tempMiddleMode) && (board[0].checkEmpty(i)) && (tempBottomMode == 1)){
				selection = i;
				j=0;
				i=10;
			}

			//Check if true when all but middle square is missing
			if ((tempBottomMode == tempTopMode) && (board[1].checkEmpty(i)) && (tempBottomMode == 1)){
				selection = i;
				j=1;
				i=10;
			}

			//Check if true when all but bottom square is missing
			if ((tempTopMode == tempMiddleMode) && (board[2].checkEmpty(i)) && (tempMiddleMode == 1)){
				selection = i;
				j=2;
				i=10;
			}			
		}
	}
	
	if (selection == 0){
		if ((board[1].storeMode(2) == board[1].storeMode(2)) && (board[0].storeMode(1) == board[2].storeMode(3)) && (board[0].storeMode(1) == i)) {
		
		}
	}

	
	//If a selection hase not yet been found...
	if (selection == 0){ //Check each board for a possible block to a win.  If no block is found, check the next board.
		for (i=0;i<3;i++){ //Remember that .stopWin() does not account for cross board wins.
			if (board[i].stopWin() > 0) { 
				selection = board[i].stopWin();
				j=i;
				i=3;
			}
		}
	}
	
	//If a selection hase not yet been found...
	if (selection == 0){
		if (board[1].checkEmpty(5)){
			selection = 5;
			j=1;
		} else if (board[0].checkEmpty(5)){
			selection = 5;
			j=0;
		} else if (board[2].checkEmpty(5)){
			selection = 5;
			j=2;
		} else if (board[1].checkCorners() > 0){
			selection = board[1].checkCorners();
			j=1;
		} else if (board[0].checkCorners() > 0){
			selection = board[0].checkCorners();
			j=0;
		} else if (board[2].checkCorners() > 0){
			selection = board[2].checkCorners();
			j=2;
		} else if (board[1].checkSides() > 0){
			selection = board[1].checkSides();
			j=1;
		} else if (board[0].checkSides() > 0){
			selection = board[0].checkSides();
			j=0;
		} else if (board[2].checkSides() > 0){
			selection = board[2].checkSides();
			j=2;
		}
	}

	//Double check to make sure that the selection is empty.  If selection is empty, choose that square!
	if (board[j].checkEmpty(selection)){
		board[j].choose(selection,2);
	}
	
	generate(board);
	return combineSelection(j,selection);
}

int stephen(section board[3]){
	int selection = 0, i=0,j=0,zone=0;;
	
	//Double check to make sure that the selection is empty.  If selection is empty, choose that square!
	checkResponse:
	if (board[zone].checkEmpty(selection)){
		board[zone].choose(selection,1);
	} else {
		for (i=0;i<3;i++){
			if(!board[i].checkFull()){
				for(j=1;j<10;j++){
					if(board[i].checkEmpty(j)){
						selection = j;
						zone = i;
						goto checkResponse;
					}
				}
			}
		}
	}

	//Regenerates board with new selection
	generate(board);
	return combineSelection(zone,selection);
}

int combineSelection(int section, int square){
	switch(section){
		case 0:
			return square;
		case 1:
			return (square + 9);
		case 2:
			return (square+18);
	}
}

//////////////////////////////////////////////////////SQUARE DESTRUCTOR///////////////////////////////////////////////////
square::~square(){
	
} //End square destructor

//////////////////////////////////////////////////////SQUARE FUNCTION//////////////////////////////////////////////////////
void square::setValue(int value) {
	val = value;
} //End setValue()

//////////////////////////////////////////////////////SQUARE FUNCTION//////////////////////////////////////////////////////
void square::setPosition(int position){
	pos = position;
} //End setPosition

//////////////////////////////////////////////////////SQUARE FUNCTION//////////////////////////////////////////////////////
void square::setMode(int num){
	mode = num;
	this->setLines(mode);
} //End square::setMode()

//////////////////////////////////////////////////////SQUARE FUNCTION//////////////////////////////////////////////////////
void square::setLines(int mode){
	switch(mode){
		case 0:
			line1 = "             ";
			line2 = "             ";
			line3 = "             ";
			line4 = "             ";
			break;
		case 1:        
			line1 = "  \\ \\   / /  ";
			line2 = "   \\ \\ / /   ";
			line3 = "   / / \\ \\   ";
			line4 = "  / /   \\ \\  ";
			break;        
		case 2:
			line1 = "   _______   ";
			line2 = "  /       \\  ";
			line3 = " |         | ";
			line4 = "  \\_______/  ";
			break;
	}
} //end square::setLines()

//////////////////////////////////////////////////////SECTION DESTRUCTOR///////////////////////////////////////////////////
section::~section(){
	
} //End section destructor

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
void section::setLevel(int lev){
	level=lev;
} //End section::setSection();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
void section::display(void){
	this->topLeft.setLines(this->topLeft.getMode());
	this->top.setLines(this->top.getMode());
	this->topRight.setLines(this->topRight.getMode());
	this->left.setLines(this->left.getMode());
	this->middle.setLines(this->middle.getMode());
	this->right.setLines(this->right.getMode());
	this->bottomLeft.setLines(this->bottomLeft.getMode());
	this->bottom.setLines(this->bottom.getMode());
	this->bottomRight.setLines(this->bottomRight.getMode());
	
	switch(level) {
		case 1:
			cout << "\t" << this->topLeft.getPosition() << this->topLeft.getLine1() << "|\t" << this->top.getPosition() << this->top.getLine1() << "|\t" << this->topRight.getPosition() << this->topRight.getLine1() << endl;
			cout << "\t " << this->topLeft.getLine2() << "|\t " << this->top.getLine2() << "|\t " << this->topRight.getLine2() << endl;
			cout << "\t " << this->topLeft.getLine3() << "|\t " << this->top.getLine3() << "|\t " << this->topRight.getLine3() << endl;
			cout << "\t " << this->topLeft.getLine4() << "|\t " << this->top.getLine4() << "|\t " << this->topRight.getLine4() << endl;
			cout << "\t---------------------------------------------" << endl;
			cout << "\t" << this->left.getPosition() << this->left.getLine1() << "|\t" << this->middle.getPosition() << this->middle.getLine1() << "|\t" << this->right.getPosition() << this->right.getLine1() << endl;
			cout << "\t " << this->left.getLine2() << "|\t " << this->middle.getLine2() << "|\t " << this->right.getLine2() << endl;
			cout << "\t " << this->left.getLine3() << "|\t " << this->middle.getLine3() << "|\t " << this->right.getLine3() << endl;
			cout << "\t " << this->left.getLine4() << "|\t " << this->middle.getLine4() << "|\t " << this->right.getLine4() << endl;
			cout << "\t---------------------------------------------" << endl;
			cout << "\t" << this->bottomLeft.getPosition() << this->bottomLeft.getLine1() << "|\t" << this->bottom.getPosition() << this->bottom.getLine1() << "|\t" << this->bottomRight.getPosition() << this->bottomRight.getLine1() << endl;
			cout << "\t " << this->bottomLeft.getLine2() << "|\t " << this->bottom.getLine2() << "|\t " << this->bottomRight.getLine2() << endl;
			cout << "\t " << this->bottomLeft.getLine3() << "|\t " << this->bottom.getLine3() << "|\t " << this->bottomRight.getLine3() << endl;
			cout << "\t " << this->bottomLeft.getLine4() << "|\t " << this->bottom.getLine4() << "|\t " << this->bottomRight.getLine4() << endl;
			break;
		case 2:
			cout << "\t\t"<< this->topLeft.getPosition() << this->topLeft.getLine1() << "|" << this->top.getPosition() << this->top.getLine1() << "|" << this->topRight.getPosition() << this->topRight.getLine1() << endl;
			cout << "\t\t  " << this->topLeft.getLine2() << "|  " << this->top.getLine2() << "|  " << this->topRight.getLine2() << endl;
			cout << "\t\t  " << this->topLeft.getLine3() << "|  " << this->top.getLine3() << "|  " << this->topRight.getLine3() << endl;
			cout << "\t\t  " << this->topLeft.getLine4() << "|  " << this->top.getLine4() << "|  " << this->topRight.getLine4() << endl;
			cout << "\t\t ---------------------------------------------" << endl;
			cout << "\t\t" << this->left.getPosition() << this->left.getLine1() << "|" << this->middle.getPosition() << this->middle.getLine1() << "|" << this->right.getPosition() << this->right.getLine1() << endl;
			cout << "\t\t  " << this->left.getLine2() << "|  " << this->middle.getLine2() << "| " << this->right.getLine2() << endl;
			cout << "\t\t  " << this->left.getLine3() << "|  " << this->middle.getLine3() << "| " << this->right.getLine3() << endl;
			cout << "\t\t  " << this->left.getLine4() << "|  " << this->middle.getLine4() << "| " << this->right.getLine4() << endl;
			cout << "\t\t ---------------------------------------------" << endl;
			cout << "\t\t" << this->bottomLeft.getPosition() << this->bottomLeft.getLine1() << "|" << this->bottom.getPosition() << this->bottom.getLine1() << "|" << this->bottomRight.getPosition() << this->bottomRight.getLine1() << endl;
			cout << "\t\t  " << this->bottomLeft.getLine2() << "|  " << this->bottom.getLine2() << "|  " << this->bottomRight.getLine2() << endl;
			cout << "\t\t  " << this->bottomLeft.getLine3() << "|  " << this->bottom.getLine3() << "|  " << this->bottomRight.getLine3() << endl;
			cout << "\t\t  " << this->bottomLeft.getLine4() << "|  " << this->bottom.getLine4() << "|  " << this->bottomRight.getLine4() << endl;
			break;
		case 3:
			cout << "\t\t\t"<< this->topLeft.getPosition() << this->topLeft.getLine1() << "|" << this->top.getPosition() << this->top.getLine1() << "|" << this->topRight.getPosition() << this->topRight.getLine1() << endl;
			cout << "\t\t\t  " << this->topLeft.getLine2() << "|  " << this->top.getLine2() << "|  " << this->topRight.getLine2() << endl;
			cout << "\t\t\t  " << this->topLeft.getLine3() << "|  " << this->top.getLine3() << "|  " << this->topRight.getLine3() << endl;
			cout << "\t\t\t  " << this->topLeft.getLine4() << "|  " << this->top.getLine4() << "|  " << this->topRight.getLine4() << endl;
			cout << "\t\t\t ---------------------------------------------" << endl;
			cout << "\t\t\t" << this->left.getPosition() << this->left.getLine1() << "|" << this->middle.getPosition() << this->middle.getLine1() << "|" << this->right.getPosition() << this->right.getLine1() << endl;
			cout << "\t\t\t  " << this->left.getLine2() << "|  " << this->middle.getLine2() << "|  " << this->right.getLine2() << endl;
			cout << "\t\t\t  " << this->left.getLine3() << "|  " << this->middle.getLine3() << "|  " << this->right.getLine3() << endl;
			cout << "\t\t\t  " << this->left.getLine4() << "|  " << this->middle.getLine4() << "|  " << this->right.getLine4() << endl;
			cout << "\t\t\t ---------------------------------------------" << endl;
			cout << "\t\t\t" << this->bottomLeft.getPosition() << this->bottomLeft.getLine1() << "|" << this->bottom.getPosition() << this->bottom.getLine1() << "|" << this->bottomRight.getPosition() << this->bottomRight.getLine1() << endl;
			cout << "\t\t\t  " << this->bottomLeft.getLine2() << "|  " << this->bottom.getLine2() << "|  " << this->bottomRight.getLine2() << endl;
			cout << "\t\t\t  " << this->bottomLeft.getLine3() << "|  " << this->bottom.getLine3() << "|  " << this->bottomRight.getLine3() << endl;
			cout << "\t\t\t  " << this->bottomLeft.getLine4() << "|  " << this->bottom.getLine4() << "|  " << this->bottomRight.getLine4() << endl;
			break;
		default:
			cout << "Error within display()" << endl;
			system("pause");
			break;	
	}
} //display();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
void section::choose(int selection, int num){
	switch(selection){
		case 1:
			this->topLeft.setMode(num);
			break;
		case 2:
			this->top.setMode(num);
			break;
		case 3:
			this->topRight.setMode(num);
			break;
		case 4:
			this->left.setMode(num);
			break;
		case 5:
			this->middle.setMode(num);
			break;
		case 6:
			this->right.setMode(num);
			break;
		case 7:
			this->bottomLeft.setMode(num);
			break;
		case 8:
			this->bottom.setMode(num);
			break;
		case 9:
			this->bottomRight.setMode(num);
			break;
		default:
			cout << "Error with parameter sent to choose(int selection, int mode)" << endl;
			system("pause");
			break;
	}
} //end choose()

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
bool section::checkEmpty(int selection){
	switch(selection){
		case 1:
			if (this->topLeft.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 2:
			if (this->top.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 3:
			if (this->topRight.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 4:
			if (this->left.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 5:
			if (this->middle.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 6:
			if (this->right.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 7:
			if (this->bottomLeft.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 8:
			if (this->bottom.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 9:
			if (this->bottomRight.getMode() == 0){
				return true;
			} else {
				return false;
			}
		case 0:
			return false;
		default:
			cout << "Error with parameter sent to checkEmpty()" << endl;
			system("pause");
			break;
	}
} //End section::checkEmpty();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
bool section::checkUser(int selection){
	switch(selection){
		case 1:
			if (this->topLeft.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 2:
			if (this->top.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 3:
			if (this->topRight.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 4:
			if (this->left.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 5:
			if (this->middle.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 6:
			if (this->right.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 7:
			if (this->bottomLeft.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 8:
			if (this->bottom.getMode() == 1){
				return true;
			} else {
				return false;
			}
		case 9:
			if (this->bottomRight.getMode() == 1){
				return true;
			} else {
				return false;
			}
		default:
			cout << "Error with parameter sent to checkUser()" << endl;
			system("pause");
			break;
	}
} //End checkUser()

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
bool section::checkAI(int selection){
	switch(selection){
		case 1:
			if (this->topLeft.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 2:
			if (this->top.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 3:
			if (this->topRight.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 4:
			if (this->left.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 5:
			if (this->middle.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 6:
			if (this->right.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 7:
			if (this->bottomLeft.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 8:
			if (this->bottom.getMode() == 2){
				return true;
			} else {
				return false;
			}
		case 9:
			if (this->bottomRight.getMode() == 2){
				return true;
			} else {
				return false;
			}
		default:
			cout << "Error with parameter sent to checkAI()" << endl;
			system("pause");
			break;
	}
} // End checkAI();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
bool section::checkFull(void){
	if ((this->topLeft.getMode() == 0) || (this->top.getMode() == 0) || (this->topRight.getMode() == 0) || (this->left.getMode() == 0) || (this->middle.getMode() == 0) || (this->right.getMode() == 0) || (this->bottomLeft.getMode() == 0) || (this->bottom.getMode() == 0) || (this->bottomRight.getMode() == 0)){
		return false;
	} else {
		return true;
	}
} //End checkFull

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
int section::checkCorners(void){
	if (this->checkEmpty(1)){
		return 1;
	} else if (this->checkEmpty(3)){
		return 3;
	} else if (this->checkEmpty(7)){
		return 7;
	} else if (this->checkEmpty(9)){
		return 9;
	} else {
		return 0;
	}
} //End checkCorners();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
int section::checkSides(void){
	if (this->checkEmpty(2)){
		return 2;
	} else if (this->checkEmpty(4)){
		return 4;
	} else if (this->checkEmpty(6)){
		return 6;
	} else if (this->checkEmpty(8)){
		return 8;
	} else {
		return 0;
	}
} //End checkSides();

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
void section::checkSection(int*p1Score, int* p2Score) {
	int topLeftMode = 0, topMode = 0, topRightMode = 0, leftMode = 0, middleMode = 0, rightMode = 0, bottomLeftMode = 0;
	int bottomMode = 0, bottomRightMode = 0, i=1;
	
	topLeftMode = this->topLeft.getMode(); //Square 1
//	cout << "TopLeftMode: " << topLeftMode << endl;
	topMode = this->top.getMode(); //Square 2
//	cout << "topMode: " << topMode << endl;
	topRightMode = this->topRight.getMode(); //Square 3
//	cout << "topRightMode: " << topRightMode << endl;
	leftMode = this->left.getMode(); //Square 4
//	cout << "leftMode: " << leftMode << endl;
	middleMode = this->middle.getMode(); //Square 5
//	cout << "middleMode: " << middleMode << endl;
	rightMode = this->right.getMode(); //Square 6
//	cout << "rightMode: " << rightMode << endl;
	bottomLeftMode = this->bottomLeft.getMode(); //Square 7
//	cout << "bottomLeftMode: " << bottomLeftMode << endl;
	bottomMode = this->bottom.getMode(); //Square 8
//	cout << "bottomMode: " << bottomMode << endl;
	bottomRightMode = this->bottomRight.getMode(); //Square 9
//	cout << "bottomRightMode: " << bottomRightMode << endl;
	
	for(i=1;i<3;i++){
		//Check for horizontal win
		if ((topLeftMode == topMode) && (topLeftMode == topRightMode) && (topMode == topRightMode) && (topLeftMode == i)) {
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		} else if ((leftMode == middleMode) && (leftMode == rightMode) && (middleMode == rightMode) && (leftMode == i)) {
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		} else if ((bottomLeftMode == bottomMode) && (bottomLeftMode == bottomRightMode) && (bottomMode == bottomRightMode) && (bottomLeftMode == i)) {
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		}
		//Check for vertical win
		if ((topLeftMode == leftMode) && (topLeftMode == bottomLeftMode) && (leftMode == bottomLeftMode) && (topLeftMode == i)){
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		} else if ((topMode == middleMode) && (topMode == bottomMode) && (middleMode == bottomMode) && (topMode == i)){
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		} else if ((topRightMode == rightMode) && (topRightMode == bottomRightMode) && (rightMode == bottomRightMode) && (topRightMode == i)){
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		}
		//Check for oblique win
		if ((topLeftMode == middleMode) && (topLeftMode == bottomRightMode) && (middleMode == bottomRightMode) && (topLeftMode == i)){
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		} else if ((topRightMode == middleMode) && (topRightMode == bottomLeftMode) && (middleMode == bottomLeftMode) && (topRightMode == i)){
			if(i==1){
				(*p1Score)++;
			} else if (i ==2){
				(*p2Score)++;
			}
		}
	}
}//end checkSection

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
int section::storeMode(int num){
	int result = 0;
	
	switch(num){
		case 1:
			result = this->topLeft.getMode();
			break;
		case 2:
			result = this->top.getMode();
			break;
		case 3:
			result = this->topRight.getMode();
			break;
		case 4:
			result = this->left.getMode();
			break;
		case 5:
			result = this->middle.getMode();
			break;
		case 6:
			result = this->right.getMode();
			break;
		case 7:
			result = this->bottomLeft.getMode();
			break;
		case 8:
			result = this->bottom.getMode();
			break;
		case 9:
			result = this->bottomRight.getMode();
			break;
	}
	return result;
} //end setMode

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
int section::stopWin(void){
	int move = 0;
	
	bool temp1=false, temp2=false;
	
	temp1 = this->checkUser(2);
	temp2 = this->checkUser(3);
	
	//cout << "temp1:" << temp1 << "\ttemp2" << temp2 << endl;
	
	//Check possible stops for topLeft square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if((this->checkUser(2) && this->checkUser(3)) || (this->checkUser(5) && this->checkUser(9)) || (this->checkUser(4) && (this->checkUser(7)))){
		if(this->checkEmpty(1)){
			move = 1;
			return move;
		}
	}
	
	//Check possible stops for top square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if((this->checkUser(1) && this->checkUser(3)) || (this->checkUser(5) && this->checkUser(8))){
		if(this->checkEmpty(2)){
			move = 2;
			return move;
		}
	}
	
	//Check possible stops for topRight sqaure; If possible block is found, check to make sure square is empty; if empty, set move to square
	if((this->checkUser(1) && this->checkUser(2)) || (this->checkUser(7) && this->checkUser(5)) || (this->checkUser(9) && this->checkUser(6))){
		if(this->checkEmpty(3)){
			move = 3;
			return move;
		}
	}
	
	//Check possible stops for left square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if((this->checkUser(1) && this->checkUser(7)) || (this->checkUser(5) && this->checkUser(6))) {
		if (this->checkEmpty(4)){
			move = 4;
			return move;
		}
	}
	
	//Check possible stops for middle square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if((this->checkUser(1) && this->checkUser(9)) || (this->checkUser(2) && this->checkUser(8)) || (this->checkUser(3) && this->checkUser(7)) || (this->checkUser(4) && this->checkUser(6))){
		if (this->checkEmpty(5)){
			move = 5;
			return move;
		}
	}
	
	//Check possible stops for right square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkUser(4) && this->checkUser(5)) || (this->checkUser(9) && this->checkUser(3))){
		if (this->checkEmpty(6)){
			move = 6;
			return move;
		}
	}
	
	//Check possible stops for bottomLeft square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkUser(1) && this->checkUser(4)) || (this->checkUser(5) && this->checkUser(3)) || (this->checkUser(8) && this->checkUser(9))){
		if (this->checkEmpty(7)){
			move = 7;
			return move;
		}
	}
	
	//Check possible stops for bottom square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkUser(7) && this->checkUser(9)) || (this->checkUser(5) && this->checkUser(2))) {
		if (this->checkEmpty(8)){
			move = 8;
			return move;
		}
	}
	
	//Check possible stops for bottomRight square; If possible block is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkUser(8) && this->checkUser(7)) || (this->checkUser(5) && this->checkUser(1)) || (this->checkUser(6) && this->checkUser(3))) {
		if (this->checkEmpty(9)){
			move = 9;
			return move;
		}
	}
	
	//If no blocks are found return a value of 0
	return move;
} //end stopWin()

//////////////////////////////////////////////////////SECTION FUNCTION//////////////////////////////////////////////////////
int section::getWin(void){
	int move = 0;
	
	//Check possible win for topLeft square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if((this->checkAI(2) && this->checkAI(3)) || (this->checkAI(5) && this->checkAI(9)) || (this->checkAI(4) && (this->checkAI(7)))){
		if(this->checkEmpty(1)){
			move = 1;
			return move;
		}
	}
	
	//Check possible win for top square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if((this->checkAI(1) && this->checkAI(3)) || (this->checkAI(5) && this->checkAI(8))){
		if(this->checkEmpty(2)){
			move = 2;
			return move;
		}
	}
	
	//Check possible win for topRight sqaure; If possible win is found, check to make sure square is empty; if empty, set move to square
	if((this->checkAI(1) && this->checkAI(2)) || (this->checkAI(7) && this->checkAI(5)) || (this->checkAI(9) && this->checkAI(6))){
		if(this->checkEmpty(3)){
			move = 3;
			return move;
		}
	}
	
	//Check possible win for left square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if((this->checkAI(1) && this->checkAI(7)) || (this->checkAI(5) && this->checkAI(6))) {
		if (this->checkEmpty(4)){
			move = 4;
			return move;
		}
	}
	
	//Check possible win for middle square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if((this->checkAI(1) && this->checkAI(9)) || (this->checkAI(2) && this->checkAI(8)) || (this->checkAI(3) && this->checkAI(7)) || (this->checkAI(4) && this->checkAI(6))){
		if (this->checkEmpty(5)){
			move = 5;
			return move;
		}
	}
	
	//Check possible win for right square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkAI(4) && this->checkAI(5)) && (this->checkAI(9) && this->checkAI(3))){
		if (this->checkEmpty(6)){
			move = 6;
			return move;
		}
	}
	
	//Check possible win for bottomLeft square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkAI(1) && this->checkAI(4)) || (this->checkAI(5) && this->checkAI(3)) || (this->checkAI(8) && this->checkAI(9))){
		if (this->checkEmpty(7)){
			move = 7;
			return move;
		}
	}
	
	//Check possible win for bottom square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkAI(7) && this->checkAI(9)) || (this->checkAI(5) && this->checkAI(2))) {
		if (this->checkEmpty(8)){
			move = 8;
			return move;
		}
	}
	
	//Check possible win for bottomRight square; If possible win is found, check to make sure square is empty; if empty, set move to square
	if ((this->checkAI(8) && this->checkAI(7)) || (this->checkAI(5) && this->checkAI(1)) || (this->checkAI(6) && this->checkAI(3))) {
		if (this->checkEmpty(9)){
			move = 9;
			return move;
		}
	}
	
	//If no blocks are found return a value of 0
	return move;	
} //getWin();
