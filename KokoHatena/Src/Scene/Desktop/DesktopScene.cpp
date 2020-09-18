#include "DesktopScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"


namespace
{
	// �w�i�F
	constexpr ColorF BACK_COLOR = Kokoha::myColor(0.05);

	// �A�C�R���o�[�̑���
	constexpr double ICONBAR_THICK = 60.0;
	// �A�C�R���o�[�̐F
	constexpr ColorF ICONBAR_COLOR = Kokoha::myColor(0.4);
}


namespace Kokoha
{

	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
	}


	void DesktopScene::update()
	{

	}


	void DesktopScene::draw() const
	{
		Scene::Rect().draw(BACK_COLOR);

		Rect(0, Scene::Height() - ICONBAR_THICK, Scene::Width(), ICONBAR_THICK).draw(ICONBAR_COLOR);
	}

}
