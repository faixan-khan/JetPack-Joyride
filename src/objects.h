#include "main.h"
#include "ball.h"

#ifndef OBJECT_H
#define OBJECT_H

class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool detect_collision(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, float width, float height, color_t color);
    glm::vec3 position;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_rotation(float rotation);
    bool detect_collision(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};


class Pool {
public:
    Pool() {}
    Pool(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    double speed;
    double yspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float detect_collision(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class Spike {
public:
    Spike() {}
    Spike(float x, float y, float width,float speed, float range,color_t color);
    glm::vec3 position;
    float rotation;
    float speed;
    float width;
    float height;
    float range;
    float center_x;
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool detect_collision(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class Coins {
public:
    Coins() {}
    Coins(float x, float y,float radius, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float radius;
    double eaten;
    bool detect_collision_coin(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};


class Evil {
public:
    Evil() {}
    Evil(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float eaten;
    bool detect_collision_evil(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
    VAO *object1;
    VAO *object2;
};

class Evil_move{
public:
    Evil_move() {}
    Evil_move(float x,float y,float width,float height,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float width;
    float height;
    void tick();
    int buj_gaya;
    bool detect_collision_evil_move(Ball ball);
    bool detect_collision_evil_move_balloon(Balloon ball);
    bounding_box_t bounding_box();
private:
    VAO *object1;    // How an object looks 
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

class Ring {
public:
    Ring() {}
    Ring(float x, float y,float radius, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float radius;
    bool detect_collision_ring(Ball ball);
    bounding_box_t bounding_box();
private:
    VAO *object;
};
class Viserion {
    public:
    Viserion() {}
    Viserion(float x,float y,color_t color);
    glm::vec3 position;
    float speed;
    float rotation;
    float yspeed;
    float damage=0;
    //float exist=1;
    float radius=0.5;
    float exist=0;
    bool detect_collision_viserions(Balloon ball);
    bool detect_collision_viserion(Ball ball);
    bounding_box_t bounding_box();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    private:
        VAO *object1;
        VAO *object2;
        VAO *object3;
        VAO *object4;
        VAO *object5;
        VAO *object6;
        VAO *object7;
};
class V_Balloon {
public:
    V_Balloon() {}
    V_Balloon(float x, float y,float radius,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float y_acc_v);
    float radius;
    float speed;
    double yspeed;
    bounding_box_t bounding_box();
    bool detect_collision_V(Ball ball);
private:
    VAO *object;    // How an object looks 
};
#endif
