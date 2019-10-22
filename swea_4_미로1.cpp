#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>
//#include <stack>
using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

bool goal = false;
//stack <int> x;
//stack <int> y;
int map[18][18];
bool possi[18][18];

void DFS(int x, int y) {
	if (goal == true) {
		return;
	}
	else if (possi[x][y] == true) {
		return;
	}
	else if(map[x][y]==3){
		goal = true;
		return;
	}
	else { // 접근가능, 도달불가, DFS 요청
		// DFS조건 dx,dy로 인한 결과에 대하여 MAP == -1인 경우는 진입이 불가하다 또한, POSSI가 TRUE면 불가능하다
		// 접근된 공간에 대해서는 POSSI를 TRUE로 변경한다. 단, 변경된 POSSI의 해당 위치가 DFS 방향에 대하여 POSSI가 아닌곳이 2개 이상이라면,
		// 현재의 위치를 스택에 보관한다. -> 생각해보니 필요가없다 단순 DFS다 ㅎ_ㅎ
		possi[x][y] = true;

		for (int idx = 0; idx < 4; idx++) {
			if(possi[x+dx[idx]][y+dy[idx]]==false && map[x+dx[idx]][y+dy[idx]]!= 1 && map[x + dx[idx]][y + dy[idx]] != -1){
				DFS(x + dx[idx], y + dy[idx]);
			}
		}

	}

	return;
}

int main() {

	int test_case=10;

	for (int t = 1; t <= test_case; t++) {
		
		int temp_stage;
		cin >> temp_stage;
		goal = false;

		//if (x.size() > 0) {
		//	x.pop();
		//}
		//if (y.size() > 0) {
		//	y.pop();
		//}

		int st_point_x=0;
		int st_point_y=0;
		int ed_point_x=0;
		int ed_point_y=0;

		memset(possi, false, sizeof(possi));

		for (int s = 0; s < 18; s++) {
			for (int t = 0; t < 18; t++) {
				map[s][t] = -1;
			}
		}

		for (int s = 1; s <= 16; s++) {
			for (int t = 1; t <= 16; t++) {
				scanf("%1d",&map[s][t]);
				if (map[s][t] == 2) {
					st_point_x = s;
					st_point_y = t;
				}
			}
		}

		DFS(st_point_x, st_point_y);

		cout << '#' << temp_stage << ' ' << goal << endl;

	}

	return 0;

}
