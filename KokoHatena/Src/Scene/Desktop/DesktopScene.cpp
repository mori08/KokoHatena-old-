#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �w�i�F
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.4);

	// �^�X�N�o�[�̑���
	constexpr int32 TASKBAR_THICK = 60;
	
	// �^�X�N�o�[�̉E��̍��W
	constexpr Point TASKBAR_POS = Point(0, 600 - TASKBAR_THICK);

	// �^�X�N�o�[�̐F
	constexpr ColorF TASKBAR_COLOR = Kokoha::myColor(0.05);


}


namespace Kokoha
{

	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		m_boardList.emplace_back(std::make_unique<TestBoard>());

		// �^�X�N�o�[�̃{�^���̐ݒ�
		m_boardSymbolMap.try_emplace(Board::Role::TEST, std::move(BoardSymbol(TASKBAR_POS, 0)));
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

		for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end();)
		{
			auto state = (*boardItr)->update();

			// �{�[�h�̍폜
			if (state == Board::StateChange::CLOSE)
			{
				auto ersItr = boardItr;
				++boardItr;
				m_boardList.erase(ersItr);
				continue;
			}

			// �{�[�h�̔�\��
			if (state == Board::StateChange::MINIMIZE)
			{
				auto boardPtr = std::move(*boardItr);
				auto ersItr = boardItr;
				++boardItr;
				m_boardList.erase(ersItr);
				m_hideBoardList.emplace_back(std::move(boardPtr));
				continue;
			}
			
			++boardItr;
		}
	}


	void DesktopScene::draw() const
	{
		Scene::Rect().draw(BACK_COLOR);

		for (auto boardItr = m_boardList.rbegin(); boardItr != m_boardList.rend(); ++boardItr)
		{
			(*boardItr)->draw();
		}

		Rect(TASKBAR_POS, Scene::Width(), TASKBAR_THICK).draw(TASKBAR_COLOR);

		for (const auto& symbol : m_boardSymbolMap)
		{
			symbol.second.draw();
		}
	}

}
