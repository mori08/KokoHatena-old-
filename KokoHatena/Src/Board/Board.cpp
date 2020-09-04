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
}


namespace Kokoha
{

    Board::Board(Role role, const String& name, const Size& size)
        : m_role(role)
        , m_name(name)
        , m_size(size)
        , m_pos(INIT_POS)
        , m_render(size, MyWhite)
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
        // ボード背景の描画
        Rect(m_pos, m_size).draw(MyBlack);

        m_render.clear(MyWhite);
        {
            // レンダーを設定してボード内の描画
            ScopedRenderTarget2D target(m_render);
            drawInBoard();
        }
        Graphics2D::Flush();
        m_render.resolve();
        m_render.draw(m_pos);

        // 内側のフレームを描画
        Rect(m_pos, m_size).drawFrame(FRAME_THICKNESS, 0, FRAME_COLOR);

        // ボード上部の操作フレームの描画
        Rect(m_pos + Point(0, -CONTROL_FRAME_THICKNESS), Size(m_size.x, CONTROL_FRAME_THICKNESS))
            .draw(FRAME_COLOR);

        // 外側フレームの描画
        Rect(m_pos + Point(0, -CONTROL_FRAME_THICKNESS), m_size + Size(0, CONTROL_FRAME_THICKNESS))
            .drawFrame(0, CONTROL_FRAME_THICKNESS, MyBlack);
    }

}
