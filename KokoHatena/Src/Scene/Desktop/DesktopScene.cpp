#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �w�i�F
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.15);
	
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
		registerBoard<TestBoard>(Board::Role::TEST1, 0);
		registerBoard<TestBoard>(Board::Role::TEST2, 0);
	}


	void DesktopScene::update()
	{
		if (MouseL.down())
		{
			// �擪��Board�̌���
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }
				moveBoardToTop(boardItr);
				break;
			}
		}

		if (!m_boardList.empty())
		{
			// �擪��Board�̓��͏���
			(*m_boardList.begin())->input();
		}

		// �eBoardSymbol�̍X�V
		for (auto& boardSymbol : m_boardSymbolMap)
		{
			auto boardState = boardSymbol.second.update();

			if (!boardState) { continue; }

			switch (boardState.value())
			{
			case BoardSymbol::BoardState::NONE:      // Board�̐���
				m_generateBoardMap[boardSymbol.first](); break;

			case BoardSymbol::BoardState::DISPLAYED: // �őO�ʂɈړ�
				moveBoardToTop(findBoardFromRole(boardSymbol.first)); break;

			case BoardSymbol::BoardState::TOP:       // ��\��
				(*findBoardFromRole(boardSymbol.first))->minimize(); break;

			case BoardSymbol::BoardState::HIDDEN:    // Board�̕\��
				displayBoard(boardSymbol.first); break;
			}
		}

		// �eBoard�̍X�V
		for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end();)
		{
			auto stateChange = (*boardItr)->update();

			// �{�[�h�̍폜
			if (stateChange == Board::StateChange::CLOSE) { boardItr = eraseBoard(boardItr); continue; }

			// �{�[�h�̔�\��
			if (stateChange == Board::StateChange::MINIMIZE) { boardItr = hideBoard(boardItr); continue; }
			
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


	DesktopScene::BoardPtrList::iterator DesktopScene::findBoardFromRole(const Board::Role& role)
	{
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if ((*itr)->getRole() == role) { return itr; }
		}
		return m_boardList.end();
	}


	DesktopScene::BoardPtrList::iterator DesktopScene::moveBoardToTop(BoardPtrList::iterator boardItr)
	{
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Failed to find Board");
		}

		// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Display�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);

		// �w�肳�ꂽBoard���őO�ʂɈړ�
		auto ersItr = boardItr; // �폜����C�e���[�^
		auto topPtr = std::move(*boardItr); // �őO�ʂɈڑ����������|�C���^
		++boardItr;
		m_boardList.erase(ersItr);
		m_boardList.emplace_front(std::move(topPtr));

		// ������ɍőO�ʂɂ���Board�̏�Ԃ�Top�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);

		return boardItr;
	}


	DesktopScene::BoardPtrList::iterator DesktopScene::eraseBoard(BoardPtrList::iterator boardItr)
	{
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Failed to find Board");
		}

		// �폜����Board�̏�Ԃ�None�ɕύX
		m_boardSymbolMap.find((*boardItr)->getRole())->second.setState(BoardSymbol::BoardState::NONE);

		// �w�肳�ꂽBoard�̍폜
		auto ersItr = boardItr;
		++boardItr;
		m_boardList.erase(ersItr);

		// �őO�ʂɂ���Board��Top�ɕύX
		if (!m_boardList.empty())
		{
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
		}

		return boardItr;
	}


	DesktopScene::BoardPtrList::iterator DesktopScene::hideBoard(BoardPtrList::iterator boardItr)
	{
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Failed to find Board");
		}

		// ��\���ɂ���Board�̏�Ԃ�Hidden�ɕύX
		m_boardSymbolMap.find((*boardItr)->getRole())->second.setState(BoardSymbol::BoardState::HIDDEN);

		// �w�肳�ꂽBoard���\����
		auto boardPtr = std::move(*boardItr);
		auto ersItr = boardItr;
		++boardItr;
		m_boardList.erase(ersItr);
		m_hideBoardMap.try_emplace(boardPtr->getRole(), std::move(boardPtr));

		// �őO�ʂɂ���Board��Top�ɕύX
		if (!m_boardList.empty())
		{
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
		}

		return boardItr;
	}


	void DesktopScene::displayBoard(Board::Role role)
	{
		if (!m_hideBoardMap.count(role))
		{
			throw Error(U"Failed to find Board");
		}

		if (!m_boardList.empty())
		{
			// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Display�ɕύX
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);
		}

		// �w�肳�ꂽBoard��\��
		auto hideItr = m_hideBoardMap.find(role);
		hideItr->second->display();
		m_boardList.emplace_front(std::move(hideItr->second));
		m_hideBoardMap.erase(role);

		// �����O�ɍőO�ʂɂ���Board�̏�Ԃ�Top�ɕύX
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
	}

}
