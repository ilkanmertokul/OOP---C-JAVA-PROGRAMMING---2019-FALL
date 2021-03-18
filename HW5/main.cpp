#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

/*ILKAN MERT OKUL 1801042649*/

#include "classses.h"

using namespace std;
using namespace NPUZZLE; //used NPUZZLE namespace needed for class and its functions.

bool isThisArrayOfBoardPossible(vector <AbstractBoard*> obj){

	int element = obj.size();
	int move_convert;

	/*I am unable to test this code, because i could not write
	== operator. But if i could write that function, this functioun would
	work. This function makes the opposite of last move and if that move is
	equal to previus board, it moves on until index is zero, which means start
	of the array.*/

	while(element>=0){

		switch(obj[element]->lastMove()){

			case 2:	move_convert=8;
				break;
			case 4:	move_convert=6;
				break;
			case 6:	move_convert=4;
				break;
			case 8:	move_convert=2;
				break;
			case -1:
				if(element!=0) return false;
				break;
		}
		if(!obj[element]->move(move_convert)) return false;

		if(!(obj[element]==obj[element-1])) return false;

		element--;
	}

	return true;
}

int main(int argc, char const *argv[]){
	
	bool loop=true;
	string filename;
	int choice;
	int current_obj=0;

	srand(time(NULL));

	vector <AbstractBoard*> obj;

	do{
		cout << "What type will you play?" << endl
			<< "1- Vector board puzzle." << endl
			<< "2- 1D array puzzle." << endl
			<< "3- 2D array puzzle." << endl;
		cin >> choice;	

	}while(choice>3 || choice<0);

	switch(choice){
		case 1:	obj.push_back(new BoardVector);
			break;
		case 2:	obj.push_back(new BoardArray1D);
			break;
		case 3:	obj.push_back(new BoardArray2D);
			break;
	}

	obj[current_obj]->setSize();
	cout << "Welcome to Npuzzle.." << endl;

	while(loop){

		obj[current_obj]->print();

		cout << "Moved " << obj[current_obj]->numberOfMoves() << "times" << endl
			<< "Last move: ";
		switch(obj[current_obj]->lastMove()){
			case -1: cout << "No moves" << endl;
				break;
			case 2:	cout << "Down" << endl;
				break;
			case 4:	cout << "Left" << endl;
				break;
			case 6:	cout << "Right" << endl;
				break;
			case 8:	cout << "Up" << endl;
				break;
		}

		cout << "Choose an action:" << endl
			<<"1- Create a new board."<< endl
			<<"2- Use file functions."<< endl
			<<"3- Move functions." << endl
			<<"4- How many boards have been created?" << endl
			<<"5- Exit "<< endl;

		cin >> choice;

		switch(choice){
			case 1:	

				do{
					cout << "What type will you play?" << endl
						<< "1- Vector board puzzle." << endl
						<< "2- 1D array puzzle." << endl
						<< "3- 2D array puzzle." << endl;
						
					cin >> choice;	

				}while(choice>3 || choice<0);

				switch(choice){
					case 1:	obj.push_back(new BoardVector);
						break;
					case 2:	obj.push_back(new BoardArray1D);
						break;
					case 3:	obj.push_back(new BoardArray2D);
						break;
					default: cout << "Wrong input" << endl;
				}
				current_obj++;
				obj[current_obj]->setSize();
				break;

			case 2:
				cout << "Choose an action:" << endl
					<< "1- Save the current game to a file." << endl
					<< "2- Read a file." << endl;
				cin >> choice;

				switch(choice){
					case 1: obj[current_obj]->writeToFile();
						break;
					case 2:
						cout << "Enter a filename" << endl;
						cin >> filename;
						if(!obj[current_obj]->readFromFile(filename)) cout << "Error reading file." << endl;
						break;
					default: cout << "Wrong input" << endl;
				}
				break;

			case 3:
				cout << "8- To UP"<< endl
					<< "2- To DOWN"<< endl
					<< "4- To LEFT"<< endl
					<< "6- To RIGHT"<< endl;
				cin >> choice;
				if(!obj[current_obj]->move(choice)) cout << "invalid move" << endl;
				else {
					obj[current_obj]->setmove(choice);
					obj[current_obj]->increaseMove();
				}
				break;

			case 4:
				cout << "You created "<< current_obj+1 << "objects." << endl; 
				break;

			case 5:
				cout << "You choosed to exit!" << endl;
				loop=false;
				break;

			default:
				cout << "You entered a wrong value." << endl;
		}

		if(obj[current_obj]->isSolved()){
			cout << "SOLVED!" << endl;
			loop = false;
		}
	}


	return 0;
}

/*ILKAN MERT OKUL 1801042649*/