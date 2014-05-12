#ifndef ___GRID___
#define ___GRID___
#include <vector>
#include <iostream>
using namespace std;

class Grid
{

public:
	Grid();
	Grid(int row, int col);
	bool safeSpot(int row, int col);
	bool setSpace( int row, int col, int value);
	
	vector< vector<int> > getGrid();
private:
	//put a space so the compiler doesn't think there's an
	//assignment operator and have a mental breakdown
	vector< vector<int> > grid_; 
	
};

ostream &operator<<(ostream&out, Grid& g);


#endif