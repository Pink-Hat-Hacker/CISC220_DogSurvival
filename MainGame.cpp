/*
 * MainGame.cpp
 *
 *  Created on: Sep 14, 2021
 *      Author: pinkhathacker
 */


#include "Board.hpp"
#include <iostream>

#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {
	srand(time(NULL));
	Board board('m',"fido", true);
	return 0;
}

