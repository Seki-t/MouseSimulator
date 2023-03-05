
# include <Siv3D.hpp>
#include"Labyrinth.hpp"
#include"SivDrawer.h"
#include"Mouce3D.h"
#include"KizunaAI.hpp"
#include"Measure.hpp"
#include"VerocityProgramming.h"
#include"Global.h"

const float Pi = 3.14f;
//# include <Siv3D.hpp>

void Main()
{
		Window::Resize(1280, 720);
		double now_time = 0;	//現在時刻
		
		//Map Settings
		Labyrinth my_labyrinth("save_map.txt");
		Labyrinth inner_map(my_labyrinth.w_size, my_labyrinth.h_size);

		std::vector<Position> goal_positions;
		goal_positions.emplace_back(5, 5);


		// Mouce Settings
		Mouce3D my_mouce(my_global::mouce_start_3d_position, Position(0, 0, 0));

		KizunaAI ai(goal_positions, inner_map);

		//壁を発見する役割
		Measure goro;

		//初期位置と初期進行方向の設定
		auto first_new_walls = goro.virtual_sensing(my_mouce.getPosition(), my_labyrinth);
		ai.updateMap(first_new_walls);
		auto first_ref_pos = ai.calcNextPos(my_mouce.getPosition());

		VerocityProgramming vec_prog(my_mouce.getContinuousPosition(), my_global::convertTo3DPos(first_ref_pos), now_time, 20);


		//for debug
		bool continue_flag = false;
		bool camera_mode = true;


		//レンダリング準備
		const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
		const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

		
				
		DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 0, 24, -6 }, Vec3{ 0, 16, -5 } };
		
		auto start_con_pos = my_mouce.getContinuousPosition();
		auto start_pos_3d = my_mouce.get3DPosition();

		Vec3 start_camera_pos = start_pos_3d + Vec3(-1.5 * cos(start_con_pos.z), 1, -1.5 * sin(start_con_pos.z));
		Vec3 start_camera_lookat = start_pos_3d + Vec3(0.3 * cos(start_con_pos.z), 0.1, 0.3 * sin(start_con_pos.z));	//今向いてる方向にちょっと進んだ方向

		BasicCamera3D robot_camera{ renderTexture.size(), 30_deg, start_camera_pos, start_camera_lookat };

		//Texture素材
		const Image image_map(U"num_tex.png");
		std::vector<Texture> number_textures;	//map chip textures
		Font font(10);

		//歩数表示用のマップチップテクスチャ生成
		for (int i = 0; i < 20; i++) {

			auto cliped_image = image_map.clipped((i % 10) * 100, (i / 10) * 100, 100, 100);
			number_textures.push_back(Texture(cliped_image, TextureDesc::MippedSRGB));
		}


		while (System::Update())
		{

			if (continue_flag) {

				//goal到着チェック
				auto now_pos = my_mouce.getPosition();
				bool is_goal_achived = any_of(goal_positions.begin(), goal_positions.end(), 
											[now_pos](Position& gps) {
												return gps == now_pos;
											});
				if(is_goal_achived) break;


				if (!vec_prog.isEnd(now_time)) {//次の進路計算
					
					auto ref_3d_pos = vec_prog.calcReferencePosition(now_time);
					my_mouce.move3DPosition(ref_3d_pos);
				}
				else {//マス目間の移動処理

					//map_pos移動
					my_mouce.movePosition(ai.getNowRefPos());	
				
					//search wall
					auto new_walls = goro.virtual_sensing(my_mouce.getPosition(), my_labyrinth);

					//calc ref_pos
					ai.updateMap(new_walls);

					auto ref_pos = ai.calcNextPos(my_mouce.getPosition());

					vec_prog = VerocityProgramming(my_mouce.getContinuousPosition(), my_global::convertTo3DPos(ref_pos), now_time, now_time + 20);
					now_time *= 1;
				}
				now_time += 1;
			}

			if (KeySpace.down()) {
				continue_flag = !continue_flag;
			}
			if (KeyC.down()) {
				camera_mode = !camera_mode;
			}

			//以下，描画処理


			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			
			if (camera_mode) {
				//camera.update(4.0);
				camera.setView(Vec3{ 0, 24, -6 }, Vec3{ 0, 16, -4 });
				Graphics3D::SetCameraTransform(camera);

			}
			else {
				auto con_pos = my_mouce.getContinuousPosition();
				auto pos_3d = my_mouce.get3DPosition();

				Vec3 camera_pos = pos_3d + Vec3(-2.0 * cos(con_pos.z), 1.5, -2.0 * sin(con_pos.z));
				Vec3 camera_lookat = pos_3d + Vec3(0.3 * cos(con_pos.z), 0.1, 0.3 * sin(con_pos.z));	//今向いてる方向にちょっと進んだ方向
				robot_camera.setView( camera_pos, camera_lookat);
			
				Graphics3D::SetCameraTransform(robot_camera);
			}

			drawLabyrinth(my_labyrinth, ai.getMap(), my_global::plane_w, my_global::plane_h);
			drawFootMap(ai.getNodesCost(), number_textures);
			my_mouce.draw();

			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}

