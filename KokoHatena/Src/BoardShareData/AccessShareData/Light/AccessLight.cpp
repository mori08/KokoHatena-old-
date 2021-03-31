#include "AccessLight.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyPixelShader/MyPixelShader.hpp"


namespace
{
	// 十分長い長さ ステージ外まで行くことのできる長さ
	constexpr double ENOUGH_LENGTH = 1e4;
	// 十分短い長さ 障害物の隙間を埋めるための長さ
	constexpr double EPSILON = 1e-2;

	/// <summary>
	/// 光についての定数バッファ(PS_1)
	/// </summary>
	struct Light
	{
		Float4 g_color;  // 色
		Float2 g_center; // 中心
		float  g_r;      // 半径
		float  g_blur;   // ぼかし
	};
}


namespace Kokoha
{
	AccessLight::AccessLight(const Circle& circle, double direction, double angle)
		: m_circle(circle)
		, m_direction(direction)
		, m_angle(angle)
	{
	}


	void AccessLight::draw(const StageData& stageData) const
	{
		// 光の不透明度
		static double ALPHA = Config::get<double>(U"Board.Access.Light.alpha");
		// 光のぼかし
		static float BLUR = Config::get<float>(U"Board.Access.Light.blur");

		if (!stageData.isWalkAble(m_circle.center)) { return; }

		// 光を長方形で近似
		Quad lightQuad =
			RectF(0, -(m_circle.r + BLUR) * Sin(m_angle), (m_circle.r + BLUR), 2 * (m_circle.r + BLUR) * Sin(m_angle))
			.rotatedAt(Vec2::Zero(), m_direction)
			.moveBy(m_circle.center);

		// 光の設定
		std::list<Vec2> lightPosList;
		setInitLightPos(lightPosList);

		// 影の設定
		for (const auto& block : stageData.getBlockList())
		{
			if (!block.intersects(lightQuad)) { continue; }
			setShadow(lightPosList, block);
		}

		// listをArrayに変換
		Array<Vec2> posAry;
		for (const auto& pos : lightPosList)
		{
			posAry.emplace_back(pos);
		}

		{
			// 定数バッファの設定
			ConstantBuffer<Light> cb;
			cb->g_color  = ColorF(MyWhite, ALPHA).rgba();
			cb->g_center = m_circle.center;
			cb->g_r      = static_cast<float>(m_circle.r);
			cb->g_blur   = BLUR;
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
			// シェーダの開始
			ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::ACCESS_LIGHT));

			// 光の描画
			Polygon(posAry).draw();
		}
	}


	void AccessLight::setInitLightPos(std::list<Vec2>& lightPosList) const
	{
		// ステージを少し広げたもの
		static RectF STAGE_RECT = Config::get<Rect>(U"Board.Access.Light.stage");

		// 光源
		lightPosList.emplace_back(m_circle.center);

		// 辺との交点
		for (const auto& stageEdge : getRectEdge(STAGE_RECT))
		{
			if (auto p = stageEdge.intersectsAt(Line(m_circle.center, m_circle.center + ENOUGH_LENGTH * angleToVec(m_direction + m_angle))))
			{
				lightPosList.emplace_back(p.value()); break;
			}
		}

		// 角
		for (const Vec2& pos : getRectNode(STAGE_RECT))
		{
			const Vec2 a = angleToVec(m_direction - m_angle), b = angleToVec(m_direction + m_angle);
			const Vec2 c = pos - m_circle.center;
			const Vec2 d = angleToVec(m_direction);
			if (d.x * c.x + d.y * c.y < 0) { continue; }
			if ((c.y * a.x - c.x * a.y) * (c.y * b.x - c.x * b.y) < 0) { lightPosList.emplace_back(pos); }
		}

		// 辺との交点
		for (const auto& stageEdge : getRectEdge(STAGE_RECT))
		{
			if (auto p = stageEdge.intersectsAt(Line(m_circle.center, m_circle.center + ENOUGH_LENGTH * angleToVec(m_direction - m_angle))))
			{
				lightPosList.emplace_back(p.value()); break;
			}
		}

		// 光源
		lightPosList.emplace_back(m_circle.center);
	}


	void AccessLight::setShadow(std::list<Vec2>& lightPosList, const RectF& rect) const
	{
		std::list<Vec2> shadowPosList;

		const Vec2 c = Vec2(rect.center() - m_circle.center).normalized();
		
		// 光源との角度が最大,最小になるもの {角度,インデックス}
		std::pair<double, int32> max_angle{ -Math::Pi,0 };
		std::pair<double, int32> min_angle{ +Math::Pi,0 };

		// 各頂点の角度の計算
		const Array<Vec2> nodes = getRectNode(rect);
		for (int32 i = 0; i < nodes.size(); ++i)
		{
			const Vec2 a = Vec2(nodes[i] - m_circle.center).normalized();

			const double nodeAngle = Acos(c.x * a.x + c.y * a.y) * (c.y * a.x - c.x * a.y > 0 ? 1 : -1);

			if (nodeAngle > max_angle.first)
			{
				max_angle = { nodeAngle,i };
			}
			if (nodeAngle < min_angle.first)
			{
				min_angle = { nodeAngle,i };
			}
		}

		// 影の形の決定
		shadowPosList.emplace_back(m_circle.center + ENOUGH_LENGTH * (nodes[min_angle.second] - m_circle.center));
		shadowPosList.emplace_back(nodes[min_angle.second]);
		if ((min_angle.second + 1) % nodes.size() != max_angle.second)
		{
			shadowPosList.emplace_back(nodes[(min_angle.second + 1) % nodes.size()]);
		}
		shadowPosList.emplace_back(nodes[max_angle.second]);
		shadowPosList.emplace_back(m_circle.center + ENOUGH_LENGTH * (nodes[max_angle.second] - m_circle.center));

		// 交点の計算
		std::pair<std::list<Vec2>::iterator, std::list<Vec2>::iterator> shadowItr = { shadowPosList.begin(),std::next(shadowPosList.begin(),1) };
		std::pair<std::list<Vec2>::iterator, std::list<Vec2>::iterator> lightCrossPosItr;
		std::pair<std::list<Vec2>::iterator, std::list<Vec2>::iterator> shadowCrossPosItr;
		std::pair<Vec2, Vec2> crossPos;
		int32 crossCnt = 0;

		lightCrossPosItr.first = lightPosList.begin();
		for (; shadowItr.second != shadowPosList.end(); ++shadowItr.first, ++shadowItr.second)
		{
			Line shadowLine(*shadowItr.first, *shadowItr.second);
			std::pair<std::list<Vec2>::iterator, std::list<Vec2>::iterator> lightItr 
				= { lightCrossPosItr.first,std::next(lightCrossPosItr.first,1) };

			for (; lightItr.second != lightPosList.end(); ++lightItr.first, ++lightItr.second)
			{
				Line lightLine(*lightItr.first, *lightItr.second);
				auto p = lightLine.intersectsAt(shadowLine);

				if (!p) { continue; }
				if (IsNaN(p.value().x) || IsNaN(p.value().y)) { continue; }
				if (crossCnt == 1 && crossPos.first.distanceFrom(p.value()) < EPSILON) { continue; }
				if (crossCnt == 2 && crossPos.second.distanceFrom(p.value()) < EPSILON) { continue; }

				if (crossCnt == 0)
				{
					lightCrossPosItr.first = lightItr.first;
					shadowCrossPosItr.first = shadowItr.second;
					crossPos.first = p.value();
				}
				else if (crossCnt != 0)
				{
					lightCrossPosItr.second = lightItr.second;
					shadowCrossPosItr.second = shadowItr.second;
					crossPos.second = p.value();
				}

				++crossCnt;
			}
		}

		// 交点が2つでない場合
		if (crossCnt < 2) { return; }

		// 影の形に合わせて光の形を更新
		lightPosList.insert(std::next(lightCrossPosItr.first, 1), crossPos.first);
		lightPosList.erase(std::next(lightCrossPosItr.first, 2), lightCrossPosItr.second);
		lightPosList.insert(std::next(lightCrossPosItr.first, 2), shadowCrossPosItr.first, shadowCrossPosItr.second);
		lightPosList.insert(lightCrossPosItr.second, crossPos.second);

		// 近い頂点を削除する
		std::unordered_map<Point, std::list<Vec2>::iterator> posMap;
		for (auto itr = lightPosList.begin(); std::next(itr,1) != lightPosList.end();)
		{
			if (posMap.count(itr->asPoint()))
			{
				lightPosList.erase(posMap[itr->asPoint()],itr);
			}
			posMap[itr->asPoint()] = itr;
			++itr;
		}
	}
}
