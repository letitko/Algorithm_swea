#include <iostream>
#include <queue>
using namespace std;

queue <int> datas;
int len; int times; int total_bugs;
class bugs_life {
public:
	bool danger = false;
	int how_many = 0;
	int direct = 0;
};
class bugs_list {
public:
	int how_many = 0;
	int direc = 0;
};

int dx[] = { -1, +1, 0,0 };
int dy[] = { 0, 0, -1,+1 };

void copy_map(bugs_life** map, bugs_life** new_map) {
	for (int s = 0; s < len; s++) {
		for (int t = 0; t < len; t++) {
			map[s][t].direct = new_map[s][t].direct;
			map[s][t].how_many = new_map[s][t].how_many;
		}
	}
	return;
}
void clear_map(bugs_life** new_map, bool** possi) {
	for (int s = 0; s < len; s++) {
		for (int t = 0; t < len; t++) {
			new_map[s][t].direct = 0;
			new_map[s][t].how_many = 0;
			possi[s][t] = false;
		}
	}
	return;
}

// 1:ªÛ , 2:«œ , 3:¡¬, 4:øÏ
void scan(bugs_life** map, bool** possi, bugs_life** new_map, int x, int y) {
	int surrounder = 0;
	int surrounder_idx = 0;
	bugs_list* list = new bugs_list[4];

	for (int idx = 0; idx < 4; idx++) {
		if (x + dx[idx] < 0 || x + dx[idx] >= len || y + dy[idx] < 0 || y + dy[idx] >= len) {
			continue;
		}
		else if (map[x + dx[idx]][y + dy[idx]].how_many != 0 && possi[x + dx[idx]][y + dy[idx]] == false) {
			if (idx == 0 && map[x + dx[idx]][y + dy[idx]].direct == 2) {// ªÛ
				list[surrounder_idx].how_many = map[x + dx[idx]][y + dy[idx]].how_many;
				list[surrounder_idx].direc = map[x + dx[idx]][y + dy[idx]].direct;
				possi[x + dx[idx]][y + dy[idx]] = true;
				surrounder += 1;
				surrounder_idx += 1;
			}
			else if (idx == 1 && map[x + dx[idx]][y + dy[idx]].direct == 1) { // «œ
				list[surrounder_idx].how_many = map[x + dx[idx]][y + dy[idx]].how_many;
				list[surrounder_idx].direc = map[x + dx[idx]][y + dy[idx]].direct;
				possi[x + dx[idx]][y + dy[idx]] = true;
				surrounder += 1;
				surrounder_idx += 1;
			}
			else if (idx == 2 && map[x + dx[idx]][y + dy[idx]].direct == 4) { // ¡¬
				list[surrounder_idx].how_many = map[x + dx[idx]][y + dy[idx]].how_many;
				list[surrounder_idx].direc = map[x + dx[idx]][y + dy[idx]].direct;
				possi[x + dx[idx]][y + dy[idx]] = true;
				surrounder += 1;
				surrounder_idx += 1;
			}
			else if (idx == 3 && map[x + dx[idx]][y + dy[idx]].direct == 3) // øÏ
			{
				list[surrounder_idx].how_many = map[x + dx[idx]][y + dy[idx]].how_many;
				list[surrounder_idx].direc = map[x + dx[idx]][y + dy[idx]].direct;
				possi[x + dx[idx]][y + dy[idx]] = true;
				surrounder += 1;
				surrounder_idx += 1;

			}
			else {
				continue;
			}
		}
	}

	if (surrounder > 0) { // ¡÷∫Øø° π∫∞° ¿÷¥Ÿ∏È
		datas.push(x);
		datas.push(y);
		int amount = 0;
		int direction = 0;
		int biggest_num = 0;
		int biggest_num_direction = 0;
		for (int idx = 0; idx < surrounder_idx; idx++) {
			amount += list[idx].how_many;
			if (list[idx].how_many > biggest_num) {
				biggest_num = list[idx].how_many;
				direction = list[idx].direc;
			}
		}

		new_map[x][y].how_many = amount;
		new_map[x][y].direct = direction;

		if (new_map[x][y].danger == true) {
			new_map[x][y].how_many /= 2;
			// 1:ªÛ , 2:«œ , 3:¡¬, 4:øÏ
			if (direction == 1)
				new_map[x][y].direct = 2;
			else if (direction == 2)
				new_map[x][y].direct = 1;
			else if (direction == 3)
				new_map[x][y].direct = 4;
			else {
				new_map[x][y].direct = 3;
			}
		}

	}
	delete[] list;
	return;
}

void process(bugs_life** map, bool** possi, bugs_life** new_map) {

	for (int s = datas.size(); s > 0; s = s-2) {
		int x = datas.front();
		datas.pop();
		int y = datas.front();
		datas.pop();

		if(map[x][y].direct == 1){
			scan(map, possi, new_map, x-1, y);
		}
		else if (map[x][y].direct == 2) {
			scan(map, possi, new_map, x+1, y);
		}
		else if (map[x][y].direct == 3) {
			scan(map, possi, new_map, x, y-1);
		}
		else {
			scan(map, possi, new_map, x, y+1);
		}
	}

	copy_map(map, new_map);
	clear_map(new_map, possi);

	return;
}

void detection(bugs_life** map, int* survivors) {
	for (int s = 0; s < len; s++) {
		for (int t = 0; t < len; t++) {
			if (map[s][t].how_many > 0) {
				*survivors += map[s][t].how_many;
			}
		}
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		cin >> len >> times >> total_bugs;

		bugs_life** map = new bugs_life * [len];
		for (int s = 0; s < len; s++) {
			map[s] = new bugs_life[len];
		}

		bugs_life** new_map = new bugs_life * [len];
		for (int s = 0; s < len; s++) {
			new_map[s] = new bugs_life[len];
		}

		bool** possi = new bool* [len];
		for (int s = 0; s < len; s++) {
			possi[s] = new bool[len];
		}
		for (int s = 0; s < len; s += (len - 1)) {
			for (int t = 0; t < len; t++) {
				map[s][t].danger = true;
				new_map[s][t].danger = true;
			}
		}
		for (int t = 0; t < len; t += (len - 1)) {
			for (int s = 0; s < len; s++) {
				map[s][t].danger = true;
				new_map[s][t].danger = true;
			}
		}

		int x, y;
		for (int s = 0; s < total_bugs; s++) {
			cin >> x >> y;
			datas.push(x);
			datas.push(y);
			cin >> map[x][y].how_many;
			cin >> map[x][y].direct;
		}

		for (int t = 1; t <= times; t++) {
			process(map, possi, new_map);
		}

		int total_amount = 0;
		detection(map, &total_amount);
		cout << '#' << t << ' ' << total_amount << endl;
	}

	return 0;
}