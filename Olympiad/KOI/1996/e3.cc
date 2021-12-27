// https://boj.kr/2669

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int a[100][100]{};
	int x1, y1, x2, y2;
	for (int i = 0; i < 4; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		for (int x = x1; x < x2; ++x) {
			for (int y = y1; y < y2; ++y) {
				a[x][y] = 1;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i < 100; ++i) {
		for (int j = 1; j < 100; ++j) {
			ans += a[i][j];
		}
	}
	cout << ans << endl;

	return 0;
}