#pragma once


#include"../LoadScene.hpp"


namespace Kokoha
{
	/// <summary>
	/// ロードシーンのデバッグ用シーン
	/// </summary>
	class TestLoadScene : public LoadScene
	{
	public:

		TestLoadScene(const InitData& init);

	private:

		void subUpdate() override;

	};
}