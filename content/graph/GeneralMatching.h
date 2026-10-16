/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Matching for general graphs.
 * Fails with probability $N / mod$.
 * Time: O(N^3)
 * Status: not very well tested
 */
#pragma once

#include "../numerical/MatrixInverse-mod.h"

vector<pair<int, int>> generalMatching(int N, vector<pair<int, int>>& ed) {
	vector<vector<long long>> mat(N, vector<long long>(N)), A;
	for (pair<int, int> pa : ed) {
		int a = pa.first, b = pa.second, r = rand() % mod;
		mat[a][b] = r, mat[b][a] = (mod - r) % mod;
	}

	int r = matInv(A = mat), M = 2*N - r, fi, fj;
	assert(r % 2 == 0);

	if (M != N) do {
		mat.resize(M, vector<long long>(M));
		for (int i = 0; i < N; ++i) {
			mat[i].resize(M);
			for (int j = N; j < M; ++j) {
				int r = rand() % mod;
				mat[i][j] = r, mat[j][i] = (mod - r) % mod;
			}
		}
	} while (matInv(A = mat) != M);

	vector<int> has(M, 1); vector<pair<int, int>> ret;
	for (int it = 0; it < M/2; ++it) {
		for (int i = 0; i < M; ++i) if (has[i])
			for (int j = i+1; j < M; ++j) if (A[i][j] && mat[i][j]) {
				fi = i; fj = j; goto done;
		} assert(0); done:
		if (fj < N) ret.emplace_back(fi, fj);
		has[fi] = has[fj] = 0;
		for (int sw = 0; sw < 2; ++sw) {
			long long a = modpow(A[fi][fj], mod-2);
			for (int i = 0; i < M; ++i) if (has[i] && A[i][fj]) {
				long long b = A[i][fj] * a % mod;
				for (int j = 0; j < M; ++j) A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
			}
			swap(fi,fj);
		}
	}
	return ret;
}
