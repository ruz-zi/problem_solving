// https://boj.kr/2668

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	int a[101], visited[101]{};
	vector<int> ans;
	function<int(int)> dfs = [&](int v) {
		visited[v] = 1;
		if (visited[a[v]] == 2) {
			visited[v] = 2;
			return 0;
		}
		if (visited[a[v]] == 1) {
			visited[v] = 2;
			ans.push_back(v);
			if (v == a[v]) return 0;
			return a[v];
		}
		int x = dfs(a[v]);
		visited[v] = 2;
		if (x == 0) return 0;
		ans.push_back(v);
		if (x == v) return 0;
		return x;
	};
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) if (visited[i] == 0) dfs(i);
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int i : ans) cout << i << '\n';

	return 0;
}