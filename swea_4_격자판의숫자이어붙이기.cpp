#include <iostream>
#include <memory.h>
using namespace std;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int map[6][6];
bool candidate[10000000];
int counter = 0;

void DFS(int x, int y, int process, int dest,int current_num);

int main() {

	int test_case = 0;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		counter = 0;
		memset(candidate, false, sizeof(candidate));

		for (int s = 0; s < 6; s++) {
			for (int t = 0; t < 6; t++) {
				map[s][t] = -1;
			}
		}

		for (int s = 1; s <= 4; s++) {
			for (int t = 1; t <= 4; t++) {
				cin >> map[s][t];
			}
		}

		for (int s = 1; s <= 4; s++) {
			for (int t = 1; t <= 4; t++) {
				DFS(s,t,0,7,0);
			}
		}

		cout << '#' << t << ' ' << counter << endl;

	}

	return 0;
}

void DFS(int x, int y, int process, int dest, int current_num) {
	
	if (candidate[current_num] == false && dest == process) {
		candidate[current_num] = true;
		counter += 1;
		return;
	}
	else if (process < dest) {

		// 현재 중간 수 백업
		int temp_num = map[x][y];
		for (int u = 1; u <= process; u++) {
			temp_num *= 10;
		} 

		// DFS 탐색
		for (int idx = 0; idx < 4; idx++) {
				if(map[x + dx[idx]][y + dy[idx]] != -1)
				DFS(x + dx[idx], y + dy[idx], process + 1, dest, current_num + temp_num);
		}

	}
	else {
		return;
	}

	return;
}
