#pragma once


#include "Type/AccessObjectType.hpp"


namespace Kokoha
{
	class AccessShareData;

	/// <summary>
	/// AccessObjectクラス
	/// AccessShareDataで使用するオブジェクト
	/// </summary>
	class AccessObject
	{
	protected:

		// 位置と判定用の範囲
		Circle m_body;

		// 種類
		const AccessObjectType m_type;

	public:

		AccessObject(const Circle& body, const AccessObjectType& type)
			: m_body(body)
			, m_type(type)
		{
		}

		virtual ~AccessObject() {}

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="cursorPos"> カーソルの座標 </param>
		virtual void input(const Vec2&) {}

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="shareData"> 共有データ </param>
		virtual void update(AccessShareData& shareData) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw()const = 0;

		/// <summary>
		/// 削除条件
		/// </summary>
		/// <returns> trueのとき削除 </returns>
		virtual bool isEraseAble()const
		{
			return false;
		}

		/// <summary>
		/// 他オブジェクトの種類と位置の確認
		/// </summary>
		/// <param name="another"> 他オブジェクト </param>
		virtual void checkAnother(const AccessObject& another) = 0;

	public:

		/// <summary>
		/// 指定の種類のオブジェクトと衝突の確認
		/// </summary>
		/// <param name="anther"> 他のオブジェクト </param>
		/// <param name="type"  > 指定する種類     </param>
		/// <returns>
		/// anotherが指定の種類のオブジェクトかつ衝突しているとき true , そうでないとき false
		/// </returns>
		bool checkTypeAndCollision(const AccessObject& another, const AccessObjectType& type) const
		{
			return (another.m_type & type) && m_body.intersects(another.m_body);
		}

		/// <summary>
		/// 指定の種類のオブジェクトのとき座標の取得
		/// </summary>
		/// <param name="type"> 指定する種類 </param>
		/// <returns> 座標 </returns>
		Optional<Vec2> checkTypeAndGetPos(const AccessObjectType& type) const
		{
			return (m_type & type) ? Optional<Vec2>(m_body.center) : Optional<Vec2>(none);
		}

	protected:

		/// <summary>
		/// オブジェクトを移動
		/// </summary>
		/// <param name="movement"> 移動量 </param>
		/// <param name="shareData"> AccessShareData </param>
		/// <returns> 実際に移動した移動量 </returns>
		Vec2 walk(Vec2 movement, const AccessShareData& shareData);

		/// <summary>
		/// オブジェクトを目的地へ移動
		/// </summary>
		/// <param name="speed"> 速さ </param>
		/// <param name="goal"> 目的地 </param>
		/// <param name="shareData"> AccessShareData </param>
		/// <returns> 実際に移動した移動量 </returns>
		Vec2 walkToGoal(double speed, const Vec2& goal, const AccessShareData& shareData);

		/// <summary>
		/// 道の真ん中を通ってオブジェクトを目的地へ移動
		/// </summary>
		/// <param name="speed"> 速さ </param>
		/// <param name="goal"> 目的地 </param>
		/// <param name="shareData"> AccessShareData </param>
		/// <returns> 実際に移動した移動量 </returns>
		Vec2 walkToGoalThroughCenter(double speed, const Vec2& goal, const AccessShareData& shareData);

	};

	using AccessObjectPtr = std::unique_ptr<AccessObject>;
}