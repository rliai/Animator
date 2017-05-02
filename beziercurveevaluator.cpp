
#include <assert.h>
#include"beziercurveevalutaor.h"
#include "vec.h"
#include "mat.h"


const int sampleRate = 30;
const Mat4d matrix = Mat4d(
	-1, 3, -3, 1,
	3, -6, 3, 0,
	-3, 3, 0, 0,
	1, 0, 0, 0
	);

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{	
	int iCtrlPtCount = ptvCtrlPts.size();
	for (int i = 0; i  < iCtrlPtCount - 3; i += 3) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i + 3]);

		// ignore Z value because it is a plane
		Vec4d px(ptvCtrlPts[i].x, ptvCtrlPts[i + 1].x, ptvCtrlPts[i + 2].x, ptvCtrlPts[i + 3].x);
		const Vec4d py(ptvCtrlPts[i].y, ptvCtrlPts[i + 1].y, ptvCtrlPts[i + 2].y, ptvCtrlPts[i + 3].y);

		for (int j = 0; j < sampleRate; ++j) {
			double t = 1 / (double)sampleRate;
			Vec4d paraVec(t * t * t, t * t, t, 1);
			Point evalPoint(paraVec*matrix*px, paraVec*matrix*py);

			if (!bWrap) {
				ptvEvaluatedCurvePts.push_back(evalPoint);
			}		
		}	
	}

	
	for (int i = iCtrlPtCount - 3; i < iCtrlPtCount; ++i) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
	}
	
	/*
	if (!bWrap)
	{
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
	*/

	
}
