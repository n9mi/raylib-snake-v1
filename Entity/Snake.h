#include <raylib.h>
#include <vector>

namespace RetroSnake {
    class Snake 
    {
        std::vector<Vector2> m_body;
        const int m_initLength = 3;
        const int m_maxLength = 203;
        const Vector2 m_initHeadPos = { 12, 12 };
        const Color m_headColor = GREEN;
        const Color m_bodyColor = LIME;
        int m_frameInterval = 7;                     // snake will move every 7 frame 

        void move(const Vector2 &);

        public: 
            Snake();
            void draw();;
            bool isFacingUp();
            bool isFacingDown();
            bool isFacingRight();
            bool isFacingLeft();
            void moveUp();
            void moveDown();
            void moveRight();
            void moveLeft();
            bool isVertical();
            bool isHorizontal();
            int getFrameInterval();
            Vector2 getHeadPosition();
            bool checkIfPositionOccupiedByHeadOrBody(const Vector2 &);
            void growTailByOne();
            void reset();
    };
}