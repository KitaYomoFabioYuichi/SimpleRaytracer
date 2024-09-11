#ifndef _ORTHOGRAPHIC_CAMERA_
#define _ORTHOGRAPHIC_CAMERA_

#include "camera.h"

class OrthographicCamera :public Camera {
public:
	OrthographicCamera(Vec3f c, Vec3f pd, Vec3f up, float s);
	~OrthographicCamera() {}
	Ray generateRay(Vec2f point);
private:
	Vec3f center;
	Vec3f projectionDir;
	Vec3f upDir;
	Vec3f horizontalDir;
	float size;
};

#endif
