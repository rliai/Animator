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
	void evaluateCurve(const std::vector<Point>& controlPoints,
		std::vector<Point>& evaluatedPoints,
		const float& animationLength,
		const bool& beWrap) const override;
};

#endif