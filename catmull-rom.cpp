
#include <assert.h>
#include "vec.h"
#include "mat.h"
#include <iostream>
#include "catmull-rom.h"
#include "curveevaluator.h"

const int sampleRate = 30;
const Mat4d matrix = Mat4d(
	-1, 3, -3, 1,
	2, -5, 4, -1,
	-1, 0, 1, 0,
	0, 2, 0, 0) / 2.0;

Point getcatmull(float t, const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	Vec4d paraVec(t*t*t, t*t, t, 1);
	Vec4d px(p1.x, p2.x, p3.x, p4.x);
	Vec4d py(p1.y, p2.y, p3.y, p4.y);
	Point evalPoint(paraVec*matrix*px, paraVec*matrix*py);
	return evalPoint;
}

void CatmullRomCurveEvaluator :: evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	ptvEvaluatedCurvePts.clear();
	vector<Point> newCtrlPts;
	Point evalPoint;
	int ctrlPt = ptvCtrlPts.size();

	if (!bWrap){
		newCtrlPts.push_back(Point(0, ptvCtrlPts[0].y));
		newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		newCtrlPts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
	else{

		Point startP1(ptvCtrlPts[ctrlPt - 2].x - fAniLength, ptvCtrlPts[ctrlPt - 2].y);
		Point startP2(ptvCtrlPts[ctrlPt - 1].x - fAniLength, ptvCtrlPts[ctrlPt - 1].y);
		Point endP1(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y);
		Point endP2(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y);

		newCtrlPts.push_back(startP1);
		newCtrlPts.push_back(startP2);
		newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		newCtrlPts.push_back(endP1);
		newCtrlPts.push_back(endP2);
	}

	for ( int i = 0; i < newCtrlPts.size() - 3; ++i){
		for (int j = 0; j < sampleRate; ++j){
			evalPoint = getcatmull(j / (float)sampleRate, newCtrlPts[i], newCtrlPts[i + 1], newCtrlPts[i + 2], newCtrlPts[i + 3]);
			if (ptvEvaluatedCurvePts.empty() || evalPoint.x > ptvEvaluatedCurvePts.back().x)
				ptvEvaluatedCurvePts.push_back(evalPoint);
		}
	}

	if (!bWrap)
	{
		if ( ptvEvaluatedCurvePts.back().x < ptvCtrlPts.back().x )
			ptvEvaluatedCurvePts.push_back(ptvCtrlPts.back());
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
}

