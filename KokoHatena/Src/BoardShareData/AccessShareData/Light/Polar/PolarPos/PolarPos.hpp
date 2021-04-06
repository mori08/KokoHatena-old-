#pragma once

#include "../PolarAngle/PolarAngle.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	/// <summary>
	/// PolarPosNX
	/// ΙΐW
	/// </summary>
	class PolarPos : public PolarAngle
	{
	private:

		// £
		double m_distance;

	public:

		/// <summary>
		/// ΙΐW
		/// </summary>
		/// <param name="angle"> px </param>
		/// <param name="distance"> £ </param>
		PolarPos(double angle, double distance)
			: PolarAngle(angle)
			, m_distance(distance)
		{
		}

	public:

		/// <summary>
		/// £ΜζΎ
		/// </summary>
		/// <returns> £ </returns>
		double r() const
		{
			return m_distance;
		}

		/// <summary>
		/// £ΜXV
		/// </summary>
		/// <param name="r"> £ </param>
		/// <remarks>
		/// ψͺm_distanceζθ¬³’κΜέXV
		/// </remarks>
		void setR(double r)
		{
			m_distance = Min(m_distance, r);
		}

		/// <summary>
		/// ΌπΐWΦΟ·
		/// </summary>
		/// <param name="center"> SΐW </param>
		/// <returns> ΌπΐW </returns>
		Vec2 toOrthogonalPos(const Vec2& center)const
		{
			return std::move(center + m_distance * angleToVec(m_angle));
		}

	};
}