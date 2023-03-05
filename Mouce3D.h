#pragma once
#include"Mouce.hpp"
#include<Siv3D.hpp>

class Mouce3D : public micromouce::Mouce {

private:
	Vec3 inipos_3d;
	Vec3 pos_3d;
	Vec3 continuous_pos;	//x,y,theta
	const Model mouce_model;
public:

	Mouce3D(Vec3 initial_pos_3d, Position initial_pos) :
		Mouce(initial_pos),
		inipos_3d{ initial_pos_3d },
		pos_3d{ initial_pos_3d },
		continuous_pos{ 0,0,0 },
		mouce_model{U"Mouce_color2.obj"}{
		Model::RegisterDiffuseTextures(mouce_model, TextureDesc::MippedSRGB);
	
		}


	void move3DPosition(Vec3 ref_pos) {

		continuous_pos = ref_pos;
		pos_3d = inipos_3d + Vec3(continuous_pos.x, 0, continuous_pos.y);

	}

	Vec3 getContinuousPosition() {
		return continuous_pos;
	}


	Vec3 get3DPosition() {
		return pos_3d;
	}

	virtual void movePosition(Position reference_pos) {
		pos = reference_pos;
	}


	void draw() {
		/*
		Cone(0.12, 0.4).asMesh()
			.rotated(Quaternion::Pitch(Pi / 2))
			.rotated(Quaternion::Yaw(-continuous_pos.z + Pi / 2))
			.translated(pos_3d.movedBy(0, 0.15, 0.35))
			.draw(ColorF(0,255,255));
			*/
		//mouce_model.draw(Mat4x4::Translate(pos_3d.movedBy(0, 0.15, 0.35)));
		//mouce_model.draw(Mat4x4::AffineTransform(0.008, Quaternion::RotateZ( -continuous_pos.z + 45_deg, pos_3d.movedBy(0, 0.15, 0.35) ), ColorF(0.3, 0.3, 0.3));

		//mouce_model.draw(Mat4x4::AffineTransform(0.008, Quaternion::RotateZ(-continuous_pos.z + 45_deg, pos_3d.movedBy(0, 0.15, 0.35)), ColorF(0.3, 0.3, 0.3));
		//const Transformer3D transform2{ Mat4x4::Scale(0.008)};
		
		//auto p = pos_3d.moveBy(0, 0.15, 0.35);
		//mouce_model.draw(Vec3(p.x * 125, p.y * 125, p.z * 125), Quaternion::RotateY(-continuous_pos.z + 45_deg));
		//mouce_model.draw(Mat4x4::Scale(0.008).translated(pos_3d.movedBy(0, 0.15, 0.35)));
		mouce_model.draw(Mat4x4::Scale(0.008).rotatedY(-continuous_pos.z + 90_deg).translated(pos_3d.movedBy(0.0, 0.15, 0.3)));
		//mouce_model.draw(0, 0, 0);
	}

};