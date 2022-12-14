/*
  									Projeto 1 de ASA
  	Determinação do número de configurações distintas com que se pode ladrilhar a área de uma figura

								       14/12/2022
  								Beatriz Gavilan - 102463
  								Eduardo Nazário - 102415
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function that hashes a vector through the use of a string
size_t vectorHash(const vector<unsigned short int> &vec) {
	//Concatenate the vector into a string
	string s;
	for (auto x: vec) {
		s += to_string(x);
	}
	return hash<string>{}(s);
}

// Don't Hash the Key (It's already a hash)
struct keyHash {
	size_t operator()(size_t const &hash) const {
		return hash;
	}
};

// Reads the input
vector<unsigned short int> readInput() {
	unsigned short int n_rows, m_cols, col;

	cin >> n_rows >> m_cols;

	vector<unsigned short int> figure;
	for (unsigned short int row = 0; row < n_rows; row++) {
		cin >> col;

		if (col == 0)
			continue;
		else {
			figure.push_back(col);
		}
	}
	return figure;
}


vector<unsigned short int>
removeSquares(const vector<unsigned short int> &figure, unsigned short int square_side, unsigned short int square_index,
			  unsigned short int size) {

	if (square_index == 0 && figure[0] == square_side) {
		// First Lines equals 0? if so remove any empty squares at the start
		unsigned short size_of_new_figure = size - square_side;
		vector<unsigned short int> newFigure(size_of_new_figure);
		int non_empty_cols = 0;
		for (unsigned short int i = square_side; i < size; i++) {
			unsigned short int newCol = figure[i];
			if (non_empty_cols || newCol) {
				newFigure[non_empty_cols] = newCol;
				non_empty_cols++;
			}
		}
		newFigure.resize(non_empty_cols);
		return newFigure;
	}

	if (square_index + square_side == size && figure[size - 1] == square_side) {
		// Last line equals 0? if so remove any empty squares at the end
		vector<unsigned short int> newFigure(square_index);

		int non_empty_cols = 0;
		for (short int i = square_index - 1; i >= 0; i--) {
			unsigned short int newCol = figure[i];
			if (non_empty_cols || newCol) {
				newFigure[i] = newCol;
				non_empty_cols++;
			}
		}
		newFigure.resize(non_empty_cols);
		return newFigure;
	}

	// normal case
	vector<unsigned short int> newFigure(size);
	unsigned short int i;
	for (i = 0; i < square_index; i++) {
		newFigure[i] = figure[i];
	}
	unsigned short int newCol = figure.at(i) - square_side;
	for (; i < square_index + square_side; i++) {
		newFigure[i] = newCol;
	}
	for (; i < size; i++) {
		newFigure[i] = figure[i];
	}
	return newFigure;
}

// Returns the pair of the locally optimal square to remove
pair<unsigned short, unsigned short>
findMaxRemovableSquare(const vector<unsigned short int> &figure, unsigned short int size) {

	unsigned short int max_index = 0;
	unsigned short int max_height = 0;
	unsigned short int max_length = 0;
	unsigned short int prev = 0;

	for (unsigned short int i = 0; i < size; i++) {

		unsigned short int current = figure[i];

		// Local Maximum
		if (current < prev)
			return {max_height, max_index};


		if (current > max_length) {
			max_index = i;
			max_height = 1;
			max_length = current;
		} else if (max_height < current) {
			// compares the height of the new possible square to the length of the current line
			max_height++;
		}
		prev = current;
	}


	return {max_height, max_index};
}


// Calculates the number of possibilities for a figure to be filled with squares
unsigned long long
calculateTilings(vector<unsigned short int> figure, unordered_map<size_t, unsigned long long, keyHash> *cache) {
	unsigned short int size = figure.size();

	// If there's only one line, there's only one way to fill it
	if (size <= 1)
		return 1;

	// Check if the figure is cached
	size_t hash = vectorHash(figure);
	auto it = cache->find(hash);
	if (it != cache->end()) {
		return it->second;
	}


	unsigned long long tilings = 0;
	// Calculate the biggest square that can be removed
	pair<unsigned short int, unsigned short int> maxPair = findMaxRemovableSquare(figure, size);
	unsigned short int maxRemovableSquare = maxPair.first;
	unsigned short int maxSquareIndex = maxPair.second;


	for (unsigned short int i = 1; i <= maxRemovableSquare; i++) {
		// Calculate the figure without the square
		vector<unsigned short int> newFigure = removeSquares(figure, i, maxSquareIndex, size);
		tilings += calculateTilings(newFigure, cache);
	}


	// Add figure to the cache
	cache->insert({hash, tilings});

	return tilings;

}


int main() {
	ios::sync_with_stdio(false);
	vector<unsigned short int> figure = readInput();

	if (figure.empty())
		cout << 0 << endl;
	else {
		// Creates map to store the results of the calculations
		static auto cache = new unordered_map<size_t, unsigned long long, keyHash>();

		cout << calculateTilings(figure, cache) << endl;
	}

	return 0;
}



