#include <stdio.h>
#include <math.h>
// x^2 = y
#define E 0.000001
#define E2 0.000000001
double binary_enum(double y)
{
	if (y <= 0) {
		return -1;
	}
	double low = 0;
	double hig = y;
	double mid = -2;
	while (fabs(hig - low) > E && low <= hig) {
		mid = (low + hig) / 2;
		double dd = mid * mid;
		if (fabs(dd - y) < E) {
			return mid;
		} else if (dd > y) {
			hig = mid - E2;
		} else if (dd < y) {
			low = mid + E2;
		}
	}
	return mid;
}

int main(void)
{
	double y;
	while (scanf("%lf", &y) != -1) {
		double x = binary_enum(y);
		printf("y:%lf,sqrt(y):%lf\n", y, x);
	}
}
