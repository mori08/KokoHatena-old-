#pragma once


#include "../../AccessShareData.hpp"


namespace Kokoha
{
	class TestObject : public AccessObject
	{
	public:

		TestObject(const Vec2& pos)
			: AccessObject(Circle(pos, 10), AccessObjectType::PLAYER)
		{
		}

	private:

		void update(AccessShareData& shareData) override;

		void draw() const override;

		void checkAnother(const AccessObject&) override {}

	};
}