#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 背景色
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.05);

	// アイコンバーの太さ
	constexpr int32 ICONBAR_THICK = 60;
	// アイコンバーの色
	constexpr ColorF ICONBAR_COLOR = Kokoha::myColor(0.4);
}


namespace Kokoha
{

	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		m_boardList.emplace_back(std::make_unique<TestBoard>());
	}


	void DesktopScene::update()
	{
		(*m_boardList.begin())->input();

		for (auto& itr : m_boardList)
		{
			itr->input();
			itr->update();
		}
	}


	void DesktopScene::draw() const
	{
		Scene::Rect().draw(BACK_COLOR);

		for (const auto& itr : m_boardList)
		{
			itr->draw();
		}

		Rect(0, Scene::Height() - ICONBAR_THICK, Scene::Width(), ICONBAR_THICK).draw(ICONBAR_COLOR);
	}

}
