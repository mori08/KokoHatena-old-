#pragma once


#include"../Scene.hpp"
#include"../../ButtonSet/ButtonSet.hpp"


namespace Kokoha
{
	/*
	* TitleSceneクラス
	* タイトルシーン
	*/
	class TitleScene : public MyApp::Scene
	{
	private:
		
		// ボタンの管理
		ButtonSet m_buttonSet;

		// カーソル
		RectF m_cursor;

		// タイトルロゴ用のピクセルシェーダ
		const PixelShader m_shiftShader;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

		void drawFadeOut(double) const override;

	private:

		/// <summary>
		/// ロゴの描画
		/// </summary>
		/// <param name="frequency"> 頻度         </param>
		/// <param name="shift"    > ずれの大きさ </param>
		void drawLogo(double frequency, double shift) const;

		/// <summary>
		/// シェーダ時に使用するシフトのベクトル
		/// </summary>
		/// <param name="frequency"> 頻度         </param>
		/// <param name="shift"    > ずれの大きさ </param>
		/// <returns> シフトのベクトル </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}