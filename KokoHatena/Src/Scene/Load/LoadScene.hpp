#pragma once


#include<future>
#include"../Scene.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadScene�N���X
	/// ���Ԃ̂�����(FPS���ቺ���邩������Ȃ�)������ʃX���b�h�ōs��
	/// </summary>
	class LoadScene : public MyApp::Scene
	{
	private:

		// ���[�h����X���b�h
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
		/// ���o�p�̍X�V
		/// </summary>
		virtual void subUpdate();

	};
}