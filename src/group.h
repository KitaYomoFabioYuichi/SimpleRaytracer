#ifndef _GROUP_
#define _GROUP_

#include "object3d.h"

class Group :public Object3D {
public:
	Group(int objNum);
	~Group();
	void addObject(int index, Object3D* obj);
	bool intersect(const Ray& r, Hit& h, float tmin);
private:
	int length;
	Object3D** objArray;
};

#endif