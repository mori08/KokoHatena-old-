#pragma once


#include<Siv3D.hpp>
#include"SecurityShareData/SecurityShareData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareData�N���X
	/// Board�Ԃŋ��L����f�[�^
	/// BoardScene�֖��߂��s��
	/// </summary>
	class BoardShareData
	{
	public:

		SecurityShareData m_securityData;

	public:

		BoardShareData();

	};
}