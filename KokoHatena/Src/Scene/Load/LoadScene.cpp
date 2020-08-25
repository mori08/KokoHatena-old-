#include "LoadScene.hpp"


namespace
{
	// テキストを表示する座標
	constexpr Point TEXT_POS = Point(690, 530);
}



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
