#include <math.h>
#include "sphere.h"

Sphere::Sphere(Vec3f cen, float rad, Vec3f col):Object3D(col) {
	center = cen;
	radius = rad;
}

bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {

	float t0, t1;

	Vec3f OmC = r.getOrigin() - center;

	float a = 1;								//Dir.Dir, como Direction es unitario, equivale a 1
	float b = 2 * r.getDirection().Dot3(OmC);	// 2 * Dir.(Origin-Center)
	float c = OmC.Dot3(OmC) - radius * radius;	// (Origin-Center)^2 - Radius^2

	float det = b * b - 4 * a * c;
	if (det < 0) return false; //Si Determinante es negativo, no colisiono la esfera

	float root = sqrt(det);
	t0 = (-b - root) / (2 * a); //t0 es el menor
	t1 = (-b + root) / (2 * a); //t1 es el mayor

	//Result
	float currentMinT = h.getT();
	if (t0 >= tmin) {
		if (t0 < currentMinT) h.set(t0, Color());
		return true;
	} 
	else if (t1 >= tmin) {
		if (t1 < currentMinT) h.set(t1, Color());
		return true;
	}

	return false;
}