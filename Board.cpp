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

//for color
#include <stdio.h>
#define RESET "\033[0m"
#define GREEN "\033[32m"

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
		//zombie addition
		zomx= rand()%12 + 2;
		zomy = rand()%11 + 8;

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
		addZombies();
		printBoard();
	}
}

void Board::addFood() {

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

//zombie addition
void Board::addZombies(){
	//cout << "I'm a zombie" << endl;
	level = tolower(level);


	if(level=='m'||level=='h'){
		board[lastx][lasty]='+';
		board[zomx+rep][zomy]='Z';
		lastx=zomx+rep;
		lasty=zomy;
		//rep++;

		if(rep==0 && updown==1){
			updown=0;
		}
		else if(rep==4){
			updown=1;
		}
		if(updown==0){
			rep++;
		}
		if(updown==1){
			rep--;
		}
	}
}

void Board::boardConfig() {
/* (8 pts) code for the boardConfig method goes here
*/
	level = tolower(level);

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
			}else if (board[i][j] == 'Z'){
				system(GREEN);
				cout << board[i][j];
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

	//for no conditional (break walls)
	//int flag = 0;
	int dir = 0;

	if(mydog.strength <= 0){
		mydog.die();
		return 0;
	}

	if(c=='u'){
		if(mydog.x!=1){
			mydog.x--;
			board[mydog.x+1][mydog.y]='+';
			dir = 1;
		}
	}
	else if(c=='d'){
		if(mydog.x!=size-2){
			mydog.x++;
			board[mydog.x-1][mydog.y]='+';
			dir = 3;
		}
	}
	else if(c=='l'){
		if(mydog.y!=1){
			mydog.y--;
			board[mydog.x][mydog.y+1]='+';
			dir = 4;
		}
	}
	else if(c=='r'){
		if((mydog.y!=size) && (board[mydog.x][mydog.y] != '|')){
			mydog.y++;
			board[mydog.x][mydog.y-1]='+';
			dir = 2;
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
	if((board[mydog.x][mydog.y]=='Z') || (board[zomx+rep][zomy] == 'D')){
			cout << "Ahhh! You got bit by a Zombie!!  [¬º-°]¬" << endl;
			mydog.die();
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
				if(dir==1){
					mydog.x=mydog.x+1;
					//board[mydog.x][mydog.y]='+';
					//board[mydog.x+1][mydog.y]='D';
				}else if(dir==3){
					mydog.x=mydog.x-1;
					//board[mydog.x][mydog.y]='+';
					//board[mydog.x-1][mydog.y]='D';
				}else if(dir==4){
					mydog.y = mydog.y+1;
					//board[mydog.x][mydog.y]='+';
					//board[mydog.x][mydog.y+1]='D';
				}else if(dir == 2){
					mydog.y = mydog.y-1;
					//board[mydog.x][mydog.y]='+';
					//board[mydog.x][mydog.y-1]='D';
				}

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
	if(mydog.strength <= 0){
		mydog.die();
		return 0;
	}
	return 1;
}


