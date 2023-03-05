#ifndef MEASHRE_HPP
#define MEASHRE_HPP
#include"Wall.hpp"
#include"Position.hpp"
#include"Labyrinth.hpp"
#include<vector>


class Measure{
	private:
	
		//virtualの場合ならここにセンサの設定・能力を定義
	public:
		Measure(){}

		std::vector<Wall> virtual_sensing(Position mouce_pos,Labyrinth lab){
			
			std::vector<Wall> new_discoverd_walls;

			//左斜め前，正面2マス，右斜め前が見れるとする
			//check front wall
			if(lab.isThereWall(mouce_pos,mouce_pos.theta)) new_discoverd_walls.push_back( Wall(mouce_pos,mouce_pos.theta) );

			//check left mouce_pos wall
			if(lab.isThereWall(mouce_pos, (mouce_pos.theta + 1) % 4 )) new_discoverd_walls.emplace_back( Wall(mouce_pos,(mouce_pos.theta + 1) % 4 ) );
			
			//check right mouce_pos wall
			if(lab.isThereWall(mouce_pos,(mouce_pos.theta + 3) % 4)) new_discoverd_walls.emplace_back( Wall(mouce_pos,(mouce_pos.theta + 3) % 4) );
		
			std::cout<<"sensing end"<<std::endl;

			return new_discoverd_walls;
			
		}

};


#endif
