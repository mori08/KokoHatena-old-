#include "MyPixelShader.hpp"


namespace Kokoha
{
	void MyPixelShader::loadPixelShader()
	{
		instance().m_shaderMap.try_emplace
		(
			Type::BOARD_SYMBOL, 
			std::move(PixelShader(U"asset/shader/BoardSymbolShader.hlsl", { { U"PSConstants2D", 0 }, { U"Region", 1 } }))
		);

		instance().m_shaderMap.try_emplace
		(
			Type::TITLE_LOGO,
			std::move(PixelShader(U"asset/shader/TitleLogoShader.hlsl", { { U"PSConstants2D", 0 }, { U"Shift", 1 } }))
		);
		
		instance().m_shaderMap.try_emplace
		(
			Type::ACCESS_LIGHT,
			std::move(PixelShader(U"asset/shader/AccessLight.hlsl", { { U"PSConstants2D", 0 }, { U"Light", 1 } }))
		);

		for (const auto& itr : instance().m_shaderMap)
		{
			if (!itr.second)
			{
				throw Error(U"Fiald to load a shader file");
			}
		}
	}

	const PixelShader& MyPixelShader::get(Type type)
	{
		return instance().m_shaderMap.find(type)->second;
	}
}
