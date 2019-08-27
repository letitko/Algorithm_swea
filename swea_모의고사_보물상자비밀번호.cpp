#include <iostream>
#include <stdlib.h>
using namespace std;

void process(char** list, char* chest, int words_partiton, int start_idx) {

	// 로테이팅
	char changer;
	changer = chest[words_partiton * 4 - 1];

	for (int s = words_partiton * 4 - 2; s >= 0; s--) {
		chest[s + 1] = chest[s];
	} chest[0] = changer;

	// 리스팅
	int origin_word_idx = 0;
	for (int idx = start_idx; idx < start_idx + 4; idx++) {
		for (int s = 0; s < words_partiton; s++) {
			list[idx][s] = chest[origin_word_idx++];
		}
	}

	return;
}

void get_rank(char** list, int** rank, int words_partition, int dest_rank) {

	// 아스키코드 자리수별 10진수화
	for (int idx = 0; idx < words_partition * 4; idx++) {
		for (int idx_2 = 0; idx_2 < words_partition; idx_2++) {

			if (48 <= (int)list[idx][idx_2] && (int)list[idx][idx_2] <= 57) {
				int stand = 1;
				for (int s = 0; s < words_partition - 1 - idx_2; s++) {
					stand *= 16;
				}
				rank[idx][0] += (((int)list[idx][idx_2]) % 48) * stand;
			}
			else {
				int stand = 1;
				for (int s = 0; s < words_partition - 1 - idx_2; s++) {
					stand *= 16;
				}
				rank[idx][0] += (((int)list[idx][idx_2]) % 55) * stand;
			}

		}
	}

	// 랭크 순위 정리
	int temp_num;
	for (int idx = 0; idx < words_partition * 4; idx++) {
		temp_num = rank[idx][0];
		for (int idx_2 = 0; idx_2 < words_partition * 4; idx_2++) {
			if (temp_num > rank[idx_2][0]) {
				rank[idx_2][1] += 1;
			}
		}
	}

	// 중복 순위 정리

	int rank_num;
	for (int rank_num = 1; rank_num <= words_partition * 4; rank_num++) {

		int counter = 0;

		for (int idx = 0; idx < words_partition * 4; idx++) {
			if (rank_num == rank[idx][1]) {
				counter += 1;
			}
		}

		if (counter > 1) {
			for (int idx = 0; idx < words_partition * 4; idx++) {
				if (rank_num < rank[idx][1]) {
					rank[idx][1] -= (counter-1);
				}
			}
		}

	}

	// 표적 순위 찾기

	for (int idx = 0; idx < words_partition * 4; idx++) {
		if (rank[idx][1] == dest_rank) {
			cout << rank[idx][0] << endl;
			break;
		}
	}

	return;
}

int main() {

	int test_case;
	cin >> test_case;

	for (int t = 1; t <= test_case; t++) {

		int total_words;
		cin >> total_words;

		int goal;
		cin >> goal;

		int words_partiotion = total_words / 4;
		int rotation = (total_words / 4) - 1;

		char* chest = new char[total_words];
		cin >> chest;

		char** list = new char* [4 * words_partiotion];
		for (int s = 0; s < 4 * words_partiotion; s++) {
			list[s] = new char[words_partiotion + 1];
		}

		int** rank = new int* [4 * words_partiotion];
		for (int s = 0; s < 4 * words_partiotion; s++) {
			rank[s] = new int[2];
		}

		for (int idx = 0; idx < 4 * words_partiotion; idx++) {
			rank[idx][0] = 0;
			rank[idx][1] = 1;
		}

		for (int s = 0; s < 4 * words_partiotion; s++) {
			list[s][words_partiotion] = '\n';
		}

		// 단어 리스트에 입력 _ 최초
		int origin_word_idx = 0;
		for (int idx = 0; idx < 4; idx++) {
			for (int s = 0; s < words_partiotion; s++) {
				list[idx][s] = chest[origin_word_idx++];
			}
		}

		// 로테이션 - > 리스트에 입력 함수 실행
		for (int phase = 1; phase <= rotation; phase++) {
			process(list, chest, words_partiotion, phase * 4);
		}

		// 랭킹 프로세스
		cout << '#' << t << ' ';
		get_rank(list, rank, words_partiotion, goal);

	}

	return 0;
}