#include "DesktopScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 背景色
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.05);

	// アイコンバーの太さ
	constexpr double ICONBAR_THICK = 60.0;
	// アイコンバーの色
	constexpr ColorF ICONBAR_COLOR = Kokoha::myColor(0.4);
}


namespace Kokoha
{

	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
	}


	void DesktopScene::update()
	{

	}


	void DesktopScene::draw() const
	{
		Scene::Rect().draw(BACK_COLOR);

		Rect(0, Scene::Height() - ICONBAR_THICK, Scene::Width(), ICONBAR_THICK).draw(ICONBAR_COLOR);
	}

}
