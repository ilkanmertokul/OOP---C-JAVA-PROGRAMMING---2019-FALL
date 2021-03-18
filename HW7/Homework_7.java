package homework_7;
/**
 * @author İLKAN MERT OKUL
 * Welcome to homework 7. This homework done by İLKAN MERT OKUL, 1801042649*/

import java.io.IOException;
import java.util.Scanner; //uses scanners.

public class Homework_7 {

	public static boolean isPossible(AbstractBoard []array) {
		/** isPossible method for homework. It takes an
		 * array to control if it is possible, then returns
		 * boolean. It also controls if the board is solved.
		 * @param Abstractboard array[]
		 * @return boolean according to result.*/
		
		int i = 0;
		AbstractBoard copy; // This is a for copying the next array's object
		
		while(array[i+1]!=null) {
			
			copy = array[i+1];
			copy.move(array[i+1].lastMove());	
			if(!array[i].Equals(copy)) return false;
			else i++;
		}
		
		if(array[i].isSolved()) return true; // return true if solved, else false.
		else return false;
	}
	
	public static void main(String[] args) throws IOException {
			
		/** Main method, it has a menu for everything.
		 * @param string args
		 * @return void.*/
		
		int choice = 0;
		int count = 0;
		
		System.out.println("Welcome to -Homework 7-\n");
		Scanner input = new Scanner(System.in);
		
		AbstractBoard [] array = new AbstractBoard[10];
		array[count] = new BoardArray2D();
		System.out.println("By default, we set the size by 4 x 4.\n");
		array[count].setSize(4,4);
		
		while(choice !=- 1) {
			
			System.out.printf("%s\n",array[count].toString());
			/*MAIN MENU*/
			System.out.println("1- Add a new board to array.");
			System.out.println("2- Use file methods.");
			System.out.println("3- Use move methods.");
			System.out.println("4- Print report of the board.");
			System.out.println("5- Quit.\n");
			
			choice = input.nextInt();
			
			if(choice==1 && count>=9) {
				System.out.println("Max board limit reached.");
				choice = -2;
			}
			
			switch(choice) {
			case 1:
				
				/*Menu for creating new objects.*/
				System.out.println("What type of class do you want to create?");
				System.out.println("1 -1D array.");
				System.out.println("2- 2D array.");
				
				choice = input.nextInt();
				
				switch(choice) {
				case 1:
					count ++;
					array[count] = new BoardArray1D();
					break;
				case 2:
					count ++;
					array[count] = new BoardArray2D();
					break;
				default:
					System.out.println("Wrong input!");
				}
				
				do {
					System.out.println("Enter a size between 3 and 9");
					choice = input.nextInt();
					if(choice<3 || choice>10) System.out.println("You entered a wrong value, try again.");
				}while(choice<3 || choice>10);
				array[count].setSize(choice,choice);
				
				break;
				
			case 2:
				
				/*Menu for file methods.*/
				System.out.println("1- Write to a file.");
				System.out.println("2- Read from a file.");			
				
				choice = input.nextInt();
				
				switch(choice) {
				case 1:
					System.out.println("Enter a filename");
					String name = input.next();
					
					array[count].writeToFile(name);
					break;
					
				case 2:	
					//array[count].readFromFile("test.txt");
					break;
					
				default:
					System.out.println("You entered a wrong value.");
				}
				break;
				
			case 3:
				
				/*Menu for Moving, increases move count by 1, if possible.*/
				System.out.println("8- Move up.");
				System.out.println("2- Move down.");
				System.out.println("4- Move left.");
				System.out.println("6- Move right.\n");
				
				choice = input.nextInt();
				
				if(!array[count].move(choice)) System.out.println("Could not move here!");
				break;
				
			case 4:
				
				System.out.printf("Number of moves = %d , Last Move = %c , Number of boards that created = %d \n",
						array[count].numberOfMoves(),array[count].lastMove(),AbstractBoard.NumberOfBoards());
				
				break;
			
			case 5:
				System.out.println("Exiting.");
				choice = -1;
				break;
				
			default:
				System.out.println("Wrong value.");
			}// end of switch case
			
			if(array[count].isSolved()) {
				System.out.printf("HEY YOU WON!! \n\n");
				choice = -1;
			}	
		}// end of while loop
		input.close();
	}// end of main
}// end of Homework_7