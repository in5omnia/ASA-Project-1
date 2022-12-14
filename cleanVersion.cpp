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

size_t vectorHash(const vector<unsigned short int> &vec) {
	size_t seed = vec.size();
	/*for (auto x: vec) {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}*/
	for (auto x: vec) {
		x = ((x * 0xcc9e2d51) << 15);
		x = ((x * 0x1b873593) << 15);
		seed = ((seed ^ x) << 13) * (0x5) + 0xe6546b64;
		//seed = seed ^ size;
	}
	return seed;
}


struct vectorHasher {
	size_t operator()(size_t const &hash) const {
		return hash;
	}
};


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
		// if it's the first "square" and it's going to be empty
		// it shouldn't show up, it's possible that there are empty squares in the following lines
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

	if (square_index + square_side == size && figure[size - 1] == square_side) { // last square
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


unsigned short int *
findMaxRemovableSquare(const vector<unsigned short int> &figure, unsigned short int size) {

	unsigned short int max_index = 0;
	unsigned short int max_height = 0;
	unsigned short int max_length = 0;
	unsigned short int prev = 0;
	bool contig = false;

	for (unsigned short int i = 0; i < size; i++) {

		unsigned short int current = figure.at(i);

		if (current < prev) {
			unsigned short int *output;
			output = static_cast<unsigned short *> (malloc(sizeof(unsigned short int) * 3));
			output[0] = max_height;
			output[1] = max_index;
			output[3] = max_length;

			return output;
		}

		if (contig && current != prev)
			contig = false;

		if (current > max_length) {
			max_index = i;
			max_height = 1;
			max_length = current;
			contig = true;

		} else if (contig && max_height < current) {
			// compares the height of the new possible square to the length of the current line
			max_height++;
		}
		prev = current;
	}

	unsigned short int *output;
	output = static_cast<unsigned short *> (malloc(sizeof(unsigned short int) * 3));
	output[0] = max_height;
	output[1] = max_index;
	output[3] = max_length;

	return output;
}



// Calculates the number of possibilities for a figure to be filled with squares
unsigned long long
calculateTilings(vector<unsigned short int> figure, unordered_map<size_t, unsigned long long, vectorHasher> *cache) {
	unsigned short int size = figure.size();


	if (size <= 1) {
		return 1;
	}

	// Check if the figure is already in the cache
	auto it = cache->find(vectorHash(figure));
	if (it != cache->end()) {
		return it->second;
	}

	unsigned long long tilings = 0;
	// Calculate the biggest square that can be removed
	unsigned short int *maxArray = findMaxRemovableSquare(figure, size);
	unsigned short int maxRemovableSquare = maxArray[0];
	unsigned short int maxSquareIndex = maxArray[1];
	unsigned short int maxSquareLength = maxArray[2];
	free(maxArray);

	if (maxSquareLength == 1)
		return 1;


	for (unsigned short int i = 1; i <= maxRemovableSquare; i++) {
		// Calculate the figure without the square
		vector<unsigned short int> newFigure = removeSquares(figure, i, maxSquareIndex, size);
		tilings += calculateTilings(newFigure, cache);
	}

	// Add the figure to the cache
	cache->insert({vectorHash(figure), tilings});
	return tilings;

}


int main() {
	ios::sync_with_stdio(false);
	vector<unsigned short int> figure = readInput();

	if (figure.empty())
		cout << 0 << endl;
	else {
		// Creates map to store the results of the calculations
		static auto cache = new unordered_map<size_t, unsigned long long, vectorHasher>();

		cout << calculateTilings(figure, cache) << endl;
	}

	return 0;
}



