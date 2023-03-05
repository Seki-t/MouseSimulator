#ifndef KIZUNA_AI_HPP
#define KIZUNA_AI_HPP
#include"Position.hpp"
#include"Labyrinth.hpp"
#include"Wall.hpp"
	
//現在持っている地図情報から，ゴールを探索するために次に向かう方向を示すAI
//地図情報から最短経路を算出するものではない．
//それは，他のクラスにやらせたい

//歩数マップ探索

class KizunaAI{

	private:
		
	//このコストはAI側で持つべき	
	// size = X_SIZE * Y_SIZE

	std::vector<int> nodes_cost;
	std::vector<Position> goal_positions;
	Labyrinth laby_map;

	Position now_ref_pos;

	size_t convertIndex(Position p){
		return (p.x + p.y * laby_map.w_size);
	}

	public:
		
	KizunaAI(std::vector<Position> gpss,Labyrinth& l_map) :
		nodes_cost(l_map.w_size * l_map.h_size),
		goal_positions(gpss),
		laby_map(l_map) {
		
//			for(int i = 0; i < gpss.size(); i++){
//				for(int j = i+1; j < gpss.size();j++){
//					
//					auto vec_pos = gpss[j] - gpss[i];
//					if(vec_pos == Position(0,1) || vec_pos == Position(0,-1) || vec_pos == Position(1,0) ||vec_pos == Position(-1,0) ){
//						laby_map.addWall(gpss[i],vec_pos);
//					}
//				}
//			}

		}

	Position calcNextPos(Position now_pos);
		
		//センサ情報から頭の中の地図を更新
		//地図を更新って，結局はどこに壁があるかっていう情報を地図に書いていくお仕事だから，壁情報を受け取る

	Position getNowRefPos() {
		return now_ref_pos;
	}

	
	void updateMap(std::vector<Wall> new_walls){
		for(auto& wall : new_walls){
			laby_map.addWall(wall.first,wall.second);
		}
	}

	std::vector<int> getNodesCost() {
		return nodes_cost;
	}

	Labyrinth getMap() {
		return laby_map;
	}
};
		
//		{
//			Position next_pos(0,0,0);
//
//			Position migimawari_wall_directions[4] = {Position(1,0),Position(0,1),Position(-1,0),Position(0,-1)} ;
//			//
//			// const int migi_map[] = {1,0,3,1};	
//			
//			int start_migite_dir = (now_pos.theta + 3) % 4;// now_pos.theta = 0なら，今(1,0)を向いているので，start_migite_dir = 3になって，(0,-1)方向が右手になる
//
//			for(int i = start_migite_dir; i < 4 + start_migite_dir; i++){
//				std::cout<<"i = "<<i<<std::endl;
//				//壁があるかを聞くより，移動可能かどうかを聞いた方が，後々汎用的になるかもしれない
//				if( ( !lab.isThereWall( now_pos, i % 4 ) ) && lab.isInLabyrinth(now_pos + migimawari_wall_directions[i % 4]) ){
//					next_pos = now_pos + (migimawari_wall_directions[i % 4]);
//					next_pos.theta = i  % 4;	//今進んだ方向を次の姿勢角とする
//					break;
//				}
//			}
//			return next_pos;
//		}



#endif
