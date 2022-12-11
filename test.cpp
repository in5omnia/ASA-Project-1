//
// Created by Beatriz Gavilan on 10/12/2022.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

size_t vectorHash(const vector<unsigned int> &vec) {
	size_t seed = vec.size();
	for (auto x: vec) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}



struct vectorHasher {
	size_t operator()(size_t const &hash) const {

		return hash;
	}
};


void printFigure(vector<unsigned int> *figure, unsigned int size) {
	cout << endl << "-------------" << endl;
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < figure->at(i); j++) {
			cout << "X";
		}
		cout << endl;
	}
	cout << "-------------" << endl << endl;
}

vector<unsigned int> readInput() {
	unsigned int n_rows, m_cols, col;

	cin >> n_rows >> m_cols;

	vector<unsigned int> figure;
	for (unsigned int row = 0; row < n_rows; row++) {
		cin >> col;

		// TODO: Ignore 1s if they are not in the last row
		if (col == 0)
			continue;
		else {
			figure.push_back(col);
		}
	}
	return figure;
}

// TODO NAO USAR FUCKING POINTER ALL HAIL DM
vector<unsigned int>
removeSquares(const vector<unsigned int> &figure, unsigned int square_side, unsigned int square_index,
			  unsigned int size) {


	if (square_index == 0 && figure[0] == square_side) {
		// if it's the first "square" and it's going to be empty
		// it shouldn't show up, it's possible that there are empty squares in the following lines
		unsigned int size_of_new_figure = size - square_side;
		vector<unsigned int> newFigure(size_of_new_figure);
		int non_empty_cols = 0;
		for (unsigned int i = square_side; i < size; i++) {
			unsigned int newCol = figure[i];
			if (non_empty_cols || newCol) {
				newFigure[non_empty_cols] = newCol;
				non_empty_cols++;
			}
		}
		newFigure.resize(non_empty_cols);
		return newFigure;
	}

	if (square_index + square_side == size && figure[size - 1] == square_side) { // last square
		vector<unsigned int> newFigure(square_index);

		int non_empty_cols = 0;
		for (short int i = square_index - 1; i >= 0; i--) {
			unsigned int newCol = figure[i];
			if (non_empty_cols || newCol) {
				newFigure[i] = newCol;
				non_empty_cols++;
			}
		}

		newFigure.resize(non_empty_cols);

		return newFigure;

	}
	// normal case
	vector<unsigned int> newFigure(size);
	unsigned int i;
	for (i = 0; i < square_index; i++) {
		newFigure[i] = figure[i];
	}
	unsigned int newCol = figure.at(i) - square_side;
	for (; i < square_index + square_side; i++) {
		newFigure[i] = newCol;
	}
	for (; i < size; i++) {
		newFigure[i] = figure[i];
	}


	return newFigure;
}


unsigned int *
findMaxRemovableSquare(const vector<unsigned int> &figure, unsigned int size) {

	unsigned int max_index = 0;
	unsigned int max_height = 0;
	unsigned int max_length = 0;
	unsigned int prev = 0;
	bool contig = false;

	for (unsigned int i = 0; i < size; i++) {


		unsigned int current = figure.at(i);

		if (contig && current != prev)
			contig = false;

		if (current > max_length) {
			max_index = i;
			max_height = 1;
			max_length = current;
			contig = true;
			// FIXME ASAP
		} else if (contig && max_height < current) {
			// compares the height of the new possible square to the length of the current line
			max_height++;
		}

		prev = current;

	}

	unsigned int *output;
	output = static_cast<unsigned int*> (malloc(sizeof(unsigned int) * 3));
	output[0] = max_height;
	output[1] = max_index;
	output[3] = max_length;

	return output;
}





// Only calculates the number of possibilities for a square of size 2+
unsigned long long
calculateTilings(vector<unsigned int> figure, unordered_map<size_t, unsigned long long, vectorHasher> *cache) {
	unsigned int size = figure.size();


	if (size <= 1)    //FIXME perhaps include columns of 1
		return 1;

	size_t hash = vectorHash(figure);
	// Check if the figure is already in the cache
	auto it = cache->find(hash);
	if (it != cache->end()) {
		//printFigure(&figure, size);    //debug
		//cout << "size:" << size << endl; //debug
		//printf("cached - Tilings: %llu\n", it->second);    //debug
		return it->second;
	}

	unsigned long long tilings = 0;
	// Calculate the biggest square that can be removed
	unsigned int *maxArray = findMaxRemovableSquare(figure, size);
	unsigned int maxRemovableSquare = maxArray[0];
	unsigned int maxSquareIndex = maxArray[1];
	unsigned int maxSquareLength = maxArray[2];
	free(maxArray);

	if (maxSquareLength == 1)
		return 1;


	//tilings += maxRemovableSquare - 1;
	for (unsigned int i = 1; i <= maxRemovableSquare; i++) {
		// Calculate the figure without the square
		vector<unsigned int> newFigure = removeSquares(figure, i, maxSquareIndex, size);
		tilings += calculateTilings(newFigure, cache);
	}

	// Add the figure to the cache
	cache->insert({vectorHash(figure), tilings});
	//printFigure(&figure, size);    //debug
	//cout << "size:" << size << endl; //debug
	//printf("Max Square to remove: %d x %d\nTilings: %llu\n", maxRemovableSquare, maxRemovableSquare,
	//	   tilings);    //debug

	return tilings;


}


int main() {
	ios::sync_with_stdio(false);
	vector<unsigned int> figure = readInput();

	if (figure.empty())
		cout << 0 << endl;
	else {

		static auto cache = new unordered_map<size_t, unsigned long long, vectorHasher>();

		cout << calculateTilings(figure, cache) << endl;
	}


	return 0;
}




