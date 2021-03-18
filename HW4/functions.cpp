#include <cstdlib>
#include <ctime>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "class.h"

using namespace std;

/*ILKAN MERT OKUL, 1801042649*/


int NPuzzle::Board::operator()(int i,int j){

	if(i>board_size[0] || j>board_size[1]){
		cout << "Wrong index for NPuzzle::Board::operator. Exiting";
		exit(-1);
	} 

	return board_array[i][j];
}

ostream & operator <<(ostream & outputstream , NPuzzle the_puzzle){

	int i;
	for(i=0;i<15;i++)	outputstream << " -";
	the_puzzle.print(0);	//calls the main print function.
	for(i=0;i<15;i++)	outputstream << " -";

	return outputstream;
}

bool NPuzzle::Board::operator ==(const Board other){
	//Checks for equality.
	int i,j;

	for(i=0;i<board_size[1];i++){
		for(j=0;j<board_size[0];j++){
			if(this->board_array[i][j]!=other.board_array[i][j]) return false;
		}
	}
	return true	;
}

/***************************/

void NPuzzle::solvePuzzle(){
	//The 'solve' algorithm.

	int i=0,j=0;
	vector<int> solved_vector;
	Board new_board,temp_board;

	while(1){
		//It loops until issolved is true.
		temp_board=board[i];
		if(temp_board.move('U') && temp_board.lastMove() != 'D'){
			board.push_back(temp_board);
			j++;
			print(j);
			if(isSolved(j)) break;
		}

		temp_board=board[i];
		if(temp_board.move('D') && temp_board.lastMove() != 'U'){
			board.push_back(temp_board);
			j++;
			print(j);
			if(isSolved(j)) break;
		}
		
		temp_board=board[i];
		if(temp_board.move('L') && temp_board.lastMove() != 'R'){
			board.push_back(temp_board);
			j++;
			print(j);
			if(isSolved(j)) break;
		}

		temp_board=board[i];
		if(temp_board.move('R') && temp_board.lastMove() != 'L'){
			board.push_back(temp_board);
			j++;
			print(j);
			if(isSolved(j)) break;
		}
		i++;
	}

	cout << "Solved!"<< endl;
	board[0]=board[j];
}

/***************************/

void NPuzzle::printReport() {

	cout << "You moved: " << board[0].numberOfMoves() << " times." << endl;
	if(!board[0].isSolved()) cout << "Your game has not finished yet." << endl;
	else cout << "Your game is finished!" << endl; 
}

bool NPuzzle::isSolved(const int index){

	return board[index].isSolved();
}

bool NPuzzle::Board::isSolved(){

	int i,j;
	int k;
	int num_cnt = 0;

	//Checks the game is finished or not.
	for(i=0;i<board_size[1];i++){
		for(j=0;j<board_size[0];j++){	
			if(board_array[i][j]!=0){
				num_cnt++;
				
				//If it is blank tile, it seeks any other number to exit, if it 'impassable blocks' only,
				//It is success!
				if(board_array[i][j]==-1){
					for(k=j+1;k<board_size[0];k++){
						if(board_array[i][k]!=0)	return false;
					}
					for(k=i+1;k<board_size[1];k++){
						for(int l=0;l<board_size[1];l++){
							if(board_array[k][l]!=0)	return false;
						}
					}
					return true;
				}
				if(board_array[i][j]!=num_cnt)	return false;
			}
		}
	}
	return true;
}

/***************************/

void NPuzzle::writeToFile(){

	string file_name;
	cout << "Enter a file name to save the game." << endl;
	cin >> file_name; 
	board[0].writeToFile(file_name);

	print(0);
}

void NPuzzle::Board::writeToFile(string file_name){

	ofstream outputFile;
	outputFile.open(file_name);

	int i,j;

	//basic nested loop to convert game to a .txt file.
	for( i=0 ; i< board_size [1] ; i++){
		for ( j=0 ; j< board_size[0] ; j++){
			if(board_array[i][j]==-1){
				outputFile << "bb ";
			}
			else{
				if(board_array[i][j] < 10 && board_array[i][j] > -1) outputFile << "0";
				outputFile << board_array[i][j]<< " " ;
			}
		}
		outputFile << endl;
	}

	cout << "Written!" << endl;
}

void NPuzzle::readFromFile(string file_name){

	reset();
	cout<< "Reading :" << file_name << ".." << endl;
	if(board[0].readFromFile(file_name))	return;
	else setSize();
}

bool NPuzzle::Board::readFromFile(string file_name){

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

	board_array.resize(9);
	for(i=0; i<9; i++)	board_array[i].resize(9);
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
					board_array[i][j] = -1;
					cord[0]= i;
					cord[1]= j;
				}
				else	board_array[i][j] = (board_from_file[i][j][0]-'0')*10 + (board_from_file[i][j][1]-'0')*1;
				// ^^ This else makes the char's tens digit + one's digit to an actual integer. 
 			}
			count ++;
		}

		prev_temp=temp;
	}

	board_array.resize(board_size[0]);
	for(i=0; i<board_size[0]; i++)	board_array[i].resize(board_size[1]);

	printf("%d %d ",board_size[0],board_size[1]);


	return true;
}

/***************************/

void NPuzzle::print(const int index)const{

	int i;
	for(i=0;i<15;i++)	cout << " -";
	board[index].print();
	for(i=0;i<15;i++)	cout << " -";
}

void NPuzzle::Board::print()const{

	cout << endl;
	int i,j;

	//prints the board.

	for( i=0 ; i< board_size [1] ; i++){
		for ( j=0 ; j< board_size[0] ; j++){
			if(board_array[i][j] < 10 && board_array[i][j] > -1) cout << "0";
			if(board_array[i][j]!=-1)	cout << board_array[i][j]<< " " ;
			else	cout << "   ";
		}
		cout << endl;
	}
}

/***************************/

void NPuzzle::reset(){

	Board new_board;
	new_board.reset();

	board.resize(0);
	board.push_back(new_board);
}

void NPuzzle::Board::reset(){

	board_number=0;
	last_move='S';
}

void NPuzzle::setSize(){

	reset();

	short input; 

	cout << "Enter a size!" << endl;
	
	do{
		cin >> input; 
		if( (9<input) && (input<3) ) cout << "Enter a value between 3 and 9!";
	}while( (9<input) && (input<3) );

	board[0].setSize(input);
}

void NPuzzle::Board::setSize(int input){

	board_size[0]=input;
	board_size[1]=input;	

	int i,j;

	board_array.resize(board_size[0]);

	for(i=0; i<board_size[0]; i++){
		board_array[i].resize(board_size[1]);
		for(j=0; j<board_size[0]; j++){
			board_array[i][j]=(i*board_size[0]+j+1);
		}
	}

	//Set coordinates to empty block.
	cord[0]=board_size[0]-1;
	cord[1]=board_size[1]-1;
	board_array[board_size[0]-1][board_size[0]-1]=-1;
}

/***************************/

void NPuzzle::shuffle(){

	board.resize(1);

	const int AMOUNT_OF_SHUFFLE= board[0].getBoardSize();	//gets size1*size2
	for(int i=0; i<AMOUNT_OF_SHUFFLE; i++)	moveRandom();//moves randomly
	cout << "Your game is shuffled!" << endl;
}

void NPuzzle::moveRandom(){

	int rdm;
	char move;

	rdm = rand() % 4 ;

	//a switch for random moves.
	switch(rdm){
		case 0: move = 'R';
			break;
		case 1: move = 'L';
			break;
		case 2: move = 'U';
			break;
		case 3: move = 'D';
	}

	board[0].move(move);
}

void NPuzzle::move(char input,int index){

	bool flag=false;
	flag=board[index].move(input);

	if(flag==false)	cout << "Invalid move." << endl;
	else board[0].numberOfMoves()++;
}

bool NPuzzle::Board::move(char input){

	switch(input){
		case 'D':	//MOVES DOWN
			if(cord[0]!=board_size[1]-1 && board_array[cord[0]+1][cord[1]]!=0 ){

				board_array[cord[0]][cord[1]]=board_array[cord[0]+1][cord[1]];
				cord[0]++;

				board_array[cord[0]][cord[1]]=-1;
			}
			else	return false;
			break;
		case 'L':	//MOVES LEFT
			if(cord[1]!=0 && board_array[cord[0]][cord[1]-1]!=0){

				board_array[cord[0]][cord[1]]=board_array[cord[0]][cord[1]-1];
				cord[1]--;

				board_array[cord[0]][cord[1]]=-1;
			}
			else 	return false;
			break;
		case 'R':	//MOVES RIGHT
			if(cord[1]!=board_size[0]-1 && board_array[cord[0]][cord[1]+1]!=0){

				board_array[cord[0]][cord[1]]=board_array[cord[0]][cord[1]+1];
				cord[1]++;

				board_array[cord[0]][cord[1]]=-1;
			}
			else 	return false;
			break;
		case 'U':	//MOVES UP
			if(cord[0]!=0 && board_array[cord[0]-1][cord[1]]!=0){

				board_array[cord[0]][cord[1]]=board_array[cord[0]-1][cord[1]];
				cord[0]--;

				board_array[cord[0]][cord[1]]=-1;
			}
			else return false;
			break;
	}

	last_move=input;
	//move_amount++;
	return true;
}