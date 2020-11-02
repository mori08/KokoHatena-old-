#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"
#include "../../Config/Config.hpp"
#include "../../MyPixelShader/MyPixelShader.hpp"


namespace
{
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

	// ボタンサイズ
	const Size& buttonSize()
	{
		static const Size& size = Kokoha::Config::get<Size>(U"TitleScene.buttonSize");
		return size;
	}

	// NEWGAMEボタン
	const Kokoha::Button& newgameButton()
	{
		static const Kokoha::Button button = Kokoha::Config::get<Kokoha::Button>(U"TitleScene.NewgameButton");
		return button;
	}

	// LOADGAMEボタン
	const Kokoha::Button& loadgameButton()
	{
		static const Kokoha::Button button = Kokoha::Config::get<Kokoha::Button>(U"TitleScene.LoadgameButton");
		return button;
	}

	// EXITGAMEボタン
	const Kokoha::Button& exitgameButton()
	{
		static const Kokoha::Button button = Kokoha::Config::get<Kokoha::Button>(U"TitleScene.ExitgameButton");
		return button;
	}

}


namespace Kokoha
{

	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, m_cursorWidth(buttonSize().x)
		, m_cursorLineLength(Scene::Size().x)
		, m_cursorLineAlpha(0)
	{
		m_buttonSet.registerButton(newgameButton());
		m_buttonSet.registerButton(loadgameButton());
		m_buttonSet.registerButton(exitgameButton());

		m_buttonSet.setOnClickFunc(newgameButton().getName(), [this]() {changeScene(SceneName::RECORD_LOAD); });

		m_buttonSet.setSelectedButton(loadgameButton().getName());
	}


	void TitleScene::update()
	{
		updateFadeOut(0);

		if (m_buttonSet.update())
		{
			m_cursorWidth = 0;
			m_cursorLineLength = 0;
			m_cursorLineAlpha = 1;
		}
	}


	void TitleScene::updateFadeOut(double)
	{
		// カーソルの移動の比
		static const double CURSOR_MOVE_RATE = Config::get<double>(U"TitleScene.cursorMoveRate");

		// カーソルの幅の変更
		internalDividingPoint
		(
			m_cursorWidth,
			buttonSize().x,
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
		// シフトの頻度
		static const double SHIFT_FREQUENCY = Config::get<double>(U"TitleScene.shiftFrequency");
		// シフトの量
		static const double SHIFT_LENGTH = Config::get<double>(U"TitleScene.shiftLength");

		// ロゴの描画
		drawLogo(SHIFT_FREQUENCY, SHIFT_LENGTH);

		// カーソルの描画
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorWidth, buttonSize().y)
		).draw(MyWhite);
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorLineLength, 1)
		).draw(ColorF(MyWhite, m_cursorLineAlpha));

		// ボタンの描画
		for (const auto& button : m_buttonSet.getButtonList())
		{
			Color color = (button.first == m_buttonSet.getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.first)
				.drawAt(button.second.getRegion().center(), color);
		}
	}


	void TitleScene::drawLogo(double frequency, double shift) const
	{
		static const Point LOGO_POS = Config::get<Point>(U"TitleScene.logoPos");

		{
			// 定数バッファの設定
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(frequency, shift);
			cb->g_gShift = makeShift(frequency, shift);
			cb->g_bShift = makeShift(frequency, shift);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// シェーダの開始
			ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::TITLE_LOGO));

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
