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
	constexpr double SHIFT_FADE_FREQUENCY = 2.0;

	// �V�t�g�̗�
	constexpr double SHIFT_FADE_LENGTH = 0.06;

	// �V�t�g�̕p�x
	constexpr double SHIFT_FREQUENCY = 1.0;

	// �V�t�g�̗�
	constexpr double SHIFT_LENGTH = 0.01;


	// �{�^���T�C�Y
	constexpr Size BUTTON_SIZE(150, 30);

	// NEWGAME�{�^��
	const Kokoha::Button NEWGAME_BUTTON
	(
		U"�͂��߂���",
		Kokoha::getRectFromCenter(Point(400, 400), BUTTON_SIZE)
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
		U"�����",
		Kokoha::getRectFromCenter(Point(400, 500), BUTTON_SIZE)
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
		, m_cursor(LOADGAME_BUTTON.getRegion())
		, m_shiftShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } })
	{
		if (!m_shiftShader)
		{
			throw Error(U"Failed to load [TitleLogoShader.hlsl]");
		}

		// �{�^���̐ݒ�
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

		// �{�^���ƃJ�[�\���̕`��
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

		// �{�^���ƃJ�[�\���̕`��
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
			// �萔�o�b�t�@�̐ݒ�
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(frequency, shift);
			cb->g_gShift = makeShift(frequency, shift);
			cb->g_bShift = makeShift(frequency, shift);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// �V�F�[�_�̊J�n
			ScopedCustomShader2D shader(m_shiftShader);

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
