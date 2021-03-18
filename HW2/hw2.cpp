/* Welcome to Hw2! */

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <ctime>

using namespace std;

/* ILKAN MERT OKUL, 1801042649, RECOMMENDED TAB SIZE: 4*/

/*FUNCTIONS USED*/

void intellegent_mover(const int board_size[2],int board_array[9][9],int cord[2]);
void read_file(int board_size[2], int board_array[9][9], int cord[2],const string filename);
void shuffle(const int board_size[2] ,int board_array[9][9], int cord[2]);
void make_a_square_board(const int board_size[2],int board_array[9][9]);
void print_table(const int board_size[2],const int board_array[9][9]);
void write_a_file(const int board_size[2],const int board_array[9][9]);

int which_row(const int board_size[2] ,const int board_array[9][9], const int cord1,const int cord2);
bool is_it_finished(const int board_size[2],const int board_array[9][9]);
int convert(const char tens_digit, const char ones_digit, int board_array[9][9], const int loc_x, const int loc_y,int cord[2]);
int main_game(int board_size[2], int board_array[9][9], const int flag , const string startfilename);

bool make_a_move(const int board_size[2],int board_array[9][9],int cord[2],const char move);
char game_menu();

/*START OF CODES*/

int which_row(const int board_size[2] ,const int board_array[9][9], const int cord1,const int cord2){

	//Used in intellegent_mover function, used for up / down score calculates.

	int count=0;
	int temp=board_array[cord1][cord2];

	while(1){
		if(temp>board_size[1]){
			temp -=board_size[1];
			count++;
		}
		else break;
	}	
	return count;
}

void intellegent_mover(const int board_size[2],int board_array[9][9],int cord[2]){

	//This function can be called once, or to solve whole puzzle.

	int total_score[4]={0,0,0,0};
	int range_1;

	if(cord[0]!=board_size[1]-1 && board_array[cord[0]+1][cord[1]]!=0 ){

		//Controls the score of "Going Down"
		range_1= (cord[0]+1) - which_row(board_size,board_array,cord[0]+1,cord[1]);
		total_score[0] = range_1 ;
	}
	if(cord[0]!=0 && board_array[cord[0]-1][cord[1]]!=0) {

		//Controls the score of "Going Up"
		range_1 = which_row(board_size,board_array,cord[0]-1,cord[1]) - (cord[0]-1);
		total_score[1] = range_1 ;
	}
	if(cord[1]!=board_size[0]-1 && board_array[cord[0]][cord[1]+1]!=0){

		//Controls the score of "Going Right"
		range_1 = (cord[1]+1)-((board_array[cord[0]][cord[1]+1]+board_size[0])%(board_size[0])-1);
		total_score[2] = range_1 ;
	}
	if(cord[1]!=0 && board_array[cord[0]-1][cord[1]]!=0){

		//Controls the score of "Going Left"
		range_1 = ((board_array[cord[0]][cord[1]-1]+board_size[0])%(board_size[0])-1) - (cord[1]-1);
		total_score[3] = range_1 ;
	}

	int max=0;
	for(int i=0;i<4;i++){
		if(total_score[i]>=total_score[max]){
			max=i;
		}
	}

	switch(max){
			case 0:
				make_a_move(board_size,board_array,cord,'D');
				break;
			case 1:
				make_a_move(board_size,board_array,cord,'U');
				break;
			case 2:
				make_a_move(board_size,board_array,cord,'R');
				break;
			case 3:
				make_a_move(board_size,board_array,cord,'L');
				break;
		}

		//This prints the scores, if you want to see,
		/*
		cout<< 	"Scores:" << endl
		<<	" *Down:" << total_score[0] 
		<<	" *Up:" << total_score[1]
		<<  " *Right:" << total_score[2] 
		<<  " *Left" << total_score[3] << endl << " Choosen move: "<< max+1 << endl;
		*/
}

void make_a_square_board(const int board_size[2],int board_array[9][9]){

	//This happens when there are no file entered while starting the code.

	for(int i=0; i<board_size[0]; i++){
		for(int j=0; j<board_size[0]; j++){
			board_array[i][j]=i*board_size[0]+j+1;
		}
	}
	board_array[board_size[0]-1][board_size[0]-1]=-1;
}

void write_a_file(const int board_size[2],const int board_array[9][9]){

	//Outputs a file. Similar to print_board but for file.

	ofstream outputFile;
	string a_file_name;

	cout << "Enter a fine name to save the board." << endl;
	cin >> a_file_name;

	outputFile.open(a_file_name);

	int i,j;
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

bool is_it_finished(const int board_size[2],const int board_array[9][9]){

	//Checks if the game is finished or not.

	int i,j;
	int k;
	int num_cnt = 0;

	for(i=0;i<board_size[1];i++){
		for(j=0;j<board_size[0];j++){	
			if(board_array[i][j]!=0){

				num_cnt++;
				
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

void shuffle(const int board_size[2] ,int board_array[9][9], int cord[2]){

	//Makes random moves, amount of some calculations below. 
	const int AMOUNT_OF_SHUFFLE=board_size[1]*board_size[0]*10;
	int rdm;
	char move;
	for(int i=0; i<AMOUNT_OF_SHUFFLE; i++){
		rdm = rand() % 4 ;

		switch(rdm){
			case 0: move = 'R';
				break;
			case 1: move = 'L';
				break;
			case 2: move = 'U';
				break;
			case 3: move = 'D';
		}
		make_a_move(board_size,board_array,cord,move);
	}
}

bool make_a_move(const int board_size[2],int board_array[9][9],int cord[2],const char move){

	//Makes a move, returns success or failure.
	switch(move){
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

int convert(const char tens_digit,const char ones_digit, int board_array[9][9], const int loc_x, const int loc_y,int cord[2]){

	//converts 2 char to an int, -1 is empty square, 0 is walls.

	int number;
	if(tens_digit=='b' && ones_digit == 'b'){
		//Empty equals to -1.
		number=-1;
		cord[0]=loc_y;
		cord[1]=loc_x;
	}
	else{
		number = (tens_digit-'0')*10 + (ones_digit-'0')*1;
		board_array[loc_y][loc_x] = number;
	}
	return number;
}

void read_file(int board_size[2], int board_array[9][9], int cord[2],const string filename){

	//Reads the file, sends the chars to function "convert" above.

	cout << "Reading " << filename << ".." << endl; 

	board_size[0]=1;
	board_size[1]=1;

	ifstream inputFile;

	int i=0 , j=0 , count=0 ,line_flag =0;

	char board_from_file[9][9][2];
	char temp;

	inputFile.open(filename);
	
	if(!inputFile){
		cout << "Error while opening the file." << endl; 
		return;
	}

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
				board_array[i][j]=convert(board_from_file[i][j][0],board_from_file[i][j][1],board_array,j,i,cord);
			}
			count ++;
		}
	}
}

void print_table(const int board_size[2],const int board_array[9][9]){

	//Prints the table

	int i,j;
	for( i=0 ; i< board_size [1] ; i++){
		for ( j=0 ; j< board_size[0] ; j++){
			if(board_array[i][j] < 10 && board_array[i][j] > -1) cout << "0";
			if(board_array[i][j]!=-1)	cout << board_array[i][j]<< " " ;
			else	cout << "   ";
		}
		cout << endl;
	}
}

char game_menu(){

	//Prints out the menu, and returns an input.
	char input;
	cout << endl << "Press: "<< endl << endl
		 << "L - Move the empty cell left."		<< endl
		 << "R - Move the empty cell right."	<< endl	
		 << "U - Move the empty cell up."		<< endl
		 << "D - Move the empty cell down." 	<< endl << endl 
		 << "I - İntelligent move for you."	<< endl
		 << "V - Solve the problem. " << endl
		 << "T - Print a report about how many moves have been done." << endl
		 << "E - Save puzzle to a file." << endl
		 << "F - Load a puzzle from a file." << endl
		 << "S - Shuffle."	<< endl
		 << "Q - Quit."		<< endl;

	cin >> input;
	return input;
}

int main_game(int board_size[2], int board_array[9][9],const bool flag , const string startfilename){

	/*
		input is for game_menu return value.
		finish is for is the game is finished or not.
		move_flag decides if the move success or not, and if it is success, move_count increases by 1.
		cord holds the empty block's coordinates.
	*/

	string fname;
	bool move_flag=1,finish=0;
	int cord[2]={board_size[0]-1,board_size[1]-1}; 
	int move_count=0,input;

	if(flag==true)	read_file(board_size,board_array,cord,startfilename);
	else	shuffle(board_size,board_array,cord);
	
	while (finish == false){

		print_table(board_size,board_array);
		input = game_menu();

		switch (input) {

			case 'R':
			case 'L':
			case 'U':
			case 'D':
				move_flag=make_a_move(board_size,board_array,cord,input);
				if(move_flag==false)	cout << "You cant move." << endl;
				else	move_count++;
				break;

			case 'T':	
				cout << "You moved :" << move_count << "times." << endl;
				finish = is_it_finished(board_size,board_array);
				if(finish==1)	cout << "THE GAME IS FINISHED"<< endl;
				else 			cout << "The game is not finished yet." << endl;
				break;

			case 'E':
				write_a_file(board_size,board_array);
				break;	

			case 'S':
				shuffle(board_size,board_array,cord);
				cout << "Your move count has been set to zero, start again." << endl; 
				move_count=0;
				break;

			case 'F':
				cout << "Please enter a filename." << endl;
				cin  >> fname;
				read_file(board_size,board_array,cord,fname);
				cout << "Your move count has been set to zero, start again." << endl; 
				move_count=0;
				break;

			case 'I':
				intellegent_mover(board_size,board_array,cord);
				move_count++;
				break;

			case 'Q':
				cout << "You choosed to exit." << endl;
				return 0;

			case 'V':
				
				while(!is_it_finished(board_size,board_array)){

					for(int i=0 ; i< 10 ; i++){
						intellegent_mover(board_size,board_array,cord);
						move_count++;

						if(is_it_finished(board_size,board_array)==1) break;
					}
					
					int rdm;
					char move;

					for(int i=0; i<3; i++){
						rdm = rand() % 4 ;

						switch(rdm){
							case 0: move = 'R';
								break;
							case 1: move = 'L';
								break;
							case 2: move = 'U';
								break;
							case 3: move = 'D';
						}
						make_a_move(board_size,board_array,cord,move);
						move_count++;
					}
					if(is_it_finished(board_size,board_array)==true) break;
					//Prints the table after every 13 move.
					print_table(board_size,board_array);
					cout << endl;
				}

				break;
			default: 	
				cout << "error" << endl; 
		}
		finish = is_it_finished(board_size,board_array);
		if(finish==true){
			cout << endl << endl << endl << endl;
			print_table(board_size,board_array);
			cout << "You made total of "<< move_count << "moves and finished!";
		}
	}
	return 1;
}

int main(int argc ,char **argv){
	
	int board_array[9][9];
	int board_size[2]={9,9};

	string startfilename;
	bool flag=false;

	srand(time(NULL));	//Random maker

	cout << " ---- Welcome to N-PUZZLE! ---- " << endl ;
	if(argc==1){
		cout	 << "Please enter a size to start the game." << endl ;
		do{
			cin  >>	board_size[0];	 
			if(board_size[0] < 3 || board_size[0] > 9) cout << "You need to enter at least 3, for puzzle.";

		}while(board_size[0] < 3 || board_size[0] > 9);
		make_a_square_board(board_size,board_array);
	}
	else{
		startfilename = argv[1];
		flag=true;
	}

	board_size[1]=board_size[0]; //to make it square, while starting the game.
	int result = main_game(board_size,board_array,  flag , startfilename  );

	if(result==1)		cout << "Nice, you won the game!" << endl;
	else 				cout << "You choosed to exit." << endl;

	cout << "Exiting." << endl;

	return 0;
}

/* Thanks for reading the code. */