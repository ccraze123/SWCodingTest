#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int map[21][21];
int n;
int ans = 0;

// 디버깅용 맵 프린트
void Print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%4d", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// 맵 복사 함수
void MapCopy(int copy[][21], int orig[][21]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			copy[i][j] = orig[i][j];
}

// 옮기기 전이랑 같은지 검사, 같으면 true
bool IsSame(int a[][21], int b[][21]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != b[i][j])
				return false;
		}
	}
	return true;
}

// 방향대로 옮기면서 합쳐주는 함수
bool Move(int direction) {
	int prevMap[21][21];
	MapCopy(prevMap, map);	// 움직이기전 맵 복사

	int tmp[21];	// 임지 저장소

	// Direction - 0:up, 1:down, 2:left, 3:right
	switch (direction) {
	case 0:	// Up
		for (int j = 0; j < n; j++) {	// 계산 배열 초기화
			for (int k = 0; k < 21; k++)
				tmp[k] = 0;
			int idx = 0;				// 계산 배열 index 생성
			int prev = map[0][j];
			tmp[idx] = prev;

			// 합치기
			for (int i = 1; i < n; i++) {
				if (map[i][j] == 0)	// 0 무시
					continue;
				else if (prev == map[i][j]) {	// 이전거와 같으면 더해서 tmp에 저장, 중복 덧셈을 막기 위해 인덱스 이동
					tmp[idx++] = prev + map[i][j];
					i++;
				}
				else {
					/*
						예를 들어 위로 옮기는데
						0 0 0
						2 0 0
						2 0 0
						일때, 위에서 0번째 자리 값을 tmp에 첫번째 값으로 넣어놔서 0이 들어가 있고,
						아래 조건이 없으면 0을 빈자리가 아닌 값으로 인식해 버려서 tmp에 4 0 0이 아닌 0 4 0이 들어가게 됨
					*/
					if (tmp[idx] != 0)
						idx++;
				}

				// 인덱스를 추가하다보면 맵 범위를 넘을 때가 있어서 조건 추가
				if (i < n) {
					prev = map[i][j];
					tmp[idx] = prev;
				}
			}

			// map으로 적용
			for (int i = 0; i < n; i++)
				map[i][j] = tmp[i];
		}
//		Print();
		break;
	// case 1~3은 인덱스 계산만 다르게 하고, 계산 메커니즘은 동일
	case 1:	// Down
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 21; k++)	// 계산 배열 초기화
				tmp[k] = 0;
			int idx = 0;					// 계산 배열 index 생성
			int prev = map[n - 1][j];
			tmp[idx] = prev;

			// 합치기
			for (int i = n - 2; i >= 0; i--) {
				if (map[i][j] == 0)
					continue;
				else if (prev == map[i][j]) {
					tmp[idx++] = prev + map[i][j];
					i--;
				}
				else {
					if(tmp[idx] != 0)
						idx++;
				}

				if (i >= 0) {
					prev = map[i][j];
					tmp[idx] = prev;
				}
			}

			// map으로 적용
			for (int i = 0; i < n; i++)
				map[n - 1 - i][j] = tmp[i];
		}
//		Print();
		break;
	case 2:	// Left
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < 21; k++)	// 계산 배열 초기화
				tmp[k] = 0;
			int idx = 0;					// 계산 배열 index 생성
			int prev = map[i][0];
			tmp[idx] = prev;

			// 합치기
			for (int j = 1; j < n; j++) {
				if (map[i][j] == 0)
					continue;
				else if (prev == map[i][j]) {
					tmp[idx++] = prev + map[i][j];
					j++;
				}
				else {
					if (tmp[idx] != 0)
						idx++;
				}

				if (j < n) {
					prev = map[i][j];
					tmp[idx] = prev;
				}
			}

			// map으로 적용
			for (int j = 0; j < n; j++)
				map[i][j] = tmp[j];
		}
//		Print();
		break;
	case 3:	// Right
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < 21; k++)	// 계산 배열 초기화
				tmp[k] = 0;
			int idx = 0;					// 계산 배열 index 생성
			int prev = map[i][n-  1];
			tmp[idx] = prev;

			// 합치기
			for (int j = n - 2; j >= 0; j--) {
				if (map[i][j] == 0)
					continue;
				else if (prev == map[i][j]) {
					tmp[idx++] = prev + map[i][j];
					j--;
				}
				else {
					if (tmp[idx] != 0)
						idx++;
				}

				if (j >= 0) {
					prev = map[i][j];
					tmp[idx] = prev;
				}
			}

			// map으로 적용
			for (int j = 0; j < n; j++)
				map[i][n - 1 - j] = tmp[j];
		}
//		Print();
		break;
	}

	return IsSame(prevMap, map);	// 원래 가지치기할 때 사용하려 했으나, 안해도 1초안에 해결되서 사용 안함
}

// 최댓값 블록 찾기
void FindMax() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = max(ans, map[i][j]);
		}
	}
}

void DFS(int cnt) {
	int restore[21][21];

	// 종료 조건
	if (cnt == 5) {
		FindMax();
		return;
	}

	for (int i = 0; i < 4; i++) {
		MapCopy(restore, map);
		Move(i);	// 움직이고
		DFS(cnt + 1);
		MapCopy(map, restore);	// 백트레킹
	}
}

int main() {
	int restore[21][21];

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	if (n == 1)
		ans = map[0][0];
	else {
		for (int i = 0; i < 4; i++) {
			MapCopy(restore, map);
			Move(i);	// 움직이고
			DFS(1);
			MapCopy(map, restore);	// 백트레킹
		}
	}

	printf("%d", ans);
	return 0;
}