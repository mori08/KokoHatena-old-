#pragma once


#include"../Scene.hpp"


namespace Kokoha
{
	/*
	* TitleSceneクラス
	* タイトルシーン
	*/
	class TitleScene : public MyApp::Scene
	{
	private:



	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}