#include <iostream>
using namespace std;

void find_man(int** map, bool** possi, int x, int y, int* total_place, int current_time, int total_time,int **dp) {

	if(possi[x][y]==false){
	*total_place += 1;
	}
	possi[x][y] = true;

	if (current_time >= total_time) {
		return;
	}
	else {

		if (dp[x][y] > current_time) {
			dp[x][y] = current_time;
			int c_hose = map[x][y];

			switch (c_hose)
			{
			case 1: // ╩Сгоаб©Л
				if ((map[x][y - 1] == 1 || map[x][y - 1] == 3 || map[x][y - 1] == 4 || map[x][y - 1] == 5)) {
					if (possi[x][y - 1] == false || (possi[x][y - 1] == true && current_time < total_time))
						find_man(map, possi, x, y - 1, total_place, current_time + 1, total_time,dp);
				} // аб
				if ((map[x][y + 1] == 1 || map[x][y + 1] == 3 || map[x][y + 1] == 6 || map[x][y + 1] == 7)) {
					if (possi[x][y + 1] == false || (possi[x][y + 1] == true && current_time < total_time))
						find_man(map, possi, x, y + 1, total_place, current_time + 1, total_time,dp);
				} // ©Л
				if ((map[x - 1][y] == 1 || map[x - 1][y] == 2 || map[x - 1][y] == 5 || map[x - 1][y] == 6)) {
					if (possi[x - 1][y] == false || (possi[x - 1][y] == true && current_time < total_time))
						find_man(map, possi, x - 1, y, total_place, current_time + 1, total_time,dp);
				} // ╩С 
				if ((map[x + 1][y] == 1 || map[x + 1][y] == 2 || map[x + 1][y] == 4 || map[x + 1][y] == 7)) {
					if (possi[x + 1][y] == false || (possi[x + 1][y] == true && current_time < total_time))
						find_man(map, possi, x + 1, y, total_place, current_time + 1, total_time,dp);
				} // го

				break;

			case 2: // ╩Сго
				if ((map[x - 1][y] == 1 || map[x - 1][y] == 2 || map[x - 1][y] == 5 || map[x - 1][y] == 6)) {
					if (possi[x - 1][y] == false || (possi[x - 1][y] == true && current_time < total_time))
						find_man(map, possi, x - 1, y, total_place, current_time + 1, total_time,dp);
				} // ╩С 
				if ((map[x + 1][y] == 1 || map[x + 1][y] == 2 || map[x + 1][y] == 4 || map[x + 1][y] == 7)) {
					if (possi[x + 1][y] == false || (possi[x + 1][y] == true && current_time < total_time))
						find_man(map, possi, x + 1, y, total_place, current_time + 1, total_time,dp);
				} // го

				break;

			case 3: // аб©Л
				if ((map[x][y - 1] == 1 || map[x][y - 1] == 3 || map[x][y - 1] == 4 || map[x][y - 1] == 5)) {
					if (possi[x][y - 1] == false || (possi[x][y - 1] == true && current_time < total_time))
						find_man(map, possi, x, y - 1, total_place, current_time + 1, total_time,dp);
				} // аб
				if ((map[x][y + 1] == 1 || map[x][y + 1] == 3 || map[x][y + 1] == 6 || map[x][y + 1] == 7)) {
					if (possi[x][y + 1] == false || (possi[x][y + 1] == true && current_time < total_time))
						find_man(map, possi, x, y + 1, total_place, current_time + 1, total_time,dp);
				} // ©Л

				break;

			case 4: // ╩С©Л
				if ((map[x][y + 1] == 1 || map[x][y + 1] == 3 || map[x][y + 1] == 6 || map[x][y + 1] == 7)) {
					if (possi[x][y + 1] == false || (possi[x][y + 1] == true && current_time < total_time))
						find_man(map, possi, x, y + 1, total_place, current_time + 1, total_time,dp);
				} // ©Л
				if ((map[x - 1][y] == 1 || map[x - 1][y] == 2 || map[x - 1][y] == 5 || map[x - 1][y] == 6)) {
					if (possi[x - 1][y] == false || (possi[x - 1][y] == true && current_time < total_time))
						find_man(map, possi, x - 1, y, total_place, current_time + 1, total_time,dp);
				} // ╩С 

				break;

			case 5: // ©Лго
				if ((map[x][y + 1] == 1 || map[x][y + 1] == 3 || map[x][y + 1] == 6 || map[x][y + 1] == 7)) {
					if (possi[x][y + 1] == false || (possi[x][y + 1] == true && current_time < total_time))
						find_man(map, possi, x, y + 1, total_place, current_time + 1, total_time,dp);
				} // ©Л

				if ((map[x + 1][y] == 1 || map[x + 1][y] == 2 || map[x + 1][y] == 4 || map[x + 1][y] == 7)) {
					if (possi[x + 1][y] == false || (possi[x + 1][y] == true && current_time < total_time))
						find_man(map, possi, x + 1, y, total_place, current_time + 1, total_time,dp);
				} // го

				break;

			case 6: // абго
				if ((map[x][y - 1] == 1 || map[x][y - 1] == 3 || map[x][y - 1] == 4 || map[x][y - 1] == 5)) {
					if (possi[x][y - 1] == false || (possi[x][y - 1] == true && current_time < total_time))
						find_man(map, possi, x, y - 1, total_place, current_time + 1, total_time,dp);
				} // аб
				if ((map[x + 1][y] == 1 || map[x + 1][y] == 2 || map[x + 1][y] == 4 || map[x + 1][y] == 7)) {
					if (possi[x + 1][y] == false || (possi[x + 1][y] == true && current_time < total_time))
						find_man(map, possi, x + 1, y, total_place, current_time + 1, total_time,dp);
				} // го

				break;

			case 7: // аб╩С
				if ((map[x][y - 1] == 1 || map[x][y - 1] == 3 || map[x][y - 1] == 4 || map[x][y - 1] == 5)) {
					if (possi[x][y - 1] == false || (possi[x][y - 1] == true && current_time < total_time))
						find_man(map, possi, x, y - 1, total_place, current_time + 1, total_time,dp);
				} // аб
				if ((map[x - 1][y] == 1 || map[x - 1][y] == 2 || map[x - 1][y] == 5 || map[x - 1][y] == 6)) {
					if (possi[x - 1][y] == false || (possi[x - 1][y] == true && current_time < total_time))
						find_man(map, possi, x - 1, y, total_place, current_time + 1, total_time,dp);
				} // ╩С 


				break;

			default:
				break;
			}

			return;
		}
		else {
		return;
		}
	}
	return;
}


int main() {

	int test_case;
	cin >> test_case;

	for(int t = 1; t <= test_case; t++) {

		int down;
		cin >> down;

		int cross;
		cin >> cross;

		int start_point_x;
		cin >> start_point_x;
		start_point_x += 1;

		int start_point_y;
		cin >> start_point_y; // x,y
		start_point_y += 1;

		int time;
		cin >> time;

		int total_place = 0;

		bool** possi = new bool* [down+2];
		for (int s = 0; s < down+2; s++) {
			possi[s] = new bool[cross+2];
		}

		for (int s = 0; s < down+2; s++) {
			for (int t = 0; t < cross+2; t++) {
				possi[s][t] = false;
			}
		}

		int** map= new int* [down+2];
		for (int s = 0; s < down+2; s++) {
			map[s] = new int[cross+2];
		}

		int** dp = new int* [down + 2];
		for (int s = 0; s < down + 2; s++) {
			dp[s] = new int[cross + 2];
		}

		for (int s = 0; s < down + 2; s++) {
			for (int t = 0; t < cross + 2; t++) {
				dp[s][t] = 987987987;
			}
		}


		for (int s = 1; s <= down;s++ ) {
			for (int t = 1; t <= cross; t++) {
				cin >> map[s][t];
			} 
		}

		find_man(map, possi, start_point_x, start_point_y, &total_place, 1, time,dp);

		cout << '#' << t << ' ' << total_place << endl;
	}

	return 0;
}