#pragma once


#include "../Scene.hpp"


namespace Kokoha
{
	/// <summary>
	/// DesktopSceneクラス
	/// Boardのリストを管理する
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}