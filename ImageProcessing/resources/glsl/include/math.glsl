const float pi = 3.1415926536;

struct Segment
{
	vec2 point0;
	vec2 point1;
};

struct IntersectionResult
{
	bool is_intersect;
	vec2 intersection_result_point;
};

float det(float a, float b, float c, float d) {
	return a * d - b * c;
}

bool between(float a, float b, double c) {
	const float EPS = 1E-4;
	return min(a, b) <= c + EPS && c <= max(a, b) + EPS;
}

IntersectionResult intersect(Segment segment1, Segment segment2)
{
	IntersectionResult return_value;
	return_value.is_intersect = false;

	vec2 a1 = segment1.point0;
	vec2 b1 = segment1.point1;
	vec2 a2 = segment2.point0;
	vec2 b2 = segment2.point1;

	float A1 = a1.y - b1.y, B1 = b1.x - a1.x, C1 = -A1*a1.x - B1*a1.y;
	float A2 = a2.y - b2.y, B2 = b2.x - a2.x, C2 = -A2*a2.x - B2*a2.y;

	float zn = det(A1, B1, A2, B2);
	if (zn != 0)
	{
		float x = -det(C1, B1, C2, B2) * 1.0 / zn;
		float y = -det(A1, C1, A2, C2) * 1.0 / zn;

		if (between(a1.x, b1.x, x) && between(a1.y, b1.y, y)
			&& between(a2.x, b2.x, x) && between(a2.y, b2.y, y))
		{
			return_value.is_intersect = true;
			return_value.intersection_result_point = vec2(x, y);
		}
	}
	return return_value;
}