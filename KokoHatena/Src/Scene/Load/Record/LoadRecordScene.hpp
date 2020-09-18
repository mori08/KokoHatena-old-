#pragma once


#include "../LoadScene.hpp"
#include "../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadRecordSceneƒNƒ‰ƒX
	/// RecordManager‚ÉRecord‚ğ“Ç‚İ‚Ş
	/// </summary>
	class LoadRecordScene : public LoadScene
	{
	private:

		SliceTexture m_boardLogo;

	public:

		LoadRecordScene(const InitData init);

	private:

		void subUpdate() override;

		void draw() const override;

	};
}