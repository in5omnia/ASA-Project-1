#include <iostream>
using namespace std;

int recursion(int *rows, int row, int col, int n, int m, int square_side);

int * readInput(){
	int * rows;
	int n_rows, m_cols, c;
	cin >> n_rows >> m_cols;
	rows = new int[n_rows];
	for (int row = 0; row < n_rows; row++){
		cin >> c;
		rows[row] = c;
	}
	return rows;
}



int ex1(int n, int m, int *rows){	// n rows, m cols

	int squares=0, count;
	for (int row=0; row<n; row++) {	// avaliar cada row
		for (int col=0; col<m; col++){	//ver na same row, o square na coluna seguinte
			for (int i=2; i<=n && i<=m; i++) {	//check all square sizes possible for the grid
				count = recursion(rows, row, col, n, m, i);
				squares += count;
				if (count==0)	//se nao cabe um 2x2, nao cabe um 3x3 and so on
					break;
			}
		}
	}
	return squares;
}

int recursion(int *rows, int row, int col, int n, int m, int square_side){
	if ((rows[row] - (col-1)) <square_side)	// nao há espaço nas colunas desta row à frente do ladrilho a avaliar
		return 0;
	if (col > rows[row])
		return 0;
	//else
	if ((row + square_side - 1) <= n && rows[row + square_side - 1] >= square_side)	//há espaço nas rows seguintes
		return 1;
	return 0;
}

int ex1_teste(){	// n rows, m cols

	int * rows;
	int n, m, c;
	cin >> n >> m;
	rows = new int[n];
	for (int row = 0; row < n; row++){
		cin >> c;
		rows[row] = c;
	}

	int squares=0, count;
	for (int row=0; row<n; row++) {	// avaliar cada row
		for (int col=1; col<=rows[row]; col++){	//ver na same row, o square na coluna seguinte
			//squares += 1;
			int temp=0;
			for (int i=2; i<=n && i<=m; i++) {	//check all square sizes possible for the grid
				count = recursion(rows, row, col, n, m, i);
				temp += count;
				if (count==0)	//se nao cabe um 2x2, nao cabe um 3x3 and so on
					break;
			}
			if (temp!=0) {
				temp +=1;	//
				squares += temp;
			}
			cout << temp << " - ";
		}
		cout << endl;
	}
	return squares + 1;	// +1 quando sao todos 1x1?
}


int main()
{
	cout << (ex1_teste());
	return 0;
}