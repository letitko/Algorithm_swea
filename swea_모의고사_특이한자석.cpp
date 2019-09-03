#include <iostream>
#include <queue>
using namespace std;

class saw_tooth {
public:
	int data[3][3];
};

int phase;
queue <int> candidate;
queue <int> final_candidate;
queue <int> candidate_direction;
queue <int> final_candidate_direction;

void who_must(saw_tooth* saw, int num, bool* possi, int direction) {

	possi[num] = true;

	if (num - 1 >= 0) {
		if (saw[num].data[1][0] != saw[num - 1].data[1][2] && possi[num - 1] == false) {
			candidate.push(num - 1);
			final_candidate.push(num - 1);
			if (direction == 1) {
				candidate_direction.push(-1);
				final_candidate_direction.push(-1);
			}
			else {
				candidate_direction.push(1);
				final_candidate_direction.push(1);
			}
		}
	}

	if (num + 1 <= 3) {
		if (saw[num].data[1][2] != saw[num + 1].data[1][0] && possi[num + 1] == false) {
			candidate.push(num + 1);
			final_candidate.push(num + 1);
			if (direction == 1) {
				candidate_direction.push(-1);
				final_candidate_direction.push(-1);
			}
			else {
				candidate_direction.push(1);
				final_candidate_direction.push(1);
			}
		}

	}

	return;
}

void rotate(int stand_way, saw_tooth* saw, int num) {
	if (stand_way == -1) { // 스탠드 == 시계방향 회전 -> 반시계로 회전
		saw[num].data[1][1] = saw[num].data[0][1];
		saw[num].data[0][1] = saw[num].data[0][2];
		saw[num].data[0][2] = saw[num].data[1][2];
		saw[num].data[1][2] = saw[num].data[2][2];
		saw[num].data[2][2] = saw[num].data[2][1];
		saw[num].data[2][1] = saw[num].data[2][0];
		saw[num].data[2][0] = saw[num].data[1][0];
		saw[num].data[1][0] = saw[num].data[0][0];
		saw[num].data[0][0] = saw[num].data[1][1];
	}
	else { // 스탠드 == 반시계방향 회전 - > 시계로 회전
		saw[num].data[1][1] = saw[num].data[0][1];
		saw[num].data[0][1] = saw[num].data[0][0];
		saw[num].data[0][0] = saw[num].data[1][0];
		saw[num].data[1][0] = saw[num].data[2][0];
		saw[num].data[2][0] = saw[num].data[2][1];
		saw[num].data[2][1] = saw[num].data[2][2];
		saw[num].data[2][2] = saw[num].data[1][2];
		saw[num].data[1][2] = saw[num].data[0][2];
		saw[num].data[0][2] = saw[num].data[1][1];
	}

	return;
}

void reset_possi(bool* possi) {
	for (int s = 0; s < 4; s++) {
		possi[s] = false;
	}
	return;
}

int get_score(saw_tooth* saw) {

	int total_score = 0;
	for (int s = 0; s < 4; s++) {
		if (saw[s].data[0][1] == 1) {
			int score = 1;
			for (int t = s; t > 0; t--) {
				score *= 2;
			}
			total_score += score;
		}
	}

	return total_score;
}

int main() { // 1 = 'S', 0 = 'N'

	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		saw_tooth* saw = new saw_tooth[4];

		cin >> phase;

		// SAW_DATA
		// 00 01 02
		// 10 11 12
		// 20 21 22

		for (int num = 0; num < 4; num++) {
			cin >> saw[num].data[0][1];
			cin >> saw[num].data[0][2];
			cin >> saw[num].data[1][2];
			cin >> saw[num].data[2][2];
			cin >> saw[num].data[2][1];
			cin >> saw[num].data[2][0];
			cin >> saw[num].data[1][0];
			cin >> saw[num].data[0][0];
		}

		bool* possi = new bool[4];

		for (int s = 0; s < phase; s++) {
			int current_num;
			cin >> current_num;
			current_num -= 1;
			possi[current_num]=true;
			candidate.push(current_num);
			final_candidate.push(current_num);

			int direction;
			cin >> direction;
			candidate_direction.push(direction);
			final_candidate_direction.push(direction);

			while (candidate.size() > 0) {
				who_must(saw, candidate.front(), possi, candidate_direction.front());
				candidate.pop();
				candidate_direction.pop();
			}

			while (final_candidate.size() > 0) {
				rotate(final_candidate_direction.front(), saw, final_candidate.front());
				final_candidate.pop();
				final_candidate_direction.pop();
			}
			reset_possi(possi);
		}

		int total_score = get_score(saw);
		cout << '#' << t << ' ' << total_score << endl;

	}

	return 0;
}