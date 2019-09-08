#include <iostream>
using namespace std;
bool food[16];
int chef[16][16];
int total_food;
int first_food;
int second_food;
int difference;

void single_idx_reset() {
	for (int s = 0; s < total_food; s++) {
			food[s] = false;
	}
}
void double_idx_reset() {
	for (int s = 0; s < total_food; s++) {
		for (int t = 0; t < total_food; t++) {
			chef[s][t] = 0;
		}
	}
}
void get_food(int how_many, int max_food, int idx) {

	if (how_many > max_food || (how_many<max_food && idx==total_food) ) {
		return;
	}
	else if (how_many == max_food && idx == total_food) {

		first_food = 0;
		second_food = 0;

		for (int ad = 0; ad < total_food; ad++) {
			if (food[ad] == true) {
				for (int s = 0; s < total_food; s++) {
					if (food[s] == true)
						first_food += chef[ad][s];
				}
			}
			else {
				for (int t = 0; t < total_food; t++) {
					if (food[t] == false)
						second_food += chef[ad][t];
				}
			}
		}

		if (difference > abs(first_food - second_food)) {
			difference = abs(first_food - second_food);
		}

		return;
	}
	else {

		for (int s = 0; s < 2; s++) {
			if (s == 1) {
				food[idx] = true;
				get_food(how_many + 1, max_food, idx + 1);
			}
			else {
				food[idx] = false;
				get_food(how_many, max_food, idx + 1);
			}
		}

	}

	return;
}

int main() {
	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {

		difference = 987987987;
		first_food = 0;
		second_food = 0;

		cin >> total_food;
		single_idx_reset();
		double_idx_reset();
		for (int s = 0; s < total_food; s++) {
			for (int t = 0; t < total_food; t++) {
				cin >> chef[s][t];
			}
		}

		get_food(0, total_food / 2, 0);
		cout << '#' << t << ' ' << difference << endl;
	}
	return 0;
}