#pragma once


#include<Siv3D.hpp>
#include"SecurityShareData/SecurityShareData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareDataクラス
	/// Board間で共有するデータ
	/// BoardSceneへ命令も行う
	/// </summary>
	class BoardShareData
	{
	public:

		SecurityShareData m_securityData;

	public:

		BoardShareData();

	};
}