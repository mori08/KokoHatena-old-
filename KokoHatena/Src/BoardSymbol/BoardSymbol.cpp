#include "BoardSymbol.hpp"


namespace
{
	// �{�^���̃T�C�Y
	constexpr Size SYMBOL_SIZE(60, 60);

	// �摜�̃T�C�Y
	constexpr Size TEXTURE_SIZE(40, 40);
}


namespace Kokoha
{

	BoardSymbol::BoardSymbol(const Point& pos, const int32& id)
		: m_region(pos, SYMBOL_SIZE)
		, m_id(id)
		, m_state(BoardState::NONE)
	{
	}


	void BoardSymbol::update()
	{
	}


	void BoardSymbol::draw() const
	{
		TextureAsset(U"BoardSymbol")(SYMBOL_SIZE.x * m_id, 0, SYMBOL_SIZE).drawAt(m_region.center());
	}

}