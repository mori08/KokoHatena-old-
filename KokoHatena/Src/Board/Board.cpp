#include "Board.hpp"


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
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
