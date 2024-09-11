#include "group.h"

Group::Group(int objNum) {
	length = objNum;
	objArray = new Object3D * [objNum];
}

Group::~Group() {
	delete[] objArray;
}

void Group::addObject(int index, Object3D* obj) {
	objArray[index] = obj;
}

bool Group::intersect(const Ray& r, Hit& h, float tmin) {
	bool collision = false;
	for (int i = 0; i < length; i++) {
		if (objArray[i]->intersect(r, h, tmin)) collision = true;
	}
	return collision;
}
