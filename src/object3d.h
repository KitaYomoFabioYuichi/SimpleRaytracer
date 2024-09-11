#ifndef _OBJECT_3D_
#define _OBJECT_3D_

#include "vectors.h"
#include "ray.h"
#include "hit.h"

class Object3D {
public:
	Object3D() { color = Vec3f(); }
	Object3D(Vec3f c) { color = c; }
	~Object3D() {}
	
	Vec3f Color() { return color; }

	virtual bool intersect(const Ray& r, Hit& h, float tmin) = 0;

private:
	Vec3f color;
};

#endif