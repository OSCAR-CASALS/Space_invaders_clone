#include "Functions.h"
#include "Objects.h"
#include "Vector.h"
#include "Shoot_func.h"

void Player::draw(){
    drawFrame(m_TextureID, m_column, m_row, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
}

void Player::update(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_D] && ((m_position.getX() + m_width) < 1280)){
        m_velocity.setX(4);
    }
    else if (state[SDL_SCANCODE_A] && (m_position.getX() > 0))
    {
        m_velocity.setX(-4);
    }

    else{
        m_velocity.setX(0);
    }
    if(state[SDL_SCANCODE_K]){
        k_pressed = true;
    }
    else if(k_pressed == true){
        player_bullets.push_back(Bullet(bullet_tex, 64, 64, m_position - Vector2D(16.0, 32), -12, 64, m_position - Vector2D(40.0, 56), 16, 14));
        k_pressed = false;
    }
    //prev_pos = m_position;
    //m_velocity += m_acceleration;
    m_position += m_velocity;
    hitbox_position = (m_position + difference_c_p);
}

void Player::clean(){
    //cout << "clean GameObject" << endl;
}

void Enemy::draw(){
    drawFrame(m_TextureID, m_row, m_column, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
}

void Enemy::update(){
    m_position += m_velocity;
    hitbox_position = m_position + difference_c_p;
    if((m_position.getX() + m_width) > 1280 || m_position.getX() < 0){
        t = true;
    }
    //Shoot
    int rand_max = 1 + (rand() % 100);
    int random_numb = rand() % rand_max;
    if(random_numb == 5){
        enemy_bls->push_back(Bullet(bullet_tex, 64, 64, m_position, 12, 128, m_position - Vector2D(24, 28), 14, 10));
    }
}

Shield::Shield(Vector2D pos, int width, int height, int shield_w, int shield_h) : m_position(pos), m_width(width), m_height(height), shield_width(shield_w), shield_height(shield_h) {
    for(int ny=0; ny < (shield_height * m_height); ny+=m_height){
        for(int nx=0; nx < (shield_width * m_width); nx+=m_width){
            rectangles_pos.push_back(Vector2D((m_position.getX() + nx), (m_position.getY() + ny)));
        }
    }
}

void Shield::draw(){ 
    for(auto &r:rectangles_pos){
        SDL_Rect rect = {int(r.getX()), int(r.getY()), m_width, m_height};
        draw_fill_rect(rect, 0, 128, 0, 1);
    }
}

bool Shield::OnCollision(Vector2D pos, int width, int height){
    bool collided = false;
    for(int i=0; i < rectangles_pos.size(); i++){
        if(vectors_cols(rectangles_pos[i], m_width, m_height, pos, width, height)){
            rectangles_pos.erase(rectangles_pos.begin() + i);
            collided = true;
        }
    }
    return collided;
}