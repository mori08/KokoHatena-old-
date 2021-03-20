#pragma once


#include "../BoardShareData/BoardShareData.hpp"


// �V�[���̖��O
enum class SceneName
{
	TITLE,       // �^�C�g��

	TEST_LOAD,   // ���[�h�V�[���̃e�X�g
	RECORD_LOAD, // ���R�[�h�̃��[�h
	DESKTOP_LOAD, // �f�X�N�g�b�v�̃��[�h

	DESKTOP      // �f�X�N�g�b�v
};

// �V�[���ŋ��L�����f�[�^
struct ShareData
{
	// Board�Ԃ̋��L�f�[�^
	Kokoha::BoardShareData boardShareData;
};

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, ShareData>;