#pragma once


#include<Siv3D.hpp>
#include "../Board/Board.hpp"
#include"SecurityShareData/SecurityShareData.hpp"
#include"AccessShareData/AccessShareData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareDataクラス
	/// Board間で共有するデータ
	/// BoardSceneへ命令も行う
	/// </summary>
	class BoardShareData
	{
	public:

		enum class BoardStateChange
		{
			OPEN, // 開く,最前面に持ってくる
			CLOSE // 閉じる
		};

	private:

		// ボードの状態変更についてのリスト
		std::list<std::pair<Board::Role, BoardStateChange>> m_boardStateChangeList;

	public:

		// SecurityBoardの状態に関する共有データ
		SecurityShareData m_securityData;

		// AccessBoardの状態に関する共有データ
		AccessShareData m_accessData;

	public:

		BoardShareData();

	public:

		/// <summary>
		/// ボードの状態変更をリストに追加
		/// </summary>
		/// <param name="role"> ボードの種類 </param>
		/// <param name="stateChange"> 変更内容 </param>
		void addBoardStateChange(Board::Role role, BoardStateChange stateChange);

		/// <summary>
		/// ボードの状態変更を取得
		/// </summary>
		/// <returns> ボードの状態変更, 無い場合 none </returns>
		Optional<std::pair<Board::Role, BoardStateChange>> getBoardStateChange();

	};
}