#pragma once


#include "../LoadScene.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadRecordScene�N���X
	/// RecordManager��Record��ǂݍ���
	/// </summary>
	class LoadRecordScene : public LoadScene
	{
	private:


	public:

		LoadRecordScene(const InitData init);

	private:

		void subUpdate() override;

		void draw() const override;

	};
}