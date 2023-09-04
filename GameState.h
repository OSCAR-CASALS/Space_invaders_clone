#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Functions.h"

class GameState{
    public:
        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool OnEnter() = 0;
        virtual bool OnExit() = 0;
        
        virtual string getStateID() const = 0;   
};
#endif