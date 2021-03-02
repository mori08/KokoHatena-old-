#include "Board.hpp"
#include "../Config/Config.hpp"
#include "../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_controlFrame(Point::Zero(),size.x,Config::get<int32>(U"Board.controlFrameHeight"))
        , m_closeButton(Config::get<Rect>(U"Board.closeButton").movedBy(size.x, 0))
        , m_minimizeButton(Config::get<Rect>(U"Board.minimizeButton").movedBy(size.x, 0))
        , m_render(size)
        , m_pos(Scene::Center() - size / 2)
        , m_alpha(0)
        , m_state(StateChange::NONE)
        , m_optMovePos(none)
    {
    }


    void Board::input(BoardShareData& shareData)
    {
        if (m_state != StateChange::NONE) { return; }

        // ����{�^���ɉ������Ƃ�
        if (MouseL.down() && m_closeButton.contains(cursorPosInBoard()))
        {
            m_state = StateChange::CLOSE;
            return;
        }

        // ����{�^���ɉ������Ƃ�
        if (MouseL.down() && m_minimizeButton.contains(cursorPosInBoard()))
        {
            m_state = StateChange::MINIMIZE;
            return;
        }

        // ����t���[���������Ĉړ�
        if (MouseL.down() && m_controlFrame.contains(cursorPosFInBoard()))
        {
            m_optMovePos = cursorPosInBoard();
        }
        if (m_optMovePos)
        {
            movePos();
            return;
        }

        inputInBoard(shareData);
    }


    Board::StateChange Board::update(BoardShareData& shareData)
    {
        if (m_state == StateChange::CLOSE) { return StateChange::CLOSE; }

        if (changeAlpha())
        {
            return m_state;
        }

        updateInBoard(shareData);

        return StateChange::NONE;
    }


    void Board::draw(const BoardShareData& shareData) const
    {
        // �t���[���̑���
        static const double FRAME_THICKNESS = Config::get<double>(U"Board.frameThickness");
        // �t���[���̐F
        static const ColorF FRAME_COLOR = Config::get<ColorF>(U"Board.frameColor");
        // �{�[�h���̐F
        static const ColorF BOARD_COLOR = Config::get<ColorF>(U"Board.boardColor");

        // �����_�[�e�N�X�`���̃N���A
        m_render.clear(BOARD_COLOR);

        {
            ScopedRenderTarget2D target(m_render);

            // �{�[�h���̕`��
            drawInBoard(shareData);

            // �t���[����`��
            Rect(Point::Zero(), m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

            // �{�[�h�㕔�̑���t���[���̕`��
            m_controlFrame.draw(FRAME_COLOR);

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
        // �A���t�@�l�ύX�̑��x
        static const double CHANGE_ALPHA_SPEED = Config::get<double>(U"Board.changeAlphaSpeed");

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


    void Board::movePos()
    {
        if (MouseL.up())
        {
            m_optMovePos = none;
            return;
        }

        // �J�[�\���̍��W
        Point cursorPos = Cursor::Pos();
        cursorPos.x = Clamp(cursorPos.x, 0, Scene::Width());
        cursorPos.y = Clamp(cursorPos.y, 0, Scene::Height());

        // ���W�̕ύX
        m_pos = cursorPos - m_optMovePos.value();
    }

}
