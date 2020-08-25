#include "LoadScene.hpp"


namespace
{
	// �e�L�X�g��\��������W
	constexpr Point TEXT_POS = Point(690, 530);
}



namespace Kokoha
{

	LoadScene::LoadScene(const InitData& init, std::function<SceneName()> loadFunc)
		: IScene(init)
	{
		// �X���b�h�̊J�n
		m_loadThread = std::async(std::launch::async, loadFunc);
	}


	LoadScene::~LoadScene()
	{
	}


	void LoadScene::update()
	{
		// ���o�p�̍X�V
		subUpdate();

		// �X���b�h�̏󋵂��擾
		auto status = m_loadThread.wait_for(std::chrono::microseconds(0));

		// �X���b�h���I�����Ă�����V�[���J��
		if (status != std::future_status::timeout)
		{
			auto sceneName = m_loadThread.get();

			if (!changeScene(sceneName))
			{
				changeScene(SceneName::TITLE);
			}
		}
	}


	void LoadScene::draw() const
	{
		FontAsset(U"20")(U"Loading").draw(TEXT_POS);
	}


	void LoadScene::drawFadeIn(double) const
	{
		draw();
	}


	void LoadScene::drawFadeOut(double) const
	{
		draw();
	}


	void LoadScene::subUpdate()
	{
	}

}
