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

    // �{�[�h���̐F
    constexpr ColorF BOARD_COLOR = Kokoha::myColor(0.2);

    // �A���t�@�l�ύX�̔䗦
    constexpr double CHANGE_ALPHA_RATE = 0.05;
}


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_pos(INIT_POS)
        , m_alpha(0)
        , m_render(size, BOARD_COLOR)
    {
    }


    void Board::input()
    {
        

        inputInBoard();
    }


    Board::StateChange Board::update()
    {
        internalDividingPoint(m_alpha, 1.0, CHANGE_ALPHA_RATE);

        updateInBoard();

        return StateChange::NONE;
    }


    void Board::draw() const
    {
        // �����_�[�e�N�X�`���̃N���A
        m_render.clear(BOARD_COLOR);

        {
            ScopedRenderTarget2D target(m_render);

            // �{�[�h���̕`��
            drawInBoard();

            // �����̃t���[����`��
            Rect(Point::Zero(), m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

            // �{�[�h�㕔�̑���t���[���̕`��
            Rect(Point::Zero(), Size(m_size.x, CONTROL_FRAME_THICKNESS))
                .draw(FRAME_COLOR);
        }

        // �����_�[�e�N�X�`���̕`��
        Graphics2D::Flush();
        m_render.resolve();
        m_render.draw(m_pos, AlphaF(m_alpha));
    }

}
