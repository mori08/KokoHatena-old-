#include "DesktopScene.hpp"
#include "../../Board/Test/TestBoard.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 背景色
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.4);

	// タスクバーの太さ
	constexpr int32 TASKBAR_THICK = 60;
	
	// タスクバーの右上の座標
	constexpr Point TASKBAR_POS = Point(0, 600 - TASKBAR_THICK);

	// タスクバーの色
	constexpr ColorF TASKBAR_COLOR = Kokoha::myColor(0.05);


}


namespace Kokoha
{

	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		m_boardList.emplace_back(std::make_unique<TestBoard>());

		// タスクバーのボタンの設定
		m_boardSymbolMap.try_emplace(Board::Role::TEST, std::move(BoardSymbol(TASKBAR_POS, 0)));
	}


	void DesktopScene::update()
	{
		if (MouseL.down())
		{
			// 先頭のBoardの決定
			for (auto boardItr = m_boardList.begin(); boardItr != m_boardList.end(); ++boardItr)
			{
				if (!(*boardItr)->getRect().mouseOver()) { continue; }
				// Boardをクリックしたとき

				// Boardを先頭に移動
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

			// ボードの削除
			if (state == Board::StateChange::CLOSE)
			{
				auto ersItr = boardItr;
				++boardItr;
				m_boardList.erase(ersItr);
				continue;
			}

			// ボードの非表示
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
