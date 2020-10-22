#pragma once


#include<Siv3D.hpp>


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

		String text;

		BoardShareData();

	};
}