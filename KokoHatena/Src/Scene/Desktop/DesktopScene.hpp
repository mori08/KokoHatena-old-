#pragma once


#include "../Scene.hpp"
#include "../../Board/Board.hpp"


namespace Kokoha
{
	/// <summary>
	/// DesktopScene�N���X
	/// Board�̃��X�g���Ǘ�����
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

		std::list<std::unique_ptr<Board>> m_boardList;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}