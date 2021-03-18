package homework_7;

/** @author İLKAN MERT OKUL
 * Welcome to AbstractBoard, This class has abstract methods.*/

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public abstract class AbstractBoard {
	
	protected int c1, c2; // gives us the coordinates of the blank cell.
	
	// Needed info for board.
	protected int boardSizeX;
	protected int boardSizeY;
	
	protected int moveCount; 
	protected char lastMove;
	
	// Count is boards that have been created, it is static.
	private static int count = 0;
	
	AbstractBoard(){
		
		moveCount=0;
		lastMove='S';
		boardSizeX=-1;
		
		count++;
	}
	
	public abstract void setSize(int sizeX, int sizeY);
	/**It takes two sizes as x and y, and assings them to 
	 * boardSizeX and boardSizeY, calls reset() function and shuffles.
	 * @param sizeX and sizeY for board sizes
	 */
	
	public abstract int cell(int x,int y);
	/**It takes two parameters as x and y and returns the
	 * value of it according to array[]
	 * @param int x , y as coordinates.
	 * @return array[x][y]*/
	
	public abstract boolean move(int m);
	/**It takes a move, 4,8,6 or 2. and tries to move
	 * the blank cell. if it is possible, returns true and
	 * increases the move count by one with changing the last move.
	 * @param move
	 * @return a boolean for is that move possible or not. */
	
	public abstract void reset();
	/** It resets the board for final solution.
	 * */
	
	public boolean Equals(AbstractBoard other){
		/**Equals checks if two objects are equal or not,
		 * and returns boolean.
		 * @param another Abstractboard to compare.
		 * @return true if equal.*/
		
		if(boardSizeX != other.boardSizeX) return false;
		if(boardSizeY != other.boardSizeY) return false;
		
		for(int i=0;i<boardSizeX;i++) {
			for(int j=0;j<boardSizeY;j++){
				if(cell(i,j)!=other.cell(i,j)) return false;
			}	
		}
		return true;
	}
	
	public void writeToFile(String fileName) throws IOException{
		/**Takes a filename as an input, and writes the puzzle.
		 * @param string filename for file name.*/
		
	    PrintWriter writer = new PrintWriter(new FileWriter(fileName));
	    
		int i,j;

		//basic nested loop to convert puzzle to a .txt file.
		for( i=0 ; i< boardSizeX ; i++){
			for ( j=0 ; j< boardSizeY ; j++){
				if(cell(i,j)==-1){
					writer.printf("bb");
				}
				else{
					if(cell(i,j) < 10 && cell(i,j) > -1) writer.printf("0");
					writer.print(cell(i,j));
					writer.printf(" ");
				}
			}
			writer.write("\n");
		}

		System.out.println("Written!");
	    writer.close();
	}
	
	public String toString() {
		
		for(int i=0; i< boardSizeX ; i++) {
			for(int j=0; j< boardSizeY ; j++) {
				if(cell(i,j)<10 && cell(i,j) > -1) System.out.printf("0");
				if(cell(i,j) !=-1) System.out.printf("%d ",cell(i,j));
				else System.out.printf("   ");
			}
			System.out.printf("\n");
		}
		return "Last move = " + lastMove + " ,Number of moves = " + moveCount;
	}
	
	public boolean isSolved() {
		
		int i,j;

		//Checks the game is finished or not.
		for(i=0;i<boardSizeX;i++){
			for(j=0;j<boardSizeY;j++){	

				if(cell(i,j)!=i*boardSizeX+j+1){
									
					if(cell(i,j)==-1 && i == boardSizeX-1 && j== boardSizeY-1) return true;
					else return false;
				}
			}
		}
		return true;
	}
	
	public static int NumberOfBoards() {
		return count;
	}
	
	public char lastMove() {
		return lastMove;
	}
	
	public int numberOfMoves() {
		return moveCount;
	}
	
}
