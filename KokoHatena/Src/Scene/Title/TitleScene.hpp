#pragma once


#include"../Scene.hpp"
#include"../../ButtonSet/ButtonSet.hpp"


namespace Kokoha
{
	/*
	* TitleScene�N���X
	* �^�C�g���V�[��
	*/
	class TitleScene : public MyApp::Scene
	{
	private:
		
		// �{�^���̊Ǘ�
		ButtonSet m_buttonSet;

		// �J�[�\���̕�
		double m_cursorWidth;

		// �J�[�\���̉��ɏo����̒���
		double m_cursorLineLength;

		// �J�[�\���̉��ɏo����̕s�����x
		double m_cursorLineAlpha;

		// �^�C�g�����S�p�̃s�N�Z���V�F�[�_
		const PixelShader m_logoShader;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void updateFadeOut(double) override;

		void draw() const override;

	private:

		/// <summary>
		/// ���S�̕`��
		/// </summary>
		/// <param name="frequency"> �p�x         </param>
		/// <param name="shift"    > ����̑傫�� </param>
		void drawLogo(double frequency, double shift) const;

		/// <summary>
		/// �V�F�[�_���Ɏg�p����V�t�g�̃x�N�g��
		/// </summary>
		/// <param name="frequency"> �p�x         </param>
		/// <param name="shift"    > ����̑傫�� </param>
		/// <returns> �V�t�g�̃x�N�g�� </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}