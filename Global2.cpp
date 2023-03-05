#include"Global.h"
extern const float Pi;

double my_global::plane_w = 8, my_global::plane_h = 8;

Vec3 my_global::mouce_start_3d_position(0.5 - plane_w / 2, 0, 0.1 - plane_h / 2);

Vec3 my_global::convertTo3DPos(Position pos) {

	return Vec3(pos.x,pos.y, Pi * double(pos.theta) / 2.0);
}
