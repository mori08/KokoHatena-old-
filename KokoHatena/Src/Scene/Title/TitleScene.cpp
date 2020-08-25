#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// ���S��`�悷����W
	constexpr Point LOGO_POS(400, 200);

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

	// �V�t�g�̕p�x
	constexpr double SHIFT_FREQUENCY = 0.4;

	// �V�t�g�̗�
	constexpr double SHIFT_LENGTH = 0.025;


	// �{�^���T�C�Y
	constexpr Size BUTTON_SIZE(150, 30);

	// NEWGAME�{�^��
	const Kokoha::Button NEWGAME_BUTTON
	(
		U"�͂��߂���",
		Kokoha::getRectFromCenter(Point(400, 390), BUTTON_SIZE)
	);

	// LOADGAME�{�^��
	const Kokoha::Button LOADGAME_BUTTON
	(
		U"�Â�����",
		Kokoha::getRectFromCenter(Point(400, 450), BUTTON_SIZE)
	);

	// EXITGAME�{�^��
	const Kokoha::Button EXITGAME_BUTTON
	(
		U"��߂�",
		Kokoha::getRectFromCenter(Point(400, 510), BUTTON_SIZE)
	);

	// �{�^���̃��X�g
	const Array<Kokoha::Button> BUTTON_LIST
	{
		NEWGAME_BUTTON,
		LOADGAME_BUTTON,
		EXITGAME_BUTTON
	};

	// �J�[�\���̈ړ��̔�
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

		// �{�^���̐ݒ�
		for (const auto& button : BUTTON_LIST)
		{
			m_buttonSet.registerButton(button);
		}

		m_buttonSet.setSelectedButton(LOADGAME_BUTTON.getName());
	}


	void TitleScene::update()
	{
		// �J�[�\���̕��̕ύX
		internalDividingPoint
		(
			m_cursorWidth,
			BUTTON_SIZE.x,
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

		if (m_buttonSet.update())
		{
			m_cursorWidth = 0;
			m_cursorLineLength = 0;
			m_cursorLineAlpha = 1;
		}
	}


	void TitleScene::updateFadeOut(double)
	{
		// �J�[�\���̕��̕ύX
		internalDividingPoint
		(
			m_cursorWidth,
			BUTTON_SIZE.x,
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
		// ���S�̕`��
		drawLogo(SHIFT_FREQUENCY, SHIFT_LENGTH);

		// �J�[�\���̕`��
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

		// �{�^���̕`��
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
			// �萔�o�b�t�@�̐ݒ�
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(frequency, shift);
			cb->g_gShift = makeShift(frequency, shift);
			cb->g_bShift = makeShift(frequency, shift);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// �V�F�[�_�̊J�n
			ScopedCustomShader2D shader(m_logoShader);

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
