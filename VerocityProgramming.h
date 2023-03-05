#pragma once

#include<Siv3D.hpp>
extern const float Pi;

class VerocityProgramming {
private:

	double start_time, end_time;	//excute_time ( function tekiyou zikan)
	Vec3 start_pos, end_pos;
	Vec3 velocity;

	double passed_time;

public:

	VerocityProgramming(Vec3 s_pos,Vec3 e_pos, double s_time,double e_time):
		start_pos{s_pos},
		end_pos{e_pos},
		start_time{ s_time },
		end_time{ e_time },
		passed_time{ 0 } {
			
		Vec3 diff = end_pos - start_pos;
		
		if (diff.z > Pi) {
			diff.z = -(2 * Pi - diff.z);
		}
		else if (diff.z < -Pi) {
			diff.z = 2 * Pi + diff.z;
		}
		velocity = diff / (end_time - start_time);
	
	
	}


	Vec3 calcReferencePosition(double now_time) {

		Vec3 next_pos = start_pos + velocity * (now_time - start_time);
		return next_pos;
	}


	bool isEnd(double passed_time) {
		return passed_time >= end_time;
	}
};