/*
 * Board.cpp
 *
 *  Created on: Sep 14, 2021
 *      Author: pinkhathacker/Zoe Valladares
 *      & Emma S.
 */

#include "Board.hpp"
//trying out
#include "Dog.hpp"
#include <iostream>
using namespace std;

Board::Board(char diff, bool d){
	level = diff;

	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}

void Board::InitAll() {
	bool keepPlaying = true;

	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % (size - 2) + 1;
		starty = 0;
		endx = rand() % (size - 2) + 1;
		endy = size-1;
		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();
		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;

		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}

void Board::playGame() {
	bool play = true;

	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}
}

void Board::addFood() {
/* (5 pts) code for the addFood method goes here
*/
	/* this method randomly adds food around the board. For easy, I added the field size
	* number of foods randomly around the board. For medium, I added size-2 foods, and for
	* hard I added size-4 foods. The amount of strength the dog gets when they eat (aka
	5
	* move onto) the food is determined in the moveDog method.
	*/

	level = tolower(level);

	int x, y, count = 0;
	//if level == easy number of food = size
	if(level == 'e'){
		do{
			x = rand() % size;
			y = rand() % size;
			if(board[x][y] == '+'){
				board[x][y] = 'F';
				count++;
			}
		}while(count <= size);
		//if level == medium number of food = size-2
	}else if(level == 'm'){
		do{
			x = rand() % size;
			y = rand() % size;
			if(board[x][y] == '+'){
				board[x][y] = 'F';
				count++;
			}
		}while(count <= size-2);
	}
	//if level == hard number of food = size -4
	else if(level == 'h'){
		do{
			x = rand() % size;
			y = rand() % size;
			if(board[x][y] == '+'){
				board[x][y] = 'F';
				count++;
			}
		}while(count <= size-4);
	}
}

void Board::addTraps() {
/* (5 pts) code for the addTraps method goes here
*/
	level = tolower(level);

	int count = 0;
	int traps = level == 'e'? (size-6): level == 'm'? (size-8) : (size-10);
	while(count <= traps){
		int i = rand()%size;
		int j = rand()%size;
		if(board[i][j] == '+'){
			if(level == 'e' && count <= (size-6)){
				board[i][j] = 'T';
				count++;
			}else if(level == 'm' && count <= (size-8)){
				board[i][j] = 'T';
				count++;
			}else if(level == 'h' && count <= (size-10)){
				board[i][j] = 'T';
				count++;
			}
		}
	}
}
void Board::boardConfig() {
/* (8 pts) code for the boardConfig method goes here
*/
	level = tolower(level);
/* this method and the moveDog method are probably the longest methods.
* This method first puts dummy values in every square (I used '+' - I just didn't want
* every square to have gibberish, so I chose a character I wasn't using for any other
* purpose and initialized every square to have that value).
* I then added my random horizontal and vertical walls.
*
* Here's how I did it the walls:
*
* I only placed walls in the odd numbered rows and columns (in other words, row one might
* have a row, but then row 2 would not, whereas row three could and row 4 could not.
* Same with columns (although you can have flexibility.
*
* I picked an odd row or column that did not already have a wall in it at all.
*
4
* I generated a total of 10 walls.
* For each wall, I picked randomly for vertical or horizontal (just rand() % 2 to get either
* 0 for vertical, 1 for horizontal.
*
* I set the easy version to have at most 9 squares in a row or column as a wall, the
* medium to have at most 13 squares as walls in a row or column, and the hard version to
* have at most 16 squares per row or column.(but you can play with this because sometimes
* the hard version was seriously hard!!!
*
* Let's say I randomly decided to place a wall in row 3. I then randomly chose 9 squares in
* row 3 to be a wall (if it was the easy version, 13 if it was the medium, and 16 if it was
* the hard)
*
* So that's the walls. Then I added the 'D' to the beginning square nad an 'E' to the end
square.
*
*
*/

	//before the loop
	//filling
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			board[i][j] = '+';
		}
	}
	//for checking purposes
//	cout << endl;
//	for(int i = 0; i < size; i++){
//		for(int j = 0; j < size; j++){
//					cout<<board[i][j];
//		}
//	}

	//TOP/BOTTOM
	for(int i = 0; i < size; i++){
		board[0][i] = '-';
	}
	for(int i = 0; i < size; i++){
		board[19][i] = '-';
	}
	//SIDES
	for(int i = 0; i < size; i++){
		board[i][0] = '|';
	}
	for(int i = 0; i < size; i++){
		board[i][19] = '|';
	}


	board[mydog.x][mydog.y] = 'D';
	board[endx][size-1] = 'E';
	//making walls
	int count = 0;
	//if level == e set to 9 else if level == m set to m else set to 16
	int res = level == 'e'? 9: level == 'm'? 13 : 16;
	while(count <= res){
		int ori = rand() % 2;
		int i = rand()%size, j = rand()%size;
		int num = rand()%7 + 3;
		if(ori == 1){
			if(i % 2 == 1){
				i++;
			}
			if(board[i][j] == '+'){
				//cout << "THIS IS i:" << i << endl;
				if(level == 'e' && count <= 9){
					for(int z = 0; z < num; z++){
						if(board[i+z][j] == '+'){
							board[i+z][j] = '|';
						}
					}
					count++;
				}else if(level == 'm' && count <= 13){
					for(int z = 0; z < num; z++){
						if(board[i+z][j] == '+'){
							board[i+z][j] = '|';
						}
					}
					count++;
				}else if(level == 'h' && count <= 16){
					for(int z = 0; z < num; z++){
						if(board[i+z][j] == '+'){
							board[i+z][j] = '|';
						}
					}
					count++;
				}
			}
		}else{
			if(j % 2 == 1){
				j++;
			}
			if(board[i][j] == '+'){
				//cout << "THIS IS j:" << j << endl;
				if(level == 'e' && count <= 9){
					for(int z = 0; z < num; z++){
						if(board[i][j+z] == '+'){
							board[i][j+z] = '-';
						}
					}
					count++;
				}else if(level == 'm' && count <= 13){
					for(int z = 0; z < num; z++){
						if(board[i][j+z] == '+'){
							board[i][j+z] = '-';
						}
					}
					count++;
				}else if(level == 'h' && count <= 16){
					for(int z = 0; z < num; z++){
						if(board[i][j+z] == '+'){
							board[i][j+z] = '-';
						}
					}
					count++;
				}
			}
		}
	}
}
void Board::printBoard() {
/* (8 pts) code for the printBoard method goes here
*/
	//BODY
	for(int i = 0; i < size; i++){
		//cout << "| ";
		for(int j = 0; j < size; j++){
			//dog info check
			if(board[i][j] == '+'){
				cout << " ";
			}else if(board[i][j] == 'T'){
				if(debug){
					cout << "T";
				}else{
					cout << " ";
				}
			}else if(board[i][j] == 'F'){
				if(debug){
					cout << "F";
				}else{
					cout << " ";
				}
			}else if(board[i][j] == 'D'){
				//cout << "D";
				cout << board[i][j];
			}else{
				cout << board[i][j];
			}
			cout << " ";
		}
		//cout << " |" << endl;
		cout << endl;
	}
	cout << endl;
}

bool Board::moveDog(char c) {
/* (12 pts) code for the moveDog method goes here
*/
/* TODO: MOVEDOG
	 * This is a somewhat long method.
	* First, it determines the new coordinats of the dog, based on teh direction in which the
	* dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
	*
	* If the dog is at teh edge of the board, teh dog should not move
	*
	* If the dog moves over food, a random number between 2 and 17 is generated, and the
	* dog's changeStrength method is used to increase the dog's strength by the random amount.
	*
	* If the dog moves over the end of the board, the dog's won method is called and false is
	* returned from this method.
	*
	* If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
	* changeStrength method is called with that negative number. (Note that the changeStrength
	* method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
	* thus the dog has died and the game is over. That boolean value is returned from this method).
	*
	* If the dog moves over a wall, the method checks to see if the dog has enough strength to
	* knock down the wall (I made it cost 6 strength points to knock down a wall). If the dog
	* has enough strength, the user is asked, "Do you want to knock down that wall?" If the user
	* responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
	* strength decreases by 6. If the answer is "no", the dog loses 1 strength point, just because.
	*
	* If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
	* method (which, again, will return false if the dog has lost all their strength and died.
	*
	* NOTE: I am not concerned with the precise rules here. If you want to change the range of
	* random numbers for food, if you are worried about whether you still lose 2 strength points for
	* moving even though you gained points for moving over food - I'm leaving all that to your
	preference.
	* I am concerned that you are using classes, objects, and object methods and accessing object
	* fields correctly!
	*
	*/

	//changing coordinates
//	if(c=='u'){
//		if(mydog.y!=size){
//			mydog.y++;
//		}
//	}
//	else if(c=='d'){
//		if(mydog.y!=0){
//			mydog.y--;
//		}
//	}
//	else if(c=='l'){
//		if(mydog.x!=0){
//			mydog.x--;
//		}
//	}
//	else if(c=='r'){
//		if(mydog.x!=size){
//			mydog.x++;
//		}
//	}
//	//determining if dog landed on square with food, trap, walls, or other
//	if(board[mydog.x][mydog.y]=='T'){
//		int damage=(rand()%16)+2;
//		mydog.changeStrength(-damage);
//		cout << "you hit a trap" << endl;
//	}
//	if(board[mydog.x][mydog.y]=='F'){
//		int health=(rand()%16)+2;
//		mydog.changeStrength(health);
//		cout << "you ate food" << endl;
//	}
//	if(board[mydog.x][mydog.y]=='-'||board[mydog.x][mydog.y]=='|'){
//		//Dog.strength??
//		//not sure what to do if dog doesn't have strength to knock over
//		if(mydog.strength>6){
//			cout << "Do you want to knock down the wall? (y/n)" << endl;
//			char ans;
//			cin >> ans;
//			if(ans=='y'){
//				mydog.changeStrength(-6);
//				board[mydog.x][mydog.y]='+';
//			}
//			else if(ans=='n'){
//				mydog.changeStrength(-1);
//				//move them back to the last square
//			}
//		}
//	}
//	//regular
//	if(board[mydog.x][mydog.y]=='+'){
//		mydog.changeStrength(-2);
//	}
//
//	return 1;

	//for no conditional (break walls)
	//int flag = 0;

	if(mydog.strength <= 0){
		mydog.die();
		return 0;
	}

	if(c=='u'){
		if(mydog.x!=1){
			mydog.x--;
			board[mydog.x+1][mydog.y]='+';
		}
	}
	else if(c=='d'){
		if(mydog.x!=size-1){
			mydog.x++;
			board[mydog.x-1][mydog.y]='+';
		}
	}
	else if(c=='l'){
		if(mydog.y!=1){
			mydog.y--;
			board[mydog.x][mydog.y+1]='+';
		}
	}
	else if(c=='r'){
		if((mydog.y!=size) && (board[mydog.x][mydog.y] != '|')){
			mydog.y++;
			board[mydog.x][mydog.y-1]='+';
		}
	}
	//determining if dog landed on square with food, trap, walls, or other
	if(board[mydog.x][mydog.y]=='T'){
		cout << "*** YOU HIT A TRAP ***" << endl;
		int damage=(rand()%16)+2;
		mydog.changeStrength(-damage);
		board[mydog.x][mydog.y]='+';
	}
	if(board[mydog.x][mydog.y]=='F'){
		cout << "*** YOU ATE FOOD ***" << endl;
		int health=(rand()%16)+2;
		mydog.changeStrength(health);
		board[mydog.x][mydog.y]='+';
	}
	if(board[mydog.x][mydog.y]=='E'){
			mydog.won();
			return 0;
	}
	if(board[mydog.x][mydog.y]=='-'||board[mydog.x][mydog.y]=='|'){
		//Dog.strength??
		//not sure what to do if dog doesn't have strength to knock over
		if(mydog.strength>6){
			cout << "Do you want to knock down the wall? (y/n)" << endl;
			char ans;
			cin >> ans;
			if(ans=='y'){
				mydog.changeStrength(-6);
				board[mydog.x][mydog.y]='+';
			}
			else if(ans=='n'){
				//flag = 1;
				mydog.changeStrength(-1);
				//move them back to the last square (trailing code)
//				if(c=='u'){
//					board[mydog.x+1][mydog.y]='D';
//				}else if(c=='d'){
//					board[mydog.x-1][mydog.y]='D';
//				}else if(c=='l'){
//					board[mydog.x][mydog.y+1]='D';
//				}else if(c=='r'){
//					board[mydog.x][mydog.y-1]='D';
//				}

				board[mydog.x][mydog.y]='D';
				return 1;

			}
		}
	}
	//regular
	if(board[mydog.x][mydog.y]=='+'){
		mydog.changeStrength(-2);
	}

	//moving dog
	//if(flag == 0){
		board[mydog.x][mydog.y]='D';
	//}
	return 1;
}


