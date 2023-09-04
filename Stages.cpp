#include "Stages.h"
#include "Game_class.h"
#include "Objects.h"
#include <set>
//#include "Enemy.h"

//menu
const string MenuStage::s_menuID = "MENU";

void MenuStage::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void MenuStage::render(){
    drawFull("Title", 12, 300, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool MenuStage::OnEnter(){
    create_text("Play_text", "PLAY", {0, 128, 0, 255}, true);
    create_text("Title", "A CLONE OF YOU KNOW WHAT", {0, 128, 0, 255}, false);
    buttons.push_back(Button("Play_text",104, 50, Vector2D(560, 500), PlayButtonClicked));
    return true;
}

bool MenuStage::OnExit(){
    removeTexture("Play_text");
    removeTexture("Title");
    return true;
}

void MenuStage::PlayButtonClicked(){
    Game::Instance()->getStateMachine()->changeState(new PlayStage());
}

//playstage
const string PlayStage::s_playID = "PLAY";

void PlayStage::update(){
    set<int> to_errase_bullets;
    set<int> to_errase_enemies;
    for(int j = 0; j < bullets.size(); j++){
        Bullet bls = bullets[j];
        for(auto &s:shield_vect){
            if(vectors_cols(bls.Gethitbox_position(), bls.getHitbox_width(), bls.getHitbox_height(), s.getPosition(), s.getShieldWidth(), s.getShieldHeight())){
                if(s.OnCollision(bls.Gethitbox_position(), bls.getHitbox_width(), bls.getHitbox_height()) == true){
                    to_errase_bullets.insert(j);
                }
            }
        }
        if(bls.getVelocity() > 0){
            if(vectors_cols(bls.Gethitbox_position(), bls.getHitbox_width(), bls.getHitbox_height(), pl.getHitbox_position(), pl.getHitbox_width(), pl.getHitbox_height())){
                Game::Instance()->getStateMachine()->changeState(new GameOverStage());
            }
            if(bls.getPosition().getY() > 780){
                to_errase_bullets.insert(j);
            }
        }
        else{
            for(int e=0; e < enemies.size(); e++){
                if(vectors_cols(bls.Gethitbox_position(), bls.getHitbox_width(), bls.getHitbox_height(), enemies[e].getHitbox_position(), enemies[e].getHitbox_width(), enemies[e].getHitbox_height())){
                    to_errase_enemies.insert(e);
                    to_errase_bullets.insert(j);
                    speed_ens += 0.4;
                }
            }
            if(bls.getPosition().getY() < (-80)){
                to_errase_bullets.insert(j);
            }
        }
        bls.update();
        bullets[j] = bls;
    }
    for(auto &n:to_errase_bullets){
        bullets.erase(bullets.begin() + n);
    }
    for(auto &enn:to_errase_enemies){
        enemies.erase(enemies.begin() + enn);
    }
    if(enemies.size() == 0){
        Game::Instance()->getStateMachine()->changeState(new WonStage());
    }
    pl.update();
    for(auto &enem:enemies){
        if(vectors_cols(enem.getHitbox_position(), enem.getHitbox_width(), enem.getHitbox_height(), pl.getHitbox_position(), pl.getHitbox_width(), pl.getHitbox_height()) || (enem.getHitbox_position().getY() > 720)){
            Game::Instance()->getStateMachine()->changeState(new MenuStage());
        }
        enem.setVelocityX(speed_ens);
        enem.update();
        if(enem.can_turn()){
            for(auto &enm:enemies){
                enm.turn();
            }
        }
    }
}

void PlayStage::render(){
    pl.draw();
    for(auto &enem:enemies){
        enem.draw();
    }
    for(auto &bls:bullets){
        bls.draw();
    }
    for(auto &shields : shield_vect){
        shields.draw();
    }
}

bool PlayStage::OnEnter(){
    loadTexture("Player_image", "Sprites/Player.png");
    loadTexture("Images", "Sprites/Sprites_3.png");
    pl.load("Player_image", 32, 32, Vector2D(608, 680), Vector2D(604, 670), 24, 18, "Images");
    shield_vect.push_back(Shield(Vector2D(10, 500), 32, 32, 4, 3));
    shield_vect.push_back(Shield(Vector2D(387, 500), 32, 32, 4, 3));
    shield_vect.push_back(Shield(Vector2D(764, 500), 32, 32, 4, 3));
    shield_vect.push_back(Shield(Vector2D(1141, 500), 32, 32, 4, 3));

    int x = 0;
    int y = 0;
    for(int j=0; j < 5; j++){
        for(int i=0; i < 11; i++){
            enemies.push_back(Enemy("Images", 64, 64, Vector2D(x, y), Vector2D(speed_ens, 0), Vector2D(x + 6, y + 10), 50, 44, "Images", bullets));
            x += 60;
        }
        x = 0;
        y += 60;
    }

    return true;
}

bool PlayStage::OnExit(){
    removeTexture("Player_image");
    removeTexture("Images");
    return true;
}

const string GameOverStage::s_overID = "GAMEOVER";

void GameOverStage::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void GameOverStage::render(){
    drawFull("GameOver_text", 460, 300, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
    //ret_button.draw();
}

bool GameOverStage::OnEnter(){
    create_text("GameOver_text", "YOU DIED", {255, 0, 0, 255});
    create_text("Retry", "RETRY?", {255, 0, 0, 255}, true);
    buttons.push_back(Button("Retry", 156, 50, Vector2D(560, 400), ReturnButtonClicked));
    return true;
}

bool GameOverStage::OnExit(){
    removeTexture("GameOver_text");
    removeTexture("Retry");
    return true;
}

void GameOverStage::ReturnButtonClicked(){ 
    Game::Instance()->getStateMachine()->changeState(new PlayStage()); 
}

const string WonStage::s_wonID = "WON";

void WonStage::update(){
    for(auto &btn:buttons){
        btn.update();
    }
}

void WonStage::render(){
    drawFull("Win_text", 440, 200, false, SDL_FLIP_NONE);
    for(auto &btn:buttons){
        btn.draw();
    }
}

bool WonStage::OnEnter(){
    //string Texture_ID, int width, int height, Vector2D pos
    create_text("Back_text", "Main Menu?", {0, 128, 0, 255}, true);
    create_text("Win_text", "YOU WON!!!", {0, 128, 0, 255}, false);
    buttons.push_back(Button("Back_text",260, 50, Vector2D(520, 420), BackButtonClicked));
    return true;
}

bool WonStage::OnExit(){
    removeTexture("Back_text");
    removeTexture("Win_text");
    return true;
}

void WonStage::BackButtonClicked(){
    Game::Instance()->getStateMachine()->changeState(new MenuStage());
}