#include "Board.hpp"


namespace
{
    // èâä˙ç¿ïW
    constexpr Point INIT_POS(100, 100);
}


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_pos(INIT_POS)
    {
    }


    void Board::input()
    {
        

        inputInBoard();
    }


    Board::StateChange Board::update()
    {
        
        updateInBoard();
    }


    void Board::draw() const
    {

        drawInBoard();
    }

}
