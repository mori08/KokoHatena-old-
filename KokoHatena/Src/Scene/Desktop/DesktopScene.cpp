#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �w�i�F
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.4);
	
	// �^�X�N�o�[�̉E��̍��W
	constexpr Point TASKBAR_POS = Point(0, 600 - Kokoha::BoardSymbol::SIZE);

	// �^�X�N�o�[�̐F
	constexpr ColorF TASKBAR_COLOR = Kokoha::myColor(0.05);


}


namespace Kokoha
{
	const Point DesktopScene::TASKBAR_POS = Point(0, 600 - Kokoha::BoardSymbol::SIZE);


	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		registerBoard<Test1Board>(Board::Role::TEST1, 0);
		registerBoard<Test1Board>(Board::Role::TEST2, 0);
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
			if (m_boardSymbolMap.count((*boardItr)->getRole()))
			{
				m_boardSymbolMap.find((*boardItr)->getRole())->second.update();
			}

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

		Rect(TASKBAR_POS, Scene::Width(), BoardSymbol::SIZE).draw(TASKBAR_COLOR);

		for (const auto& symbol : m_boardSymbolMap)
		{
			symbol.second.draw();
		}
	}


	DesktopScene::BoardPtrList::iterator DesktopScene::moveBoardToTop(BoardPtrList::iterator boardItr)
	{
		if (m_boardList.empty())
		{
			throw Error(U"BoardList is empty");
		}

		// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Display�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAY);

		// �w�肳�ꂽBoard���őO�ʂɈړ�
		auto ersItr = boardItr; // �폜����C�e���[�^
		auto topPtr = std::move(*boardItr); // �őO�ʂɈڑ����������|�C���^
		++boardItr;
		m_boardList.erase(ersItr);
		m_boardList.emplace_front(std::move(topPtr));

		// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Top�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);

		return boardItr;
	}

}
