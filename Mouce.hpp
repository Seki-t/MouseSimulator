#ifndef MOUCE_HPP
#define MOUCE_HPP
#include"Position.hpp"
#include"Wall.hpp"
#include"Labyrinth.hpp"
#include"KizunaAI.hpp"
#include"Wall.hpp"
#include<vector>

namespace micromouce {


	class Mouce {

	protected:

		Position pos;


		//センサから得られた計測クラスを持たせようかと思ったけれど，センシングはどんなセンサを使おうがマウスの動作と独立であってほしいし，RTOSでも割り込みでもどっちでも，Mouceクラスの中にあるよりは外にあったほうがやりやすい．必要なデータだけ関数とかで受け取る．メッセージぱっしんぐっぽい？
		//		Measure measure;	

	public:

		Mouce(Position initial_position) :
			pos{ initial_position } {}

		//1マス移動
		//movePositionに必要な情報は？ 現在分かっている地図情報・

		virtual void movePosition(Position reference_pos) {

			//nextDirectionのほうがアニメーション作るときよいか？

			Position next_pos = reference_pos;

			pos = next_pos;
		}

		Position getPosition() {
			return pos;
		}

	};
};

#endif	//MOUCE_HPP

