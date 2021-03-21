#include "AccessLight.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	AccessLight::AccessLight(const Circle& circle, const Vec2& direction, double cosin)
		: m_circle(circle)
		, m_direction(direction)
		, m_cosin(cosin)
	{
	}


	void AccessLight::draw(const StageData& stageData) const
	{
		ClearPrint();
		if (!stageData.isWalkAble(m_circle.center)) { return; }

		// 照らす範囲をポリゴンで管理
		Polygon polygon = m_circle.asPolygon(24);

		// 光が届く範囲のマス
		Rect rect = getRectFromTwoPoint
		(
			StageData::pixelToSquare(m_circle.center - Vec2::One() * m_circle.r),
			StageData::pixelToSquare(m_circle.center + Vec2::One() * m_circle.r)
		);

		// 影になる部分をポリゴンから削除
		for (const auto& square : getGridPoint(rect))
		{
			if (stageData.isWalkAble(square) || !stageData.isInBoard(square)) { continue; }

			// 影の範囲の計算
			Rect cell(square * StageData::SQUARE_SIZE, StageData::SQUARE_SIZE);
			Array<Vec2> pointList;
			for (const auto& p : { cell.tl()+Vec2(-e,-e),cell.tr()+Vec2(e,-e),cell.bl()+Vec2(-e,e),cell.br()+Vec2(e,e) })
			{
				pointList.emplace_back(p);
				pointList.emplace_back(p + 1000 * (p - m_circle.center)); // 1000は十分遠い距離として使用
			}
			Polygon shadow = Polygon(pointList).calculateConvexHull();

			// 影部分を光から削除
			if (!shadow.intersects(polygon)) { continue; }
			auto polygons = Geometry2D::Subtract(polygon, shadow);
			if (!polygons.empty()) { polygon = polygons[0]; }
		}

		polygon.draw(ColorF(1,1,1,0.5));
		Circle(m_circle.center, 2).draw(Palette::Red);
	}
}
