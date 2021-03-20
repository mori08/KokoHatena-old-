#pragma once


#include "../LoadScene.hpp"
#include "../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadDesktopScene�N���X
	/// Record�̓��e�ɉ�����boardShareData��������
	/// </summary>
	class LoadDesktopScene : public LoadScene
	{
	private:

		SliceTexture m_boardLogo;

	public:

		LoadDesktopScene(const InitData& init);

	private:

		void subUpdate() override;

		void draw() const override;

	};
}