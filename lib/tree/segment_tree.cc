#include <vector>
#include <functional>

template <typename T>
struct segment_tree
{
	int n, i, j, k, init;
	std::vector<T> st;
	std::function<T(T &,T &)> opr = [&](T & a, T & b) {
		return a + b;
	};
	
	segment_tree(const int N, auto _opr = opr, T _init = 0)
	: opr(_opr), init(_init) {
		n = 1 << 32 - __builtin_clz(N - 1);
		st.resize(n << 1, init);
	}
	segment_tree(const vector<T> & a, auto _opr = opr, T _init = 0)
	: segment_tree(a.size(), _opr, _init) {
		for (i = 0; i < a.size(); ++i)
			st[i + n] = a[i];
		for (i = n - 1; i > 0; --i)
			st[i] = opr(st[i << 1], st[i << 1 | 1]);
	}
	void update(int p, T x) {
		i = 1, j = 0, k = n;
		while (i > 0) {
			if (j < p && p <= j + k - 1)
				i <<= 1, k >>= 1;
			else {
				if (k == 1) st[i] += x;
				while (i & 1) {
					st[i >> 1] = opr(st[i], st[i ^ 1]);
					i >>= 1, j -= k, k <<= 1;
				}
				if (i) i |= 1, j += k;
			}
		}
	}
	T query(int s, int e) {
		T res = init;
		i = 1, j = 0, k = n;
		while (i > 0) {
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