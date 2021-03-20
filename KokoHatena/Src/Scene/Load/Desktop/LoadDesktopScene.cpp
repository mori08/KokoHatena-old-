#include "LoadDesktopScene.hpp"
#include "../../../RecordManager/RecordManager.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"

namespace
{
	// ロゴのサイズ
	static const Size& logoSize()
	{
		static const Size LOGO_SIZE = Kokoha::Config::get<Size>(U"LoadDesktopScene.logoSize");
		return LOGO_SIZE;
	}
}



namespace Kokoha
{
	LoadDesktopScene::LoadDesktopScene(const InitData& init)
		: LoadScene(init)
		, m_boardLogo(U"BoardLogo",logoSize())
	{
		// ロゴのアニメーション
		static Animation LOGO_ANIM = Config::get<Animation>(U"LoadDesktopScene.LogoAnim");
		m_boardLogo.setAnimation(U"Update", LOGO_ANIM);
		m_boardLogo.start(U"Update");

		auto& boardShareData = getData().boardShareData;

		setLoadThread
		(
			[&boardShareData]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(3));

				// 日付を1進める
				int32 date = RecordManager::instance().getRecord(U"Date");
				++date;
				
				RecordManager::instance().setRecord(U"Date", date);

				boardShareData.load();

				return SceneName::DESKTOP;
			}
		);
	}


	void LoadDesktopScene::subUpdate()
	{
		m_boardLogo.update();
	}

	
	void LoadDesktopScene::draw() const
	{
		// テキストを表示する座標
		static const Point TEXT_DRAW_POS = Config::get<Point>(U"LoadDesktopScene.textDrawPos");
		// 演出の円
		static const Circle LOADING_CIRCLE = Config::get<Circle>(U"LoadDesktopScene.loadingCircle");
		// 演出の弧の太さ
		static const double LOADING_ARC_THICNESS = Config::get<double>(U"LoadDesktopScene.loadingArcThickness");
		// 演出の弧の長さ
		static const double LOADING_ARC_LENGTH = Config::get<double>(U"LoadDesktopScene.loadingArcLength");
		// 小さな円の個数
		static const int32  SMALL_CIRCLE_NUM = Config::get<int32>(U"LoadDesktopScene.smallCircleNum");

		// 演出用の円の描画
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
