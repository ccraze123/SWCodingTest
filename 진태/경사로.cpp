#include <cstdio>
#include <algorithm>

using namespace std;

int map[100][100];
int slope[100][100];
int n, l;
int cnt;
bool road;
int ans = 0;

int main() {

	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			slope[i][j] = 0;

	// 가로 한 번
	for (int i = 0; i < n; i++) {
		cnt = 1;
		road = true;
		for (int j = 0; j < n - 1; j++) {
			if (map[i][j] == map[i][j + 1]) {
				cnt++;
			}
			else if (abs(map[i][j] - map[i][j + 1]) == 1) {
				// 바로 뒤가 더 높은 경우 지금까지 카운트한 거로 경사로 판단
				if (map[i][j] < map[i][j + 1]) {
					int tmp = cnt;
					cnt = 1;
					if (tmp < l) {
						road = false;
						break;
					}
					// 경사로 두기
					else {
						for (int k = 0; k < l; k++) {
							if (slope[i][j - k] == 0)
								slope[i][j - k] = 1;	// 경사로 겹치는 것 때문에 표시
							else {
								road = false;
								break;
							}
						}
					}
				}
				// 바로 뒤가 더 낮은 경우
				else {
					cnt = 1;
					int tmp = 1;
					for (int k = 1; k < l; k++) {	// 뒤로 넘어가서 따로 체크
						if (map[i][j + k] == map[i][j + k + 1]) {
							tmp++;
						}
					}
					if (tmp < l) {
						road = false;
						break;
					}
					// 경사로 두기
					else {
						for (int k = 0; k < l; k++) {
							if (slope[i][j + k + 1] == 0)
								slope[i][j + k + 1] = 1;
							else {
								road = false;
								break;
							}
						}
					}
				}
			}
			else {
				road = false;
				break;
			}
		}
		if (road == true) {
			ans++;
//			printf("i:%d\n", i);
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			slope[i][j] = 0;

	// 세로 한 번, 가로랑 인덱스만 다르다
	for (int j = 0; j < n; j++) {
		cnt = 1;
		road = true;
		for (int i = 0; i < n - 1; i++) {
			if (map[i][j] == map[i + 1][j]) {
				cnt++;
			}
			else if (abs(map[i][j] - map[i + 1][j]) == 1) {
				// 바로 뒤가 더 높은 경우
				if (map[i][j] < map[i + 1][j]) {
					int tmp = cnt;
					cnt = 1;
					if (tmp < l) {
						road = false;
						break;
					}
					// 경사로 두기
					else {
						for (int k = 0; k < l; k++) {
							if (slope[i - k][j] == 0)
								slope[i - k][j] = 1;
							else {
								road = false;
								break;
							}
						}
					}
				}
				// 바로 뒤가 더 낮은 경우
				else {
					cnt = 1;
					int tmp = 1;
					for (int k = 1; k < l; k++) {
						if (map[i + k][j] == map[i + k + 1][j]) {
							tmp++;
						}
					}
					if (tmp < l) {
						road = false;
						break;
					}
					// 경사로 두기
					else {
						for (int k = 0; k < l; k++) {
							if (slope[i + k + 1][j] == 0)
								slope[i + k + 1][j] = 1;
							else {
								road = false;
								break;
							}
						}
					}
				}
			}
			else {
				road = false;
				break;
			}
		}
		if (road == true) {
			ans++;
//			printf("j:%d\n", j);
		}
	}

	printf("%d", ans);
	return 0;
}