//
// Created by Beatriz Gavilan on 10/12/2022. - last code with arrays
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

size_t arrayHash(unsigned short int *vec, unsigned short int size){
	size_t seed = sizeof (unsigned short) * size;
	for (unsigned short i = 0; i<size; i++) {
		unsigned short int x = vec[i];
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

struct vectorHasher {
	std::size_t operator()(std::vector<ushort> const &vec) const {
		std::size_t seed = vec.size();
		for (auto x: vec) {
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = (x >> 16) ^ x;
			seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};


void printFigure(unsigned short int *figure, unsigned short int size) {
	cout << endl << "-------------" << endl;
	for (unsigned short int i = 0; i < size; i++) {
		for (unsigned short int j = 0; j < figure[i]; j++) {
			cout << "X";
		}
		cout << endl;
	}
	cout << "-------------" << endl << endl;
}

pair<unsigned short int *, unsigned short int> readInput() {
	unsigned short int n_rows, m_cols, col;

	cin >> n_rows >> m_cols;

	int i = 0;
	auto *figure = new unsigned short int[n_rows];
	for (unsigned short int row = 0; row < n_rows; row++) {
		cin >> col;

		// TODO: Ignore 1s if they are not in the last row
		if (col == 0) {
			continue;
		}
		else {
			figure[i] = col;
			i++;
		}
	}
	figure = (unsigned short *) realloc(figure, i * sizeof(unsigned short int));
	return {figure, i};
}

// TODO NAO USAR FUCKING POINTER ALL HAIL DM
pair<unsigned short int*, unsigned short int>
removeSquares(unsigned short int* figure, unsigned short int square_side, unsigned short int square_index,
			  unsigned short int size) {

	// FIXME Pode surgir 0s


	if (square_index == 0 && figure[0] == square_side) {
		// if it's the first "square" and it's going to be empty
		// it shouldn't show up, it's possible that there are empty squares in the following lines
		unsigned short int *newFigure;
		newFigure = (unsigned short int *) malloc((size - square_side) * sizeof(unsigned short int));

		unsigned short a = 0;
		bool empty = true;
		for (unsigned short int i = square_side; i < size; i++) {
			cout << "mimi: " << i << endl;
			unsigned short int newCol = figure[i];
			if (!empty || newCol) {
				newFigure[a] = figure[i];
				a++;
				empty = false;
			}
		}
		newFigure = (unsigned short *) realloc(newFigure, a * sizeof(unsigned short));
		return {newFigure, a};
	}
	if (square_index + square_side == size && figure[size - 1] == square_side) { // last square
		unsigned short int *newFigure;
		newFigure = (unsigned short int *) malloc((square_index) * sizeof(unsigned short int));

		bool empty = true;
		unsigned short int numEmptyLines = 0;
		for (short int i = square_index - 1; i >= 0; i--) {
			cout << "meme: " << i << endl;
			unsigned short int newCol = figure[i];
			if (!empty || newCol) {
				newFigure[i] = figure[i];
				empty = false;
			} else {
				numEmptyLines++;
			}
		}
		unsigned short int newSize = square_index - numEmptyLines;
		newFigure = (unsigned short *) realloc(newFigure, (newSize) * sizeof(unsigned short));

		return {newFigure, newSize};
	}

	// normal case
	unsigned short int *newFigure;
	newFigure = (unsigned short int *) malloc((size) * sizeof(unsigned short int));
	unsigned short int i;
	for (i = 0; i < square_index; i++) {
		newFigure[i] = figure[i];
	}
	unsigned short int newCol = figure[i] - square_side;
	for (; i < square_index + square_side; i++) {
		newFigure[i] = newCol;
	}
	for (; i < size; i++) {
		newFigure[i] = figure[i];
	}


	return {newFigure, size};
}


pair<unsigned short int, unsigned short int>
findMaxRemovableSquare(const unsigned short int *figure, unsigned short int size) {

	unsigned short int max_index = 0;
	unsigned short int max_height = 0;
	unsigned short int max_length = 0;
	unsigned short int prev = 0;
	bool contig = false;

	for (unsigned short int i = 0; i < size; i++) {


		unsigned short int current = figure[i];

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

	return {max_height, max_index};
}


/*int upperRightLine = size - 1;
for (
int i = upperRightLine - 1;
i >= 0; i--) {    //find longest line
if (figure[i] < figure[upperRightLine])
break;
upperRightLine = i;
}
return
min(figure[upperRightLine], size
- upperRightLine + 1);
}*/


// Only calculates the number of possibilities for a square of size 2+
unsigned long long calculateTilings(unsigned short int *figure, unsigned short int size,
									unordered_map<size_t, unsigned long long> *cache) {


	if (size <= 1) {    //FIXME perhaps include columns of 1
		//printFigure(figure, size);    //debug
		//cout << "size:" << size << endl;	//debug
		//printf("0/1 Figure - Tilings: %llu\n", 1);    //debug
		return 1;
	}

	// Check if the figure is already in the cache
	size_t hash = arrayHash(figure, size);
	auto it = cache->find(hash);
	if (it != cache->end()) {
		//printFigure(figure, size);    //debug
		//cout << "size:" << size << endl; //debug
		//printf("cached - Tilings: %llu\n", it->second);    //debug
		return it->second;
	}

	unsigned long long tilings = 0;
	// Calculate the biggest square that can be removed
	auto maxPair = findMaxRemovableSquare(figure, size);
	unsigned short int maxRemovableSquare = maxPair.first;
	unsigned short int maxSquareIndex = maxPair.second;

	//tilings += maxRemovableSquare - 1;
	for (unsigned short int i = 1; i <= maxRemovableSquare; i++) {
		// Calculate the figure without the square
		auto figurePair = removeSquares(figure, i, maxSquareIndex, size);
		unsigned short int *newFigure = figurePair.first;
		unsigned short int newSize = figurePair.second;

		tilings += calculateTilings(newFigure, newSize, cache);

		free(newFigure);
	}

	// Add the figure to the cache
	cache->insert({hash, tilings});
	//printFigure(figure, size);    //debug
	//cout << "size:" << size << endl; //debug
	//printf("Max Square to remove: %d x %d\nTilings: %llu\n", maxRemovableSquare, maxRemovableSquare,
	//	   tilings);    //debug

	return tilings;


}


int main() {
	ios::sync_with_stdio(false);
	unsigned short int *figure;
	unsigned short int figure_size;
	pair<unsigned short int *, unsigned short int> input = readInput();
	figure = input.first;
	figure_size = input.second;

	if (!figure_size)
		cout << 0 << endl;
	else {

		auto cache = new unordered_map<size_t, unsigned long long>();

		cout << calculateTilings(figure, figure_size, cache) << endl;
	}

	free(figure);

	return 0;
}




