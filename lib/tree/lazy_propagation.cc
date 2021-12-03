#include <vector>
#include <functional>
template <typename T>
struct segment_tree
{
	int n, i, j, k;
	std::vector<T> st;
	std::vector<T> lz;
	std::function<T(T &,T &)> opr = [&](T & a, T & b) {
		return a + b;
	};
	std::function<void(void)> ppg = [&]() {
		if (lz[i]) {
			st[i] += lz[i] * k;
			if (i < n) {
				lz[i << 1] += lz[i];
				lz[i << 1 | 1] += lz[i];
			}
			lz[i] = 0;
		}
	};
	
	segment_tree(const int N) {
		n = 1 << 32 - __builtin_clz(N - 1);
		st.resize(n << 1);
		lz.resize(n << 1);
	}
	segment_tree(const vector<T> & a) : segment_tree(a.size()) {
		for (i = 0; i < a.size(); ++i)
			st[i + n] = a[i];
		for (i = n - 1; i > 0; --i)
			st[i] = opr(st[i << 1], st[i << 1 | 1]);
	}
	void update(int s, int e, T x) {
		i = 1, j = 0, k = n;
		while (i > 0) {
			ppg();
			if (j < s && s <= j + k - 1 || j <= e && e < j + k - 1)
				i <<= 1, k >>= 1;
			else {
				if (s <= j && j + k - 1 <= e) lz[i] += x, ppg();
				while (i & 1) {
					st[i >> 1] = st[i] + st[i ^ 1];
					i >>= 1, j -= k, k <<= 1;
				}
				if (i) i |= 1, j += k;
			}
		}
	}
	T query(int s, int e) {
		T res = 0;
		i = 1, j = 0, k = n;
		while (i > 0) {
			ppg();
			if (j < s && s <= j + k - 1 || j <= e && e < j + k - 1)
				i <<= 1, k >>= 1;
			else {
				if (s <= j && j + k - 1 <= e) res = opr(res, st[i]);
				while (i & 1) i >>= 1, j -= k, k <<= 1;
				if (i) i |= 1, j += k;
			}
		}
		return res;
	}
};