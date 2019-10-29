#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>
using namespace std;

int minimum = 987987987;
int shelve_height;
int total_people;
int list[10000];

void recursion(int sum, int idx, int len, int dest) {

	if (idx>len) {
		return;
	}

	if (sum >= dest) {
		if (sum <= minimum) {
			minimum = sum;
			return;
		}
		else {
			return;
		}
	}
	else{
		recursion(sum + list[idx], idx + 1, len,dest);
		recursion(sum, idx + 1, len,dest);
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		minimum = 987987987;
		cin >> total_people;
		cin >> shelve_height;

		for (int s = 0; s < total_people; s++) {
			cin >> list[s];
		}

		recursion(0, 0, total_people, shelve_height);

		cout << '#' << t << ' ' << minimum - shelve_height << endl;

	}

	return 0;
}
