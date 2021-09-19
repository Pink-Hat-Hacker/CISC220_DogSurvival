/*
 * Dog.hpp
 *
 *  Created on: Sep 14, 2021
 *      Author: pinkhathacker
 */

#ifndef DOG_HPP_
#define DOG_HPP_
/*
 * • string name; // for the dog's name
• int strength; //for the dog's current strength
• int x; // the x coordinate of where the dog is currently on the board
• int y; // the y coordinate of where the dog is currently on the board
 */

/*• (4 pts) Dog(string n); //constructor
• (3 pts) TODO: DONE Dog(); //constructor
• (6 pts) TODO: DONE bool changeStrength(int amt); //changes dog’s strength field
• (3 pts) TODO: DONE void die(); //die message when strength at or below 0
• (3 pts) TODO: DONE void printDog(); // prints out info about dog
• (3 pts) TODO: DONE void won(); //won message for when dog is at end of evil forest
• (3 pts) TODO: DONE void reset(); //resets dog for restarting a new game
*/


#include <string>
#include <stdlib.h>
using namespace std;

class Dog{
	friend class Board;

	string name;
	int strength;
	int x, y;

public:
	Dog(string);
	Dog();

	bool changeStrength(int);
	void die();
	void printDog();
	void won();
	void reset();
};



#endif /* DOG_HPP_ */
