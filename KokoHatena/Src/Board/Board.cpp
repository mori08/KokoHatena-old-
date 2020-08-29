#include "Board.hpp"
#include "../MyLibrary/MyLibrary.hpp"


namespace
{
    // �������W
    constexpr Point INIT_POS(100, 100);

    // �t���[���̌���
    constexpr double FRAME_THICKNESS = 1.5;

    // ����t���[���̌���
    constexpr int32 CONTROL_FRAME_THICKNESS = 30;

    // �t���[���̐F
    constexpr ColorF FRAME_COLOR = Kokoha::myColor(0.8);
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

        return StateChange::NONE;
    }


    void Board::draw() const
    {
        // �{�[�h�w�i�̕`��
        Rect(m_pos, m_size).draw(MyBlack);

        drawInBoard();

        // �����̃t���[����`��
        Rect(m_pos, m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

        // �{�[�h�㕔�̑���t���[���̕`��
        Rect(m_pos + Point(0, -CONTROL_FRAME_THICKNESS), Size(m_size.x, CONTROL_FRAME_THICKNESS))
            .draw(FRAME_COLOR);

        // �O���t���[���̕`��
        Rect(m_pos + Point(0, -CONTROL_FRAME_THICKNESS), m_size + Size(0, CONTROL_FRAME_THICKNESS))
            .drawFrame(0, CONTROL_FRAME_THICKNESS, MyBlack);
    }

}
