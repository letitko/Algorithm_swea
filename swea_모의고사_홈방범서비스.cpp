#include <iostream>
using namespace std;

int best_k = 0;

int cost(int k) {
	return (k * k) +((k - 1) * (k - 1));
}
int gain(int h, int m) {
	return m * h;
}
void check_house(int** map, int x, int y, int k, int n, int* house) {

	for (int s = 0; s < k; s++) {
		for (int t = 0; t < k - s; t++) {
			if (s == 0) {
				if (x - s >= 0 && y + t < n) {
					if (y + t != y - t) {
						if (map[x - s][y + t] == 1)
							* house += 1;
					}
				}

				if (x - s >= 0 && y - t >= 0) {
					if (map[x - s][y - t] == 1)
						* house += 1;
				}
			}
			else {
				// ╩С аб©Л
				if (x - s >= 0 && y + t < n) {
					if(y+t != y-t){
						if (map[x - s][y + t] == 1)
							* house += 1;
					}
				}
	
				if (x - s >= 0 && y - t >= 0) {
					if (map[x - s][y - t] == 1)
						* house += 1;
				}
	
				// го аб©Л
				if (x + s < n && y + t < n) {
					if(y+t != y-t){
						if (map[x + s][y + t] == 1)
							* house += 1;
					}
				}
	
				if (x + s < n && y - t >= 0) {
					if (map[x + s][y - t] == 1)
						* house += 1;
				}
			}
		}
	}
}

void process(int** map, bool** area, int n, int m) {

	int house = 0;
	int best_house = 0;

	for(int k=1;k<=n+1;k++){
		int current_cost = cost(k);
		for (int s = 0; s < n; s++) {
			for(int t = 0; t < n; t++) {
				house = 0;
				check_house(map,s,t,k,n,&house);
				if(house > best_house){
					best_house = house;
					int current_gain = gain(house, m);
					if (current_cost <= current_gain){
						best_k = best_house;
					}
				}
			}
		}
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;
	
	for (int t = 1; t <= test_case; t++) {

		best_k = 0;

		int n;
		cin >> n;

		int m;
		cin >> m;

		int** map = new int* [n];
		for (int s = 0; s < n; s++) {
			map[s] = new int[n];
		}

		bool** area = new bool* [n];
		for (int s = 0; s < n; s++) {
			area[s] = new bool[n];
		}

		for (int s = 0; s < n; s++) {
			for (int t = 0; t < n; t++) {
				cin >> map[s][t];
			}
		}

		process(map, area, n, m);

		cout << "#" << t << ' ' << best_k << endl;
	}

	return 0;
}