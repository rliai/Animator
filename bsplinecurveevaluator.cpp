
#include <assert.h>
#include "vec.h"
#include "mat.h"
#include <iostream>
#include "bsplinecurveevaluator.h"
#include "curveevaluator.h"

const int sampleRate = 30;
const Mat4d matrix = Mat4d(
-1, 3, -3, 1,
3, -6, 3, 0,
-3, 0, 3, 0,
1, 4, 1, 0)/6.0;

Point getBSpline(float t, const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{	
	Vec4d paraVec(t*t*t, t*t, t, 1);
	Vec4d px(p1.x, p2.x, p3.x, p4.x);
	Vec4d py(p1.y, p2.y, p3.y, p4.y);
	Point evalPoint(paraVec*matrix*px, paraVec*matrix*py);
	return evalPoint;
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

		newCtrlPts.push_back(ptvCtrlPts[0]);
		newCtrlPts.push_back(ptvCtrlPts[0]);
		newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		newCtrlPts.push_back(ptvCtrlPts.back());
		newCtrlPts.push_back(ptvCtrlPts.back());
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts[0].y));

	}
	else{
		Point evalPoint;

		Point startP1(ptvCtrlPts[ctrlPt - 2].x - fAniLength, ptvCtrlPts[ctrlPt - 2].y);
		Point startP2(ptvCtrlPts[ctrlPt - 1].x - fAniLength, ptvCtrlPts[ctrlPt - 1].y);
		Point endP1(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y);
		Point endP2(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y);
		for (int j = 0; j < sampleRate; ++j){
			
			evalPoint = getBSpline(j / (float)sampleRate, startP1, startP2, ptvCtrlPts[0], ptvCtrlPts[1]);
			if (evalPoint.x > 0) {
				ptvEvaluatedCurvePts.push_back(evalPoint);
			}
			if (ctrlPt != 2) {
				evalPoint = getBSpline(j / (float)sampleRate, startP2, ptvCtrlPts[0], ptvCtrlPts[1], ptvCtrlPts[2]);
				if (evalPoint.x > 0 && evalPoint.x < fAniLength) {
					ptvEvaluatedCurvePts.push_back(evalPoint);
				}
				evalPoint = getBSpline(j / (float)sampleRate, ptvCtrlPts[ctrlPt - 3], ptvCtrlPts[ctrlPt - 2], ptvCtrlPts[ctrlPt - 1], endP1);
				if (evalPoint.x > 0 && evalPoint.x < fAniLength) {
					ptvEvaluatedCurvePts.push_back(evalPoint);
				}
			}
			else {
				evalPoint = getBSpline(j / (float)sampleRate, startP2, ptvCtrlPts[0], ptvCtrlPts[1], endP1);
				if (evalPoint.x > 0 && evalPoint.x < fAniLength) {
					ptvEvaluatedCurvePts.push_back(evalPoint);
				}
			}
			evalPoint = getBSpline(j / (float)sampleRate, ptvCtrlPts[ctrlPt - 2], ptvCtrlPts[ctrlPt - 1], endP1, endP2);
			if (evalPoint.x < fAniLength) {
				ptvEvaluatedCurvePts.push_back(evalPoint);
			}
		}
		newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	if (newCtrlPts.size() >= 4){
		for (int i = 0; i < newCtrlPts.size() - 3; ++i){
			for (int j = 0; j < sampleRate; ++j){
				ptvEvaluatedCurvePts.push_back(getBSpline(j / (float) sampleRate, newCtrlPts[i], newCtrlPts[i + 1], newCtrlPts[i + 2], newCtrlPts[i + 3]));
			}
		}
	}
}