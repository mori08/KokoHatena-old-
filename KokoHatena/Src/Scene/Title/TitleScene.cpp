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
	constexpr double SHIFT_FREQUENCY = 0.4;

	// シフトの量
	constexpr double SHIFT_LENGTH = 0.025;


	// ボタンサイズ
	constexpr Size BUTTON_SIZE(150, 30);

	// NEWGAMEボタン
	const Kokoha::Button NEWGAME_BUTTON
	(
		U"はじめから",
		Kokoha::getRectFromCenter(Point(400, 390), BUTTON_SIZE)
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
		U"やめる",
		Kokoha::getRectFromCenter(Point(400, 510), BUTTON_SIZE)
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
		, m_cursorWidth(BUTTON_SIZE.x)
		, m_cursorLineLength(Scene::Size().x)
		, m_cursorLineAlpha(0)
		, m_logoShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } })
	{
		if (!m_logoShader)
		{
			throw Error(U"Failed to load [TitleLogoShader.hlsl]");
		}

		// ボタンの設定
		for (const auto& button : BUTTON_LIST)
		{
			m_buttonSet.registerButton(button);
		}

		m_buttonSet.setSelectedButton(LOADGAME_BUTTON.getName());
	}


	void TitleScene::update()
	{
		// カーソルの幅の変更
		internalDividingPoint
		(
			m_cursorWidth,
			BUTTON_SIZE.x,
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の長さの変更
		internalDividingPoint
		(
			m_cursorLineLength,
			Scene::Width(),
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の不透明度の変更
		internalDividingPoint
		(
			m_cursorLineAlpha,
			0,
			CURSOR_MOVE_RATE
		);

		if (m_buttonSet.update())
		{
			m_cursorWidth = 0;
			m_cursorLineLength = 0;
			m_cursorLineAlpha = 1;
		}
	}


	void TitleScene::updateFadeOut(double)
	{
		// カーソルの幅の変更
		internalDividingPoint
		(
			m_cursorWidth,
			BUTTON_SIZE.x,
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の長さの変更
		internalDividingPoint
		(
			m_cursorLineLength,
			Scene::Width(),
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の不透明度の変更
		internalDividingPoint
		(
			m_cursorLineAlpha,
			0,
			CURSOR_MOVE_RATE
		);
	}


	void TitleScene::draw() const
	{
		// ロゴの描画
		drawLogo(SHIFT_FREQUENCY, SHIFT_LENGTH);

		// カーソルの描画
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorWidth, BUTTON_SIZE.y)
		).draw(MyWhite);
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorLineLength, 1)
		).draw(ColorF(MyWhite, m_cursorLineAlpha));

		// ボタンの描画
		for (const auto& button : BUTTON_LIST)
		{
			Color color = (button.getName() == m_buttonSet.getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.getName())
				.drawAt(button.getRegion().center(), color);
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
			ScopedCustomShader2D shader(m_logoShader);

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
