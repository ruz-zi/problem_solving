// https://boj.kr/2667

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<string> a(n);
	vector<int> ans;
	auto bfs = [&](int y, int x) {
		queue<pair<int, int>> q;
		q.emplace(y, x);
		a[y][x] = '0';
		int cnt = 0;
		while (q.size()) {
			cnt++;
			tie(y, x) = q.front(); q.pop();
			for (int w = 0; w < 4; ++w) {
				int ny = y + "1201"[w] - '1';
				int nx = x + "2110"[w] - '1';
				if (ny >= 0 && nx >= 0 && ny < n && nx < n && a[ny][nx] == '1') {
					q.emplace(ny, nx);
					a[ny][nx] = '0';
				}
			}
		}
		return cnt;
	};
	for (auto & i : a) cin >> i;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (a[i][j] == '1') ans.push_back(bfs(i, j));
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int i : ans) cout << i << '\n';

	return 0;
}