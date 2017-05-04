
#ifndef BEZIER_CURVE_EVALUATOR_H
#define BEZIER_CURVE_EVALUATOR_H

#include "curveevaluator.h"

class BezierCurveEvaluator : public CurveEvaluator
{
public:

	void evaluateCurve(const std::vector<Point>& controlPoints,
		std::vector<Point>& evaluatedPoints,
		const float& animationLength,
		const bool& beWrap) const;
};


#endif