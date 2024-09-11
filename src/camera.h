#ifndef _CAMERA_
#define _CAMERA_

#include "object3d.h"

class Camera {
public:
	virtual Ray generateRay(Vec2f point) = 0;
};

#endif