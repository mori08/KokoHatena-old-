#pragma once


#include<Siv3D.hpp>


// �V�[���̖��O
enum class SceneName
{
	TITLE,      // �^�C�g��

	TEST_LOAD,  // ���[�h�V�[���̃e�X�g
	RECORD_LOAD // ���R�[�h�̃��[�h
};

// �V�[���ŋ��L�����f�[�^
struct ShareData
{

};

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, ShareData>;