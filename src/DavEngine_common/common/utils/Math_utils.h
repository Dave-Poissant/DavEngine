#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class MathUtils
{
public:
	MathUtils() {};
	~MathUtils() {};

	void CalcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy);
	int Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
};

#endif // !_MATH_UTILS_H_
