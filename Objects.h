#ifndef OBJECTS_H
#define OBJECTS_H

#include "Functions.h"
#include "Vector.h"
#include "Shoot_func.h"

class Player{
    private:
        string m_TextureID;
        int m_width;
        int m_height;
        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;
        int m_row = 0;
        int m_column = 0;
        Vector2D hitbox_position;
        Vector2D difference_c_p;
        int hitbox_width;
        int hitbox_height;
        vector<Bullet> &player_bullets;
        string bullet_tex;
        bool k_pressed = false;

    public:
        Player(vector<Bullet> &b_vector) : m_position(0, 0), m_velocity(0, 0), m_acceleration(0, 0), hitbox_position(0, 0), difference_c_p(0, 0), player_bullets(b_vector) {} 
        void load(string Texture_ID, int width, int height, Vector2D pos, Vector2D hitbox_pos, int hitbox_w, int hitbox_h, string bullet_texture){
            m_TextureID = Texture_ID;
            m_width = width;
            m_height = height;
            m_position = pos;
            hitbox_position = hitbox_pos;
            hitbox_width = hitbox_w;
            hitbox_height = hitbox_h;
            bullet_tex = bullet_texture;
            difference_c_p = m_position - hitbox_position;
        }

        void draw();

        void update();

        void clean();

        Vector2D getPosition(){ return m_position; }

        Vector2D getVelocity(){ return m_velocity; }

        void setVelocity(float speedx, float speedy){ 
            m_velocity.setX(speedx);
            m_velocity.setY(speedy);
        }

        int getHeight(){ return m_height; }

        int getWidth(){ return m_width; }

        Vector2D getHitbox_position() { return hitbox_position; }
        int getHitbox_width() { return hitbox_width; }
        int getHitbox_height() { return hitbox_height; }
};

class Enemy{
    private:
        string m_TextureID;
        int m_width;
        int m_height;
        Vector2D m_position;
        Vector2D m_velocity;
        int m_row = 0;
        int m_column = 0;
        Vector2D hitbox_position;
        Vector2D difference_c_p;
        int hitbox_width;
        int hitbox_height;
        string bullet_tex;
        vector<Bullet> *enemy_bls;
        bool t = false;
        float dir = 1;

    public:
        Enemy(string Texture_ID, int width, int height, Vector2D pos, Vector2D vel, Vector2D hitbox_pos, int hitbox_w, int hitbox_h, string bullet_texture, vector<Bullet> &bullet_vect) : m_TextureID(Texture_ID), m_width(width), m_height(height), m_position(pos), m_velocity(vel), hitbox_position(hitbox_pos), difference_c_p(0, 0), hitbox_width(hitbox_w), hitbox_height(hitbox_h), bullet_tex(bullet_texture), enemy_bls(&bullet_vect) {
            difference_c_p = hitbox_position - m_position;
        }
        void draw();
        void update();
        bool can_turn() { return t; }
        void turn(){
            m_velocity *= (-1);
            dir *= (-1);
            m_position.setY(m_position.getY() + 10);
            t = false;
        }
        Vector2D getHitbox_position() { return hitbox_position; }
        int getHitbox_width() { return hitbox_width; }
        int getHitbox_height() { return hitbox_height; }
        Vector2D getVelocity() { return m_velocity; }
        void setVelocityX(float speedx) { m_velocity.setX(speedx * dir); }
};

class Shield{
    private:
        Vector2D m_position;
        int m_width;
        int m_height;
        int shield_width;
        int shield_height;
        vector<Vector2D> rectangles_pos;
    public:
        Shield(Vector2D pos, int width, int height, int shield_w, int shield_h);
        void draw();
        Vector2D getPosition(){ return m_position; }
        int getShieldWidth(){ return shield_width * m_width; }
        int getShieldHeight() { return shield_height * m_height; }
        bool OnCollision(Vector2D pos, int width, int height);
};

#endif