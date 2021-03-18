#include <string>
#include <vector>

using namespace std;

/*ILKAN MERT OKUL, 1801042649*/

class NPuzzle{

	public:

		void setSize();
		void reset();
		void print(const int index)const;
		void shuffle();
		void moveRandom();
		void move(char input,int index);
		void readFromFile(string file_name);
		void writeToFile();
		void printReport();
		bool isSolved(const int index);
		void solvePuzzle();
		friend ostream & operator << (ostream & outputstream, NPuzzle the_puzzle);
		//friend void operator >> (istream & inputstream, NPuzzle the_puzzle);

	private:

		class Board{

			public:

				int getBoardSize(){return board_size[0]*board_size[1];};

				void setSize(int input);
				void reset();
				void print()const;
				bool move(char input);
				int & numberOfMoves(){return move_amount;}
				int NumberOfBoards(){return board_number;}
				char lastMove(){return last_move;}
				bool readFromFile(string file_name);
				void writeToFile(string file_name);	
				bool isSolved();
				bool operator ==(const Board other);
				int operator()(int i,int j);
				
			private:	
				int board_number;				

				vector<vector<int>> board_array;
				char last_move;
				int move_amount=0;

				int cord[2];
				int board_size[2]={9,9};

		};

		vector<Board> board;
};