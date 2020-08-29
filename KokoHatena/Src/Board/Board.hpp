#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Boardクラス
	/// ボードの基底
	/// </summary>
	class Board
	{
	public:

		/// <summary>
		/// 種類(役割) 識別用にも使う
		/// </summary>
		enum class Role
		{
			MAIL // メール
		};

		/// <summary>
		/// 状態の切り替えについての出力
		/// </summary>
		enum class StateChange
		{
			CLOSE,    // 閉じる
			MINIMIZE, // 最小化
			NONE      // 変更なし
		};

	private:

		// 種類(役割)
		const Role m_role;

		// 名前
		const String m_name;

		// サイズ
		const Size m_size;

		// ウィンドウを左上の座標
		Point m_pos;

	public:

		Board(Role role, const String& name, const Size& size);

	public:

		/// <summary>
		/// 入力の受付
		/// </summary>
		void input();

		/// <summary>
		/// ボード内の入力の受付
		/// </summary>
		virtual void inputInBoard() = 0;

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns> 状態の変更 </returns>
		StateChange update();

		/// <summary>
		/// ボード内の更新
		/// </summary>
		/// <remarks>
		/// マウスやキーボードの入力が必要なものは
		/// input関数で行う
		/// </remarks>
		virtual void updateInBoard() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// ボード内の描画
		/// </summary>
		virtual void drawInBoard() const = 0;

	};

}