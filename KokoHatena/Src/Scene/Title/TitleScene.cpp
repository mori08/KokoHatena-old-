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


	// ボタンサイズ
	constexpr Size BUTTON_SIZE(150, 30);

	// NEWGAMEボタン
	const Kokoha::Button NEWGAME_BUTTON
	(
		U"はじめから",
		Kokoha::getRectFromCenter(Point(400, 400), BUTTON_SIZE)
	);

	// LOADGAMEボタン
	const Kokoha::Button LOADGAME_BUTTON
	(
		U"つづきから",
		Kokoha::getRectFromCenter(Point(400, 450), BUTTON_SIZE)
	);

	// EXITGAMEボタン
	const Kokoha::Button EXITGAME_BUTTON
	(
		U"おわる",
		Kokoha::getRectFromCenter(Point(400, 500), BUTTON_SIZE)
	);

	// ボタンのリスト
	const Array<Kokoha::Button> BUTTON_LIST
	{
		NEWGAME_BUTTON,
		LOADGAME_BUTTON,
		EXITGAME_BUTTON
	};

	// カーソルの移動の比
	constexpr double CURSOR_MOVE_RATE = 0.005;

}


namespace Kokoha
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, m_cursor(LOADGAME_BUTTON.getRegion())
		, m_shiftShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } })
	{
		if (!m_shiftShader)
		{
			throw Error(U"Failed to load [TitleLogoShader.hlsl]");
		}

		// ボタンの設定
		for (const auto& button : BUTTON_LIST)
		{
			m_buttonSet.registerButton(button);
		}
	}


	void TitleScene::update()
	{
		internalDividingPoint
		(
			m_cursor.pos,
			m_buttonSet.getSelectedButton().getRegion().pos,
			CURSOR_MOVE_RATE
		);

		m_buttonSet.update();
	}


	void TitleScene::draw() const
	{
		drawLogo(SHIFT_FREQUENCY, SHIFT_LENGTH);

		// ボタンとカーソルの描画
		m_cursor.draw(MyWhite);
		for (const auto& button : BUTTON_LIST)
		{
			FontAsset(U"20")(button.getName())
				.drawAt(button.getRegion().center(), MyWhite);
		}

	}


	void TitleScene::drawFadeOut(double) const
	{
		drawLogo(SHIFT_FADE_FREQUENCY, SHIFT_FADE_LENGTH);

		// ボタンとカーソルの描画
		m_cursor.draw(MyWhite);
		for (const auto& button : BUTTON_LIST)
		{
			FontAsset(U"20")(button.getName())
				.drawAt(button.getRegion().center(), MyWhite);
		}
	}


	void TitleScene::drawLogo(double frequency, double shift) const
	{
		{
			// 定数バッファの設定
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(frequency, shift);
			cb->g_gShift = makeShift(frequency, shift);
			cb->g_bShift = makeShift(frequency, shift);
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
