#include "BoardSymbol.hpp"
#include "../MyLibrary/MyLibrary.hpp"
#include "../Config/Config.hpp"
#include "../MyPixelShader/MyPixelShader.hpp"


namespace
{
	/*
	* 定数バッファ (PS_1)
	* 範囲
	*/
	struct Region
	{
		Float4 g_rect;
	};

}


namespace Kokoha
{

	BoardSymbol::BoardSymbol(const Point& pos, const int32& id)
		: m_region(pos, height())
		, m_id(id)
		, m_state(BoardState::NONE)
		, m_lightWidth(0)
	{
		
	}


	Optional<Kokoha::BoardSymbol::BoardState> BoardSymbol::update()
	{
		// 光変更の割合
		static const double LIGHT_RATE = Config::get<double>(U"BoardSymbol.lightRate");

		internalDividingPoint(m_lightWidth, getLightWidth(), LIGHT_RATE);

		if (m_region.leftClicked())
		{
			return m_state;
		}

		return none;
	}


	void BoardSymbol::draw() const
	{
		// 光の余白
		static const double LIGHT_BLANK = Config::get<double>(U"BoardSymbol.lightBlank");
		// 画像のサイズ
		static const Size TEXTURE_SIZE = Config::get<Size>(U"BoardSymbol.textureSize");

		RectF rect
		(
			m_region.pos + Vec2(LIGHT_BLANK, height() - m_lightWidth),
			Vec2(m_region.w - 2 * LIGHT_BLANK, m_lightWidth)
		);
		rect.draw(MyWhite);

		{
			// 定数バッファの設定
			ConstantBuffer<Region> cb;
			cb->g_rect.x = (float)rect.x;
			cb->g_rect.y = (float)rect.y;
			cb->g_rect.z = (float)rect.w;
			cb->g_rect.w = (float)rect.h;
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// シェーダの開始
			ScopedCustomShader2D shader(MyPixelShader::get(MyPixelShader::Type::BOARD_SYMBOL));

			// ボタンの描画
			TextureAsset(U"BoardSymbol")(TEXTURE_SIZE.x * m_id, 0, TEXTURE_SIZE).drawAt(m_region.center());
		}
	}


	double BoardSymbol::getLightWidth() const
	{
		switch (m_state)
		{
		case BoardState::NONE:      return 0.0;
		case BoardState::HIDDEN:    return 3.0;
		case BoardState::DISPLAYED: return 53.0;
		case BoardState::TOP:       return 57.0;
		}
		return 0.0;
	}

}