#include "Curve.h"

bool Curve::intersect(int x, int y)
{
	return intersectsPoint(x, y) != nullptr;
}

void Curve::AddTranslation(int x, int y, ofVec3f _draggedPixelVector)
{
	ofPoint tmp;
	tmp.x = x - this->getTranslation().x;
	tmp.y = y - this->getTranslation().y;

	ofPoint closestPoint = curve.getClosestPoint(tmp);
	ofPoint * inersected = intersectsPoint(tmp.x, tmp.y);

	if (inersected != nullptr)
	{
		inersected->x = x - this->getTranslation().x;
		inersected->y = y - this->getTranslation().y;
		inersected = nullptr;
	}
	else if (distanceBetweenPoints(tmp.x, tmp.y, closestPoint.x, closestPoint.y) < 10)
		Object2D::AddTranslation(x, y, _draggedPixelVector);
}

ofPoint * Curve::intersectsPoint(int x, int y)
{
	for (ofPoint & p : points)
	{
		if (abs(p.x - x) <= 10 && abs(p.y - y) <= 10)
			return &p;
	}

	return nullptr;
}

bool Curve::isPointInCurve(int x, int y)
{
	if (x >= points[points.size() - 1].x)
		return false;

	int treshold = 5;
	int index1, index2 = 0;
	while (points[index2].x < x && index2 < points.size())
	{
		index2++;
	}
	if (index2 == 0)
	{
		return false;
	}
	index1 = index2 - 1;

	return distanceBetweenPoints(points[index1].x, points[index1].y, x, y) +
		distanceBetweenPoints(x, y, points[index2].x, points[index2].y) -
		distanceBetweenPoints(points[index1].x, points[index1].y, points[index2].x, points[index2].y) <=
		treshold;
}

float Curve::distanceBetweenPoints(const float & x1, const float & y1, const float & x2, const float & y2) const
{
	return (float) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
