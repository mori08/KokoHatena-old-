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

    // �A���t�@�l�ύX�̑��x
    constexpr double CHANGE_ALPHA_SPEED = 4.0;

    // ����{�^���̈ʒu
    constexpr Rect CLOSE_BUTTON = Kokoha::getRectFromCenter(Point(-15, 15), Size(30, 30));

    // �ŏ����{�^���̈ʒu
    constexpr Rect MINIMIZE_BUTTON = Kokoha::getRectFromCenter(Point(-45, 15), Size(30, 30));
}


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_pos(INIT_POS)
        , m_state(StateChange::NONE)
        , m_alpha(0)
        , m_closeButton(CLOSE_BUTTON.movedBy(size.x,0))
        , m_minimizeButton(MINIMIZE_BUTTON.movedBy(size.x, 0))
        , m_render(size, BOARD_COLOR)
    {
    }


    void Board::input()
    {
        if (m_state != StateChange::NONE) { return; }

        // ����{�^���ɉ������Ƃ�
        if (MouseL.up() && m_closeButton.contains(cursorPosInBoard()))
        {
            m_state = StateChange::CLOSE;
            return;
        }

        // ����{�^���ɉ������Ƃ�
        if (MouseL.up() && m_minimizeButton.contains(cursorPosInBoard()))
        {
            m_state = StateChange::MINIMIZE;
            return;
        }

        inputInBoard();
    }


    Board::StateChange Board::update()
    {
        if (changeAlpha())
        {
            return m_state;
        }

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

            // �t���[����`��
            Rect(Point::Zero(), m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

            // �{�[�h�㕔�̑���t���[���̕`��
            Rect(Point::Zero(), Size(m_size.x, CONTROL_FRAME_THICKNESS))
                .draw(FRAME_COLOR);

            // ����E�ŏ����{�^����`��
            if (m_closeButton   .contains(cursorPosInBoard())) { m_closeButton   .draw(MyWhite); }
            if (m_minimizeButton.contains(cursorPosInBoard())) { m_minimizeButton.draw(MyWhite); }
            TextureAsset(U"CloseButton").draw(m_closeButton.pos);
            TextureAsset(U"MinimizeButton").draw(m_minimizeButton.pos);
        }

        // �����_�[�e�N�X�`���̕`��
        Graphics2D::Flush();
        m_render.resolve();
        m_render.draw(m_pos, AlphaF(m_alpha));
    }


    bool Board::changeAlpha()
    {
        if (m_state == StateChange::NONE)
        {
            m_alpha += Scene::DeltaTime() * CHANGE_ALPHA_SPEED;
            m_alpha = Min(1.0, m_alpha);
            return false;
        }

        m_alpha -= Scene::DeltaTime() * CHANGE_ALPHA_SPEED;

        if (m_alpha < 0)
        {
            m_alpha = 0;
            return true;
        }
        
        return false;
    }

}
