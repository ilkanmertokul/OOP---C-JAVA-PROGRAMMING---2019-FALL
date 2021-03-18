/* Welcome to Hw1, Npuzzle! */

#include <iostream>

#include <cstdlib>
#include <ctime>

// ^^ this headers used for "random number generators"

using namespace std;

/* 1801042649, İLKAN MERT OKUL */

/* Best read with tab width : 4 */

int make_a_move(int board_size, int **board_array, int *cord, char move){

	int return_v=1;
		
	switch(move){
		case 'D':	//MOVES DOWN

			if(cord[0]!=board_size-1){

				board_array[cord[0]][cord[1]]=board_array[cord[0]+1][cord[1]];
				cord[0]++;

				board_array[cord[0]][cord[1]]=0;
			}
			else return_v=0;

			break;
		case 'L':	//MOVES LEFT

			if(cord[1]!=0){

				board_array[cord[0]][cord[1]]=board_array[cord[0]][cord[1]-1];
				cord[1]--;

				board_array[cord[0]][cord[1]]=0;
			}
			else return_v=0;

			break;
		case 'R':	//MOVES RIGHT

			if(cord[1]!=board_size-1){

				board_array[cord[0]][cord[1]]=board_array[cord[0]][cord[1]+1];
				cord[1]++;

				board_array[cord[0]][cord[1]]=0;
			}
			else return_v=0;

			break;
		case 'U':	//MOVES UP

			if(cord[0]!=0){

				board_array[cord[0]][cord[1]]=board_array[cord[0]-1][cord[1]];
				cord[0]--;

				board_array[cord[0]][cord[1]]=0;
			}
			else return_v=0;

			break;
		}
		return return_v; //return value determines if the move was succesful or not. 1=true, 0=false.
}

void randomizer(int board_size, int **board_array , int *cord){

	int AMOUNT_OF_SHUFFLE = board_size*board_size*board_size;

	//This part of the code makes the puzzle ordered:

	for(int i=0; i<board_size; i++){
		for(int j=0; j<board_size; j++){

			board_array[i][j]=i*board_size+j+1;
		}
	}

	board_array[board_size-1][board_size-1]=0;
	cord[0]=board_size-1;	
	cord[1]=board_size-1;	//resets the coordinates of blank box.

	//This part shuffles:

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

		rdm = make_a_move(board_size,board_array,cord,move);	//randomizer just makes random moves. 1000 times.
																// It is 1000 times because if you play like 12x12 board,
																// Like 100 shuffle is not enough.				
	}
}

void print_table(int board_size, int **board_array, int *cord){

	//It is carefully calculated to print all sizes of tables, from 2x2 to infinity
	//If user has enough screen to display it, though.

	int i,j;
	int board_space_controller = 10;
	int digit=1, digit_control=1;

	while(1){ //Just calculates the digit of the max number. Like in 11x11 board, digit is 3.
		if(digit_control*10>board_size*board_size-1)	break;
		else{
			digit++;
			digit_control *=10;
		} 
	}

	for(i=0;i<board_size;i++){

		cout << " ";
		for(j=0;j<=(digit+3)*board_size-1;++j) cout<<"-";	//digit used here, to make board more beautiful.
		cout << endl;

		for(j=0;j<board_size;j++){
		 	if (board_array[i][j]!=0)	cout << " | " << board_array[i][j] ;
			else cout << " |  ";

		 	board_space_controller = 10;

		 	while(1){

		 		if(board_size*board_size-1>=board_space_controller && board_array[i][j]<board_space_controller )	cout << " ";
		 	 
		 		if(board_size*board_size-1>=board_space_controller)		board_space_controller *=10; 
		 		else break;
		 	}
		}	
		cout << "|" << endl;
	}

	cout << " ";
	for(j=0;j<=(digit+3)*board_size-1;++j) cout<<"-";
	cout << endl;
}

char game_menu(){

	//Prints out the menu, and returns an input.

	char input;

	cout << "Press: "
		 << "L - Move the empty cell left."		<< endl
		 << "R - Move the empty cell right."	<< endl	
		 << "U - Move the empty cell up."		<< endl
		 << "D - Move the empty cell down." 	<< endl
		 << "I - “İntelligent” move for you."	<< endl
		 << "S - Shuffle."	<< endl
		 << "Q - Quit."		<< endl;

	cin >> input;

	return input;
}

int is_it_finished(int board_size, int **board_array){

	//Checks the board, if it is finished or not. Returns the value of success.

	int i,j;

	for(i=0;i<board_size; i++){
		for(j=0; j<board_size; j++){

			if(i==board_size-1 && j==board_size-1){
				if(board_array[i][j]!=0) return 0;
			}
			else if(board_array[i][j]!=i*board_size+j+1) return 0;
			
		}
	}
	return 1;
}

int which_row(int board_size,int ** board_array, int cord1, int cord2){

	//Used in intellegent_mover function, used for up / down score calculates.

	int count=0;
	int temp=board_array[cord1][cord2];

	while(1){

		if(temp>board_size){

			temp -=board_size;
			count++;
		}
		else break;
	}	

	return count;
}

void intellegent_mover(int board_size, int **board_array, int *cord){

	//This part has an easy AI to think what move will be the best,

	/*

	SCORE IS BASICALLY THE DISTANCE BETWEEN THE BLOCK AND
	WHERE IT BELONGS TO. IF THE MOVE CAN MAKE THE DISTANCE SMALLER,
	SCORE IS POSITIVE. OTHERWISE, NEGATIVE.

	*/

	int return_v=0;
	int range_1;
	int total_score[4]={0,0,0,0};

	if(cord[0]!=board_size-1){

		//Controls the score of "Going Down"

		range_1= (cord[0]+1) - which_row(board_size,board_array,cord[0]+1,cord[1]);

		total_score[0] = range_1 ;
	}	
	if(cord[0]!=0){

		//Controls the score of "Going Up"

		range_1 = which_row(board_size,board_array,cord[0]-1,cord[1]) - (cord[0]-1);

		total_score[1] = range_1 ;
	}
	if(cord[1]!=board_size-1){

		//Controls the score of "Going Right"

		range_1 = (cord[1]+1)-((board_array[cord[0]][cord[1]+1]+board_size)%(board_size)-1);

		total_score[2] = range_1 ;
	}
	if(cord[1]!=0){

		//Controls the score of "Going Left"

		range_1 = ((board_array[cord[0]][cord[1]-1]+board_size)%(board_size)-1) - (cord[1]-1);

		total_score[3] = range_1 ;
	}


	int max=0;

	for(int i=0;i<4;i++){
		if(total_score[i]>=total_score[max]){
			max=i;
		}
	}
	while(return_v==0){

		switch(max){
			case 0:
				return_v=make_a_move(board_size,board_array,cord,'D');
				break;

			case 1:
				return_v=make_a_move(board_size,board_array,cord,'U');
				break;

			case 2:
				return_v=make_a_move(board_size,board_array,cord,'R');
				break;

			case 3:
				return_v=make_a_move(board_size,board_array,cord,'L');
				break;
		}
		if(return_v==0){
			if(max<3){
				max++;
			}
			else max=0;
		}
	}

	cout<< 	"Scores:" << endl
		<<	" *Down:" << total_score[0] 
		<<	" *Up:" << total_score[1]
		<<  " *Right:" << total_score[2] 
		<<  " *Left" << total_score[3] << endl << " Choosen move: "<< max+1 << endl;
}

int main_game(int board_size, int **board_array){

	int input;
	int finish=0,move_flg;
	int cord[2]={board_size-1,board_size-1}; 
	int move=0;

	randomizer(board_size, board_array, cord);

	while(finish == 0){

	print_table(board_size, board_array, cord);
	input = game_menu();
	move_flg=1;

	switch(input){

		case 'R':
		case 'L':
		case 'U':
		case 'D':

			//Move cases

			move_flg=make_a_move(board_size,board_array,cord,input);
			if(move_flg==0) cout << "You cannot move there." << endl;
			else move++;
			break;

		case 'I':	

			intellegent_mover(board_size, board_array, cord);
			move++;
			break;

		case 'S':

			randomizer(board_size, board_array, cord);
			move=0;
			cout << "Move count has been set to zero" << endl;
			break;

		case 'Q':
			return 0; // if user quits the game, returns 0.
		
		default:	cout << "error"<< endl;
		}

		//Controls the game every end of loop.
		finish=is_it_finished(board_size, board_array);
	}

	print_table(board_size, board_array, cord);
	cout << "Total move = " << move;
	return 1; // if user wins the game, returns 1.
}

int main(){
	
	int i,j;
	int board_size;

	cout << " ---- Welcome to N-PUZZLE! ---- " << endl 
		 << "Please enter a size to start the game." ;

	do{
		cin  >>	board_size;	 
		if(board_size <3 ) cout << "You need to enter at least 3, for puzzle.";

	}while(board_size<3);

	//
		srand(time(NULL));	//Random maker
	//

	int **board_array; // declared array according to board size.

	board_array = (int ** ) malloc (board_size * sizeof * board_array );
	for(int i=0; i< board_size ; i++ )	board_array[i] = (int *) malloc (board_size * sizeof * board_array[i]);
	
	int result = main_game(board_size, board_array);

	for(i=0;i<board_size;i++)	free(board_array[i]);
	free(board_array);	

	if(result==1)	cout << "Nice, you won the game!" << endl;
	else 			cout << "You choosed to exit." << endl;

	cout << "Exiting." << endl;

	return 0;
}

/* Thanks for reading the code! */
