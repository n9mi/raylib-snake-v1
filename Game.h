#include "Entity/Food.h"
#include "Entity/Snake.h"

namespace RetroSnake {
    class Game 
    {
        bool m_isRunning;
        int m_fpsCounter = 0;
        int m_isPlay = false;

        Snake *m_snake = nullptr;
        Food *m_food = nullptr;

        int m_score = 0;

        void trackFps();
        bool isFrameIntervalPassed();

        void updateSnakePerFrame();
        bool checkSnakeFoodCollision();
        bool checkSnakeWallCollision();

        public:
            Game();
            ~Game();
            void run();
    };
}