#include "main.h"

#ifndef BALL_H
#define BALL_H
#define GLM_ENABLE_EXPERIMENTAL

class Ball {
public:
    Ball() {}
    Ball(float x, float y,float radius,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
    double yspeed;
    int halo;
    int ud_raha_hu=0;
    int inside_ring = 0;
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
    //VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;

};

class Enemy_Ball :public Ball{
public:
    Enemy_Ball(): Ball() {}
    Enemy_Ball(float x, float y, float radius, float speed, color_t color) : Ball( x,  y, radius,speed, color){};
    void tick(float viscous); 
};

class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y,float radius,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    double speed;
    double yspeed;
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};



class Halo {
public:
    Halo() {}
    Halo(float x, float y,float radius,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
    float speed;
    double yspeed;
    bool detect_collision_halo(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

//#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, float offset,int score_effect, color_t color);
    glm::vec3 position;
    glm::vec3 init_position;
    glm::vec3 abs_position;
    int score_effect;
    // glm::vec3 position2;
    bool visible;
    float rotation;
    float offset;
    float before;
    bounding_box_t box;
    bool get_visibility();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    void move_downward();
    bounding_box_t get_box();
    void collided();
    float get_x();
    bool boomerang_collision(Ball ball);
private:
    VAO *boomerang;
};

class Special {
public:
    Special() {}
    Special(float x, float y,float radius,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_acc_v);
    float radius;
    double speed;
    double yspeed;
    float y_speed_special = 0;
    float y_acc_special = 0.0008;
    bounding_box_t bounding_box();
    bool special_collision(Ball ball);
private:
    VAO *object;    // How an object looks 
};
#endif // BOOMERANG_H