#include "Animation.hpp"


namespace Kokoha
{

	Animation::Animation(const PosOrder& posOrder, bool isLoop)
		: m_totalSecond(getTotalSecond(posOrder))
		, m_posOrder(getPosOrder(posOrder))
		, m_isLoop(isLoop)
	{
	}


	Point Animation::getTexturePos(double animSecond) const
	{
		if (animSecond < m_posOrder.begin()->first)
		{
			// Å‰‚Ì‰æ‘œ
			return m_posOrder.begin()->second;
		}

		if (animSecond > m_posOrder.rbegin()->first)
		{
			// ÅŒã‚Ì‰æ‘œ
			return m_posOrder.rbegin()->second;
		}

		// “ñ•ª’Tõ‚Å‰æ‘œ‚ð‘I‘ð
		size_t l = 0, g = m_posOrder.size() - 1;
		while (g - l > 1)
		{
			size_t mid = (l + g) / 2;
			if (m_posOrder[mid].first < animSecond)
			{
				g = mid;
			}
			else
			{
				l = mid;
			}
		}
		return m_posOrder[g].second;
	}


	double Animation::getTotalSecond(const PosOrder& posOrder)
	{
		double rtn = 0;
		for (const auto& p : posOrder) { rtn += p.first; }
		return rtn;
	}


	PosOrder Animation::getPosOrder(PosOrder posOrder)
	{
		for (int32 i = 1; i < posOrder.size(); ++i)
		{
			posOrder[i].first += posOrder[i - 1].first;
		}
		return std::move(posOrder);
	}
}
