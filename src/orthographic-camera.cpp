#include "orthographic-camera.h"

Vec3f projection(Vec3f base, Vec3f vector) {
	return base * (vector.Dot3(base) / base.Dot3(base));
}

OrthographicCamera::OrthographicCamera(Vec3f c, Vec3f pd, Vec3f up, float s) {
	center = c;

	projectionDir = pd;
	projectionDir.Normalize();

	upDir = up - projection(projectionDir, up);
	upDir.Normalize();

	Vec3f::Cross3(horizontalDir, projectionDir, upDir);
	horizontalDir.Normalize();

	size = s;
}

Ray OrthographicCamera::generateRay(Vec2f point) {
	Vec3f origin = center + horizontalDir * size * (point.x() - 0.5) + upDir * size * (point.y() - 0.5);
	return Ray(projectionDir, origin);
}
