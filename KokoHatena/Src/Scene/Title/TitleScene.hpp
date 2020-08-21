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
		
		const PixelShader m_shiftShader;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

		void drawFadeOut(double) const override;

	private:

		/// <summary>
		/// シェーダ時に使用するシフトのベクトル
		/// </summary>
		/// <param name="frequency"> 頻度         </param>
		/// <param name="shift"    > ずれの大きさ </param>
		/// <returns> シフトのベクトル </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}