#include "Snake.h"
#include "../Config/Screen.h"

namespace RetroSnake {
    Snake::Snake()
    {
        m_body.reserve(m_maxLength);
        for (int i = 0; i < m_initLength; i++)
        {
            m_body.emplace_back(Vector2{ m_initHeadPos.x - i, m_initHeadPos.y });
        }
    }

    void Snake::growTailByOne()
    {
        if (m_body[m_body.size() - 1].x == m_body[m_body.size() - 2].x)
        {
            m_body.emplace_back(Vector2{ m_body[m_body.size() - 1].x + 1, m_body[m_body.size() - 1].y });
        } else if (m_body[m_body.size() - 1].y == m_body[m_body.size() - 2].y)
        {
            m_body.emplace_back(Vector2{ m_body[m_body.size() - 1].x, m_body[m_body.size() - 1].y + 1 });
        }
    }

    void Snake::draw()
    {
        for (int i = 0; i < m_body.size(); i++)
        {
            DrawRectangleRounded(
                Rectangle{
                    (m_body[i].x) * Screen::s_cellSize, 
                    (m_body[i].y) * Screen::s_cellSize,
                    Screen::s_cellSize,
                    Screen::s_cellSize}, 
                0.5, 6, (i == 0 ? m_headColor : m_bodyColor));
        }
    }

    void Snake::move(const Vector2 &mov)
    {
        Vector2 prevPos = { m_body[0].x, m_body[0].y };

        m_body[0].x += mov.x; 
        m_body[0].y += mov.y;

        for (int i = 1; i < m_body.size(); i++)
        {
            Vector2 temp = { m_body[i].x, m_body[i].y };
            m_body[i].x = prevPos.x;
            m_body[i].y = prevPos.y;
            prevPos = temp;
        }
    }

    void Snake::moveUp()
    {
        Snake::move({ 0, -1 });
    }

    void Snake::moveDown()
    {
        Snake::move({ 0, 1 });
    }

    void Snake::moveRight() 
    {
        Snake::move({ 1, 0 });
    }

    void Snake::moveLeft()
    {
        Snake::move({ -1, 0 });
    }

    bool Snake::isFacingUp()
    {
        return m_body[0].y < m_body[1].y;
    }

    bool Snake::isFacingDown()
    {
        return m_body[0].y > m_body[1].y;
    }

    bool Snake::isFacingRight()
    {
        return m_body[0].x > m_body[1].x;
    }

    bool Snake::isFacingLeft()
    {
        return m_body[0].x < m_body[1].x;
    }

    bool Snake::isVertical()
    {
        return m_body[0].x == m_body[1].x;
    }

    bool Snake::isHorizontal()
    {
        return m_body[0].y == m_body[1].y;
    }

    Vector2 Snake::getHeadPosition()
    {
        return m_body[0];
    }

    int Snake::getFrameInterval()
    {
        return Snake::m_frameInterval;
    }

    bool Snake::checkIfPositionOccupiedByHeadOrBody(const Vector2 &position)
    {
        for (int i = 0; i < m_body.size(); i++)
        {
            if (m_body[i].x == position.x && m_body[i].y == position.y)
            {
                return true;
            }
        }

        return false;
    }

    bool Snake::checkifHeadBodyCollision()
    {   
        for (int i = 1; i < m_body.size(); i++)
        {
            if ((m_body[0].x == m_body[i].x) && (m_body[0].y == m_body[i].y))
            {
                return true;
            }
        }

        return false;
    }

    void Snake::reset()
    {
        m_body.erase(m_body.begin() + m_initLength, m_body.end());
        for (int i = 0; i < m_initLength; i++)
        {
            m_body[i].x = m_initHeadPos.x - i;
            m_body[i].y = m_initHeadPos.y;
        }
    }
}