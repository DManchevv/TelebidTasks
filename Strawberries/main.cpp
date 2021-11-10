#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

// Creating node struct
struct Node {
	int data;
	int X;
	int Y;
	Node* next;
};

// Implementing Queue
class Queue {
	Node* head;
	Node* tail;
public:
	Queue() {
		head = NULL;
		tail = NULL;
	}

	void push_back(int value, int coordx, int coordy);
	void pop_front();
	void print();
	Node* getHead();
};

Node* Queue::getHead() {
	return head;
}

// Add element to the queue 
void Queue::push_back(int value, int coordx, int coordy) {
	// Create new node with the given values
	Node* tmp = new Node;
	tmp->data = value;
	tmp->X = coordx;
	tmp->Y = coordy;
	tmp->next = NULL;

	// If this is the first element assign it to the head and tail pointers
	if (head == NULL) {
		head = tmp;
		tail = tmp;
	}
	// If it's not the first element add it to the tail of the queue
	else {
		tail->next = tmp;
		tail = tmp;
	}
}

void Queue::pop_front() {
	// If there are no elements, return
	if (head == NULL) {
		return;
	}

	// Remove the first element of the queue
	head = head->next;
}

// TEST PRINT FUNCTION
void Queue::print() {
	Node* tmp = new Node;
	tmp = head;

	while (tmp != NULL) {
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}

// Check if we can rot the strawberry which is up from our current position
bool up(int** &matrix, int x, int y, int day, int N, int M) {
	if (x - 1 >= 0 and y < M and y >= 0 and x < N) {
		if (matrix[x - 1][y] == -1) {
			matrix[x - 1][y] = day;
			return true;
		}
	}
	return false;
}

// Same as up function
bool left(int** &matrix, int x, int y, int day, int N, int M) {
	if (y - 1 >= 0 and y < M and x >= 0 and x < N) {
		if (matrix[x][y - 1] == -1) {
			matrix[x][y - 1] = day;
			return true;
		}
	}
	return false;
}

bool right(int** &matrix, int x, int y, int day, int N, int M) {
	if (y + 1 < M and y >= 0 and x >= 0 and x < N) {
		if (matrix[x][y + 1] == -1) {
			matrix[x][y + 1] = day;
			return true;
		}
	}
	return false;
}

bool down(int** &matrix, int x, int y, int day, int N, int M) {
	if (x + 1 < N and x >= 0 and y < M and y >= 0) {
		if (matrix[x + 1][y] == -1) {
			matrix[x + 1][y] = day;
			return true;
		}
	}
	return false;
}

void printMatrix(int** matrix, int N, int M, std::ofstream& file) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			file << matrix[i][j] << " ";
		}
		file << std::endl;
	}
}

int main() {
	int K, L, R;
	std::cin >> K >> L >> R;

	// Creating file
	std::ofstream myfile;
	myfile.open("output.txt");
	myfile << K << " " << L << "\n";
	// Create matrix
	int** matrix = new int*[K];

	// Starting state of the matrix, all strawberries are considered healthy
	// Healthy strawberry has -1 value
	for (size_t i = 0; i < K; i++) {
		matrix[i] = new int[L];
		for (size_t j = 0; j < L; j++) {
			matrix[i][j] = -1;
		}
	}

	int coordx, coordy;
	int dayCounter = 0;
	int destroyed = 0;

	Queue que;

	// Enter 1 or 2 strawberries
	while (std::cin >> coordx >> coordy) {
		que.push_back(dayCounter, coordx - 1, coordy - 1);
		destroyed++;
	}

	Node* tmp = new Node;
	tmp = que.getHead();

	// Set the positions of the first rotten strawberry in the matrix
	// Rotten strawberries has the day of its rot as its value
	matrix[tmp->X][tmp->Y] = dayCounter;

	// If second rotten strawberry was entered, set its position too
	if (tmp->next != NULL) {
		matrix[tmp->next->X][tmp->next->Y] = dayCounter;
	}

	dayCounter++;

	// Iterate until the R-th day
	for (; dayCounter <= R; dayCounter++) {
		tmp = que.getHead();

		// If there are no new rotten strawberies or everything is destroyed -> end
		if (tmp == NULL or destroyed >= K * L) {
			break;
		}
		else {
			// Iterate while the rotten strawberries in the queue are from the last day
			while (tmp->data == dayCounter - 1) {
				// If we can rot strawberry which is 1 position up from ours, rot it.
				if (up(matrix, tmp->X, tmp->Y, dayCounter, K, L)) {
					que.push_back(dayCounter, tmp->X - 1, tmp->Y);
					destroyed++;
				}

				if (left(matrix, tmp->X, tmp->Y, dayCounter, K, L)) {
					que.push_back(dayCounter, tmp->X, tmp->Y - 1);
					destroyed++;
				}

				if (right(matrix, tmp->X, tmp->Y, dayCounter, K, L)) {
					que.push_back(dayCounter, tmp->X, tmp->Y + 1);
					destroyed++;
				}

				if (down(matrix, tmp->X, tmp->Y, dayCounter, K, L)) {
					que.push_back(dayCounter, tmp->X + 1, tmp->Y);
					destroyed++;
				}

				// Go to next one
				tmp = tmp->next;
				// Pop the current one
				que.pop_front();
			}
		}
	}

	int answer = 0;

	// Check which strawberries are healthy.
	for (size_t i = 0; i < K; i++) {
		for (size_t j = 0; j < L; j++) {
			if (matrix[i][j] == -1) {
				answer++;
			}
		}
	}

	printMatrix(matrix, K, L, myfile);

	// Print the result
	std::cout << answer << std::endl;
	return 0;
}
