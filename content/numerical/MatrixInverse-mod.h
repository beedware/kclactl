/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The World Opens 2011
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For a non-prime mod, inverse may not exist; add gcd checks and be prepared to fail.
 * Time: O(n^3)
 * Status: tested
 */
#pragma once

#include "../number-theory/ModPow.h"

int matInv(vector<vector<long long>>& A) {
	int n = (int)A.size(); vector<int> col(n);
	vector<vector<long long>> tmp(n, vector<long long>(n));
	for (int i = 0; i < n; ++i) tmp[i][i] = 1, col[i] = i;

	for (int i = 0; i < n; ++i) {
		int r = i, c = i;
		for (int j = i; j < n; ++j) for (int k = i; k < n; ++k)
			if (A[j][k]) { r = j; c = k; goto found; }
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		for (int j = 0; j < n; ++j)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		long long v = modpow(A[i][i], mod - 2);
		for (int j = i+1; j < n; ++j) {
			long long f = A[j][i] * v % mod;
			A[j][i] = 0;
			for (int k = i+1; k < n; ++k) (A[j][k] -= f*A[i][k]) %= mod;
			for (int k = 0; k < n; ++k) (tmp[j][k] -= f*tmp[i][k]) %= mod;
		}
		for (int j = i+1; j < n; ++j) (A[i][j] *= v) %= mod;
		for (int j = 0; j < n; ++j) (tmp[i][j] *= v) %= mod;
		A[i][i] = 1;
	}

	for (int i = n-1; i > 0; --i) for (int j = 0; j < i; ++j) {
		long long v = A[j][i];
		for (int k = 0; k < n; ++k) (tmp[j][k] -= v*tmp[i][k]) %= mod;
	}

	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0)*mod;
	return n;
}
