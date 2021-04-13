#pragma once


#include "../../AccessShareData.hpp"


namespace Kokoha
{
	class TestObject : public AccessObject
	{
	private:

		Vec2 goal;
		double direction;

	public:

		TestObject(const Vec2& pos);

	private:

		void input(const Vec2& cursorPos) override;

		void update(AccessShareData& shareData) override;

		void draw() const override;

		void checkAnother(const AccessObject&) override {}

	};
}