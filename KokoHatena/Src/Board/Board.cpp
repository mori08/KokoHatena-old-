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

    // アルファ値変更の比率
    constexpr double CHANGE_ALPHA_RATE = 0.05;

    // 閉じるボタンの位置
    constexpr Rect CLOSE_BUTTON = Kokoha::getRectFromCenter(Point(-15, 15), Size(20, 20));

    // 最小化ボタンの位置
    constexpr Rect MINIMIZE_BUTTON = Kokoha::getRectFromCenter(Point(-45, 15), Size(20, 20));
}


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_pos(INIT_POS)
        , m_alpha(0)
        , m_closeButton(CLOSE_BUTTON.movedBy(size.x,0))
        , m_minimizeButton(MINIMIZE_BUTTON.movedBy(size.x, 0))
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
            TextureAsset(U"CloseButton").draw(m_closeButton.pos);
            TextureAsset(U"MinimizeButton").draw(m_minimizeButton.pos);
        }

        // レンダーテクスチャの描画
        Graphics2D::Flush();
        m_render.resolve();
        m_render.draw(m_pos, AlphaF(m_alpha));
    }

}
