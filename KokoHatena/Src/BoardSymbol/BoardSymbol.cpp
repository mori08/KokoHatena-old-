#include "BoardSymbol.hpp"
#include "../MyLibrary/MyLibrary.hpp"


namespace
{
	// 画像のサイズ
	constexpr Size TEXTURE_SIZE(40, 40);

	// 光変更の割合
	constexpr double LIGHT_RATE = 0.0001;

	// 光の余白
	constexpr double LIGHT_BLANK = 1.0;

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
		: m_region(pos, SIZE)
		, m_id(id)
		, m_state(BoardState::NONE)
		, m_lightWidth(0)
		, m_shader(U"asset/shader/BoardSymbolShader.hlsl", { { U"PSConstants2D", 0 }, { U"Region", 1 } })
	{
	}


	Optional<Kokoha::BoardSymbol::BoardState> BoardSymbol::update()
	{
		internalDividingPoint(m_lightWidth, getLightWidth(), LIGHT_RATE);

		if (m_region.leftClicked())
		{
			return m_state;
		}

		return none;
	}


	void BoardSymbol::draw() const
	{
		RectF rect
		(
			m_region.pos + Vec2(LIGHT_BLANK, SIZE - m_lightWidth),
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
			ScopedCustomShader2D shader(m_shader);

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
		case BoardState::DISPLAYED: return 55.0;
		case BoardState::TOP:       return 59.0;
		}
		return 0.0;
	}

}