#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 背景色
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.15);
	
	// タスクバーの右上の座標
	constexpr Point TASKBAR_POS = Point(0, 600 - Kokoha::BoardSymbol::SIZE);

	// タスクバーの色
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
			// 先頭のBoardの決定
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }
				moveBoardToTop(boardItr);
				break;
			}
		}

		if (!m_boardList.empty())
		{
			// 先頭のBoardの入力処理
			(*m_boardList.begin())->input();
		}

		// 各BoardSymbolの更新
		for (auto& boardSymbol : m_boardSymbolMap)
		{
			auto boardState = boardSymbol.second.update();

			if (!boardState) { continue; }

			switch (boardState.value())
			{
			case BoardSymbol::BoardState::NONE:      // Boardの生成
				m_generateBoardMap[boardSymbol.first](); break;

			case BoardSymbol::BoardState::DISPLAYED: // 最前面に移動
				moveBoardToTop(findBoardFromRole(boardSymbol.first)); break;

			case BoardSymbol::BoardState::TOP:       // 非表示
				(*findBoardFromRole(boardSymbol.first))->minimize(); break;

			case BoardSymbol::BoardState::HIDDEN:    // Boardの表示
				displayBoard(boardSymbol.first); break;
			}
		}

		// 各Boardの更新
		for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end();)
		{
			auto stateChange = (*boardItr)->update();

			// ボードの削除
			if (stateChange == Board::StateChange::CLOSE) { boardItr = eraseBoard(boardItr); continue; }

			// ボードの非表示
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

		// 処理前に最前面にいるBoardの状態をDisplayに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);

		// 指定されたBoardを最前面に移動
		auto ersItr = boardItr; // 削除するイテレータ
		auto topPtr = std::move(*boardItr); // 最前面に移送させたいポインタ
		++boardItr;
		m_boardList.erase(ersItr);
		m_boardList.emplace_front(std::move(topPtr));

		// 処理後に最前面にいるBoardの状態をTopに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);

		return boardItr;
	}


	DesktopScene::BoardPtrList::iterator DesktopScene::eraseBoard(BoardPtrList::iterator boardItr)
	{
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Failed to find Board");
		}

		// 削除するBoardの状態をNoneに変更
		m_boardSymbolMap.find((*boardItr)->getRole())->second.setState(BoardSymbol::BoardState::NONE);

		// 指定されたBoardの削除
		auto ersItr = boardItr;
		++boardItr;
		m_boardList.erase(ersItr);

		// 最前面にきたBoardをTopに変更
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

		// 非表示にするBoardの状態をHiddenに変更
		m_boardSymbolMap.find((*boardItr)->getRole())->second.setState(BoardSymbol::BoardState::HIDDEN);

		// 指定されたBoardを非表示に
		auto boardPtr = std::move(*boardItr);
		auto ersItr = boardItr;
		++boardItr;
		m_boardList.erase(ersItr);
		m_hideBoardMap.try_emplace(boardPtr->getRole(), std::move(boardPtr));

		// 最前面にきたBoardをTopに変更
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
			// 処理前に最前面にいるBoardの状態をDisplayに変更
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);
		}

		// 指定されたBoardを表示
		auto hideItr = m_hideBoardMap.find(role);
		hideItr->second->display();
		m_boardList.emplace_front(std::move(hideItr->second));
		m_hideBoardMap.erase(role);

		// 処理前に最前面にいるBoardの状態をTopに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
	}

}
