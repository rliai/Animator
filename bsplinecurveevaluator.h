#pragma once
#ifndef BSPLINE_CURVE_EVALUATOR_H
#define BSPLINE_CURVE_EVALUATOR_H

#include "curveevaluator.h"

class BSplineCurveEvaluator : public CurveEvaluator
{
public:
	/*
	* Override to get a bezier curve according to control Points
	*/
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};


#endif