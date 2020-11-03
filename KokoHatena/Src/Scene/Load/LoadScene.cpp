#include "LoadScene.hpp"
#include "../../Config/Config.hpp"


namespace Kokoha
{

	LoadScene::LoadScene(const InitData& init, std::function<SceneName()> loadFunc)
		: IScene(init)
	{
		// スレッドの開始
		m_loadThread = std::async(std::launch::async, loadFunc);
	}


	LoadScene::~LoadScene()
	{
	}


	void LoadScene::update()
	{
		// 演出用の更新
		subUpdate();

		// スレッドの状況を取得
		auto status = m_loadThread.wait_for(std::chrono::microseconds(0));

		// スレッドが終了していたらシーン遷移
		if (status != std::future_status::timeout)
		{
			auto sceneName = m_loadThread.get();

			if (!changeScene(sceneName))
			{
				changeScene(SceneName::TITLE);
			}
		}
	}


	void LoadScene::draw() const
	{
		// テキストを表示する座標
		static const Point TEXT_POS = Config::get<Point>(U"LoadScene.textPos");
		FontAsset(U"20")(U"Loading").draw(TEXT_POS);
	}


	void LoadScene::drawFadeIn(double) const
	{
		draw();
	}


	void LoadScene::drawFadeOut(double) const
	{
		draw();
	}


	void LoadScene::subUpdate()
	{
	}

}
