#include <iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<algorithm>
#include"Labyrinth.hpp"
#include"Position.hpp"
#include<cassert>
using namespace std;


//w_sizeとw_walls.size()は値が違うことに注意

Labyrinth::Labyrinth(int ws, int hs) :
	w_walls(ws * (hs + 1)),
	h_walls(hs * (ws + 1)),
	w_size(ws),
	h_size(hs)
{
	int hasi_kabe_w[] = {0, h_size-1};
	int hasi_kabe_h[] = {0, w_size-1};
	
	//姿勢角dirは0,1,2,3とx正軸から左回りを使う
	//そのため，それにあうようにここで変換をかます
	//wall専門の値 -> 姿勢角で使う値への変更
	

	int dir_map[] = {2,0,3,1};

	// down up : w_wall

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < w_size; j++ ){
			addWall( Position(j, hasi_kabe_w[i]), dir_map[2 + i] );
		}
	}

	//left right : h_wall

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < h_size; j++ ){
			addWall( Position(hasi_kabe_h[i], j), dir_map[i] );
		}
	}
}/*}}}*/

Labyrinth::Labyrinth(string file_name){/*{{{*/
	

	ifstream ifs(file_name);
	
	string read_line;
	vector<int> read_numbers;
	string one_wall;
	
	//get w_size,h_size

	getline(ifs,read_line);
	stringstream ss0;
	ss0<<read_line;
	ss0>>w_size;
	ss0>>h_size;

	getline(ifs,read_line);
	
	stringstream ss1;
	ss1<<read_line;
	
	while( getline(ss1, one_wall, ',') ){
		auto num = stoi(one_wall);
		w_walls.push_back(num);
	}
	getline(ifs,read_line);
	
	stringstream ss2;
	ss2<<read_line;
	
	while( getline(ss2, one_wall, ',') ){
		auto num = stoi(one_wall);
		h_walls.push_back(num);
	}
	
//	cout<<w_walls.size()<<endl;	
//	cout<<h_walls.size()<<endl;	
//	
//	for(size_t i = 0; i < w_walls.size(); i++){
//		cout<<w_walls[i]<<endl;
//	}
//	cout<<","<<endl;
//	for(size_t i = 0; i < h_walls.size(); i++){
//		cout<<h_walls[i]<<endl;
//	}

}	/*}}}*/

//w_sizeとw_walls.size()は値が違うことに注意

void Labyrinth::outputMap(string file_name){/*{{{*/
	
	ofstream ofs(file_name);

	ofs<<w_size<<" "<<h_size<<endl;
	
	for( size_t i = 0; i < w_walls.size()-1; i++ ){
		ofs<<w_walls[i]<<",";
	}
	ofs<<w_walls[w_walls.size() -1]<<endl;

	for( size_t i = 0; i < h_walls.size()-1; i++ ){
		ofs<<h_walls[i]<<",";
	}
	ofs<<h_walls[h_walls.size() -1]<<endl;
}/*}}}*/

void Labyrinth::addWall(Position pos,Position pos_dir){/*{{{*/

	auto new_wall = wall_mapping(pos, pos_dir_to_wall_dir(pos_dir));
	*new_wall = 1;
}/*}}}*/

void Labyrinth::addWall(Position p,int wall_dir){/*{{{*/
	auto new_wall = wall_mapping(p,wall_dir);
	*new_wall = 1;
}/*}}}*/

int Labyrinth::isThereWall(Position pos, Position pos_dir){/*{{{*/
	
	return isThereWall( pos, pos_dir_to_wall_dir(pos_dir) );
}/*}}}*/

int Labyrinth::isThereWall(Position p, int dir){/*{{{*/
	
	return *(wall_mapping(p,dir));
}	/*}}}*/

int* Labyrinth::wall_mapping(int pos_x,int pos_y,int wall_dir){
	
	assert( wall_dir >= 0 && wall_dir <= 3);
	assert( pos_x < w_size && pos_x >= 0 && pos_y < h_size && pos_y >= 0);
	
	//姿勢の0,1,2,3の方向から，wall内部でしか使わない方向値に変換

	int w_map[] = {1,3,0,2};	
	
	wall_dir = w_map[wall_dir];
	// d = 
	// 0 : left
	// 1 : right
	// 2 : down
	// 3 : up

	if(wall_dir <= 1){
		return &(h_walls[ pos_x  + (w_size+1) * pos_y + wall_dir]);
	}
	return &(w_walls[pos_y + (h_size+1) * pos_x + wall_dir - 2]);
}

int* Labyrinth::wall_mapping(Position pos, Position pos_dir){
	return wall_mapping(pos.x, pos.y, pos_dir_to_wall_dir(pos_dir));
}

int* Labyrinth::wall_mapping(Position pos,int wall_dir){
	return wall_mapping(pos.x, pos.y, wall_dir);
}

int pos_dir_to_wall_dir(Position pos_dir){
	
	assert(pos_dir == Position(0,1) || pos_dir == Position(0,-1) || pos_dir == Position(1,0) ||pos_dir == Position(-1,0) );
	
	//姿勢角の0,1,2,3に直してる


	if(pos_dir.x == 0){
		return (pos_dir.y == 1) ? 1 : 3;
	}
	return (pos_dir.x == 1) ? 0 : 2;
}


