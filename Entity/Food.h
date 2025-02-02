#include <raylib.h>

namespace RetroSnake {
    class Food 
    {
        Vector2 m_position = { 8, 8 };
        const Color m_color = RED;

        public:
            void draw();
            Vector2 getPositon();
            void setPosition(const Vector2 &);
            void resetPosition();
    };
}