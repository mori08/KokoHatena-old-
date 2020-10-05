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
		registerBoard<Test2Board>(Board::Role::TEST2, 0);
	}


	void DesktopScene::update()
	{
		if (MouseL.down())
		{
			// �擪��Board�̌���
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }

				// TODO moveBoardToTop�ɕύX
				// Board��擪�Ɉړ�
				auto boardPtr = std::move(*boardItr);
				m_boardList.erase(boardItr);
				m_boardList.emplace_front(std::move(boardPtr));

				break;
			}
		}

		if (!m_boardList.empty())
		{
			// �擪��Board�̓��͏���
			(*m_boardList.begin())->input();
		}

		// �eBoardSymbol�̍X�V
		for (auto boardSymbol : m_boardSymbolMap)
		{
			auto boardState = boardSymbol.second.update();

			if (!boardState) { continue; }

			switch (boardState.value())
			{
			case BoardSymbol::BoardState::NONE: // Board�̐���
				m_generateBoardMap[boardSymbol.first](); break;
			}
		}

		// �eBoard�̍X�V
		for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end();)
		{
			if (m_boardSymbolMap.count((*boardItr)->getRole()))
			{
				auto boardState = m_boardSymbolMap.find((*boardItr)->getRole())->second.update();
			}

			auto stateChange = (*boardItr)->update();

			// �{�[�h�̍폜
			if (stateChange == Board::StateChange::CLOSE)
			{
				// TODO eraseBoard�ɕύX
				auto ersItr = boardItr;
				++boardItr;
				m_boardList.erase(ersItr);
				continue;
			}

			// �{�[�h�̔�\��
			if (stateChange == Board::StateChange::MINIMIZE)
			{
				// TODO hideBoard�ɕύX
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
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);

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
