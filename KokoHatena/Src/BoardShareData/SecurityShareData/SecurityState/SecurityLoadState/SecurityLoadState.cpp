#include "SecurityLoadState.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	SecurityLoadState::SecurityLoadState(const String& text, const std::function<void()>& finishFunc, const std::function<void()>& closeFunc)
		: SecurityState(closeFunc)
		, m_text(text)
		, m_finishFunc(finishFunc)
		, m_progress(Config::get<double>(U"Board.Security.Load.ProgressBar.range.init"))
	{
		
	}


	void SecurityLoadState::input(Optional<Vec2>)
	{
	}


	void SecurityLoadState::update(const Vec2&)
	{
		static const double MAX_PROGRESS = Config::get<double>(U"Board.Security.Load.ProgressBar.range.max");
		static const double SPEED = Config::get<double>(U"Board.Security.Load.ProgressBar.speed");
		
		m_progress += SPEED * Scene::DeltaTime();
		if (m_progress > MAX_PROGRESS)
		{
			m_finishFunc();
		}
	}


	void SecurityLoadState::draw() const
	{
		static const Point BAR_POS = Config::get<Point>(U"Board.Security.Load.ProgressBar.pos");
		static const double BAR_LENGTH = Config::get<double>(U"Board.Security.Load.ProgressBar.length");
		static const double BAR_WIDTH  = Config::get<double>(U"Board.Security.Load.ProgressBar.width");
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Load.textPos");

		FontAsset(U"15")(m_text).draw(TEXT_POS, MyWhite);
		RectF(BAR_POS, BAR_LENGTH * Clamp(m_progress, 0.0, 1.0), BAR_WIDTH).draw(MyWhite);
	}
}
