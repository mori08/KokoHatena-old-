#pragma once


#include "../Scene.hpp"
#include "../../Board/Board.hpp"
#include "../../BoardSymbol/BoardSymbol.hpp"


namespace Kokoha
{
	/// <summary>
	/// DesktopSceneクラス
	/// Boardのリストを管理する
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

		/// <summary>
		/// Boardのポインタのリスト
		/// </summary>
		using BoardPtrList = std::list<std::unique_ptr<Board>>;

	private:

		// 表示中のボードのリスト
		BoardPtrList m_boardList;

		// 非表示のボードのリスト
		BoardPtrList m_hideBoardList;

		// タスクバーに配置するボタン
		std::unordered_map<Board::Role, BoardSymbol> m_boardSymbolMap;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="boardItr"></param>
		/// <returns></returns>
		BoardPtrList::iterator moveBoardToTop(BoardPtrList::iterator boardItr);

	};
}