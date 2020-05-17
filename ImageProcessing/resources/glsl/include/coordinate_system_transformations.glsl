vec2 coordinate_transformation(vec2 new_center_coordinate_system, vec2 xy)
{
	return vec2(xy.x - new_center_coordinate_system.x, xy.y - new_center_coordinate_system.y);
}

float get_angle(vec2 vec)
{
	float sign = 1.0;
	if (vec.y <= 0)
		sign = -1;

	// (a,b) = |a| * |b| * cos(a,b)

	vec2 a = vec2(1.f, 0.f);
	vec2 b = vec;

	float l1 = length(a);
	float l2 = length(b);

	float cos_a_b = dot(a, b) / l1 / l2;

	return sign * acos(cos_a_b);

//	return atan2(vec.y(), vec.x());
}

vec2 to_polar_coordinate_system(vec2 xy)
{
	float x = xy.x;
	float y = xy.y;
	float fi;
	fi = get_angle(vec2(x, y));//atan(y, x);
	float r = sqrt(x * x + y * y);
	return vec2(r, fi);
}
vec2 from_polar_coordinate_system(float r, float fi)
{
	float x = r * cos(fi);
	float y = r * sin(fi);
	return vec2(x, y);
}