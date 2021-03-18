#include <cstdlib>
#include <ctime>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "class.h"

using namespace std;


int main(int argc, char const *argv[]){

	string file_name;

	bool while_loop=true;	//for breaking the big while loop.
	srand(time(NULL));

	NPuzzle the_puzzle;		//our class to play puzzle.

	cout << " ---- Welcome to N-PUZZLE! ---- " << endl ;
	if(argc == 1){
		the_puzzle.setSize();
		the_puzzle.shuffle();
	}
	else the_puzzle.readFromFile(argv[1]);

	while(while_loop){

		the_puzzle.print(0);
		char input;
		cout << endl << "Press: "<< endl
			<< "V - Solve the problem. " << endl
			<< "T - Print a report about how many moves have been done." << endl
			<< "E - Save puzzle to a file." << endl
			<< "O - Load a puzzle from a file." << endl
		 	<< "L - Move the empty cell left."		<< endl
		 	<< "R - Move the empty cell right."	<< endl	
		 	<< "U - Move the empty cell up."		<< endl
		 	<< "D - Move the empty cell down." 	<< endl 
		 	<< "S - Shuffle."	<< endl
		 	<< "Q - Quit."		<< endl;
		cin >> input;

		switch(input){

			case 'V':	//Solves the puzzle.
				the_puzzle.solvePuzzle();
				break;

			case 'T':	//Prints the report.
				the_puzzle.printReport();
				break;

			case 'E':	//Writes the game to a file.
				the_puzzle.writeToFile();
				break;

			case 'O':	//Reads a file to restart.
				cin >>  file_name;
				the_puzzle.readFromFile(file_name);
				break;

			case 'L':
			case 'R':
			case 'U':
			case 'D':
				//Moves.
				the_puzzle.move(input,0);
				break;

			case 'S':
				//Shuffles the game after resetting the game.
				the_puzzle.shuffle();
				break;

			case 'Q':
				//Quits the game.
				while_loop=false;
				break;
		}

		if(the_puzzle.isSolved(0))	the_puzzle.printReport();
	}

	cout << "Exiting" << endl;

	return 0;
}