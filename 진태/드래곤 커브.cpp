#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

int map[101][101];
int n;
int x, y, d, g;
int ans = 0;

stack<int> dragon;
stack<int> cal;
stack<int> tmp1;
queue<int> tmp2;


int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

int main() {

	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			map[i][j] = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x, &y, &d, &g);

		// Solve
		/* 
		여기서 queue랑 stack으로 계산을 좀 복잡하게 했는데 그냥 vector써서 인덱스 잘 조절하면 더 짧게 될 거같다.
		드래곤 커브 그리는 원리

		방향을 숫자로 나타낸다
		0:Right, 1:Up, 2:Left, 3:Down

		0으로 시작한다고 가정하면 시작점으로 부터 이렇게 그려진다
		0세대: 0
		1세대: 0 1
		2세대: 0 1 2 1
		3세대: 0 1 2 1 2 3 2 1
		4세대: 0 1 2 1 2 3 2 1 2 3 0 3 2 3 2 1

		이전 세대에서 역순으로 (x + 1) % 4 해준 후, 나열하면 된다.
		
		저걸 먼저 계산한 후, 시작점으로부터 차례대로 그리면 완성
		*/
		map[x][y] = 1;	// 시작점 표시
		dragon.push(d);

		// 드래곤 커브 방향 만들기
		for (int j = 0; j < g; j++) {
			
			while (!dragon.empty()) {
				int value = dragon.top();
				dragon.pop();

				tmp1.push(value);

				value = (value + 1) % 4;
				tmp2.push(value);
			}

			// 방향 정렬
			while (!tmp1.empty()) {
				dragon.push(tmp1.top());
				tmp1.pop();
			}
			while (!tmp2.empty()) {
				dragon.push(tmp2.front());
				tmp2.pop();
			}
		}
		while (!dragon.empty()) {
			cal.push(dragon.top());
			dragon.pop();
		}

		// 좌표 계산
		while (!cal.empty()) {
			int index = cal.top();
			cal.pop();
		
			x = x + dx[index];
			y = y + dy[index];

			map[x][y] = 1;
		}
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j] == 1 && map[i + 1][j + 1] == 1)
				ans++;
		}
	}

	printf("%d", ans);
	return 0;
}