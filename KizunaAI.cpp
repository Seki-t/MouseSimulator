#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <climits>
#include<functional>
#include"KizunaAI.hpp"
//using namespace std;

#define INF INT_MAX/3
#define REP(i,n) for(int i=0;i<n;i++)


struct foot{
	int cost;
	Position pos;
	
	foot(){}
	foot(int c,Position p) : cost{c}, pos{p} {}
	
	//>にはconstつけないと，stlで使えない

	bool operator > (foot f)const{
		return cost > f.cost;
	}
};

Position KizunaAI::calcNextPos(Position now_pos){
	
	std::fill(nodes_cost.begin(),nodes_cost.end(),10000); //全costをINFに
	

	std::priority_queue<foot, std::vector<foot>,std::greater<foot>> que;
	
	//std::queue<foot> que;	
	
	//goalを歩数マップ0にして探索開始位置に
	
	for(auto& gps : goal_positions){
		nodes_cost[convertIndex(gps)] = 0;
		que.emplace(0,gps);
	}	

	
	int excute_count = 0;
	while(!que.empty()){

		auto p = que.top(); que.pop();
		auto selected_pos = p.pos;

		REP(i,4){
			if( !laby_map.isThereWall(selected_pos, i) ){
				auto new_pos = selected_pos.moved_position(i);
				auto idx = convertIndex(new_pos);
				
				if(nodes_cost[idx] > p.cost + 1){
					nodes_cost[idx] = p.cost + 1;
					que.emplace(p.cost + 1, new_pos);
					excute_count++;
				}
			}
		}
	}
	//cout<<"exe = "<<excute_count<<endl;
	
	Position next_pos;
	int now_cost = 1000000;
	//移動方向の決定(現在の進行方向を有線)
	
	int priority_direction[4] = {0,1,3,2};

	REP(i,4){
		
		auto dir_candidate = priority_direction[(now_pos.theta + i) % 4 ];

		if( !laby_map.isThereWall(now_pos,dir_candidate)){
			
			if(nodes_cost[convertIndex(now_pos.moved_position(dir_candidate))] < now_cost){

				next_pos = now_pos.moved_position(dir_candidate);
				next_pos.theta = dir_candidate % 4;

				now_cost = nodes_cost[convertIndex(next_pos)];
			}
		}
	}

	
	//歩数マップの描画
/*
	for(int i = laby_map.h_size - 1 ;i >= 0; i--){
		REP(j,laby_map.w_size){
			cout<<nodes_cost[j + i * laby_map.w_size]<<",";
		}
		cout<<endl;
	}
	*/

	if (next_pos.theta != now_pos.theta) {
		next_pos.x = now_pos.x;
		next_pos.y = now_pos.y;
	}

	now_ref_pos = next_pos;
	return next_pos;

}

