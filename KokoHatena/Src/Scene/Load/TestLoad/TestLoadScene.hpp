#pragma once


#include"../LoadScene.hpp"


namespace Kokoha
{
	/// <summary>
	/// ���[�h�V�[���̃f�o�b�O�p�V�[��
	/// </summary>
	class TestLoadScene : public LoadScene
	{
	public:

		TestLoadScene(const InitData& init);

	private:

		void subUpdate() override;

	};
}