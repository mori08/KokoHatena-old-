#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �w�i�F
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.05);

	// �A�C�R���o�[�̑���
	constexpr int32 ICONBAR_THICK = 60;
	// �A�C�R���o�[�̐F
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
