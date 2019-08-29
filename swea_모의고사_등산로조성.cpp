#include <iostream>
#include <queue>
using namespace std;

int max_num = -987987987;
int longest = 0;
int dx[] = { 0,0,+1,-1 };
int dy[] = { +1,-1.0,0 };
// BFS 우좌하상

void possi_reset(bool** possi, int map_len) {
	for (int s = 0; s < map_len; s++) {
		for (int t = 0; t < map_len; t++) {
			possi[s][t]=false;
		}
	}

	return ;
}

void dig_the_map(int** map, int x, int y,int map_len , int shovel, int current_len, bool** possibility, int my_value, bool used) {

	// 맵 오류 방지 기저조건
	if (x < 0 || x >= map_len || y >= map_len || y < 0 || possibility[x][y] == true) {
		return;
	}

	// 최대 거리 찾기용 부분 갱신
	if (current_len > longest) {
		longest = current_len;
		//cout << "longest : " <<  longest << endl;
	}

	// BFS용 다음맵 생성
	bool **temp_possi = new bool*[map_len];
	for (int is = 0; is < map_len; is++) {
		temp_possi[is] = new bool[map_len];
	} 
	for (int s = 0; s < map_len; s++) {
		for (int t = 0; t < map_len; t++) {
			temp_possi[s][t] = possibility[s][t];
		}
	} 

	// 내 현재위치 사용여부 표기
	temp_possi[x][y] = true;

	// 조건부 BFS 실행
	if(used == false){ // 아직 삽 안쓴경우
		for(int shovels=0;shovels<=shovel;shovels++){
			for (int idx = 0; idx < 4; idx++) {
				if (x + dx[idx] < 0 || x + dx[idx] >= map_len || y + dy[idx] >= map_len || y + dy[idx] < 0) {
					continue;
				}

				if (shovels == 0) {
					if (map[x + dx[idx]][y + dy[idx]] < my_value && temp_possi[x + dx[idx]][y + dy[idx]] == false) {
						dig_the_map(map, x + dx[idx], y + dy[idx], map_len, shovel, current_len + 1, temp_possi, map[x + dx[idx]][y + dy[idx]], false);
					}
				}
				else {
					if (map[x + dx[idx]][y + dy[idx]] - shovels < my_value && temp_possi[x + dx[idx]][y + dy[idx]] == false) {
						dig_the_map(map, x + dx[idx], y + dy[idx], map_len, shovel, current_len + 1, temp_possi, map[x + dx[idx]][y + dy[idx]] - shovels, true);
					}
				}

			}	
		}
	}
	else { // 삽 쓴경우
		for (int idx = 0; idx < 4; idx++) {
			if (x + dx[idx] < 0 || x +dx[idx] >= map_len || y+dy[idx] >= map_len || y+dy[idx] < 0) {
				continue;
			}

			if (map[x + dx[idx]][y + dy[idx]] < my_value && temp_possi[x+dx[idx]][y+dy[idx]] == false) {
				dig_the_map(map, x + dx[idx], y + dy[idx], map_len, shovel, current_len+1, temp_possi, map[x + dx[idx]][y + dy[idx]],true);
			}		
		}
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		max_num = -987987987;
		longest = 0;
		int n; int k;
		cin >> n;
		cin >> k;
		queue <int> position;

		int** map = new int* [n];
		for (int s = 0; s < n; s++) {
			map[s] = new int[n];
		}

		bool** possi = new bool* [n];
		for (int s = 0; s < n; s++) {
			possi[s] = new bool[n];
		}

		for (int s = 0; s < n; s++) {
			for (int t = 0; t < n; t++) {
				cin >> map[s][t];
				if (max_num < map[s][t]) {
					max_num = map[s][t];
				}
			}
		} 

		for (int s = 0; s < n; s++) {
			for (int t = 0; t < n; t++) {
				if (max_num == map[s][t]) {
					position.push(s);
					position.push(t);
				}
			}
		}

		int x;
		int y;

		while (position.size() > 0) {

			x = position.front();
			position.pop();

			y = position.front();
			position.pop();

			
			dig_the_map(map,x,y,n,k,1,possi,max_num,false);

			possi_reset(possi, n);

		}

		cout << '#' << t << ' ' << longest << endl;

	}

	return 0;

}