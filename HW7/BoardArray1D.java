package homework_7;

public class BoardArray1D extends AbstractBoard{

	private int [] array; 
	
	BoardArray1D(){
		System.out.println("Creating a 1D board.");
	}
	
	public void setSize(int sizeX, int sizeY) {
		
		boardSizeX = sizeX;
		boardSizeY= sizeY;
		
		array = new int[boardSizeX*boardSizeY+1];
		reset();
		for(int i=0;i<100;i++) move(((int)(Math.random()*(4)+1)*2));
		
		moveCount=0;
		lastMove='S';
	}

	public void reset(){
		for(int i=0;i<boardSizeX;i++) {
			for(int j=0;j<boardSizeY;j++){
				array[i*boardSizeY+j+1]=i*boardSizeX+j+1;
			}	
		}
		c1=boardSizeX-1;
		c2=boardSizeY-1;
		
		array[c1*boardSizeY+c2+1]=-1; // -1 means blank tile, c1 and c2 holds blank tile.
	}
	
	public int cell(int x,int y) {
		return array[x*boardSizeY+y+1];
	}
	
	public boolean move(int m) {

		switch(m){
		case 8: // MOVES UP
			if(c1!=0 && cell(c1-1,c2)!=0) {
				array[c1*boardSizeY+c2+1]=cell(c1-1,c2);
				c1--;
				
				array[c1*boardSizeY+c2+1]=-1;
				lastMove='U';
				moveCount++;
			}
			else return false;
			break;
			
		case 4: // MOVES LEFT
			if(c2!=0 && cell(c1,c2-1)!=0) {
				array[c1*boardSizeY+c2+1]=cell(c1,c2-1);
				c2--;
				
				array[c1*boardSizeY+c2+1]=-1;
				lastMove='L';
				moveCount++;
			}
			else return false;
			break;
			
		case 2:	// MOVES DOWN
			if(c1!=boardSizeX-1 && cell(c1+1,c2)!=0) {
				array[c1*boardSizeY+c2+1]=cell(c1+1,c2);
				c1++;
				
				array[c1*boardSizeY+c2+1]=-1;
				lastMove='D';
				moveCount++;
			}
			else return false;
			break;
			
		case 6: // MOVES RIGHT
			if(c2!=boardSizeY-1 && cell(c1,c2+1)!=0) {
				array[c1*boardSizeY+c2+1]=cell(c1,c2+1);
				c2++;
				
				array[c1*boardSizeY+c2+1]=-1;
				lastMove='R';
				moveCount++;
			}
			else return false;
			break;
			
		default:
			System.out.println("You entered a wrong value.");
			return false;
		}	
		
		return true;
	}// end of move() 
		
} // end of class;