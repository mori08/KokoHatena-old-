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

		// タスクバーの右上の座標
		static const Point TASKBAR_POS;

		// 表示中のボードのリスト
		BoardPtrList m_boardList;

		// 非表示のボードのリスト
		BoardPtrList m_hideBoardList;

		// タスクバーに配置するボタン
		std::unordered_map<Board::Role, BoardSymbol> m_boardSymbolMap;

		// Board生成用の連想配列
		std::unordered_map<Board::Role, std::function<void()>> m_generateBoardMap;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// Boardの登録
		/// </summary>
		/// <typeparam name="BoardType"> Boardの型 </typeparam>
		/// <param name="role"> Boardに対応するBoard::Role </param>
		template<typename BoardType>
		void registerBoard(const Board::Role& role, int32 id);

		/// <summary>
		/// Board::Roleに対応するBoardのイテレータを探す
		/// </summary>
		/// <param name="role"> Boardに対応するBoard::Role </param>
		/// <returns> 対応するイテレータ </returns>
		BoardPtrList::iterator findBoardFromRole(const Board::Role& role);

		/// <summary>
		/// 指定したBoardを最前面に移動
		/// </summary>
		/// <param name="boardItr"> 指定したBoardに対応したイテレータ </param>
		/// <returns> 次のイテレータ </returns>
		BoardPtrList::iterator moveBoardToTop(BoardPtrList::iterator boardItr);

		/// <summary>
		/// Boardの生成
		/// </summary>
		/// <typeparam name="BoardType"> Boardの型 </typeparam>
		template<typename BoardType>
		void generateBoard();

		/// <summary>
		/// Boardの削除
		/// </summary>
		/// <param name="boardItr"> 削除したいBoardのイテレータ </param>
		/// <returns> 次のイテレータ </returns>
		BoardPtrList::iterator eraseBoard(BoardPtrList::iterator boardItr);

	};
	

	template<typename BoardType>
	void DesktopScene::registerBoard(const Board::Role& role, int32 id)
	{
		if (m_boardSymbolMap.count(role)) { return; }

		Point pos = TASKBAR_POS + Point(m_boardSymbolMap.size() * BoardSymbol::SIZE, 0);
		m_boardSymbolMap.try_emplace(role, std::move(BoardSymbol(pos, id)));

		// TODO 関数作る
		m_generateBoardMap[role] = [this]() { generateBoard<BoardType>(); };
	}


	template<typename BoardType>
	inline void DesktopScene::generateBoard()
	{
		if (!m_boardList.empty())
		{
			// 処理前に最前面にいるBoardの状態をDisplayに変更
			m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::DISPLAYED);
		}

		// ボードの生成
		m_boardList.emplace_front(std::make_unique<BoardType>());

		// 処理前に最前面にいるBoardの状態をTopに変更
		m_boardSymbolMap.find((*m_boardList.begin())->getRole())->second.setState(BoardSymbol::BoardState::TOP);
	}

}