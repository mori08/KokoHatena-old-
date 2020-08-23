#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// ロゴを描画する座標
	constexpr Point LOGO_POS(400, 200);

	/*
	* 定数バッファ (PS_1)
	* RGBのずれ
	*/
	struct Shift
	{
		Float2 g_rShift;
		Float2 g_gShift;
		Float2 g_bShift;
		Float2 unusedB = {};
	};

	// シフトの頻度
	constexpr double SHIFT_FADE_FREQUENCY = 2.0;

	// シフトの量
	constexpr double SHIFT_FADE_LENGTH = 0.06;

	// シフトの頻度
	constexpr double SHIFT_FREQUENCY = 1.0;

	// シフトの量
	constexpr double SHIFT_LENGTH = 0.01;
}


namespace Kokoha
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, m_shiftShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } })
	{
		if (!m_shiftShader)
		{
			throw Error(U"Failed to load [TitleLogoShader.hlsl]");
		}
	}


	void TitleScene::update()
	{
		
	}


	void TitleScene::draw() const
	{
		{
			// 定数バッファの設定
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			cb->g_gShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			cb->g_bShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// シェーダの開始
			ScopedCustomShader2D shader(m_shiftShader);

			// ロゴの描画
			TextureAsset(U"Logo").drawAt(LOGO_POS);
		}
	}


	void TitleScene::drawFadeOut(double) const
	{
		{
			// 定数バッファの設定
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(SHIFT_FADE_FREQUENCY, SHIFT_FADE_LENGTH);
			cb->g_gShift = makeShift(SHIFT_FADE_FREQUENCY, SHIFT_FADE_LENGTH);
			cb->g_bShift = makeShift(SHIFT_FADE_FREQUENCY, SHIFT_FADE_LENGTH);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// シェーダの開始
			ScopedCustomShader2D shader(m_shiftShader);

			// ロゴの描画
			TextureAsset(U"Logo").drawAt(LOGO_POS);
		}
	}


	Float2 TitleScene::makeShift(double frequency, double shift)
	{
		return randomFrequency(frequency)
			? Float2(Random(-shift, shift), Random(-shift, shift))
			: Float2::Zero();
	}

}
