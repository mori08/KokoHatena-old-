#include "MessageData.hpp"


namespace Kokoha
{	
	MessageData::MessageData()
		: m_toml(U"asset/data/message.toml")
	{
		if (!m_toml)
		{
			throw Error(U"Failed to load message.toml");
		}

	}
	
}
