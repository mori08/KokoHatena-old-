#include "StageData.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace
{
	// ������
	constexpr double INF = std::numeric_limits<double>::infinity();
}


namespace Kokoha
{
    bool StageData::isWalkAble(const Point& square) const
    {
        if (square.x < 0 || square.x >= WIDTH) { return false; }
        if (square.y < 0 || square.y >= HEIGHT) { return false; }
        return !m_terrain[squareToInteger(square)];
    }


    Vec2 StageData::getPath(const Vec2& pixelS, const Vec2& pixelT) const
    {
		// �o�H�T�����s���ŒZ����
		static const double MIN_LENGTH = Config::get<double>(U"Board.Access.Stage.minLength");

		if (!isWalkAble(pixelS) || !isWalkAble(pixelT) || (pixelS - pixelT).length() < MIN_LENGTH)
		{
			return Vec2::Zero();
		}

		const int32 s = squareToInteger(pixelToSquare(pixelS));
		const int32 t = squareToInteger(pixelToSquare(pixelT));

		if (s == t)
		{
			return (pixelT - pixelS).normalize();
		}

		return m_path[s][t];
    }


	double StageData::getDistance(const Vec2& pixelS, const Vec2& pixelT) const
	{
		if (!isWalkAble(pixelS) || !isWalkAble(pixelT))
		{
			return INF;
		}

		return m_distance[squareToInteger(pixelToSquare(pixelS))][squareToInteger(pixelToSquare(pixelT))];
	}


	void StageData::init()
	{
		// �n�`�̃��Z�b�g
		for (int32 i = 0; i < N; ++i)
		{
			m_terrain[i] = false;
		}
	}


	void StageData::searchPath()
	{
		// �אڂ���}�X�ɕӂ�����
		for (int32 i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				auto edge = getEdge(i, j);
				m_path[i][j] = edge.first;
				m_distance[i][j] = edge.second;
			}
		}

		// ���[�V�����t���C�h�@��p�����o�H�T��
		for (int32 k = 0; k < N; ++k)
		{
			for (int32 i = 0; i < N; ++i)
			{
				for (int32 j = 0; j < N; ++j)
				{
					if (m_distance[i][j] > m_distance[i][k] + m_distance[k][j])
					{
						m_distance[i][j] = m_distance[i][k] + m_distance[k][j];
						m_path[i][j] = m_path[i][k];
					}
				}
			}
		}
	}


	void StageData::draw() const
	{
		for (int32 i = 0; i < N; ++i)
		{
			const Point square = integerToSquare(i);
			if (isWalkAble(square)) { continue; }
			Rect(SQUARE_SIZE * square, SQUARE_SIZE).draw(MyBlack);
		}
	}


	std::pair<Vec2, double> StageData::getEdge(int s, int t) const
	{
		const Point squareS = integerToSquare(s);
		const Point squareT = integerToSquare(t);
		const Point sub = squareT - squareS;

		// �n�_���I�_���ǂɂȂ�Ƃ�
		if (!isWalkAble(squareS) || !isWalkAble(squareT))
		{
			return { Vec2::Zero(),INF }; // �ӂȂ�
		}

		// �n�_�ƏI�_������Ă���Ƃ�
		if (Abs(sub.x) > 1 || Abs(sub.y) > 1)
		{
			return { Vec2::Zero(),INF }; // �ӂȂ�
		}

		// �n�_�ƏI�_�������_�ł���Ƃ�
		if (sub.isZero())
		{
			return { Vec2::Zero(),0 }; // �R�X�g0
		}

		// �n�_�ɑ΂��ďI�_�������ׂɂ���Ƃ�
		if (sub.x == 0 || sub.y == 0)
		{
			return { Vec2(sub),1 };
		}

		// �n�_�ɑ΂��ďI�_�������΂߂ɂ���Ƃ�

		// ���̉��ɕǂ�����Ƃ�
		if (!isWalkAble(Point(squareS.x, squareT.y)) || !isWalkAble(Point(squareT.x, squareS.y)))
		{
			return { Vec2::Zero(),INF }; // �ӂȂ�
		}

		return { Vec2(sub).normalize(),Sqrt(2) };
	}

}