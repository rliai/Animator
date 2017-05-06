#pragma once
#ifndef CATMULLROM_CURVE_EVALUATOR_H
#define CATMULLROM_CURVE_EVALUATOR_H

#include "curveevaluator.h"

class CatmullRomCurveEvaluator : public CurveEvaluator
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