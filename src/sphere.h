#ifndef _SPHERE_
#define _SPHERE_

#include "object3d.h"

class Sphere: public Object3D {
public:
	Sphere(Vec3f ce, float rad, Vec3f col);
	~Sphere() {}
	bool intersect(const Ray& r, Hit& h, float tmin);
private:
	Vec3f center;
	float radius;
};

#endif