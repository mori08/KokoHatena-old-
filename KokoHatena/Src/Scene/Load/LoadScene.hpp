#pragma once


#include<future>
#include"../Scene.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadSceneクラス
	/// 時間のかかる(FPSが低下するかもしれない)処理を別スレッドで行う
	/// </summary>
	class LoadScene : public MyApp::Scene
	{
	private:

		// ロードするスレッド
		std::future<SceneName> m_loadThread;

	public:

		LoadScene(const InitData& init, std::function<SceneName()> loadFunc);

		virtual ~LoadScene();

	private:

		void update() override;

		virtual void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	private:

		/// <summary>
		/// 演出用の更新
		/// </summary>
		virtual void subUpdate();

	};
}