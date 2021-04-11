#include "AccessLight.hpp"
#include "Polar/PolarPair/PolarPair.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyPixelShader/MyPixelShader.hpp"


namespace
{
	// �\���������� �X�e�[�W�O�܂ōs�����Ƃ̂ł��钷��
	constexpr double ENOUGH_LENGTH = 1e4;
	// �\���Z������ ��Q���̌��Ԃ𖄂߂邽�߂̒���
	constexpr double EPSILON = 1e-1;

	/// <summary>
	/// ���ɂ��Ă̒萔�o�b�t�@(PS_1)
	/// </summary>
	struct Light
	{
		Float4 g_color;     // �F
		Float2 g_center;    // ���S
		float  g_r;         // ���a
		float  g_direction; // ����
		float  g_angle;     // �͈�
		Float3 _unused;
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
		// ���̕s�����x
		static double ALPHA = Config::get<double>(U"Board.Access.Light.alpha");

		if (!stageData.isWalkAble(m_circle.center)) { return; }

		// ���𒷕��`�ŋߎ�
		Quad lightQuad =
			(m_angle < Math::HalfPi 
			? RectF(0, -m_circle.r * Sin(m_angle), m_circle.r, 2 * m_circle.r * Sin(m_angle))
			: RectF(m_circle.r*Cos(m_angle), -m_circle.r, m_circle.r*(1-Cos(m_angle)), 2 * m_circle.r)
			).rotatedAt(Vec2::Zero(), m_direction).moveBy(m_circle.center);
		
		// ���̋ɍ��W���X�g
		std::set<PolarPair> lightPosSet;

		// ���̏������W��ݒ�
		setInitLightPos(lightPosSet);

		// �e�̐ݒ�
		for (const RectF& block : stageData.getBlockList())
		{
			if (block.intersects(lightQuad))
			{
				setShadow(lightPosSet, block);
			}
		}

		// �`��
		drawLight(lightPosSet);
		Circle(m_circle.center, 4).draw(MyWhite).drawFrame(0, 2, MyBlack);
		//lightQuad.drawFrame(1, Palette::Blue);
	}


	void AccessLight::setInitLightPos(std::set<PolarPair>& lightPosSet) const
	{
		static RectF STAGE_RECT = Config::get<Rect>(U"Board.Access.Light.stage");

		for (const Vec2& node : getRectNode(STAGE_RECT))
		{
			lightPosSet.insert(PolarPair(node - m_circle.center));
		}

		lightPosSet.insert(PolarPair(+Math::Pi, m_circle.center.x));
		lightPosSet.insert(PolarPair(-Math::Pi, m_circle.center.x));
	}


	void AccessLight::setShadow(std::set<PolarPair>& lightPosSet, const RectF& rect) const
	{
		// �e�̍쐬
		std::set<PolarPair> shadowPosSet;
		for (const auto& node : getRectNode(rect))
		{
			// ���_�E�����̈ʒu�֌W��\���x�N�g��
			Vec2 c = rect.center() - node; c.x /= Abs(c.x); c.y /= Abs(c.y);
			double angle_cen = twoVecToAngle(m_circle.center - node, c);

			if (Abs(angle_cen) < Math::QuarterPi) { continue; }

			// �ɍ��W�̃y�A���쐬
			double distance = node.distanceFrom(m_circle.center);
			std::pair<double, double> distPair = (Abs(angle_cen) > 3 * Math::QuarterPi)
				? std::pair(distance, distance)
				: std::pair(distance, ENOUGH_LENGTH);
			if (angle_cen < 0) { std::swap(distPair.first, distPair.second); }
			PolarPair shadowPos(vecToAngle(node - m_circle.center), distPair);

			// �e�ɋɍ��W��ǉ�
			if (shadowPosSet.count(shadowPos))
			{
				auto itr = shadowPosSet.find(shadowPos);
				shadowPos.posPair.first .setR(itr->posPair.first.r());
				shadowPos.posPair.second.setR(itr->posPair.second.r());
				shadowPosSet.erase(itr);
			}
			shadowPosSet.emplace(shadowPos);
		}

		// �p�xPi�ɋɍ��W��ǉ�
		if (auto distPi
			= PolarPos::twoVecToLine(shadowPosSet.begin()->posPair.first, shadowPosSet.rbegin()->posPair.second, Math::Pi))
		{
			if (shadowPosSet.begin()->m_angle * shadowPosSet.rbegin()->m_angle < 0)
			{
				shadowPosSet.insert(PolarPair(-Math::Pi, distPi.value(), distPi.value()));
				shadowPosSet.insert(PolarPair(+Math::Pi, distPi.value(), distPi.value()));
			}
		}

		// ���̌`���e�ɍ��킹�ĕύX
		auto lightItr = lightPosSet.begin();
		auto shadowItr = shadowPosSet.begin();
		std::pair<double, double> lightPre (lightItr->m_angle , lightItr->posPair.first.r());
		std::pair<double, double> shadowPre(shadowItr->m_angle, shadowItr->posPair.first.r());
		while (lightItr != lightPosSet.end() && shadowItr != shadowPosSet.end())
		{
			PolarPos lightPrePos (lightPre.first,  lightPre.second);
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
			newPolar.posPair.first .setR(shadowItr->posPair.first .r());
			newPolar.posPair.second.setR(shadowItr->posPair.second.r());
			
			lightItr = lightPosSet.erase(lightItr);
			++shadowItr;
			lightPosSet.emplace(newPolar);
		}
	}


	void AccessLight::drawLight(const std::set<PolarPair>& lightPosSet) const
	{
		if (lightPosSet.empty()) { return; }

		static bool debugMode = true;
		if (KeySpace.down()) { debugMode = !debugMode; }

		if (debugMode)
		{
			Vec2 pre = lightPosSet.begin()->posPair.first.toOrthogonalPos(m_circle.center);

			for (const auto& polar : lightPosSet)
			{
				Line(pre, polar.posPair.first.toOrthogonalPos(m_circle.center))
					.drawArrow(6, Vec2(10, 20), Palette::Red);

				Circle(polar.posPair.first.toOrthogonalPos(m_circle.center), 4).draw(Palette::Red);

				if (Abs(polar.posPair.first.r() - polar.posPair.second.r()) < 0.1)
				{
					Circle(polar.posPair.first.toOrthogonalPos(m_circle.center), 8).drawFrame(2, Palette::Red);
				}
				else
				{
					Line
					(
						polar.posPair.first.toOrthogonalPos(m_circle.center),
						polar.posPair.second.toOrthogonalPos(m_circle.center)
					).drawArrow(6, Vec2(10, 20), Palette::Red);
				}
				pre = polar.posPair.second.toOrthogonalPos(m_circle.center);
			}
		}
		else
		{
			Array<Vec2> posAry;
			for (const auto& polar : lightPosSet)
			{
				posAry.emplace_back(polar.posPair.first .toOrthogonalPos(m_circle.center));
				posAry.emplace_back(polar.posPair.second.toOrthogonalPos(m_circle.center));
			}
			
			ColorF color = MyWhite; color.setA(0.5);

			{
				// �萔�o�b�t�@�̐ݒ�
				ConstantBuffer<Light> cb;
				cb->g_color     = color.rgba();
				cb->g_center    = m_circle.center;
				cb->g_r         = (float)m_circle.r;
				cb->g_direction = (float)m_direction;
				cb->g_angle     = (float)m_angle;
				Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

				// �V�F�[�_�̊J�n
				ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::ACCESS_LIGHT));

				// ���̕`��
				Polygon(posAry).draw();
			}
		}
	}
}
