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

		/// <remarks>
		/// �����瑤�̃R���X�g���N�^���g�p����ꍇ
		/// �K��setLoadThread�Ŋ֐���ݒ肷�邱��
		/// </remarks>
		LoadScene(const InitData& init);

		virtual ~LoadScene();

	private:

		void update() override;

		virtual void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	protected:

		/// <summary>
		/// ���o�p�̍X�V
		/// </summary>
		virtual void subUpdate();

		/// <summary>
		/// �X���b�h�Ɋ֐��̐ݒ�
		/// </summary>
		/// <param name="loadFunc"> �֐� </param>
		void setLoadThread(std::function<SceneName()> loadFunc);

	};
}