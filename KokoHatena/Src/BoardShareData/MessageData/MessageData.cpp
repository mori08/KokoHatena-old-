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


	const Array<Message>& MessageData::getHistory(const String& name) const
	{
		if (!m_history.count(name))
		{
			throw Error(U"Not exist [" + name + U"] in MessageData's history");
		}
		return m_history.find(name)->second;
	}
	
}
