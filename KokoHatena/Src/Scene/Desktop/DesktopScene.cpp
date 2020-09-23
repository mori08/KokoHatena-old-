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
		m_boardList.emplace_back(std::make_unique<TestBoard>());
	}


	void DesktopScene::update()
	{
		if (MouseL.down())
		{
			// �擪��Board�̌���
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }
				// Board���N���b�N�����Ƃ�

				// Board��擪�Ɉړ�
				auto boardPtr = std::move(*boardItr);
				m_boardList.erase(boardItr);
				m_boardList.emplace_front(std::move(boardPtr));

				break;
			}
		}

		if (!m_boardList.empty())
		{
			(*m_boardList.begin())->input();
		}

		for (const auto& boardPtr : m_boardList)
		{
			boardPtr->update();
		}
	}


	void DesktopScene::draw() const
	{
		Scene::Rect().draw(BACK_COLOR);

		for (auto boardItr = m_boardList.rbegin(); boardItr != m_boardList.rend(); ++boardItr)
		{
			(*boardItr)->draw();
		}

		Rect(0, Scene::Height() - ICONBAR_THICK, Scene::Width(), ICONBAR_THICK).draw(ICONBAR_COLOR);
	}

}
