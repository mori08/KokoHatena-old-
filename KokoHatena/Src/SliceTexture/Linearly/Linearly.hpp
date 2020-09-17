#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Lineary�N���X
	/// ���^�I�ɒl��ύX
	/// ���double��Vec2,Vec3�Ȃǂ̏����l�ň���
	/// </summary>
	/// <typeparam name="Type"> �ύX����l�̌^ </typeparam>
	template<typename Type>
	class Linearly
	{
	private:

		// ���b�Œl��ύX���邩 (DeltaTime��������1�t���[����mRate��1�ɂ���)
		double m_changeSecond;

		// �[�_ { �n�_, �I�_ }
		std::pair<Type, Type> m_endPoint;

		// ������ [0,1]
		double m_rate;

	public:

		/// <summary>
		/// ���`�⊮
		/// </summary>
		/// <param name="changeSecond"> ���b�Œl��ύX���邩 </param>
		/// <param name="start"       > �n�_                 </param>
		/// <param name="goal"        > �I�_                 </param>
		Linearly(double changeSecond, const Type& start, const Type& goal)
			: m_changeSecond(changeSecond)
			, m_endPoint({ start,goal })
			, m_rate(0)
		{
		}

		/// <summary>
		/// ���`�⊮
		/// </summary>
		/// <param name="changeSecond"> ���b�Œl��ύX���邩 </param>
		/// <param name="goal"        > �I�_                 </param>
		Linearly(double changeSecond, Type goal)
			: m_changeSecond(changeSecond)
			, m_endPoint({ Type(),goal })
			, m_rate(0)
		{
		}

		/// <summary>
		/// �n�_�ɖ߂�
		/// </summary>
		void restart()
		{
			m_rate = 0;
		}

		/// <summary>
		/// �I�_�ɂƂ΂�
		/// </summary>
		void toGoal()
		{
			m_rate = 1;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		/// <returns>
		/// �����䂪 1 �𒴂����� true, �����łȂ��Ƃ� false
		/// </returns>
		bool update()
		{
			const double deltaTime = Scene::DeltaTime();

			if (deltaTime > m_changeSecond) // mChangeSecond��0�̂Ƃ��̑΍�
			{
				m_rate = 1;
				return true;
			}

			m_rate += deltaTime / m_changeSecond;

			if (m_rate > 1)
			{
				m_rate = 1;
				return true;
			}

			return false;
		}

		/// <summary>
		/// �l�̎擾
		/// </summary>
		Type getValue() const
		{
			return Type(m_endPoint.first + m_rate * (m_endPoint.second - m_endPoint.first));
		}

		/// <summary>
		/// �I�_�̎擾
		/// </summary>
		Type getGoal() const
		{
			return m_endPoint.first + m_endPoint.second;
		}

	};
}