#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include "GameState.h"

class GameStageMachine{
    private:
        vector<GameState*> m_gameStates; 
    public:
        void pushState(GameState *pState);
        void changeState(GameState *pState);
        void popState();

        void update();
        void render();
};

#endif