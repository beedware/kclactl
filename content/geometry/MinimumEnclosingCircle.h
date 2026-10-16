/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum enclosing circle of a set of points.
 * Time: Expected O(n)
 * Status: stress-tested
 */
#pragma once

#include "circumcircle.h"

pair<P, double> mec(vector<P> ps) {
	shuffle(ps.begin(), ps.end(), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	auto out = [&](P p) { return (o - p).dist() > r * EPS; };
	for (int i = 0; i < (int)ps.size(); ++i) if (out(ps[i])) {
		o = ps[i], r = 0;
		for (int j = 0; j < i; ++j) if (out(ps[j])) {
			o = (ps[i] + ps[j]) / 2, r = (o - ps[i]).dist();
			for (int k = 0; k < j; ++k) if (out(ps[k])) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}
