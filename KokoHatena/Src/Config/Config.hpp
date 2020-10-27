#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Config�N���X
	/// �萔�̊Ǘ� (App/asset/data/config.toml)
	/// </summary>
	class Config
	{
	private:

		// �ݒ�t�@�C��
		const TOMLReader m_toml;
		
	public:

		Config();

	private:

		static Config& instance()
		{
			static Config config;
			return config;
		}

	public:

		/// <summary>
		/// �ݒ肳�ꂽ�萔�̎擾
		/// </summary>
		/// <typeparam name="Type"> �擾����^ </typeparam>
		/// <param name="name"> �萔�̖��O </param>
		/// <returns> �ݒ肳�ꂽ�萔 </returns>
		template<typename Type>
		static Type get(const String& name);

	};


	template<typename Type>
	inline Type Config::get(const String& name)
	{
		return instance().m_toml[name].get<Type>();
	}

	template<>
	inline Point Config::get(const String& name)
	{
		return Point(
			instance().m_toml[name + U".x"].get<int32>(),
			instance().m_toml[name + U".y"].get<int32>()
		);
	}

	template<>
	inline Rect Config::get(const String& name)
	{
		return Rect(
			instance().m_toml[name + U".x"].get<int32>(),
			instance().m_toml[name + U".y"].get<int32>(),
			instance().m_toml[name + U".w"].get<int32>(),
			instance().m_toml[name + U".h"].get<int32>()
		);
	}

	template<>
	inline ColorF Config::get(const String& name)
	{
		ColorF color(instance().m_toml[name + U".rgb"].getOr<double>(0.0));
		color.r = instance().m_toml[name + U".r"].getOr<double>(color.r);
		color.g = instance().m_toml[name + U".g"].getOr<double>(color.g);
		color.b = instance().m_toml[name + U".b"].getOr<double>(color.b);
		color.a = instance().m_toml[name + U".a"].getOr<double>(1.0);
		return color;
	}

}