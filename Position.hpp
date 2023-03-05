#ifndef POSITION_HPP
#define POSITION_HPP
#include<cmath>
#include<cassert>
struct Position{

	int x,y,theta;

	Position(){}
	Position(int _x,int _y, int _theta) : x{_x}, y{_y}, theta{_theta} {}

	Position(int _x,int _y) : x{_x}, y{_y}, theta{0} {}

	Position moved_position(int move_x,int move_y,int move_theta)const {
		return Position(x + move_x, y + move_y, theta + move_theta);
	}

	Position moved_position(Position&& dir_pos)const {
		return Position(x + dir_pos.x,y + dir_pos.y, theta + dir_pos.theta);
	}
	Position moved_position(Position& dir_pos)const {
		return Position(x + dir_pos.x,y + dir_pos.y, theta + dir_pos.theta);
	}

	Position moved_position(int wall_dir)const {
		return moved_position( convertDirection( wall_dir ));
	}

	//wallの0,1,2,3を

	Position convertDirection(int wall_direction)const {/*{{{*/
		switch(wall_direction){
			case 0:
				return Position(1,0);
				break;
			case 1:
				return Position(0,1);
				break;
			case 2:
				return Position(-1,0);
				break;
			case 3:
				return Position(0,-1);
				break;
		}
		assert("wall dir is invalid");
		return Position(0,0);
	}/*}}}*/

	Position operator +(const Position& pos)const {
		return Position(x + pos.x, y + pos.y, theta + pos.theta);
	}

	Position operator -(const Position& pos)const {
		return Position(x - pos.x, y - pos.y, theta - pos.theta);
	}

	Position& operator += (const Position& pos){
		this->x += pos.x;
		this->y += pos.y;
		this->theta += pos.theta;
		return *this;
	}

	Position& operator -= (const Position& pos){
		this->x -= pos.x;
		this->y -= pos.y;
		this->theta -= pos.theta;
		return *this;
	}

	Position& operator =(const Position& pos){
		x = pos.x;
		y = pos.y;
		theta = pos.theta;
		return *this;
	}

	bool operator !=(const Position& pos)const {
		return ((x != pos.x) || (y != pos.y) || (theta != pos.theta ));
	}

	bool operator ==(const Position& pos)const {
		return ((x == pos.x) && (y == pos.y) );
	}

	bool operator !=(Position&& pos)const {
		return ((x != pos.x) || (y != pos.y) || (theta != pos.theta ));
	}

	bool operator ==(Position&& pos)const {
		return ((x == pos.x) && (y == pos.y) && (theta == pos.theta) );
	}
	
	bool equalPos(Position pos)const {
		return ((x == pos.x) && (y == pos.y) );
	}

	int Get_Norm()const {
		return sqrt(x*x + y*y);
	}

	int manhattan(Position p1, Position p2){
		return abs(p1.x - p2.x) + abs(p1.y - p2.y);
	}
};

#endif

