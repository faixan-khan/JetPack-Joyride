#include<bits/stdc++.h>
#include "objects.h"
#include "main.h"
#include "timer.h"

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    
    GLfloat vertex_buffer_data[45] ={ 
        0.9f, 0.0f, 0.0f,
        0.9f, 1.1f, 0.0f,
        0.7f, 1.0f, 0.0f,

        0.9f, 0.0f, 0.0f,
        0.7f, 1.1f, 0.0f,
        0.7f, 0.0f, 0.0f,

        0.7f, 1.0f, 0.0f,
       -0.7f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.1f, 0.0f,
       -0.7f, 1.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.1f, 0.0f,
       -0.9f, 0.0f, 0.0f

    }; 

    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Trampoline::detect_collision(Ball ball) {
    return std::fabs(this->position.x - ball.position.x) < (ball.radius + 0.7f) && std::fabs(this->position.y - ball.position.y) < (ball.radius);
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1.7f, 1.1f };
    return bbox;
}


Magnet::Magnet(float x, float y, float width, float height, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    
    GLfloat vertex_buffer_data[45] ={ 
        0.9f, 0.0f, 0.0f,
        0.9f, 1.1f, 0.0f,
        0.7f, 1.0f, 0.0f,

        0.9f, 0.0f, 0.0f,
        0.7f, 1.1f, 0.0f,
        0.7f, 0.0f, 0.0f,

        0.7f, 1.0f, 0.0f,
       -0.7f, 1.0f, 0.0f,
        0.0f, 2.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.1f, 0.0f,
       -0.7f, 1.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.1f, 0.0f,
       -0.9f, 0.0f, 0.0f

    }; 

    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::set_rotation(float rotation) {
    this->rotation = rotation;
}

bool Magnet::detect_collision(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + 1 ) * ( ball.radius + 1 ) );
    //return std::fabs(this->position.y - ball.position.y) < (ball.radius + 0.7f);  
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}

Pool::Pool(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
   
    radius = 1.99;
    speed = 0.01;
    yspeed = 0;

    GLfloat vertex_buffer_data[450]; 
    int sides = 100;
    float angle = (2*3.14159)/sides;

    for(int i =0; i < sides/2;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle + 3.14159); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle + 3.14159) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle + 3.14159); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle + 3.14159); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 3*sides/2, vertex_buffer_data, color, GL_FILL);

}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
}

void Pool::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

float Pool::detect_collision(Ball ball) {
    return (this->position.x - ball.position.x)*(this->position.x - ball.position.x) 
          + (this->position.y - ball.position.y)*(this->position.y - ball.position.y) 
          - (ball.radius - this->radius)*(ball.radius - this->radius);
}

bounding_box_t Pool::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

Spike::Spike(float x, float y,float width,float speed,float range, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->center_x = x;
    this->width = width;
    this->speed = speed;
    this->height = 0.2f;
    float no_of_spikes = 5.0;
    float spike_size = width/no_of_spikes;
    this->range = range;

    GLfloat vertex_buffer_data[45];

    for(int i=0;i<no_of_spikes;i++){

        vertex_buffer_data[9*i] = i*spike_size;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = (i+1/2.0)*spike_size; 
        vertex_buffer_data[9*i + 4] =  height;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = (i+1)*spike_size; 
        vertex_buffer_data[9*i + 7] = 0.0f; 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Spike::tick(){
    this->position.x -= speed;
    if(std::fabs(this->position.x - this->center_x - 0.5f) > this->range/4)
        this->speed = -this->speed;

}

void Spike::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spike::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Spike::detect_collision(Ball ball) {

    return std::fabs(this->position.y +this->height/2 - ball.position.y) < (ball.radius + this->height/2) && std::fabs(this->position.x  + this->width/2 - ball.position.x) < (ball.radius + this->width/2);

}

bounding_box_t Spike::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1.7f, 1.1f };
    return bbox;
}

Coins::Coins(float x, float y, float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 10;
    this->radius = radius;
    this->eaten = 0;
    GLfloat vertex_buffer_data[900]; 
    int sides = 100;
    float angle = (2*3.14159)/sides;
    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, color, GL_FILL);
}

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->eaten == 0)
        draw3DObject(this->object);
}





//void Coins::draw(glm::mat4 VP) {
//    Matrices.model = glm::mat4(1.0f);
//    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
//    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
//    Matrices.model *= (translate * rotate);
//    glm::mat4 MVP = VP * Matrices.model;
//    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    if(this->eaten == 0)
//        draw3DObject(this->object);
//}

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Coins::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

bool Coins::detect_collision_coin(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}


/////////////////////////////////

Evil::Evil(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float x1 = x+1;
    float y1 = y+2;
    this->eaten = 0;
    static const GLfloat vertex_buffer_data[] = {
    0, 0.0,0.0, // triangle 2 : begin
    1.25, 1.2,0.0,
    2, 2,0.0,

    };
    static const GLfloat vertex_buffer_data1[] = {
    -0.1,0.1,0.0,
    -0.1,-0.1,0.0,
    0.1,-0.1,0.0,

    -0.1,0.1,0.0,
    0.1,0.1,0.0,
    0.1,-0.1,0.0,


    };

    static const GLfloat vertex_buffer_data2[] = {
      2,2,0.0,
      2.2,2,0.0,
      2.2,2.2,0.0,

      2,2,0.0,
      2.2,2.2,0.0,
      2,2.2,0.0,
    };
    
    this->object = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);

}

void Evil::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->eaten == 0){
        draw3DObject(this->object);
        draw3DObject(this->object1);
        draw3DObject(this->object2);
    }

}

void Evil::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);   
}


bounding_box_t Evil::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, x+1, y+2 };
    return bbox;
}

bool Evil::detect_collision_evil(Ball ball) {
    float d1 = (ball.position.x - this->position.x)*(ball.position.x - this->position.x) + (ball.position.y - this->position.y)*(ball.position.y - this->position.y);
    d1 = sqrt(d1);
    float d2 = (ball.position.x - (this->position.x+2))*(ball.position.x - (this->position.x+2)) + (ball.position.y - (this->position.y+2))*(ball.position.y - (this->position.y+2));
    d2 = sqrt(d2);
    float pt = d1+d2;
    if(pt <= 3 && pt >= 1.8)
        return true;
    else
        return false;
}

///////////////////fire beams/////////////////////////////////////////////


Evil_move::Evil_move(float x, float y, float width,float height, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->buj_gaya = 0;
    
    static const GLfloat vertex_buffer_data1[] = {
    -0.1,0.1,0.0,
    -0.1,-0.1,0.0,
    0.1,-0.1,0.0,

    -0.1,0.1,0.0,
    0.1,0.1,0.0,
    0.1,-0.1,0.0,


    };
    static const GLfloat vertex_buffer_data2[] = {
        0, 0.0,0.0, // triangle 2 : begin
        3, 0.05,0.0,
        6.1, 0.0,0.0,
    };
    static const GLfloat vertex_buffer_data3[] = {
       6,-0.1,0.0,
       6.2,-0.1,0.0,
       6.2,0.1,0.0,

       6,-0.1,0.0,
       6,0.1,0.0,
       6.2,0.1,0.0,
     };

    static const GLfloat vertex_buffer_data4[] = {      
        -0.1,-0.5,0.0,
        -0.1,-0.7,0.0,
        0.1,-0.7,0.0,

        -0.1,-0.5,0.0,
        0.1,-0.5,0.0,
        0.1,-0.7,0.0, 
    };

    static const GLfloat vertex_buffer_data5[] = {
        0, -0.6,0.0, // triangle 2 : begin
        3, -0.5,0.0,
        6.1, -0.6,0.0,
    };
    static const GLfloat vertex_buffer_data6[] = {
       6,-0.5,0.0,
       6.2,-0.7,0.0,
       6.2,-0.5,0.0,

       6,-0.5,0.0,
       6,-0.7,0.0,
       6.2,-0.7,0.0,
     };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_YELLOW, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data5, COLOR_RED, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, COLOR_YELLOW, GL_FILL);

}



void Evil_move::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->buj_gaya == 0){
        draw3DObject(this->object1);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
        draw3DObject(this->object4);
        draw3DObject(this->object5);
        draw3DObject(this->object6);
    }

}

void Evil_move::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);   
}
int dir=1;
void Evil_move::tick() {
    if(dir == 1)
        this->position.y += 0.01;
    if(dir == 0)
        this->position.y -= 0.01;
    if(this->position.y <= 1)
        dir = 1;
    if(this->position.y >= 4)
        dir = 0;
}
bounding_box_t Evil_move::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}

bool Evil_move::detect_collision_evil_move(Ball ball) {
    if(ball.position.x > this->position.x && ball.position.x < (this->position.x+6) && ball.position.y < this->position.y && ball.position.y > (this->position.y-1.5)){
          
            return true;
    }
    else
        return false;
}

bool Evil_move::detect_collision_evil_move_balloon(Balloon ball) {
    if(ball.position.x > this->position.x && ball.position.x < (this->position.x+6) && ball.position.y < this->position.y && ball.position.y > (this->position.y-1.5)){
          
            return true;
    }
    else
        return false;
}

////////////////////////////////////////////////////         ring

Ring::Ring(float x, float y,float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->speed = speed;
    GLfloat vertex_buffer_data[900]; 
    int sides = 100;
    float angle = (3.14159)/sides;
    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, color, GL_POINT);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
   // rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {

   // this->position.x -= speed;
}
bounding_box_t Ring::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

bool Ring::detect_collision_ring(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}

///////////////////////////////////////////////////////////////////////////////////////////

Viserion::Viserion(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    
    GLfloat vertex_buffer_data[] ={ 
        -0.5f,-0.5f,0.0f,
        -0.3f,-0.5f,0.0f,
        -0.3f,-0.3f,0.0f,

        0.5f,-0.5f,0.0f,
        0.3f,-0.5f,0.0f,
        0.3f,-0.3f,0.0f,

    }; 

    GLfloat vertex_buffer_data2[] ={
        0.3f,-0.3f,0.0f,
        -0.3f,-0.3f,0.0f,
        0.3f,0.3f,0.0f,

        0.3f,0.3f,0.0f,
        -0.3f,0.3f,0.0f,
        -0.3f,-0.3f,0.0f,
    };

    GLfloat vertex_buffer_data3[] ={
        0.0f,0.5f,0.0f,
        -0.1f,0.3f,0.0f,
        0.1f,0.3f,0.0f,
    };

    GLfloat vertex_buffer_data4[] ={
        0.0f,0.5f,0.0f,
        0.0f,0.9f,0.0f,
        -0.4f,0.7f,0.0f,
    };

    float vertex_buffer_data5[] ={
        0.1f,0.3f,0.0f,
        0.3f,0.5f,0.0f,
        0.3f,0.3f,0.0f,
    };

    float vertex_buffer_data6[] ={
        0.3f,0.5f,0.0f,
        0.0f,0.5f,0.0f,
        0.0f,0.9f,0.0f,
    }; 

  

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_BROWN, GL_LINE);
    this->object5 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data5, COLOR_GREEN, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data6, color, GL_FILL);
  //  this->object7 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data7, color, GL_LINE);


}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->damage < 1)
        draw3DObject(this->object1);
    if(this->damage < 2)
        draw3DObject(this->object2);
    if(this->damage < 4)
        draw3DObject(this->object3);
    if(this->damage < 7)
        draw3DObject(this->object4);
    if(this->damage < 5)
        draw3DObject(this->object5);
    if(this->damage < 6)
        draw3DObject(this->object6);
    //draw3DObject(this->object7);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Viserion::detect_collision_viserion(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}
bool Viserion::detect_collision_viserions(Balloon ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}
bounding_box_t Viserion::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1.7f, 1.1f };
    return bbox;
}

//////////////
V_Balloon::V_Balloon(float x, float y, float radius,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->speed = speed;
    yspeed = 0;
    GLfloat vertex_buffer_data[900]; 
    int sides = 100;
    float angle = (2*3.14159)/sides;
    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, color, GL_FILL);
}

void V_Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void V_Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void V_Balloon::tick(float y_acc_v) {

    this->position.x -= 0.1;
    //this->position.y += yspeed;
	if(this->position.y > 0){
				this->position.y -= this->speed; 
				this->speed += y_acc_v;
			}
    if(this->position.y <= 0)
        this->position.y = -20;

}

bounding_box_t V_Balloon::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

bool V_Balloon::detect_collision_V(Ball ball) {
     return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}