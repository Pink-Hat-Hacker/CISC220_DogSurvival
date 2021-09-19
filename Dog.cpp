///*
// * Dog.cpp
// *
// *  Created on: Sep 14, 2021
// *      Author: pinkhathacker
// */
//
///*
//NOTE: The dog header file (created by right-clicking on the project, then selecting file->new->header file) should contain the
//following line right below the class Dog { line:
//friend class Board;//by making the Board a friend of this class, the
////Dog class is allowing the board class and objects
////to access all of the dog class' private fields
//Here are more in-depth explanations of the constructors and the methods for the dog class:
//• Dog(string n); (
///* constructor, sets the name to be whatever name gets passed in, the
//* strength to be 50 (I just picked 50 - you want another number, go for it!) and I made
//* the original coordinates be 0 and 0 because the compiler yells at me a tiny little yell
//* if I don't initialize all my fields in the constructor
//*/
////• Dog();
/////* constructor, I made the default be fluffy, but you can make it anything you like!!
////* I set the strength to be 50 (again, I just picked 50), and I made the original
////* coordinates be 0 and 0 because...
////*/
////• bool changeStrength(int amt);
/////*changeStrength modifies the strength property by whatever amt is (basically adding here)
////* It then calls printDog method to print out current information about the dog.
////* It also checks to make sure that the dog object's strength is >0.
////* If the dog object's strength is 0 or less, it calls the die method.
////* It returns true if the strength is still >0 and false otherwise.
////*/
////• void die();
/////* This method just prints out a sad pathetic death of a dog message, letting everyone
////* know of the demise of the dog object. My message has ACK!!! and judgmental statements
////* about how the user is a cruel, heartless person for letting a puppy dog die, but
////* yours can be whatever you like.
////*/
////• void printDog();
/////* this method just prints out the basic information about the dog - its
////*name and its current strength.
////*/
////• void won();
/////* again, just a message about the user's incredible prowess in successfully navigating the
////* sweet little puppy dog through the evil forest to the other side. You can make it whatever
////* you like.
////*/
////• void reset();
/////* this method just resets the strength (for me it was 50) and the x and y to 0 and 0.*/
//
//
////constructors
///*
// * TODO: Dog(string n)
// */
//Dog::Dog(string nName){
//	//pass
//}
//
///*
// * TODO: Dog()
// */
//Dog::Dog(){
//	//pass
//}
//
//
////methods
//
///*
// * TODO: bool changeStrength(int amt)
// */
//bool Dog::changeStrength(int amt){
//	//pass
//}
//
///*
// * TODO:void die();
// */
//
//void Dog::die(){
//	//pass
//}
//
///*
// * TODO: void printDog()
// */
//void Dog::printDog(){
//	//pass
//}
//
///*
// * TODO: void won();
// */
//
//void Dog::won(){
//	//pass
//}
//
///*
// * TODO: Void reset();
// */
//void Dog::reset(){
//
//}
