#pragma once


#include<Siv3D.hpp>


// �V�[���̖��O
enum class SceneName
{
	TITLE // �^�C�g��
};

// �V�[���ŋ��L�����f�[�^
struct ShareData
{

};

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, ShareData>;