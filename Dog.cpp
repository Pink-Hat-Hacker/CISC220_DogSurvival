///*
// * Dog.cpp
// *
// *  Created on: Sep 14, 2021
// *      Author: pinkhathacker
// */
//
///*

#include "Dog.hpp"
#include <iostream>
using namespace std;
////constructors
///*
// * TODO: Dog(string n)
// */
Dog::Dog(string nName){
	name = nName;
	strength=50;
	x=0;
	y=0;
}
//
///*
// * TODO: Dog()
// */
Dog::Dog(){
	name = "Spot";
	strength=50;
	x=0;
	y=0;
}
//
//
////methods
//
///*
// * TODO: bool changeStrength(int amt)
// */
bool Dog::changeStrength(int amt){
	bool alive=1;
	strength=strength+amt;
	printDog();
	if(strength<0){
		alive=0;
		die();
	}
	return alive;
}
//
///*
// * TODO:void die();
// */
//
void Dog::die(){
	cout << "Oh no! "<< name << " died in the evil forest!"<< endl;

	cout << " ∩_---_∩ " << "\n";
	cout << "{ X ꈊ X }" << "\n";
	cout << " -------" << endl;
}
//
///*
// * TODO: void printDog()
// */
void Dog::printDog(){
	//cout << "Your dog's name is " << name << "." << endl;
	cout << name << " has " << strength << " strength left.   \\(ง • ̀ꈊ • ́) ง " << endl;
	//testing
	cout << "x: " << x << "  y: " << y << "\n" << endl;
}
//
///*
// * TODO: void won();
// */
//
void Dog::won(){
	cout << "Congratulations!!! You survived the evil Forest!" << endl;

	cout << "* * * * * * * * *" << "\n";
	cout << "* *  ∩_---_∩  * *" << "\n";
	cout << "* \\{ @ ꈊ @ } * *" << "\n";
	cout << "* *  -------  * *" << "\n";
	cout << "* * * * * * * * *" << endl;

}
//
///*
// * TODO: Void reset();
// */
void Dog::reset(){
	strength=50;
	x=0;
	y=0;
}
