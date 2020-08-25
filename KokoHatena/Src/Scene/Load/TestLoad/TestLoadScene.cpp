#include "TestLoadScene.hpp"


namespace Kokoha
{
	TestLoadScene::TestLoadScene(const InitData& init)
		: LoadScene
		(
			init,
			[]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return SceneName::TITLE;
			}
		)
	{
	}

	void TestLoadScene::subUpdate()
	{
		ClearPrint();
		Print << Scene::Time();
	}
}
