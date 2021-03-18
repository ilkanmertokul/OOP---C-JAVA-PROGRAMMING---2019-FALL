#include <vector>
#include <iostream>

/*ILKAN MERT OKUL 1801042649*/

using namespace std;

namespace NPUZZLE{
/*used namespace named NPUZZLE*/

	class AbstractBoard{

		public:
			void setmove(int m){last_m=m;}
			/*Setmove sets the lastmove*/

			void increaseMove(){m_count+=m_count;}
			/*IncreaseMove increases the move count if move is successful */

			int lastMove(){return last_m;}
			int numberOfMoves(){return m_count;}
			/*some get functions.*/

			virtual void setSize();
			/*setSize takes a input and sets boardsize to it and
			allocates some space if needed */

			virtual void reset();
			/*reset works with setSize(), and it sets the board.*/

			virtual void print();
			/*print prints the current board.*/

			virtual bool move(int input);
			/*move takes an input as a move and returns a boolean
			if move is successful or not.*/

			virtual bool isSolved();
			/*isSolved checks if the game finished or not, and
			returns a boolean value according to it.*/

			virtual void writeToFile();
			/*writeToFile writes the current board to a file,
			with a format.*/

			virtual bool readFromFile(string file_name)=0;
			/*readFromFile takes a string as a filename, and reads
			it to convert to a int board. bb means blank, 00 means wall.*/

			virtual int& operator()(int x, int y)=0;
			/*This operator makes everything easy, takes two input as x and
			y, and returns the value in it.*/

			virtual bool operator==(const AbstractBoard& other)=0;
			/*This operator checks if two boards is equal, and
			returns boolean.*/

		protected:
			/*last m is last move ,m_count is move count
			and board_size with cord makes some board functions easy.*/

			int last_m,m_count;
			int board_size[2];
			int cord[2];

	};

	class BoardVector:public AbstractBoard{

		/*BoardVector, an inheritance of AbstractBoard. Uses vector as board matrix.*/

		public:
			void setSize();
			void reset();
			void print();
			bool move(int input);
			bool isSolved();
			void writeToFile();
			bool readFromFile(string file_name);

			int& operator()(int x, int y);
			bool operator==(const AbstractBoard& other);

		private:
			vector<vector<int>> array;
	};

	class BoardArray1D:public AbstractBoard{

		/*BoardArray1D, an inheritance of AbstractBoard. Uses 1D int array as board matrix.*/

		public:
			~BoardArray1D(); // destructor.

			void setSize();
			void reset();
			void print();
			bool move(int input);
			bool isSolved();
			void writeToFile();
			bool readFromFile(string file_name);

			int& operator()(int x, int y);
			bool operator==(const AbstractBoard& other);
		
		private:
			int *array;
	};

	class BoardArray2D:public AbstractBoard{

		/*BoardArray2D, an inheritance of AbstractBoard. Uses 2D int array as board matrix.*/

		public:
			~BoardArray2D(); // destructor.

			void setSize();
			void reset();
			void print();
			bool move(int input);
			bool isSolved();
			void writeToFile();
			bool readFromFile(string file_name);

			int& operator()(int x, int y);
			bool operator==(const AbstractBoard& other);	

		private:
			int **array;
	};

}

/*ILKAN MERT OKUL 1801042649*/