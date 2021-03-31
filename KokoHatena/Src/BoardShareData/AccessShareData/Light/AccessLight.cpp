#include "AccessLight.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyPixelShader/MyPixelShader.hpp"


namespace
{
	// �\���������� �X�e�[�W�O�܂ōs�����Ƃ̂ł��钷��
	constexpr double ENOUGH_LENGTH = 1e4;
	// �\���Z������ ��Q���̌��Ԃ𖄂߂邽�߂̒���
	constexpr double EPSILON = 1e-2;

	/// <summary>
	/// ���ɂ��Ă̒萔�o�b�t�@(PS_1)
	/// </summary>
	struct Light
	{
		Float4 g_color;  // �F
		Float2 g_center; // ���S
		float  g_r;      // ���a
		float  g_blur;   // �ڂ���
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
		// ���̂ڂ���
		static float BLUR = Config::get<float>(U"Board.Access.Light.blur");

		if (!stageData.isWalkAble(m_circle.center)) { return; }

		// ���𒷕��`�ŋߎ�
		Quad lightQuad =
			RectF(0, -(m_circle.r + BLUR) * Sin(m_angle), (m_circle.r + BLUR), 2 * (m_circle.r + BLUR) * Sin(m_angle))
			.rotatedAt(Vec2::Zero(), m_direction)
			.moveBy(m_circle.center);

		// ���̐ݒ�
		std::list<Vec2> lightPosList;
		setInitLightPos(lightPosList);

		// �e�̐ݒ�
		for (const auto& block : stageData.getBlockList())
		{
			if (!block.intersects(lightQuad)) { continue; }
			setShadow(lightPosList, block);
		}

		// list��Array�ɕϊ�
		Array<Vec2> posAry;
		for (const auto& pos : lightPosList)
		{
			posAry.emplace_back(pos);
		}

		{
			// �萔�o�b�t�@�̐ݒ�
			ConstantBuffer<Light> cb;
			cb->g_color  = ColorF(MyWhite, ALPHA).rgba();
			cb->g_center = m_circle.center;
			cb->g_r      = static_cast<float>(m_circle.r);
			cb->g_blur   = BLUR;
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
			// �V�F�[�_�̊J�n
			ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::ACCESS_LIGHT));

			// ���̕`��
			Polygon(posAry).draw();
		}
	}


	void AccessLight::setInitLightPos(std::list<Vec2>& lightPosList) const
	{
		// �X�e�[�W�������L��������
		static RectF STAGE_RECT = Config::get<Rect>(U"Board.Access.Light.stage");

		// ����
		lightPosList.emplace_back(m_circle.center);

		// �ӂƂ̌�_
		for (const auto& stageEdge : getRectEdge(STAGE_RECT))
		{
			if (auto p = stageEdge.intersectsAt(Line(m_circle.center, m_circle.center + ENOUGH_LENGTH * angleToVec(m_direction + m_angle))))
			{
				lightPosList.emplace_back(p.value()); break;
			}
		}

		// �p
		for (const Vec2& pos : getRectNode(STAGE_RECT))
		{
			const Vec2 a = angleToVec(m_direction - m_angle), b = angleToVec(m_direction + m_angle);
			const Vec2 c = pos - m_circle.center;
			const Vec2 d = angleToVec(m_direction);
			if (d.x * c.x + d.y * c.y < 0) { continue; }
			if ((c.y * a.x - c.x * a.y) * (c.y * b.x - c.x * b.y) < 0) { lightPosList.emplace_back(pos); }
		}

		// �ӂƂ̌�_
		for (const auto& stageEdge : getRectEdge(STAGE_RECT))
		{
			if (auto p = stageEdge.intersectsAt(Line(m_circle.center, m_circle.center + ENOUGH_LENGTH * angleToVec(m_direction - m_angle))))
			{
				lightPosList.emplace_back(p.value()); break;
			}
		}

		// ����
		lightPosList.emplace_back(m_circle.center);
	}


	void AccessLight::setShadow(std::list<Vec2>& lightPosList, const RectF& rect) const
	{
		std::list<Vec2> shadowPosList;

		const Vec2 c = Vec2(rect.center() - m_circle.center).normalized();
		
		// �����Ƃ̊p�x���ő�,�ŏ��ɂȂ���� {�p�x,�C���f�b�N�X}
		std::pair<double, int32> max_angle{ -Math::Pi,0 };
		std::pair<double, int32> min_angle{ +Math::Pi,0 };

		// �e���_�̊p�x�̌v�Z
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

		// �e�̌`�̌���
		shadowPosList.emplace_back(m_circle.center + ENOUGH_LENGTH * (nodes[min_angle.second] - m_circle.center));
		shadowPosList.emplace_back(nodes[min_angle.second]);
		if ((min_angle.second + 1) % nodes.size() != max_angle.second)
		{
			shadowPosList.emplace_back(nodes[(min_angle.second + 1) % nodes.size()]);
		}
		shadowPosList.emplace_back(nodes[max_angle.second]);
		shadowPosList.emplace_back(m_circle.center + ENOUGH_LENGTH * (nodes[max_angle.second] - m_circle.center));

		// ��_�̌v�Z
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

		// ��_��2�łȂ��ꍇ
		if (crossCnt < 2) { return; }

		// �e�̌`�ɍ��킹�Č��̌`���X�V
		lightPosList.insert(std::next(lightCrossPosItr.first, 1), crossPos.first);
		lightPosList.erase(std::next(lightCrossPosItr.first, 2), lightCrossPosItr.second);
		lightPosList.insert(std::next(lightCrossPosItr.first, 2), shadowCrossPosItr.first, shadowCrossPosItr.second);
		lightPosList.insert(lightCrossPosItr.second, crossPos.second);

		// �߂����_���폜����
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
