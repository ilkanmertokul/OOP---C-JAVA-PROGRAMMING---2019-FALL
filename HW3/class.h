#include <string>
using namespace std;

/*ILKAN MERT OKUL, 1801042649*/

class NPuzzle{

	public:

		void readFromFile(const string filename);
		void print() const;
		void setSize();
		void move(const char input);
		void shuffle();
		void moveRandom();
		void writeToFile() const;
		void printReport() const;
		bool isSolved() const;
		void moveIntelligent();
		void solvePuzzle();
		void reset();

	private:

		class Board{

			public:

				int getBoardSize(){return board_size[0]*board_size[1];};

				void setSize(int input);	
				void print() const;
				void readFromFile(const string filename);
				bool move(const char input);
				void writeToFile(const string filename) const ;
				bool isSolved() const;
				bool moveIntelligent();
				void reset();

			private:

				int whichRow(int customcord1,int customcord2);

				int board_array[9][9];
				int board_size[2]={9,9};
				int cord[2];
		};

		int move_amount=0;
		Board board;
};
