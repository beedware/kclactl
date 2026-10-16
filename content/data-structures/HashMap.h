/**
 * Author: Simon Lindholm
 * Date: 2018-01-14
 * License: CC0
 * Source: http://codeforces.com/blog/entry/62393
 * Description: Hash map with mostly the same API as \texttt{unordered\_map}, but \tilde 3x faster.
 * Initial capacity can be specified in the constructor (must be a power of two).
 * Also consider \texttt{unordered\_map<int, int>} with \texttt{reserve(1 << 16)} and \texttt{max\_load\_factor(0.25)}.
 * Time: O(1)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
// To use most bits rather than just the lowest ones:
struct chash { // large odd number for C
	const uint64_t C = (long long)(4e18 * acos(0)) | 71;
	long long operator()(long long x) const {
		return __builtin_bswap64(x*C);
	}
};
using namespace __gnu_pbds;
gp_hash_table<long long, int, chash> h({},{},{},{},{1<<16});

/** For CodeForces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = (long long)(4e18 * acos(0)) | 71; // large odd number
	long long operator()(long long x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
gp_hash_table<long long, int, chash> h({},{},{},{}, {1 << 16});
*/
