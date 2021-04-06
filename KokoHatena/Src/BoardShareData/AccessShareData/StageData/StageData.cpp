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
		m_blockList.clear();
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


	void StageData::makeBlockList()
	{
		Array<Array<int32>> isChecked(WIDTH, Array<int32>(HEIGHT, 0));

		for (int32 i = 0; i < N; ++i)
		{
			// 左上の座標
			Point p = integerToSquare(i);
			if (isWalkAble(p) || isChecked[p.x][p.y]) { continue; }

			// サイズ
			Size s = Size::One();
			while (p.x + s.x < WIDTH && !isWalkAble(Point(p.x + s.x, p.y)) && !isChecked[p.x + s.x][p.y]) { s.x++; }
			while (p.y + s.y < HEIGHT)
			{
				bool flag = true;
				for (int32 x = p.x; x < p.x + s.x; ++x)
				{
					if (isWalkAble(Point(x, p.y + s.y))||isChecked[x][p.y + s.y]) { flag = false; break; }
				}
				if (!flag) { break; }
				s.y++;
			}

			m_blockList.emplace_back(p * SQUARE_SIZE, s * SQUARE_SIZE);

			// チェックリストの更新
			for (const auto& square : getGridPoint(Rect(p, s - Point::One())))
			{
				isChecked[square.x][square.y] = 1;
			}
		}
	}


	void StageData::draw() const
	{
#ifdef _DEBUG
		static bool debugMode = true;
		debugMode ^= Key0.up();

		// デバッグ時に薄い明りとマスを示す線を描画
		if (debugMode)
		{
			Scene::Rect().draw(Color(MyWhite, 0x20));
			for (int32 i = 0; i < StageData::N; ++i)
			{
				const Point square = StageData::integerToSquare(i);
				Rect(StageData::SQUARE_SIZE * square, StageData::SQUARE_SIZE).drawFrame(1, MyBlack);
			}
		}
#endif // _DEBUG

		for (int32 i = 0; i < N; ++i)
		{
			const Point square = integerToSquare(i);
			if (isWalkAble(square)) { continue; }
			Rect(SQUARE_SIZE * square, SQUARE_SIZE).draw(MyBlack);
		}

#ifdef _DEBUG

		if (debugMode)
		{
			if (m_blockList.empty()) { return; }
			m_blockList[(int32)(Scene::Time()) % m_blockList.size()].drawFrame(1, Palette::Aqua);
			FontAsset(U"15")(ToString((int32)(Scene::Time()) % m_blockList.size())).drawAt(m_blockList[(int32)(Scene::Time()) % m_blockList.size()].center(), Palette::Aqua);
		}
#endif // _DEBUG
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