#pragma once


#include"../BoardSymbol/BoardSymbol.hpp"


namespace Kokoha
{
	class BoardShareData;

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
			TEST1,   // テスト1
			TEST2,   // テスト2
			MAIL,    // メール
			SECURITY // セキュリティ
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

		// 操作フレーム
		const Rect m_controlFrame;

		// 閉じるボタン
		const Rect m_closeButton;

		// 最小化ボタン
		const Rect m_minimizeButton;

		// レンダーテクスチャ(ボード内の描画)
		const MSRenderTexture m_render;

		// 左上の座標
		Point m_pos;

		// 不当明度
		double m_alpha;

		// 状態
		StateChange m_state;

		// 座標移動時の基準座標(noneのとき移動しない)
		Optional<Point> m_optMovePos;

	public:

		Board(Role role, const String& name, const Size& size);

		virtual ~Board() {}

	public:

		/// <summary>
		/// 入力の受付
		/// </summary>
		void input(BoardShareData& shareData);

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns> 状態の変更 </returns>
		StateChange update(BoardShareData& shareData);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shareData"> 共有データ </param>
		void draw(const BoardShareData& shareData) const;

		/// <summary>
		/// 種類(役割)の取得
		/// </summary>
		/// <returns> 種類(役割) </returns>
		Role getRole() const
		{
			return m_role;
		}

		/// <summary>
		/// ウィンドウの範囲を示す長方形の取得
		/// </summary>
		/// <returns> ウィンドウの範囲を示す長方形 </returns>
		Rect getRect() const
		{
			return std::move(Rect(m_pos, m_size));
		}

		/// <summary>
		/// マウスで左クリックしたか
		/// </summary>
		/// <returns></returns>
		bool mouseLeftDown() const
		{
			return MouseL.down() 
				&& Rect(m_pos, m_size).mouseOver() 
				&& (Cursor::PosF().y < Scene::Height() - BoardSymbol::height());
		}

		/// <summary>
		/// 表示
		/// </summary>
		void display()
		{
			m_state = StateChange::NONE;
		}

		/// <summary>
		/// 最小化
		/// </summary>
		void minimize()
		{
			m_state = StateChange::MINIMIZE;
		}

		/// <summary>
		/// 削除待ち状態での更新
		/// </summary>
		/// <returns> 削除するとき true, そうでないとき false </returns>
		bool erasingUpdate()
		{
			return changeAlpha();
		}

	protected:


		/// <summary>
		/// ボード内の入力の受付
		/// </summary>
		/// <param name="shareData"> 共有データ </param>
		virtual void inputInBoard(BoardShareData& shareData) = 0;

		/// <summary>
		/// ボード内の更新
		/// </summary>
		/// <param name="shareData"> 共有データ </param>
		/// <remarks>
		/// マウスやキーボードの入力が必要なものは
		/// input関数で行う
		/// </remarks>
		virtual void updateInBoard(BoardShareData& shareData) = 0;

		/// <summary>
		/// ボード内の描画
		/// </summary>
		/// <param name="shareData"> 共有データ </param>
		virtual void drawInBoard(const BoardShareData& shareData) const = 0;

	protected:

		/// <summary>
		/// ボード内のマウス座標の取得
		/// </summary>
		/// <returns> ボード内のマウス座標 </returns>
		Point cursorPosInBoard() const
		{
			return Cursor::Pos() - m_pos;
		}

		/// <summary>
		/// ボード内のマウス座標の取得
		/// </summary>
		/// <returns> ボード内のマウス座標 </returns>
		Vec2 cursorPosFInBoard() const
		{
			return Cursor::PosF() - m_pos;
		}

	private:

		/// <summary>
		/// 不当明度の変更
		/// </summary>
		/// <returns> 変更が終了したとき true , そうでないとき false </returns>
		bool changeAlpha();

		/// <summary>
		/// カーソルでの座標の移動
		/// <\summary>
		void movePos();

	};

}