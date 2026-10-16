/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: To get all uniquely determined values of $x$ for an invertible system $Ax = b$,
 * do Gauss-Jordan elimination:
 */
#pragma once

#include "SolveLinear.h"

for (int j = 0; j < n; ++j) if (j != i) // instead of j = i+1..n
// ... then at the end:
x.assign(m, undefined);
for (int i = 0; i < rank; ++i) {
	for (int j = rank; j < m; ++j) if (fabs(A[i][j]) > eps) goto fail;
	x[col[i]] = b[i] / A[i][i];
fail:; }
