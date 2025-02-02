#include <raylib.h>
#include "Food.h"
#include "../Config/Screen.h"

namespace RetroSnake {
    void Food::draw()
    {
        DrawRectangleRounded(
            Rectangle{
                m_position.x * Screen::s_cellSize, 
                m_position.y * Screen::s_cellSize,
                Screen::s_cellSize,
                Screen::s_cellSize}, 
            0.85, 6, m_color);
    }

    Vector2 Food::getPositon()
    {
        return m_position;
    }

    void Food::setPosition(const Vector2 &newPos)
    {
        m_position = newPos;
    }

    void Food::resetPosition()
    {
        setPosition({ 8, 8 });
    }
}