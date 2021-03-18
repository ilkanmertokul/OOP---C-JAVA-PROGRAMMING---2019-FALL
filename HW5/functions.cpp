#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

/*ILKAN MERT OKUL 1801042649*/

#include "classses.h"

using namespace std;

namespace NPUZZLE{

	BoardArray2D::~BoardArray2D(){

		int i;
		for(i=0;i<board_size[1];i++){
			delete array[i];
		}
		delete *array;
	}

	BoardArray1D::~BoardArray1D(){

		delete array;
	}

	/* INHERITED setSize() FUNCTION */

	void AbstractBoard::setSize(){

		cout << "Enter a size greater then three to set size." << endl;

		cin >> board_size[0] ;
		board_size[1]=board_size[0];

		cout << "You entered " << board_size[0] << "."<< endl;

		if(board_size[0]<3 || board_size[1]<3 ){
			cout << "You entered some values that lesser then zero." << endl;
			setSize();
		}
	}

	void BoardVector::setSize(){

		int i;

		cout << "BoardVector:" << endl;
		AbstractBoard::setSize();

		array.resize(board_size[0]);
		for(i=0;i<board_size[0];i++){
			array[i].resize(board_size[1]);
		}

		reset();
		for(i=0;i<100;i++) move((rand()%4+1)*2);

		setmove(-1);
	}

	void BoardArray1D::setSize(){

		int i;

		cout << "BoardArray1D:" << endl;
		AbstractBoard::setSize();

		array = new int [board_size[0]*board_size[1]];

		reset();
		for(i=0;i<100;i++) move((rand()%4+1)*2);
		setmove(-1);
	}

	void BoardArray2D::setSize(){

		int i;

		cout << "BoardArray2D:" << endl;
		AbstractBoard::setSize();

		array = new int* [board_size[0]];
		for(int i=0;i<board_size[0];i++){
			array[i]=new int[board_size[1]];
		}

		reset();
		for(i=0;i<100;i++) move((rand()%4+1)*2);
		setmove(-1);
	}

	/* INHERITED reset() FUNCTION */

	void AbstractBoard::reset(){

		int i,j;

		for(i=0; i<board_size[0]; i++){
			for(j=0; j<board_size[0]; j++){
				(*this)(i,j)=(i*board_size[0]+j+1);
			}
		}

		cord[0]=board_size[0]-1;
		cord[1]=board_size[1]-1;

		(*this)(board_size[0]-1,board_size[0]-1)=-1;
	}

	void BoardVector::reset(){
		AbstractBoard::reset();
		cout << "Board is done for vector" << endl;
	}

	void BoardArray1D::reset(){
		AbstractBoard::reset();
		cout << "Board is done for 1d" << endl;
	}

	void BoardArray2D::reset(){
		AbstractBoard::reset();
		cout << "Board is done for 2d" << endl;
	}

	/* INHERITED print() FUNCTION */

	void AbstractBoard::print(){
		int i,j;
		for( i=0 ; i< board_size [1] ; i++){
			for ( j=0 ; j< board_size[0] ; j++){
				if((*this)(i,j) < 10 && (*this)(i,j)  > -1) cout << "0";
				if((*this)(i,j) !=-1)	cout << (*this)(i,j) << " " ;
				else	cout << "   ";
			}
			cout << endl;
		}
	}

	void BoardVector::print(){

		AbstractBoard::print();
	}

	void BoardArray1D::print(){

		AbstractBoard::print();
	}

	void BoardArray2D::print(){

		AbstractBoard::print();
	}

	/* INHERITED move() FUNCTION */

	bool AbstractBoard::move(int input){

		switch(input){
			case 2:	//MOVES DOWN
				if(cord[0]!=board_size[1]-1 && (*this)(cord[0]+1,cord[1])!=0 ){

					(*this)(cord[0],cord[1])=(*this)(cord[0]+1,cord[1]);
					cord[0]++;

					(*this)(cord[0],cord[1])=-1;
				}
				else	return false;
				break;
			case 4:	//MOVES LEFT
				if(cord[1]!=0 && (*this)(cord[0],cord[1]-1)!=0){

					(*this)(cord[0],cord[1])=(*this)(cord[0],cord[1]-1);
					cord[1]--;

					(*this)(cord[0],cord[1])=-1;
				}
				else 	return false;
				break;
			case 6:	//MOVES RIGHT
				if(cord[1]!=board_size[0]-1 && (*this)(cord[0],cord[1]+1)!=0){

					(*this)(cord[0],cord[1])=(*this)(cord[0],cord[1]+1);
					cord[1]++;

					(*this)(cord[0],cord[1])=-1;
				}
				else 	return false;
				break;
			case 8:	//MOVES UP
				if(cord[0]!=0 && (*this)(cord[0]-1,cord[1])!=0){

					(*this)(cord[0],cord[1])=(*this)(cord[0]-1,cord[1]);
					cord[0]--;

					(*this)(cord[0],cord[1])=-1;
				}
				else return false;
				break;
		}

		return true;
	}

	bool BoardVector::move(int input){

		return AbstractBoard::move(input);
	}

	bool BoardArray1D::move(int input){

		return AbstractBoard::move(input);
	}

	bool BoardArray2D::move(int input){

		return AbstractBoard::move(input);
	}

	/* INHERITED isSolved() FUNCTION */

	bool AbstractBoard::isSolved(){

		int i,j;
		int k;
		int num_cnt = 0;

		//Checks the game is finished or not.
		for(i=0;i<board_size[1];i++){
			for(j=0;j<board_size[0];j++){	
				if((*this)(i,j)!=0){
					num_cnt++;
					
					//If it is blank tile, it seeks any other number to exit, if it 'impassable blocks' only,
					//It is success!
					if((*this)(i,j)==-1){
						for(k=j+1;k<board_size[0];k++){
							if((*this)(i,k)!=0)	return false;
						}
						for(k=i+1;k<board_size[1];k++){
							for(int l=0;l<board_size[1];l++){
								if((*this)(k,l)!=0)	return false;
							}
						}
						return true;
					}
					if((*this)(i,j)!=num_cnt)	return false;
				}
			}
		}

		return true;
	}

	bool BoardVector::isSolved(){

		return AbstractBoard::isSolved();
	}

	bool BoardArray1D::isSolved(){
		
		return AbstractBoard::isSolved();
	}

	bool BoardArray2D::isSolved(){

		return AbstractBoard::isSolved();
	}

	/* INHERITED writeToFile() FUNCTION */

	void AbstractBoard::writeToFile(){

		string file_name;
		cout << "Enter a file name to save the game." << endl;
		cin >> file_name; 

		ofstream outputFile;
		outputFile.open(file_name);

		int i,j;

		//basic nested loop to convert game to a .txt file.
		for( i=0 ; i< board_size [1] ; i++){
			for ( j=0 ; j< board_size[0] ; j++){
				if((*this)(i,j)==-1){
					outputFile << "bb ";
				}
				else{
					if((*this)(i,j) < 10 && (*this)(i,j) > -1) outputFile << "0";
					outputFile << (*this)(i,j)<< " " ;
				}
			}
			outputFile << endl;
		}

		cout << "Written!" << endl;
	}

	void BoardVector::writeToFile(){

		AbstractBoard::writeToFile();
	}

	void BoardArray1D::writeToFile(){

		AbstractBoard::writeToFile();
	}

	void BoardArray2D::writeToFile(){
		
		AbstractBoard::writeToFile();
	}

	/* INHERITED readFromFile() FUNCTION */

	bool BoardVector::readFromFile(string file_name){

		board_size[0]=1;
		board_size[1]=1;

		ifstream inputFile;

		int i, j, count=0 ,line_flag =0;
		int number;

		char board_from_file[9][9][2];
		char temp,prev_temp;

		inputFile.open(file_name);
		
		if(!inputFile){
			cout << "Error while opening the file." << endl; 
			cout << "Restarting.." << endl;
			return false;
		}

		array.resize(9);
		for(i=0; i<9; i++)	array[i].resize(9);
		i=j=0;

		//basic loop to convert file's chars to integer board.
		while( !inputFile.eof() ){

			inputFile.get(temp);

			if(temp == ' '){
				j++;
				if(line_flag == 0) board_size[0]++;
			}
			else if(temp == '\n' && prev_temp!='\n'){
				i++;
				j=0;
				board_size[1]++;
				line_flag=1;
			}
			else{
				board_from_file[i][j][count%2]=temp;
				if(count%2==1){
					
					if(board_from_file[i][j][0]=='b' && board_from_file[i][j][1]=='b'){
						(*this)(i,j) = -1;
						cord[0]= i;
						cord[1]= j;
					}
					else	(*this)(i,j) = (board_from_file[i][j][0]-'0')*10 + (board_from_file[i][j][1]-'0')*1;
					// ^^ This else makes the char's tens digit + one's digit to an actual integer. 
	 			}
				count ++;
			}
			prev_temp=temp;
		}

		array.resize(board_size[0]);
		for(i=0; i<board_size[0]; i++)	array[i].resize(board_size[1]);

		return true;
	}

	bool BoardArray1D::readFromFile(string file_name){

		board_size[0]=1;
		board_size[1]=1;

		ifstream inputFile;

		int i, j, count=0 ,line_flag =0;
		int number;

		char board_from_file[9][9][2];
		char temp,prev_temp;

		inputFile.open(file_name);
		
		if(!inputFile){
			cout << "Error while opening the file." << endl; 
			cout << "Restarting.." << endl;
			return false;
		}

		delete array;

		board_size[0]=9;
		board_size[1]=9;

		array = new int [board_size[0]*board_size[1]+1];

		board_size[0]=1;
		board_size[1]=1;

		i=j=0;

		//basic loop to convert file's chars to integer board.

		while( !inputFile.eof() ){

			inputFile.get(temp);

			if(temp == ' '){
				j++;
				if(line_flag == 0) board_size[0]++;
			}
			else if(temp == '\n' && prev_temp!='\n'){
				i++;
				j=0;
				board_size[1]++;
				line_flag=1;
			}
			else{
				board_from_file[i][j][count%2]=temp;
				if(count%2==1){
					
					if(board_from_file[i][j][0]=='b' && board_from_file[i][j][1]=='b'){
						(*this)(i,j) = -1;
						cord[0]= i;
						cord[1]= j;
					}
					else	(*this)(i,j) = (board_from_file[i][j][0]-'0')*10 + (board_from_file[i][j][1]-'0')*1;
					// ^^ This else makes the char's tens digit + one's digit to an actual integer. 
	 			}
				count ++;
			}
			prev_temp=temp;
		}

		return true;
	}

	bool BoardArray2D::readFromFile(string file_name){

		ifstream inputFile;

		int i, j, count=0 ,line_flag =0;
		int number;

		char board_from_file[9][9][2];
		char temp,prev_temp;

		inputFile.open(file_name);
		
		if(!inputFile){
			cout << "Error while opening the file." << endl; 
			cout << "Restarting.." << endl;
			return false;
		}

		for(i=0;i<board_size[1];i++){
			delete array[i];
		}
		delete *array;

		board_size[0]=9;
		board_size[1]=9;

		array = new int* [board_size[0]];
		for(int i=0;i<board_size[0];i++){
			array[i]=new int[board_size[1]];
		}

		board_size[0]=1;
		board_size[1]=1;

		i=j=0;

		//basic loop to convert file's chars to integer board.
		while( !inputFile.eof() ){

			inputFile.get(temp);

			if(temp == ' '){
				j++;
				if(line_flag == 0) board_size[0]++;
			}
			else if(temp == '\n' && prev_temp!='\n'){
				i++;
				j=0;
				board_size[1]++;
				line_flag=1;
			}
			else{
				board_from_file[i][j][count%2]=temp;
				if(count%2==1){
					
					if(board_from_file[i][j][0]=='b' && board_from_file[i][j][1]=='b'){
						(*this)(i,j) = -1;
						cord[0]= i;
						cord[1]= j;
					}
					else	(*this)(i,j) = (board_from_file[i][j][0]-'0')*10 + (board_from_file[i][j][1]-'0')*1;
					// ^^ This else makes the char's tens digit + one's digit to an actual integer. 
	 			}
				count ++;
			}
			prev_temp=temp;
		}

		return true;
	}

	/* INHERITED operator() FUNCTION */

	int& BoardVector::operator()(int x, int y){

		return array[x][y]; 
	}

	int& BoardArray1D::operator()(int x, int y){

		return array[x*board_size[1]+y+1];
	}

	int& BoardArray2D::operator()(int x, int y){

		return array[x][y];
	}

	/* INHERITED operator== FUNCTION */

	bool BoardVector::operator==(const AbstractBoard& other){

		/*i could not write == operator, sorry*/
		return true;
	}

	bool BoardArray1D::operator==(const AbstractBoard& other){

		/*i could not write == operator, sorry*/
		return true;
	}

	bool BoardArray2D::operator==(const AbstractBoard& other){

		/*i could not write == operator, sorry*/
		return true;
	}

}

/*ILKAN MERT OKUL 1801042649*/