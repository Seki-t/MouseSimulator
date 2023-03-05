#pragma once
#include"Labyrinth.hpp"
#include"Global.h"
#include<Siv3D.hpp>
#include<vector>

void drawLabyrinth(Labyrinth lab,Labyrinth inner_map,double field_w,double field_h) {

	auto h_size = lab.h_size;
	auto w_size = lab.w_size;


	const auto redc = ColorF(1, 0, 0).removeSRGBCurve();
	const auto whitec = ColorF(1, 1, 1).removeSRGBCurve();
	for (auto i = h_size-1; i >= 0; i--) {

		// up
		for (auto j = 0; j < w_size; j++) {

			if (lab.isThereWall(Position(j, i), Position(0, 1))) {

				auto mieru = inner_map.isThereWall(Position(j, i), Position(0, 1));

				//Box(Vec3(0, 0, 0), Vec3(0.1, 0.5, 1)).
				//	.oriented(Quaternion::RollPitchYaw(0,0, 90_deg))
				//	.translated(j + 0.05 - field_w / 2 + 0.5, 0.25, 1.0 + i - field_h / 2).draw( mieru == 0 ? whitec : redc);

				OrientedBox(Vec3(j + 0.05 - field_w / 2 + 0.5, 0.25, 1.0 + i - field_h / 2), Vec3(0.1, 0.5, 1), Quaternion::RotateY(90_deg))
					.draw(mieru == 0 ? whitec : redc);


			}
		}
		
		
		for (int j = 0; j < w_size; j++) {
			//left
			if (lab.isThereWall(Position(j, i), Position(-1, 0))) {
				auto mieru = inner_map.isThereWall(Position(j, i), Position(-1, 0));

				/*Box(Vec3(0, 0, 0), Vec3(0.1, 0.5, 1))
					.asMesh()
					.translated(j + 0.05 - field_w / 2, 0.25,0.5 + i - field_h / 2).draw(mieru == 0 ? whitec : redc);*/

				OrientedBox(Vec3(j + 0.05 - field_w / 2, 0.25, 0.5 + i - field_h / 2), Vec3(0.1, 0.5, 1))
					.draw(mieru == 0 ? whitec : redc);

			}
			
		}
		
		//right
		if (lab.isThereWall(Position(w_size - 1, i), Position(1, 0))) {
			auto mieru = inner_map.isThereWall(Position(w_size - 1, i), Position(1, 0));

		/*	Box(Vec3(0, 0, 0), Vec3(0.1, 0.5, 1))
				.asMesh()
				.translated(1.0 + (w_size-1) + 0.05 - field_w / 2, 0.25,0.5 + i - field_h / 2).draw(mieru == 0 ? whitec : redc);*/

			OrientedBox(Vec3(1.0 + (w_size - 1) + 0.05 - field_w / 2, 0.25, 0.5 + i - field_h / 2), Vec3(0.1, 0.5, 1))
				.draw(mieru == 0 ? whitec : redc);
		}

	}
	// down
	for (int j = 0; j < w_size; j++) {

		if (lab.isThereWall(Position(j, 0), Position(0, -1))) {
			auto mieru = inner_map.isThereWall(Position(j, 0), Position(0, -1));

			/*Box(Vec3(0, 0, 0), Vec3(0.1, 0.5, 1))
				.asMesh()
				.rotated(Quaternion::Yaw(Pi / 2))
				.translated(0.5 + j + 0.05 - field_w / 2, 0.25, -field_h / 2).draw(mieru == 0 ? whitec : redc);*/

			OrientedBox(Vec3(0.5 + j + 0.05 - field_w / 2, 0.25, -field_h / 2), Vec3(0.1, 0.5, 1), Quaternion::RotateY(90_deg))
				.draw(mieru == 0 ? whitec : redc);
		}
	}

}



void drawFootMap(const std::vector<int>& nodes_cost, std::vector<Texture>& numbers) {
	
	for (int i = 0; i < my_global::plane_w; i++) {
		for (int j = 0; j < my_global::plane_h; j++) {

			auto nc = nodes_cost[i + j * my_global::plane_w];
			if (nc >=19) {
				nc = 19;
			}

			Plane(1, 1).
				moveBy(0.5 + double(i - my_global::plane_w / 2), 0, 0.5 + double(j - my_global::plane_h / 2)).
				draw(numbers[nc]);
		}
	}
}