#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"
#include "../../Config/Config.hpp"
#include "../../MyPixelShader/MyPixelShader.hpp"


namespace
{
	/*
	* �萔�o�b�t�@ (PS_1)
	* RGB�̂���
	*/
	struct Shift
	{
		Float2 g_rShift;
		Float2 g_gShift;
		Float2 g_bShift;
		Float2 unusedB = {};
	};

	// �{�^���T�C�Y
	const Size& buttonSize()
	{
		static const Size& size = Kokoha::Config::get<Size>(U"TitleScene.buttonSize");
		return size;
	}

	// NEWGAME�{�^��
	const Kokoha::Button& newgameButton()
	{
		static const Kokoha::Button button = Kokoha::Config::get<Kokoha::Button>(U"TitleScene.NewgameButton");
		return button;
	}

	// LOADGAME�{�^��
	const Kokoha::Button& loadgameButton()
	{
		static const Kokoha::Button button = Kokoha::Config::get<Kokoha::Button>(U"TitleScene.LoadgameButton");
		return button;
	}

	// EXITGAME�{�^��
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
		// �J�[�\���̈ړ��̔�
		static const double CURSOR_MOVE_RATE = Config::get<double>(U"TitleScene.cursorMoveRate");

		// �J�[�\���̕��̕ύX
		internalDividingPoint
		(
			m_cursorWidth,
			buttonSize().x,
			CURSOR_MOVE_RATE
		);

		// �J�[�\���̉��ɏo����̒����̕ύX
		internalDividingPoint
		(
			m_cursorLineLength,
			Scene::Width(),
			CURSOR_MOVE_RATE
		);

		// �J�[�\���̉��ɏo����̕s�����x�̕ύX
		internalDividingPoint
		(
			m_cursorLineAlpha,
			0,
			CURSOR_MOVE_RATE
		);
	}


	void TitleScene::draw() const
	{
		// �V�t�g�̕p�x
		static const double SHIFT_FREQUENCY = Config::get<double>(U"TitleScene.shiftFrequency");
		// �V�t�g�̗�
		static const double SHIFT_LENGTH = Config::get<double>(U"TitleScene.shiftLength");

		// ���S�̕`��
		drawLogo(SHIFT_FREQUENCY, SHIFT_LENGTH);

		// �J�[�\���̕`��
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

		// �{�^���̕`��
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
			// �萔�o�b�t�@�̐ݒ�
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(frequency, shift);
			cb->g_gShift = makeShift(frequency, shift);
			cb->g_bShift = makeShift(frequency, shift);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// �V�F�[�_�̊J�n
			ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::TITLE_LOGO));

			// ���S�̕`��
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
