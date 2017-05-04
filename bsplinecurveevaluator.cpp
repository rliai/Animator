
#include <assert.h>
#include "vec.h"
#include "mat.h"
#include <iostream>
#include "bsplinecurveevaluator.h"
#include "curveevaluator.h"
#include"beziercurveevaluator.h"


const int sampleRate = 30;
const Mat4d matrix = Mat4d(
	-1, 3, -3, 1,
	3, -6, 3, 0,
	-3, 3, 0, 0,
	1, 0, 0, 0
)/6.0;

Point calculateBSpline(float t, const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	Point result;
	Vec4f T(t*t*t, t*t, t, 1);
	Mat4f M(-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 0, 3, 0,
		1, 4, 1, 0);
	Vec4f Gx(p1.x, p2.x, p3.x, p4.x);
	Vec4f Gy(p1.y, p2.y, p3.y, p4.y);

	result.x = (T*M)*Gx / 6;
	result.y = (T*M)*Gy / 6;
	return result;
}


void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	ptvEvaluatedCurvePts.clear();
	int ctrlPt = ptvCtrlPts.size();
	vector<Point> newCtrlPts;

	if (!bWrap) {


		newCtrlPts.push_back(ptvCtrlPts.front());
		newCtrlPts.push_back(ptvCtrlPts.front());
		newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		newCtrlPts.push_back(ptvCtrlPts.back());
		newCtrlPts.push_back(ptvCtrlPts.back());
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.front().y));

	}
	else
	{
		Point evalPoint;
		Point endP1(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y);
		Point endP2(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y);
		Point startP1(ptvCtrlPts[ptvCtrlPts.size() - 2].x - fAniLength, ptvCtrlPts[ptvCtrlPts.size() - 2].y);
		Point startP2(ptvCtrlPts[ptvCtrlPts.size() - 1].x - fAniLength, ptvCtrlPts[ptvCtrlPts.size() - 1].y);	
		for (int j = 0; j <= sampleRate; ++j)
		{
			evalPoint = calculateBSpline((float)j / sampleRate, startP1, startP2, ptvCtrlPts[0], ptvCtrlPts[1]);
			if (evalPoint.x >= 0)ptvEvaluatedCurvePts.push_back(evalPoint);
			evalPoint = calculateBSpline((float)j / sampleRate, startP2, ptvCtrlPts[0], ptvCtrlPts[1], ptvCtrlPts[2]);
			if (evalPoint.x >= 0 && evalPoint.x <= fAniLength)ptvEvaluatedCurvePts.push_back(evalPoint);
			evalPoint = calculateBSpline((float)j / sampleRate, ptvCtrlPts[ptvCtrlPts.size() - 3], ptvCtrlPts[ptvCtrlPts.size() - 2], ptvCtrlPts[ptvCtrlPts.size() - 1], endP1);
			if (evalPoint.x >= 0 && evalPoint.x <= fAniLength)ptvEvaluatedCurvePts.push_back(evalPoint);
			Point evalPoint;
			evalPoint = calculateBSpline((float)j / sampleRate, ptvCtrlPts[ptvCtrlPts.size() - 2], ptvCtrlPts[ptvCtrlPts.size() - 1], endP1, endP2);
			if (evalPoint.x <= fAniLength)ptvEvaluatedCurvePts.push_back(evalPoint);
			newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());

	}

	if (newCtrlPts.size() >= 4)
	{
		for (int i = 0; i < newCtrlPts.size() - 3; ++i)
		{
			for (int j = 0; j <= sampleRate; ++j)
			{
				ptvEvaluatedCurvePts.push_back(calculateBSpline((float)j / sampleRate, newCtrlPts[i], newCtrlPts[i + 1], newCtrlPts[i + 2], newCtrlPts[i + 3]));
			}
		}
	}



}