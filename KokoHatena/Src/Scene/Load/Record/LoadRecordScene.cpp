#include "LoadRecordScene.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace
{
	// テキストを表示する座標
	constexpr Point TEXT_DRAW_POS(420, 480);

	// 演出の円
	constexpr Circle LOADING_CIRCLE(360, 480, 11.0);
	// 演出の弧の太さ
	constexpr double LOADING_ARC_THICNESS = 2.0;
	// 演出の弧の長さ
	constexpr double LOADING_ARC_LENGTH = 5.0;
	// 小さな円の個数
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
		
		FontAsset(U"20")(U"Loading").drawAt(TEXT_DRAW_POS, MyWhite);
	}


}
