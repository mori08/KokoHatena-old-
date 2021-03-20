#include "LoadRecordScene.hpp"
#include "../../../RecordManager/RecordManager.hpp"


namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData init)
		: LoadScene
		(
			init,
			[]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(3));
				switch (RecordManager::instance().load())
				{
				case RecordManager::LoadResult::NEW_GAME:
				case RecordManager::LoadResult::CONTINUE:
					return SceneName::DESKTOP_LOAD;
				case RecordManager::LoadResult::ERROR:
					return SceneName::TITLE;
				}
				return SceneName::TITLE;
			}
		)
	{
	}


	void LoadRecordScene::subUpdate()
	{
		
	}


	void LoadRecordScene::draw() const
	{
		
	}


}
