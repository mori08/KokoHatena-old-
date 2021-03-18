#include "StageData.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace
{
	// 無限大
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
		// 経路探索を行う最短距離
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
		// 地形のリセット
		for (int32 i = 0; i < N; ++i)
		{
			m_terrain[i] = false;
		}
	}


	void StageData::searchPath()
	{
		// 隣接するマスに辺をつける
		for (int32 i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				auto edge = getEdge(i, j);
				m_path[i][j] = edge.first;
				m_distance[i][j] = edge.second;
			}
		}

		// ワーシャルフロイド法を用いた経路探索
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

		// 始点か終点が壁になるとき
		if (!isWalkAble(squareS) || !isWalkAble(squareT))
		{
			return { Vec2::Zero(),INF }; // 辺なし
		}

		// 始点と終点が離れているとき
		if (Abs(sub.x) > 1 || Abs(sub.y) > 1)
		{
			return { Vec2::Zero(),INF }; // 辺なし
		}

		// 始点と終点が同じ点であるとき
		if (sub.isZero())
		{
			return { Vec2::Zero(),0 }; // コスト0
		}

		// 始点に対して終点がすぐ隣にあるとき
		if (sub.x == 0 || sub.y == 0)
		{
			return { Vec2(sub),1 };
		}

		// 始点に対して終点がすぐ斜めにあるとき

		// その横に壁があるとき
		if (!isWalkAble(Point(squareS.x, squareT.y)) || !isWalkAble(Point(squareT.x, squareS.y)))
		{
			return { Vec2::Zero(),INF }; // 辺なし
		}

		return { Vec2(sub).normalize(),Sqrt(2) };
	}

}