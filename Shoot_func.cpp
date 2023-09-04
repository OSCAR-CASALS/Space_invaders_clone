#include "Shoot_func.h"

void Bullet::draw(){
    drawFrame(m_TextureID, m_row, m_column, m_width, m_height, (int)m_position.getX(), (int)m_position.getY(), false, SDL_FLIP_NONE);
}

void Bullet::update(){
    m_position.setY(m_position.getY() + speed);
    hitbox_position = (m_position + dif_col_pos);
}