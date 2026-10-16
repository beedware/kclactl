/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description: Calculates determinant using modular arithmetics.
 * Modulos can also be removed to get a pure-integer version.
 * Time: $O(N^3)$
 * Status: bruteforce-tested for N <= 3, mod <= 7
 */
#pragma once

const long long mod = 12345;
long long det(vector<vector<long long>>& a) {
	int n = (int)a.size(); long long ans = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			while (a[j][i] != 0) { // gcd step
				long long t = a[i][i] / a[j][i];
				if (t) for (int k = i; k < n; ++k)
					a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i] % mod;
		if (!ans) return 0;
	}
	return (ans + mod) % mod;
}
