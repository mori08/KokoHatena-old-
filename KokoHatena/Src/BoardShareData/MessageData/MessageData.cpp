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

		Print << m_toml[U"Test.text"].getString();
		Print << m_toml[U"Test.num"].get<int32>();
		Print << m_toml[U"Test.flag"].get<bool>();
	}
	
}
