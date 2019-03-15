#include <cstdio>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int selected[21];
int map[21][21];
vector<int> start;
vector<int> link;
int ans = numeric_limits<int>::max();

void MatrixSum() {

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			map[i][j] += map[j][i];
		}
	}
}

void DFS(int cur, int count) {

	// 절반을 선택했으면
	if (count == n / 2) {
		start.clear();
		link.clear();

		// 팀나누기
		for (int i = 0; i < n; i++) {
			if (selected[i] == 1)
				start.push_back(i);
			else
				link.push_back(i);
		}

		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < start.size(); i++) {
			for (int j = i + 1; j < start.size(); j++) {
				sum1 += map[start[i]][start[j]];
			}
		}
		for (int i = 0; i < link.size(); i++) {
			for (int j = i + 1; j < link.size(); j++) {
				sum2 += map[link[i]][link[j]];
			}
		}

		ans = min(ans, abs(sum1 - sum2));
		return;
	}

	// 선택된 사람은 다시 선택할 필요가 없기 때문에, cur+1부터 다시 DFS
	for (int i = cur + 1; i < n; i++) {
		if (selected[i] == 0) {
			selected[i] = 1;
			DFS(i, count + 1);
			selected[i] = 0;
		}
	}
}

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);

	MatrixSum();

	for (int i = 0; i < n; i++) {
		if (selected[i] == 0) {
			selected[i] = 1;
			DFS(i, 1);
			selected[i] = 0;	// 백트레킹
		}
	}

	printf("%d\n", ans);

	return 0;
}