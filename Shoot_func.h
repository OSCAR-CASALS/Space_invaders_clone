#ifndef SHOOT_FUNC_H
#define SHOOT_FUNC_H

#include "Functions.h"
#include "Vector.h"

class Bullet{
    private:
        string m_TextureID;
        int m_width;
        int m_height;
        Vector2D m_position;
        int m_row = 0;
        float speed = 0;
        int m_column = 0;
        Vector2D hitbox_position;
        int hitbox_width = 0;
        int hitbox_height = 0;
        Vector2D dif_col_pos;
    public:
        Bullet(string Texture_ID, int width, int height, Vector2D pos, float velocity, int col, Vector2D hitbox_pos, int hitbox_w, int hitbox_h) : m_TextureID(Texture_ID), m_width(width), m_height(height), m_position(pos), speed(velocity), m_column(col), hitbox_position(hitbox_pos), hitbox_width(hitbox_w), hitbox_height(hitbox_h), dif_col_pos(0, 0) {
            dif_col_pos = m_position - hitbox_position;
        }
        void draw();
        void update();

        float getVelocity() { return speed; }

        Vector2D getPosition(){ return m_position;}
        Vector2D Gethitbox_position() { return hitbox_position; }
        int getHitbox_width() { return hitbox_width; }
        int getHitbox_height() { return hitbox_height; }

};

#endif