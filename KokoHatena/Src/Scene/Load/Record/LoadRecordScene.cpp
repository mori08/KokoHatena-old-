#include "LoadRecordScene.hpp"
#include "../../../RecordManager/RecordManager.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �e�L�X�g��\��������W
	constexpr Point TEXT_DRAW_POS(410, 410);

	// ���o�̉~
	constexpr Circle LOADING_CIRCLE(350, 410, 8.0);
	// ���o�̌ʂ̑���
	constexpr double LOADING_ARC_THICNESS = 1.5;
	// ���o�̌ʂ̒���
	constexpr double LOADING_ARC_LENGTH = 5.0;
	// �����ȉ~�̌�
	constexpr int32  SMALL_CIRCLE_NUM = 8;

	// ���S�̃T�C�Y
	constexpr Size LOGO_SIZE(180, 180);
	// ���S�̃A�j���[�V����
	const Kokoha::Animation LOGO_ANIM
	(
		Kokoha::PosOrder
		{ 
			{0.04,Point(0,0)},
			{0.04,Point(1,0)},
			{0.04,Point(2,0)},
			{0.04,Point(3,0)},
			{0.04,Point(0,1)},
			{0.04,Point(1,1)},
			{0.04,Point(2,1)},
			{0.04,Point(3,1)},
			{0.04,Point(0,2)},
			{0.04,Point(1,2)},
			{0.04,Point(2,2)},
			{0.04,Point(3,2)},
			{0.04,Point(0,3)},
			{0.04,Point(1,3)},
			{0.04,Point(2,3)},
			{0.04,Point(3,3)},
			{0.04,Point(0,4)},
			{0.80,Point(1,4)},
			{0.04,Point(2,4)},
			{0.04,Point(3,4)},
			{0.04,Point(0,5)}
		},
		false
	);
}


namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData init)
		: LoadScene
		(
			init,
			[]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(3));
				switch (RecordManager::instance().load())
				{
				case RecordManager::LoadResult::NEW_GAME:
				case RecordManager::LoadResult::CONTINUE:
					return SceneName::DESKTOP;
				case RecordManager::LoadResult::ERROR:
					return SceneName::TITLE;
				}
				return SceneName::TITLE;
			}
		)
		, m_boardLogo(U"BoardLogo", LOGO_SIZE)
	{
		m_boardLogo.setAnimation(U"Update", LOGO_ANIM);
		m_boardLogo.start(U"Update");
	}


	void LoadRecordScene::subUpdate()
	{
		m_boardLogo.update();
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
		
		m_boardLogo.getTexture().drawAt(Scene::Center());

		FontAsset(U"20")(U"Loading").drawAt(TEXT_DRAW_POS, MyWhite);
	}


}
