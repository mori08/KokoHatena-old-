#include "Config.hpp"


namespace Kokoha
{
	Config::Config()
		: m_toml(U"asset/data/config.toml")
	{
		const String name = U"LoadRecordScene.LogoAnim";

		PosOrder posOrder;
		for (const auto& obj : m_toml[name][U"posOrder"].tableArrayView())
		{
			std::pair<double, Point> timePos;
			timePos.first = obj[U"t"].get<double>();
			timePos.second.x = obj[U"x"].get<int32>();
			timePos.second.y = obj[U"y"].get<int32>();
			posOrder << timePos;
		}
		bool loop = m_toml[name][U"loop"].get<bool>();
		
		Animation anim(posOrder, loop);
	}
}
