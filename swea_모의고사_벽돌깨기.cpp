#include <iostream>
using namespace std;

int map[5][15][12];
int possi[5][15][12];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1, -1 ,0,0 };
int times, width, height, origin_block;
int best_dest = 0;
int temp_dest=0;

void map_resign(int bead) {
	for(int t=0;t<width;t++){
		for (int s = 0; s < height; s++) {

			if (map[bead][s][t] == 0) {
				for (int idx = s; idx > 0; idx--) {
					map[bead][idx][t] = map[bead][idx - 1][t];
					if (idx == 1) {
						map[bead][idx - 1][t] = 0;
					}
				}
			}

		}
	}
	return;
}

void destroy(int x, int y, int bead) {

	if (x < 0 || y < 0 || x >= height || y >= width || map[bead][x][y] == 0 ) {
		return;
	}
	else {
		possi[bead][x][y] = true;
		temp_dest += 1;

		for(int s=0; s < map[bead][x][y]; s++){
			for (int idx = 0; idx < 4; idx++) {
				if (x + (dx[idx] * s) < 0 || y + (dy[idx] * s) < 0 || x + (dx[idx] * s) >= height || y + (dy[idx] * s) >= width) {
					continue;
				}
				if (map[bead][x + (dx[idx] * s)][y + (dy[idx] * s)] >= 1 && possi[bead][x + (dx[idx] * s)][y + (dy[idx] * s)] ==false) {
					possi[bead][x + (dx[idx] * s)][y + (dy[idx] * s)] = true;
					destroy(x + (dx[idx] * s), y + (dy[idx] * s),bead);
				}
			}
		}
		map[bead][x][y] = 0;
	}

	return;
}

int bomb(int start_idx, int bead) {

	int idx = -1;
	temp_dest = 0;
	for (int s = 0; s < height; s++) {
		if (map[bead][s][start_idx] > 0) {
			idx = s;
			break;
		}
	}

	if (idx == -1) {
		return 0;
	}
	else {
		destroy(idx, start_idx, bead);
	}

	return temp_dest;
}

void process(int bead, int times, int current_dest) {

	if (current_dest > best_dest) {
		best_dest = current_dest;
	}
	if (bead > times) {
		return;
	}

	for (int idx = 0; idx < width; idx++) {
		int new_dest = 0;
		for (int s = 0; s < height; s++) {
			for (int t = 0; t < width; t++) {
				possi[bead][s][t] = false;
				map[bead][s][t] = map[bead - 1][s][t];
			}
		}
		new_dest = bomb(idx,bead);
		map_resign(bead);
		process(bead + 1, times, current_dest + new_dest);
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {

		temp_dest = 0;
		origin_block = 0;
		best_dest = 0;

		cin >> times;
		cin >> width;
		cin >> height;

		for (int s = 0; s < height; s++) {
			for (int t = 0; t < width; t++) {
				cin >> map[0][s][t];
				if (map[0][s][t] > 0) {
					origin_block++;
				}
			}
		}

		for (int s = 0; s < height; s++) {
			for (int t = 0; t < width; t++) {
					possi[0][s][t]=false;
			}
		}
	
		process(1, times, 0);

		cout << '#' << t << ' ' << (origin_block - best_dest) << endl;
	}

	return 0;

}