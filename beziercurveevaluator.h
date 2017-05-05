
#ifndef BEZIER_CURVE_EVALUATOR_H
#define BEZIER_CURVE_EVALUATOR_H

#include "curveevaluator.h"

class BezierCurveEvaluator : public CurveEvaluator
{
public:

	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};


#endif