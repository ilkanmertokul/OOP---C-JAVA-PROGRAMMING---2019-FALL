#include <cstdlib>
#include <ctime>

#include <string>
#include <fstream>
#include <iostream>
#include "class.h"

using namespace std;

/*ILKAN MERT OKUL, 1801042649*/

void NPuzzle::reset(){

	board.reset();
}

void NPuzzle::Board::reset(){

	int i,j;
	int count = 1;

	//Sorts whole puzzle.
	for(i=0;i<board_size[1];i++){
		for(j=0;j<board_size[0];j++){

			if(board_array[i][j]!=0){

				board_array[i][j]=count;
				++count;

			}
		}
	}

	//Puts blank tile to last avaiable spot. 
	for(i=board_size[1]-1;i>=0;i--){
		for(j=board_size[0]-1;j>=0;j--){

			if(board_array[i][j]!=0){

				board_array[i][j]=-1;
				
				cord[0]=i;
				cord[1]=j;

				return;
			}
		}
	}
}

/********************/

void NPuzzle::solvePuzzle(){

	int rdm;
	char input;

	//Solves the puzzle using moveIntelligent function.
	while(!isSolved()){

		for(int i=0 ; i< 10 ; i++){
			moveIntelligent();

			if(isSolved()) break;
		}

		for(int i=0; i<3; i++){
			rdm = rand() % 4 ;

			switch(rdm){
				case 0: input = 'R';
					break;
				case 1: input = 'L';
					break;
				case 2: input = 'U';
					break;
				case 3: input = 'D';
			}
			move(input);

			if(isSolved()) break;
		}
		print();
	}
}

int NPuzzle::Board::whichRow(int customcord1,int customcord2){

	//Used in moveIntelligent function, used for up / down score calculates.
	int count=0;
	int temp=board_array[customcord1][customcord2];

	while(1){
		if(temp>board_size[1]){
			temp -=board_size[1];
			count++;
		}
		else break;
	}	
	return count;
}

void NPuzzle::moveIntelligent(){

	if(board.moveIntelligent()) move_amount++;
}

bool NPuzzle::Board::moveIntelligent(){

	int total_score[4]={0,0,0,0};
	int range_1;

	if(cord[0]!=board_size[1]-1 && board_array[cord[0]+1][cord[1]]!=0 ){

		//Controls the score of "Going Down"
		range_1= (cord[0]+1) - whichRow(cord[0]+1,cord[1]);
		total_score[0] = range_1 ;
	}
	else	total_score[0] = -50;

	if(cord[0]!=0 && board_array[cord[0]-1][cord[1]]!=0) {

		//Controls the score of "Going Up"
		range_1 = whichRow(cord[0]-1,cord[1]) - (cord[0]-1);
		total_score[1] = range_1 ;
	}
	else	total_score[1] = -50;

	if(cord[1]!=board_size[0]-1 && board_array[cord[0]][cord[1]+1]!=0){

		//Controls the score of "Going Right"
		range_1 = (cord[1]+1)-((board_array[cord[0]][cord[1]+1]+board_size[0])%(board_size[0])-1);
		total_score[2] = range_1 ;
	}
	else	total_score[2] = -50;

	if(cord[1]!=0 && board_array[cord[0]-1][cord[1]]!=0){

		//Controls the score of "Going Left"
		range_1 = ((board_array[cord[0]][cord[1]-1]+board_size[0])%(board_size[0])-1) - (cord[1]-1);
		total_score[3] = range_1 ;
	}
	else	total_score[3] = -50;

	int max=0;
	for(int i=0;i<4;i++){
		if(total_score[i]>=total_score[max]){
			max=i;
		}
	}

	switch(max){
			case 0:
				return move('D');
				break;
			case 1:
				return move('U');
				break;
			case 2:
				return move('R');
				break;
			case 3:
				return move('L');
				break;
		}
}

/********************/

bool NPuzzle::isSolved() const {

	return board.isSolved();
}

bool NPuzzle::Board::isSolved() const {

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

/********************/

void NPuzzle::printReport() const {

	cout << "You moved: " << move_amount << " times." << endl;
	if(!board.isSolved()) cout << "Your game has not finished yet." << endl;
	else cout << "Your game is finished!" << endl; 
}

/********************/

void NPuzzle::shuffle(){

	reset();
	const int AMOUNT_OF_SHUFFLE= board.getBoardSize();	//gets size1*size2
	for(int i=0; i<AMOUNT_OF_SHUFFLE; i++)	moveRandom();//moves randomly
	cout << "Your game is shuffled!" << endl;
	move_amount -= AMOUNT_OF_SHUFFLE ;
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

	board.move(move);
	++move_amount;
}

void NPuzzle::move(const char input){

	bool flag=false;
	flag=board.move(input);

	if(flag==false)	cout << "Invalid move." << endl	;
	else	++move_amount;
}

bool NPuzzle::Board::move(const char input){

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
	return true;
}

/********************/

void NPuzzle::writeToFile() const {

	string file_name;
	cout << "Enter a file name to save the game." << endl;
	cin >> file_name; 
	board.writeToFile(file_name);
}

void NPuzzle::Board::writeToFile(const string file_name) const {

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
}

void NPuzzle::readFromFile(const string file_name){

	cout<< "Reading :" << file_name << ".." << endl;
	board.readFromFile(file_name);
}

void NPuzzle::Board::readFromFile(const string file_name){

	board_size[0]=1;
	board_size[1]=1;

	ifstream inputFile;

	int i=0 , j=0 , count=0 ,line_flag =0;
	int number;

	char board_from_file[9][9][2];
	char temp;

	inputFile.open(file_name);
	
	if(!inputFile){
		cout << "Error while opening the file." << endl; 
		return;
	}

	//basic loop to convert file's chars to integer board.
	while( !inputFile.eof() ){
		inputFile.get(temp);

		if(temp == ' '){
			j++;
			if(line_flag == 0) board_size[0]++;
		}
		else if(temp == '\n'){
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
	}
}

/********************/

void NPuzzle::print() const {

	int i;
	for(i=0;i<15;i++)	cout << " -";
	board.print();
	for(i=0;i<15;i++)	cout << " -";
}

void NPuzzle::Board::print() const {

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

/********************/

void NPuzzle::setSize(){

	short input; 

	cout << "Enter a size!" << endl;
	
	do{
		cin >> input; 
		if( (9<input) && (input<3) ) cout << "Enter a value between 3 and 9!";

	}while( (9<input) && (input<3) );

	board.setSize(input);
}

void NPuzzle::Board::setSize(int input){

	board_size[0]=input;
	board_size[1]=input;	

	for(int i=0; i<board_size[0]; i++){
		for(int j=0; j<board_size[0]; j++){
			board_array[i][j]=i*board_size[0]+j+1;
		}
	}

	//Set coordinates to empty block.
	cord[0]=board_size[0]-1;
	cord[1]=board_size[1]-1;
	board_array[board_size[0]-1][board_size[0]-1]=-1;
}

/*******************/
