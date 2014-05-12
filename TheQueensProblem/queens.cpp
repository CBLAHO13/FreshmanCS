/*
Dueling Divas -- A Fresh Twist on N-Queens
CS 175, Winter 2014
Copyright no one, because this problem has been beaten to death 
	twice over four times eight. 

This code provided by Colleen Blaho in 2014.

*/



#include <vector>
#include <iostream>
#include "Grid.h"
using namespace std;

bool placeDivas(Grid& board, int row){ 
    for(int i=0; i<board.getGrid().size(); i++) {
		if(board.safeSpot(row,i)) {
            board.setSpace(row,i,row + 1);
			//cout << board << endl <<endl;
			if (row == board.getGrid().size()-1)
				return true;
            //Is this the last row? If so, we suceeded	
            if (row<board.getGrid().size()-1) {
				 if (!placeDivas(board,row+1)){
					board.setSpace(row, i, -1);
					continue;
				}
			}
				//if we get here, then the problem is solved
            else{ //Failed, try a different row
					board.setSpace(row,i, -1);
					continue;
				}
			return true;
			//cout << board << endl <<endl;
		}	
    }
    return false; 
	//If we got here, then we ran out of columns. Return failure and
	//bounce up the stack to the section that clears our work and retries
}


int main(){
	bool execution = true;
	char ch;
	int side1;
	int side2;
	while(execution)
	{
		cout <<endl << "Please enter the sides of the square board." <<endl
			<< "For example, if you want a (4x4) board, enter (4,4)." <<endl <<
			endl << "To quit, type (0,0)." << endl <<
			"WARNING! For numbers over 15, execution will take a very long time!" <<endl;
		cin >> ch; //discard parens
		cin >> side1;
		cin >> ch; //discard comma
		cin >> side2;
		cin >> ch; //discard parens
		if (side1 > 0 && side2 > 0 && side1 < 100 && side2 < 100){
			//sorry super computer users, you'll have to edit the code
			Grid g(side1,side2);
			placeDivas(g,0);
			cout << g;
		}
		else if (side1 == 0 && side2 == 0){
			execution = false;
			
		}
		else
			cout << "Invalid response." << endl;
	}
	cout << "Program exiting." << endl;
	return 0;
}