
#include <assert.h>
#include"catmull-rom.h"
#include "vec.h"
#include "mat.h"
#include <iostream>



const int sampleRate = 30;
const Mat4d matrix = Mat4d(
	-1, 3, -3, 1,
	3, -6, 3, 0,
	-3, 3, 0, 0,
	1, 0, 0, 0
);


void CatmullRomCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{

	ptvEvaluatedCurvePts.clear();
	int ctrlPt = ptvCtrlPts.size();
	int ctrlPtGroup = (ctrlPt - 1) / 3;
	int remainPt = ctrlPt - ctrlPtGroup * 3;


	// No corner case for wrapping
	for (int i = 0; i < ctrlPtGroup; ++i)
	{
		int pos = 3 * i;
		Vec4d px(ptvCtrlPts[pos].x, ptvCtrlPts[pos + 1].x, ptvCtrlPts[pos + 2].x, ptvCtrlPts[pos + 3].x);
		Vec4d py(ptvCtrlPts[pos].y, ptvCtrlPts[pos + 1].y, ptvCtrlPts[pos + 2].y, ptvCtrlPts[pos + 3].y);

		for (int j = 0; j < sampleRate; ++j)
		{
			float t = j / (float)sampleRate;
			Vec4d paraVec(t*t*t, t*t, t, 1);
			Point evalPoint(paraVec*matrix*px, paraVec*matrix*py);
			if (evalPoint.x < fAniLength) {
				ptvEvaluatedCurvePts.push_back(evalPoint);
			}
		}
	}

	// corner case for wrpping
	if (!bWrap)
	{
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
	else
	{
		if (remainPt != 3)
		{
			// linear interpolation 
			float y1;
			if ((ptvCtrlPts[0].x + fAniLength) - ptvCtrlPts.back().x > 0.0f)
			{
				y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts.back().x) +
					ptvCtrlPts.back().y * ptvCtrlPts[0].x) /
					(ptvCtrlPts[0].x + fAniLength - ptvCtrlPts.back().x);
			}
			else {
				y1 = ptvCtrlPts[0].y;
			}

			ptvEvaluatedCurvePts.push_back(Point(0, y1));
			ptvEvaluatedCurvePts.push_back(Point(fAniLength, y1));

		}
		else
		{
			Point firstPt(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y);

			int pos = ctrlPt - remainPt;
			Vec4d px(ptvCtrlPts[pos].x, ptvCtrlPts[pos + 1].x, ptvCtrlPts[pos + 2].x, firstPt.x);
			Vec4d py(ptvCtrlPts[pos].y, ptvCtrlPts[pos + 1].y, ptvCtrlPts[pos + 2].y, firstPt.y);
			for (int j = 0; j < sampleRate; ++j)
			{
				float t = j / (float)sampleRate;
				Vec4d paraVec(t*t*t, t*t, t, 1);
				Point evalPoint(paraVec*matrix*px, paraVec*matrix*py);

				if (evalPoint.x > fAniLength) {
					ptvEvaluatedCurvePts.push_back(Point(evalPoint.x - fAniLength, evalPoint.y));
				}
				else {
					ptvEvaluatedCurvePts.push_back(evalPoint);
				}
			}
		}
	}

	if (!bWrap || remainPt != 3)
	{
		for (int i = ctrlPt - remainPt; i < ctrlPt; ++i)
		{
			ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
		}
	}

}




