#include "Button.hpp"


namespace Kokoha
{

	Button::Button(const String& name, const Rect& region)
		: m_name(name)
		, m_region(region)
		, m_onClickFunc([](){})
	{
	}

}