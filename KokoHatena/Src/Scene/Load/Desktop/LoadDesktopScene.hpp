#pragma once


#include "../LoadScene.hpp"
#include "../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadDesktopSceneƒNƒ‰ƒX
	/// Record‚Ì“à—e‚É‰‚¶‚ÄboardShareData‚ğ‰Šú‰»
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