
#include<Siv3D.hpp>

namespace
{
	// 画面サイズ
	constexpr Size WINDOW_SIZE(800, 600);
}

void Main()
{
	Window::Resize(WINDOW_SIZE);

	while (System::Update())
	{
		
	}
}
