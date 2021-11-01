// The segments task with bad complexity -> O(n^2)

#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>

int main() {
	size_t N, a, b, c;
	
	std::cin >> N >> a >> b >> c;

	// Array that stores the points that George put
	int* first = new int[N / a];
	// Array that stores the point that Gergana put
	int* second = new int[N / b];

	for (size_t i = 0; i < N / a; i++) {
		first[i] = a * (i + 1);
	}

	for (size_t i = 0; i < N / b; i++) {
		second[i] = b * (i + 1);
	}

	size_t coloredPartStart = 0;
	size_t coloredPartEnd = 0;
	// Map that is storing the path of the colored part of the segment
	std::map<int, int> path;

	// Comparing each point of George to each point of Gergana
	for (size_t i = 0; i < N / a; i++) {
		for (size_t j = 0; j < N / b; j++) {
			// If we find a difference of c 
			if (abs(first[i] - second[j]) == c) {

				size_t bigger = std::max(first[i], second[j]);
				size_t smaller = std::min(first[i], second[j]);

				// Add the points to our map
				path[smaller] = bigger;
			}
		}
	}
	// Iterator for our map
	std::map<int, int>::iterator it;
	// The uncolored part of the segment
	size_t uncoloredPartLength = N;

	/* DEBUGGING PART
		for (it = path.begin(); it != path.end(); it++) {
		std::cout << it->first << "-" << it->second << std::endl;
	}*/


	for (it = path.begin(); it != path.end(); it++) {
		// If we just started, add the first point as start and the second point as end
		if (coloredPartEnd == 0) {
			coloredPartStart = it->first;
			coloredPartEnd = it->second;
			continue;
		}
		
		// If the first point is between a colored segment, increase this colored segment
		if (it->first <= coloredPartEnd) {
			if (it->second > coloredPartEnd) {
				coloredPartEnd = it->second;
			}
		}
		// If the first point is outside a colored segment, just create a new one and substract the length of the previous one
		else {
			uncoloredPartLength -= coloredPartEnd - coloredPartStart;
			coloredPartEnd = it->second;
			coloredPartStart = it->first;
		}
	}

	// Final substract because the last check won't happen in the for cycle
	uncoloredPartLength -= coloredPartEnd - coloredPartStart;
	
	// Printing the result
	std::cout << uncoloredPartLength << std::endl;

	return 0;
}
