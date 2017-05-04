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
	void evaluateCurve(const std::vector<Point>& controlPoints,
		std::vector<Point>& evaluatedPoints,
		const float& animationLength,
		const bool& beWrap) const override;	
};


#endif