#ifndef STAGES_H
#define STAGES_H

#include "Functions.h"
#include "GameState.h"
#include "Objects.h"
#include "Button.h"
#include "Shoot_func.h"
#include <memory>


class MenuStage : public GameState{
    private:
        static const string s_menuID;
        vector <Button> buttons;
        //Functions
        static void PlayButtonClicked();
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const {return s_menuID;}
};

class PlayStage : public GameState{
    private:
        static const string s_playID;
        Player pl;
        vector<Bullet> bullets;
        vector<Enemy> enemies;
        vector <Shield> shield_vect;
        float speed_ens = 1.0;
        bool winned = true;
    public:
        PlayStage() : pl(bullets) {}
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();
        virtual string getStateID() const {return s_playID;}
};

class GameOverStage : public GameState{
    private:
        static const string s_overID;
        vector <Button> buttons;
        static void ReturnButtonClicked();
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const { return s_overID; }
};

class WonStage : public GameState{
    private:
        static const string s_wonID;
        vector <Button> buttons;
        //Functions
        static void BackButtonClicked();
    public:
        virtual void update();
        virtual void render();

        virtual bool OnEnter();
        virtual bool OnExit();

        virtual string getStateID() const {return s_wonID;}
};


#endif
