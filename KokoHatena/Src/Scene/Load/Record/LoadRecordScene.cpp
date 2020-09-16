#include "LoadRecordScene.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �e�L�X�g��\��������W
	constexpr Point TEXT_DRAW_POS(420, 480);

	// ���o�̉~
	constexpr Circle LOADING_CIRCLE(360, 480, 11.0);
	// ���o�̌ʂ̑���
	constexpr double LOADING_ARC_THICNESS = 2.0;
	// ���o�̌ʂ̒���
	constexpr double LOADING_ARC_LENGTH = 5.0;
	// �����ȉ~�̌�
	constexpr int32  SMALL_CIRCLE_NUM = 10;
}


namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData init)
		: LoadScene
		(
			init,
			[]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(5));
				return SceneName::TITLE;
			}
		)
	{
	}


	void LoadRecordScene::subUpdate()
	{

	}


	void LoadRecordScene::draw() const
	{
		// ���o�p�̉~�̕`��
		static double angle = 0;
		angle += Scene::DeltaTime();
		for (int32 i = 0; i < SMALL_CIRCLE_NUM; ++i)
		{
			double a = Math::TwoPi * i / SMALL_CIRCLE_NUM - angle;
			Circle
			(
				LOADING_CIRCLE.center + LOADING_CIRCLE.r * Vec2(Cos(a), Sin(a)),
				LOADING_ARC_THICNESS
			).draw(Color(MyWhite, 0xA0));
		}
		LOADING_CIRCLE.drawArc(angle, LOADING_ARC_LENGTH, LOADING_ARC_THICNESS, LOADING_ARC_THICNESS, MyWhite);
		
		FontAsset(U"20")(U"Loading").drawAt(TEXT_DRAW_POS, MyWhite);
	}


}
