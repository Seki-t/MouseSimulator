#ifndef LABYRINTH_HPP
#define LABYRINTH_HPP
#include"Position.hpp"
#include<vector>
#include<string>
//#include<stdint>

class Labyrinth{
	private:	
	
	
	//w_wallはx軸平行の壁，h_wallはy軸平行の壁

	std::vector<int> w_walls;
	std::vector<int> h_walls;

/*
	// X_SIZE * (Y_SIZE + 1)	| の壁
	vector<int> w_wall_infomation;
	// Y_SIZE * (X_SIZE + 1)	- の壁
	vector<int> h_wall_infomation;
*/

	int* wall_mapping(int pos_x, int pos_y, int wall_dir);
	int* wall_mapping(Position pos, int wall_dir);
	int* wall_mapping(Position pos, Position pos_dir);
	
	public:
	int w_size,h_size;
	Labyrinth(int ws,int hs);
	
	Labyrinth(std::string file_name);

	void outputMap(std::string str);
	
	void addWall(Position p1,Position p2);
	void addWall(Position p,int wall_dir);
	
	void deleteWall(Position p1,Position p2);
	void deleteWall(Position p,int wall_dir);
	
	int isThereWall(Position p1, Position p2);

	int isThereWall(Position p, int dir);
	
	bool isInLabyrinth(Position p){
		return (p.x >= 0 && p.x < w_size && p.y >= 0 && p.y < h_size);
	}


};

int pos_dir_to_wall_dir(Position pos_dir);

#endif
