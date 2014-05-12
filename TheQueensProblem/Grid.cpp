#include "Grid.h"
#include <vector>
#include <iostream>
#include "assert.h"
using namespace std;




	Grid::Grid(){
		//create a 1x1 grid -- the smallest possible grid that places
		//one queen. Problem solved before we begin. 
		//DO NOT USE FOR IMPLEMENTATION: This is for testing only.
		Grid(1,1);
		
	}
	Grid::Grid(int row, int col){
		if (row > col){
			int temp = col;
			col = row;
			row = temp;
		}
		for (int i = 0; i < col-1; i++)
		{
			vector<int> rowVector(col, -1);
			grid_.assign(row, rowVector);
		}
	}
	bool Grid::safeSpot(int row, int col){
		if (grid_[row][col] != -1)
			//checks for a diva in that space
				return false;
		else {
			//diagonal checks and row checks
			for (int i = 1; i < grid_.size(); i++){
				if (row - i >=0){
					if (grid_[row-i][col] != -1)
						return false;
					if (col - i >=0){
						if (grid_[row-i][col -i] != -1)
							return false;
						
					}
					
				if (col + i < grid_.size()){
						if (grid_[row-i][col +i] != -1)
							return false;
					}
				}
				else 
					if (col - i >=0){
						if (grid_[row][col -i] != -1)
							return false;
						}
					if (col + i < grid_.size()){
						if (grid_[row][col + i] != -1)
							return false;
					}
					//what is below me is not important because there are no queens there. 
			
			}//if you get to here without short circuiting, then it must be valid
			return true;
		}
	}
	bool Grid::setSpace(int row, int col, int value)
	{
		/*bool queenPlacementOkay;
		if (value > 0) //placing a queen
		{
			queenPlacementOkay = safeSpot(row,col);
			//can we place the queen?
			if (queenPlacementOkay){
				return false;
				//couldn't do it!
			}
			else 
			{
				grid_[row][col] = value;
			return true;
			}
		}
		else //not placing a queen
			if (!(grid_[row][col] > 0)){
				//queen is there already, do not overwrite
				*/
				grid_[row][col] = value;
				
				return true;
			
			
	}
	vector< vector<int> > Grid::getGrid()
	{
		return grid_;
	}

	ostream &operator<<(ostream&out, Grid& g)
{
	//basic two array traversing, prints values with three spaces inbetween
	
	for (unsigned int i = 0; i < g.getGrid().size(); i++)
	{
		for (unsigned int j = 0; j < (g.getGrid())[i].size(); j++)
		{
			if(((g.getGrid())[i][j]) > 0)
				out << (g.getGrid())[i][j] << " ";
			else 
				out << ". ";
		}
		out << endl; //EOL output
	}
	return out;
}