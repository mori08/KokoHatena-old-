#include "Board.hpp"
#include "../MyLibrary/MyLibrary.hpp"


namespace
{
    // 初期座標
    constexpr Point INIT_POS(100, 100);

    // フレームの厚さ
    constexpr double FRAME_THICKNESS = 1.5;

    // 操作フレームの厚さ
    constexpr int32 CONTROL_FRAME_THICKNESS = 30;

    // フレームの色
    constexpr ColorF FRAME_COLOR = Kokoha::myColor(0.8);

    // ボード内の色
    constexpr ColorF BOARD_COLOR = Kokoha::myColor(0.2);

    // アルファ値変更の速度
    constexpr double CHANGE_ALPHA_SPEED = 4.0;

    // 閉じるボタンの位置
    constexpr Rect CLOSE_BUTTON = Kokoha::getRectFromCenter(Point(-15, 15), Size(30, 30));

    // 最小化ボタンの位置
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

        // 閉じるボタンに押したとき
        if (MouseL.up() && m_closeButton.contains(cursorPosInBoard()))
        {
            m_state = StateChange::CLOSE;
            return;
        }

        // 閉じるボタンに押したとき
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
        // レンダーテクスチャのクリア
        m_render.clear(BOARD_COLOR);

        {
            ScopedRenderTarget2D target(m_render);

            // ボード内の描画
            drawInBoard();

            // フレームを描画
            Rect(Point::Zero(), m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

            // ボード上部の操作フレームの描画
            Rect(Point::Zero(), Size(m_size.x, CONTROL_FRAME_THICKNESS))
                .draw(FRAME_COLOR);

            // 閉じる・最小化ボタンを描画
            if (m_closeButton   .contains(cursorPosInBoard())) { m_closeButton   .draw(MyWhite); }
            if (m_minimizeButton.contains(cursorPosInBoard())) { m_minimizeButton.draw(MyWhite); }
            TextureAsset(U"CloseButton").draw(m_closeButton.pos);
            TextureAsset(U"MinimizeButton").draw(m_minimizeButton.pos);
        }

        // レンダーテクスチャの描画
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
