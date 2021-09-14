#include "AccessLight.hpp"
#include "Polar/PolarPair/PolarPair.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyPixelShader/MyPixelShader.hpp"


namespace
{
	// 十分長い長さ ステージ外まで行くことのできる長さ
	constexpr double ENOUGH_LENGTH = 1e4;
	// 十分短い長さ 障害物の隙間を埋めるための長さ
	constexpr double EPSILON = 1e-1;
}


namespace Kokoha
{
	AccessLight::AccessLight(const Circle& circle, const ColorF color)
		: m_circle(circle)
		, m_color(color)
	{
	}


	ColorF AccessLight::white(double alpha)
	{
		return ColorF(MyWhite).setA(alpha);
	}


	void AccessLight::draw(const StageData& stageData) const
	{
		if (!stageData.isWalkAble(m_circle.center)) { return; }
		if (m_circle.r < 1e-1) { return; }

		// 光を長方形で近似
		RectF lightRect(Arg::center(m_circle.center), 2 * m_circle.r);

		// 光の極座標リスト
		std::set<PolarPair> lightPosSet;

		// 光の初期座標を設定
		setInitLightPos(lightPosSet);

		// 影の設定
		for (const RectF& block : stageData.getBlockList())
		{
			if (block.intersects(lightRect))
			{
				setShadow(lightPosSet, block);
			}
		}

		// 描画
		drawLight(lightPosSet);
	}


	void AccessLight::setInitLightPos(std::set<PolarPair>& lightPosSet) const
	{
		static const RectF STAGE_RECT = Config::get<Rect>(U"Board.Access.Light.stage");

		for (const Vec2& node : getRectNode(STAGE_RECT))
		{
			lightPosSet.insert(PolarPair(node - m_circle.center));
		}

		lightPosSet.insert(PolarPair(+Math::Pi, m_circle.center.x));
		lightPosSet.insert(PolarPair(-Math::Pi, m_circle.center.x));
	}


	void AccessLight::setShadow(std::set<PolarPair>& lightPosSet, const RectF& rect) const
	{
		// 影の作成
		std::set<PolarPair> shadowPosSet;
		for (const auto& node : getRectNode(rect))
		{
			// 頂点・光源の位置関係を表すベクトル
			Vec2 c = rect.center() - node; c.x /= Abs(c.x); c.y /= Abs(c.y);
			double angle_cen = twoVecToAngle(m_circle.center - node, c);

			if (Abs(angle_cen) < Math::QuarterPi) { continue; }

			// 極座標のペアを作成
			double distance = node.distanceFrom(m_circle.center);
			std::pair<double, double> distPair = (Abs(angle_cen) > 3 * Math::QuarterPi)
				? std::pair(distance, distance)
				: std::pair(distance, ENOUGH_LENGTH);
			if (angle_cen < 0) { std::swap(distPair.first, distPair.second); }
			PolarPair shadowPos(vecToAngle(node - m_circle.center), distPair);

			// 影に極座標を追加
			if (shadowPosSet.count(shadowPos))
			{
				auto itr = shadowPosSet.find(shadowPos);
				shadowPos.posPair.first.setR(itr->posPair.first.r());
				shadowPos.posPair.second.setR(itr->posPair.second.r());
				shadowPosSet.erase(itr);
			}
			shadowPosSet.emplace(shadowPos);
		}

		// 角度Piに極座標を追加
		if (auto distPi
			= PolarPos::twoVecToLine(shadowPosSet.begin()->posPair.first, shadowPosSet.rbegin()->posPair.second, Math::Pi))
		{
			if (shadowPosSet.begin()->m_angle * shadowPosSet.rbegin()->m_angle < 0)
			{
				shadowPosSet.insert(PolarPair(-Math::Pi, distPi.value(), distPi.value()));
				shadowPosSet.insert(PolarPair(+Math::Pi, distPi.value(), distPi.value()));
			}
		}

		// 光の形を影に合わせて変更
		auto lightItr = lightPosSet.begin();
		auto shadowItr = shadowPosSet.begin();
		std::pair<double, double> lightPre(lightItr->m_angle, lightItr->posPair.first.r());
		std::pair<double, double> shadowPre(shadowItr->m_angle, shadowItr->posPair.first.r());
		while (lightItr != lightPosSet.end() && shadowItr != shadowPosSet.end())
		{
			PolarPos lightPrePos(lightPre.first, lightPre.second);
			PolarPos shadowPrePos(shadowPre.first, shadowPre.second);

			if (*lightItr < *shadowItr)
			{
				if (lightItr->m_angle < shadowPrePos.m_angle)
				{
					lightPre = { lightItr->m_angle, lightItr->posPair.second.r() };
					++lightItr; continue;
				}

				lightPre = { lightItr->m_angle,lightItr->posPair.second.r() };

				auto crossR = PolarPos::twoVecToLine(shadowItr->posPair.first, shadowPrePos, lightItr->m_angle);
				if (!crossR) { ++lightItr; continue; }

				if (crossR.value() > lightItr->posPair.first.r() && crossR.value() > lightItr->posPair.second.r())
				{
					++lightItr; continue;
				}

				if (crossR.value() < lightItr->posPair.first.r() - EPSILON && crossR.value() < lightItr->posPair.second.r() - EPSILON)
				{
					lightItr = lightPosSet.erase(lightItr); continue;
				}

				PolarPair newPolar(*lightItr);
				newPolar.posPair.first.setR(crossR.value());
				newPolar.posPair.second.setR(crossR.value());
				lightItr = lightPosSet.erase(lightItr);
				lightPosSet.emplace(newPolar);
				continue;
			}

			if (*shadowItr < *lightItr)
			{
				if (shadowItr->m_angle < lightPrePos.m_angle)
				{
					shadowPre = { shadowItr->m_angle, shadowItr->posPair.second.r() };
					++shadowItr; continue;
				}

				shadowPre = { shadowItr->m_angle,shadowItr->posPair.second.r() };

				auto crossR = PolarPos::twoVecToLine(lightItr->posPair.first, lightPrePos, shadowItr->m_angle);
				if (crossR)
				{
					if (crossR.value() > shadowItr->posPair.first.r() - EPSILON || crossR.value() > shadowItr->posPair.second.r() - EPSILON)
					{
						PolarPair newPolar(*shadowItr);
						newPolar.posPair.first.setR(crossR.value());
						newPolar.posPair.second.setR(crossR.value());
						lightPosSet.insert(newPolar);
					}
				}

				++shadowItr; continue;
			}

			lightPre = { lightItr->m_angle,lightItr->posPair.second.r() };
			shadowPre = { shadowItr->m_angle,shadowItr->posPair.second.r() };

			PolarPair newPolar(*lightItr);
			newPolar.posPair.first.setR(shadowItr->posPair.first.r());
			newPolar.posPair.second.setR(shadowItr->posPair.second.r());

			lightItr = lightPosSet.erase(lightItr);
			++shadowItr;
			lightPosSet.emplace(newPolar);
		}
	}


	void AccessLight::drawLight(std::set<PolarPair>& lightPosSet) const
	{
		if (lightPosSet.empty()) { return; }

		Array<Vec2> posAry;
		for (auto pre = lightPosSet.begin(), itr = std::next(pre); itr != lightPosSet.end(); pre = itr, ++itr)
		{
			getAngleFromLine(pre->posPair.second, itr->posPair.first, lightPosSet);
		}

		static const int32 QUALITY = Config::get<int32>(U"Board.Access.Light.quality");
		auto itr = lightPosSet.begin();
		std::pair<double, double> pre = { itr->m_angle, itr->posPair.first.r() };
		for (int32 i = -QUALITY; i <= QUALITY;)
		{
			const double angle = Math::Pi * i / QUALITY;

			if (angle > itr->m_angle)
			{
				addToPosAry(itr->posPair.first , posAry);
				addToPosAry(itr->posPair.second, posAry);
				pre = { itr->m_angle, itr->posPair.second.r() };
				if (++itr == lightPosSet.end()) { break; }
				continue;
			}

			PolarPos prePolar(pre.first, pre.second);

			auto optR = PolarPos::twoVecToLine(prePolar, itr->posPair.first, angle);

			if (optR && optR.value() > m_circle.r)
			{
				addToPosAry(PolarPos(angle, m_circle.r), posAry);
			}

			++i;
		}

		Polygon(posAry).draw(m_color);
	}


	void AccessLight::getAngleFromLine(const PolarPos& p1, const PolarPos& p2, std::set<PolarPair>& lightPosSet) const
	{
		if (p1.r() - m_circle.r < 0 && p2.r() - m_circle.r < 0) { return; }

		if ((p1.r() - m_circle.r) * (p2.r() - m_circle.r) < 0)
		{
			// 交点を計算
			double l = p1.m_angle, g = p2.m_angle;
			if (p1.r() > p2.r()) { std::swap(l, g); }
			while(true)
			{
				const double m = (l + g) / 2;
				if (auto r = PolarPos::twoVecToLine(p1, p2, m))
				{
					if (Abs(r.value() - m_circle.r) < 1e-2)
					{
						lightPosSet.insert(PolarPair(m, r.value()));
						return;
					}

					if (r.value() < m_circle.r) { l = m; }
					else { g = m; }
					continue;
				}
				return;
			}
			return;
		}

		if (Abs(p1.r() - m_circle.r) < 1e-2) { return; }
		if (Abs(p2.r() - m_circle.r) < 1e-2) { return; }

		// m_circle.centerに一番近い点を計算
		std::pair<double, double>
			lp = { p1.m_angle, p1.r() },
			gp = { p2.m_angle, p2.r() };
		
		while (Abs(gp.first - lp.first) * m_circle.r > 1e-1)
		{
			const double angle = (lp .first + gp.first) / 2;
			if (auto r = PolarPos::twoVecToLine(p1, p2, angle))
			{
				if (lp.second > gp.second) { lp = { angle, r.value() }; }
				else { gp = { angle, r.value() }; }

				continue;
			}
			return;
		}

		if (lp.second > m_circle.r) { return; }

		double l = lp.first, g = p2.m_angle;
		while(true)
		{
			const double m = (l + g) / 2;
			if (auto r = PolarPos::twoVecToLine(p1, p2, m))
			{
				if (Abs(r.value() - m_circle.r) < 1e-2)
				{
					lightPosSet.insert(PolarPair(m, r.value()));
					if (2 * lp.first - m < p1.m_angle) { return; }
					lightPosSet.insert(PolarPair(2 * lp.first - m, r.value()));
					return;
				}

				if (r.value() < m_circle.r) { l = m; }
				else { g = m; }
				continue;
			}
			return;
		}
		return;
	}


	void AccessLight::addToPosAry(PolarPos polar, Array<Vec2>& posAry) const
	{
		polar.setR(m_circle.r);
		Vec2 pos = polar.toOrthogonalPos(m_circle.center);
		
		if (!posAry.empty() && posAry.rbegin()->distanceFrom(pos) < 1e-1) { return; }
		posAry.emplace_back(pos);
	}
}
