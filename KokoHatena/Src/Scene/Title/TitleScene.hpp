#pragma once


#include"../Scene.hpp"


namespace Kokoha
{
	/*
	* TitleScene�N���X
	* �^�C�g���V�[��
	*/
	class TitleScene : public MyApp::Scene
	{
	private:
		
		const PixelShader m_shiftShader;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

		void drawFadeOut(double) const override;

	private:

		/// <summary>
		/// �V�F�[�_���Ɏg�p����V�t�g�̃x�N�g��
		/// </summary>
		/// <param name="frequency"> �p�x         </param>
		/// <param name="shift"    > ����̑傫�� </param>
		/// <returns> �V�t�g�̃x�N�g�� </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}