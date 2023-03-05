#pragma once
//global
#include<Siv3D.hpp>
#include"Position.hpp"


namespace my_global {

	extern double plane_w,plane_h;
	extern Vec3 mouce_start_3d_position;

	Vec3 convertTo3DPos(Position pos);

}