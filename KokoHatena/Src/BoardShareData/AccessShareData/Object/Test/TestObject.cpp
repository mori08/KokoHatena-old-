#include "TestObject.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	void TestObject::update(AccessShareData&)
	{
		
	}


	void TestObject::draw() const
	{
		m_body.draw(MyBlack);
	}
}
