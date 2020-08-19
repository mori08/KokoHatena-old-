
#include"MyLibrary/MyLibrary.hpp"

namespace
{
	// 画面サイズ
	constexpr Size WINDOW_SIZE(800, 600);
}

void Main()
{
	Window::Resize(WINDOW_SIZE);

	// アセット管理
	Kokoha::registerAsset(U"asset/");
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);

	while (System::Update())
	{
		Kokoha::showFPS();
	}
}
