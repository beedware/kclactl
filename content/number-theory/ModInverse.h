/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Inverses of $1$ through $LIM-1$ for prime mod,
 * with $2\le LIM\le \text{mod}$. Products must fit in ll.
 * Time: O(LIM)
 * Status: Works
 */
#pragma once

// const ll mod = 1000000007, LIM = 200000; ///include-line
vector<ll> inv(LIM); inv[1] = 1;
rep(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
