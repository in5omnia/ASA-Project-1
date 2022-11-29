#include <iostream>
using namespace std;

int main()
{
	return 0;
}

int ** readInput(){
	int ** matrix;
	int n_rows, n_cols, c, col;
	cin >> n_rows >> n_cols;
	matrix = new int*[n_rows];
	for (int row = 0; row < n_rows; row++){
		matrix[row] = new int[n_cols];
		cin >> c;
		for (col = 0; col < c; col++)
			matrix[row][col] = 1;
		while(col < n_cols){
			col++;	//OU ++COL?
			matrix[row][col] = 0;
		}
	}
	return matrix;
}