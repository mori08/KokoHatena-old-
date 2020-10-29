#include "LoadRecordScene.hpp"
#include "../../../RecordManager/RecordManager.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"


namespace
{
	// ���S�̃T�C�Y
	static const Size& logoSize()
	{
		static Size LOGO_SIZE = Kokoha::Config::get<Size>(U"LoadRecordScene.logoSize");
		return LOGO_SIZE;
	}
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
		, m_boardLogo(U"BoardLogo", logoSize())
	{
		// ���S�̃A�j���[�V����
		static Animation LOGO_ANIM = Config::get<Animation>(U"LoadRecordScene.LogoAnim");

		m_boardLogo.setAnimation(U"Update", LOGO_ANIM);
		m_boardLogo.start(U"Update");
	}


	void LoadRecordScene::subUpdate()
	{
		m_boardLogo.update();
	}


	void LoadRecordScene::draw() const
	{
		// �e�L�X�g��\��������W
		static const Point TEXT_DRAW_POS = Config::get<Point>(U"LoadRecordScene.textDrawPos");
		// ���o�̉~
		static const Circle LOADING_CIRCLE = Config::get<Circle>(U"LoadRecordScene.loadingCircle");
		// ���o�̌ʂ̑���
		static const double LOADING_ARC_THICNESS = Config::get<double>(U"LoadRecordScene.loadingArcThickness");
		// ���o�̌ʂ̒���
		static const double LOADING_ARC_LENGTH = Config::get<double>(U"LoadRecordScene.loadingArcLength");
		// �����ȉ~�̌�
		static const int32  SMALL_CIRCLE_NUM = Config::get<int32>(U"LoadRecordScene.smallCircleNum");

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
