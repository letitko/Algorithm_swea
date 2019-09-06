#include <iostream>
#include <queue>
using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

class info {
public :
	int stay;
	int life;
	int x;
	int y;
};

int main() {
	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {
		
		queue <info> value[11];
		int height, width, phase;
		cin >> height >> width >> phase;

		bool** dead_cell = new bool* [400];
		for (int s = 0; s < 400; s++) {
			dead_cell[s] = new bool[400];
		}
		for (int s = 0; s < 400; s++) {
			for (int t = 0; t < 400; t++) {
				dead_cell[s][t] = false;
			}
		}


		bool** old_cell = new bool* [400];
		for (int s = 0; s < 400; s++) {
			old_cell[s] = new bool[400];
		}
		for (int s = 0; s < 400; s++) {
			for (int t = 0; t < 400; t++) {
				old_cell[s][t] = false;
			}
		}
		int** map = new int* [400];
		for (int s = 0; s < 400; s++) {
			map[s] = new int[400];
		}
		for (int s = 0; s < 400; s++) {
			for (int t = 0; t < 400; t++) {
				map[s][t] = 0;
			}
		}

		int total_cells = 0;
		int total_death = 0;

		for (int s = 0; s < height; s++){
			for (int t = 0; t < width; t++) {
				int num;
				cin >> num;

				if(num>0){
					map[s+175][t+175] = num;
					old_cell[s+175][t+175] = true;
					value[num].push({ 0,-1,s+175,t+175 });
				}

			}
		}
		
		int len[11] = {0,0,0,0,0,0,0,0,0,0,0 };
		for(int s=0;s< phase;s++){

			for (int s = 1; s <= 10; s++) {
				len[s] = value[s].size();
			}

			for (int num = 1; num <= 10; num++) {

				if (len[num] == 0) {
					continue;
				}

				for (int t = 0; t < len[num];t++) {
						
						auto current = value[num].front();
						value[num].pop();

						if (map[current.x][current.y] != num) { // 허수 배제
							continue;
						}

						if (current.life == -1) { // 아직 미 활성화 이라면
							if (current.stay + 1 != num) {
								value[num].push({ current.stay + 1, -1, current.x, current.y });
							}
							else {
								value[num].push({ current.stay + 1, num,current.x,current.y });
							}
						}
						else if (current.life > 0) { // 활성화 단계라면
							for (int idx = 0; idx < 4; idx++) {
								if (old_cell[current.x + dx[idx]][current.y + dy[idx]] == false) {
									if (map[current.x + dx[idx]][current.y + dy[idx]] < num) {
										map[current.x + dx[idx]][current.y + dy[idx]] = num;
										value[num].push({ 0,-1,current.x + dx[idx],current.y + dy[idx] });
									}
								}
							}
							if (current.life - 1 == 0) {
								dead_cell[current.x][current.y] = true;
							}
							else {
								value[num].push({ current.stay,current.life - 1,current.x,current.y });
							}
						}
				}

			}

			for (int s = 0; s < 400; s++) {
				for (int t = 0; t < 400; t++) {
					if (map[s][t] > 0) {
						old_cell[s][t] = true;
					}
				}
			}

		}

		for (int s = 0; s < 400; s++) {
			for (int t = 0; t < 400; t++) {
				if (dead_cell[s][t] == true) {
					total_death++;
				}
			}
		}
		for (int s = 0; s < 400; s++) {
			for (int t = 0; t < 400; t++) {
				if (map[s][t] > 0) {
					total_cells++;
				}
			}
		}

		cout << '#' << t << ' ' << (total_cells - total_death) << endl;
	}

	return 0;
}

