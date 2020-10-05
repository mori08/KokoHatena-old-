#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 背景色
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.4);
	
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
		registerBoard<Test1Board>(Board::Role::TEST1, 0);
		registerBoard<Test2Board>(Board::Role::TEST2, 0);
	}


	void DesktopScene::update()
	{
		if (MouseL.down())
		{
			// 先頭のBoardの決定
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }

				// TODO moveBoardToTopに変更
				// Boardを先頭に移動
				auto boardPtr = std::move(*boardItr);
				m_boardList.erase(boardItr);
				m_boardList.emplace_front(std::move(boardPtr));

				break;
			}
		}

		if (!m_boardList.empty())
		{
			// 先頭のBoardの入力処理
			(*m_boardList.begin())->input();
		}

		// 各BoardSymbolの更新
		for (auto boardSymbol : m_boardSymbolMap)
		{
			auto boardState = boardSymbol.second.update();

			if (!boardState) { continue; }

			switch (boardState.value())
			{
			case BoardSymbol::BoardState::NONE: // Boardの生成
				m_generateBoardMap[boardSymbol.first](); break;
			}
		}

		// 各Boardの更新
		for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end();)
		{
			if (m_boardSymbolMap.count((*boardItr)->getRole()))
			{
				auto boardState = m_boardSymbolMap.find((*boardItr)->getRole())->second.update();
			}

			auto stateChange = (*boardItr)->update();

			// ボードの削除
			if (stateChange == Board::StateChange::CLOSE)
			{
				// TODO eraseBoardに変更
				auto ersItr = boardItr;
				++boardItr;
				m_boardList.erase(ersItr);
				continue;
			}

			// ボードの非表示
			if (stateChange == Board::StateChange::MINIMIZE)
			{
				// TODO hideBoardに変更
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

		// 処理前に最前面にいるBoardの状態をDisplayに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);

		// 指定されたBoardを最前面に移動
		auto ersItr = boardItr; // 削除するイテレータ
		auto topPtr = std::move(*boardItr); // 最前面に移送させたいポインタ
		++boardItr;
		m_boardList.erase(ersItr);
		m_boardList.emplace_front(std::move(topPtr));

		// 処理前に最前面にいるBoardの状態をTopに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);

		return boardItr;
	}

}
