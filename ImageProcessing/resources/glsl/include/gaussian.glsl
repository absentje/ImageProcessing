const float pi = 3.1415926536;

float Gaussian(float sigma, float x, float y)
{
	return exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2.0 * pi * sigma * sigma);
}

int getGaussianKernelSize(float sigma)
{
	// r = 3*sigma
//	int k = 6 * sigma + 1; // k = 2 * r + 1;
	int k = int(6 * sigma + 1);
	return k + (1 - k % 2);	// на выходе нечетное число
}


// sigma - среднеквадратичное отклонение,
// x0, y0 - отступы
float Gaussian1D(float sigma, float x0, float x)
{
	float A = 1.0 / (sigma * sqrt(2 * pi));
	return A * exp(-0.5 * pow((x - x0) / sigma, 2.0));
}

float Gaussian2D(float sigma_x, float sigma_y, float x0, float y0, float x, float y)
{
	float A = 1 / (2 * pi * sigma_x * sigma_y);

	return A * exp(-0.5 * (pow((x - x0) / sigma_x, 2.0) + pow((y - y0) / sigma_y, 2.0)) );
}

// гауссиана без амплитуды
float NormalizedGaussian1D(float sigma, float x0, float x)
{
	return exp(-0.5 * pow((x - x0) / sigma, 2.0));
}

float NormalizedGaussian2D(float sigma_x, float sigma_y, float x0, float y0, float x, float y)
{
	return exp(-0.5 * (pow((x - x0) / sigma_x, 2.0) + pow((y - y0) / sigma_y, 2.0)) );
}
/////

float f(float r, float sigma, float focus, float k1, float k2)
{
	// y1 = k1 * x;
	// y2 = k2 * x;
	// lim(f(r, focus) / r) = k1
	//	r->+∞
	// lim(f(r, focus) / r) = k1
	//	r->-∞
	// lim f(r, focus) = k2 * focus
	//	r->focus

	//	f1 = NormalizedGaussian1D(sigma, focus, r);
	//	f = mix(k1 * r, k2 * r, f1);

	float f1 = NormalizedGaussian1D(sigma, focus, r);

	return mix(k1 * r, k2 * r, f1);
}