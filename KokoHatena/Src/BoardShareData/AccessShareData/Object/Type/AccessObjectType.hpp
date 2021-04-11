#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// AccessObjectTypeクラス
	/// AccessObjectの種類 またはその集合
	/// unit8型の1bitを1種類に割り当てる
	/// </summary>
	class AccessObjectType
	{
	private:

		uint8 m_value;

	public:

		static const AccessObjectType PLAYER;

	private:

		constexpr AccessObjectType(uint8 value)
			: m_value(value)
		{
		}

	public:

		/// <summary>
		/// 和集合の作成
		/// </summary>
		AccessObjectType operator|(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value | another.m_value);
		}

		/// <summary>
		/// 積集合の作成
		/// </summary>
		AccessObjectType operator&(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value & another.m_value);
		}

		/// <summary>
		/// 差集合の作成
		/// </summary>
		AccessObjectType operator-(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value & ~another.m_value);
		}

		/// <summary>
		/// 集合に追加
		/// </summary>
		const AccessObjectType& operator|=(const AccessObjectType& another)
		{
			m_value |= another.m_value;
			return *this;
		}

		/// <summary>
		/// 集合から削除
		/// </summary>
		const AccessObjectType& operator-=(const AccessObjectType& another)
		{
			m_value &= ~another.m_value;
			return *this;
		}

		/// <summary>
		/// 補集合の取得
		/// </summary>
		const AccessObjectType operator~()const
		{
			return AccessObjectType(~m_value);
		}

		/// <summary>
		/// 空集合のとき false , そうでないとき true
		/// </summary>
		explicit operator bool() const
		{
			return m_value != 0;
		}

	};
}