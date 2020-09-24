#pragma once


#include "../Scene.hpp"
#include "../../Board/Board.hpp"


namespace Kokoha
{
	/// <summary>
	/// DesktopSceneクラス
	/// Boardのリストを管理する
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

		// 表示中のボードのリスト
		std::list<std::unique_ptr<Board>> m_boardList;

		// 非表示のボードのリスト
		std::list<std::unique_ptr<Board>> m_hideBoardList;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}