#include "SecurityLoadState.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	SecurityLoadState::SecurityLoadState(const String& text, const std::function<void()>& finishFunc)
		: m_text(text)
		, m_finishFunc(finishFunc)
		, m_progress(Config::get<double>(U"Board.Security.Load.ProgressBar.range.init"))
	{
		
	}


	void SecurityLoadState::input(Optional<Vec2>)
	{
	}


	void SecurityLoadState::update(const Vec2&)
	{
		static const double SPEED = Config::get<double>(U"Board.Security.Load.ProgressBar.speed");
		m_progress += SPEED * Scene::DeltaTime();
	}


	void SecurityLoadState::draw() const
	{
		static const Point BAR_POS = Config::get<Point>(U"Board.Security.Load.ProgressBar.pos");
		static const double BAR_LENGTH = Config::get<double>(U"Board.Security.Load.ProgressBar.length");

		RectF(BAR_POS, BAR_LENGTH * Clamp(m_progress, 0.0, 1.0), 1).draw(MyWhite);
	}
}
