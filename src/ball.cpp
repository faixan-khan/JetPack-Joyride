#include "ball.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;
#define GLM_ENABLE_EXPERIMENTAL
Ball::Ball(float x, float y, float radius,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->speed = speed;
    this->ud_raha_hu;
    yspeed = 0;
    this->halo = 0;
    this->inside_ring = 0;

   // GLfloat vertex_buffer_data[900]; 
    //int sides = 100;
    //float angle = (2*3.14159)/sides;
    static const GLfloat vertex_buffer_data[] = {
         0, 0.8,0.0, // triangle 2 : begin
         0, 0.6,0.0,
         0.2, 0.8,0.0, // triangle 2 : end

         0, 0.1, 0.0,
         0.05, 0.1, 0.0,
         0.05, 0, 0,

         0, 0.1, 0.0,
         0.0, 0.0, 0.0,
         0.05, 0.0, 0.0,

         0.17, 0.1, 0.0,
         0.22, 0.1, 0.0,
         0.22, 0.0 , 0.0,

         0.22, 0.0, 0.0,
         0.17, 0.0, 0.0,
         0.17, 0.1, 0.0,

         -0.05, 0.425, 0.0,
         0.0, 0.425, 0.0,
         0.0, 0.375, 0.0,

         0.0, 0.375, 0.0,
         -0.05, 0.375, 0.0,
         -0.05, 0.425, 0.0

          };

    static const GLfloat vertex_buffer_data1[] = {
         0, 0.6,0.0,
         0.15, 0.6, 0.0,
         0.15, 0.75, 0.0,

         0.05, 0.6, 0.0,
         0.1, 0.6, 0.0,
         0.1, 0.5, 0.0,

         0.1, 0.5, 0.0,
         0.05, 0.5, 0.0,
         0.05, 0.6, 0.0,

         0, 0.5, 0.0,
         0.17, 0.5, 0.0,
         0.17, 0.3, 0.0,

         0, 0.3, 0.0,
         0, 0.5, 0.0,
         0.17, 0.3, 0.0,
          };

    static const GLfloat vertex_buffer_data2[] = {
         0, 0.3, 0.0,
         0, 0.1, 0.0,
         0.075, 0.3, 0.0,

         0.17, 0.3, 0.0,
         0.17, 0.1, 0.0,
         0.075, 0.3, 0.0,

         -0.15, 0.5, 0.0,
         -0.05, 0.5, 0.0,
         -0.05, 0.25, 0.0,

         -0.15, 0.5, 0.0,
         -0.05, 0.25, 0.0,
         -0.15, 0.25, 0.0,
          };

    static const GLfloat vertex_buffer_data3[] = {
      -0.15, 0.2, 0.0,
      -0.1, 0.2, 0.0,
      -0.15, 0.0, 0.0,

      -0.1, 0.2, 0.0,
      -0.05, 0.2, 0.0,
      -0.05, 0.0, 0.0,

          };

    static const GLfloat vertex_buffer_data4[] = {
        0.1,1.0,0.0,
        0.0,1.2,0.0,
        0.2,1.2,0.00,

    };

    static const GLfloat vertex_buffer_data5[] = {
        0.1,1.2,0.0,
        0.05,1.1,0.0,
        0.15,1.1,0.00,

    };

    
    
    this->object = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_YELLOW, GL_LINE);
    this->object5 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data5, COLOR_RED, GL_FILL);



    //for(int i =0; i < sides;i++)
    //{
    //    vertex_buffer_data[9*i] = 0.0f;
    //    vertex_buffer_data[9*i + 1] = 0.0f;  
    //    vertex_buffer_data[9*i + 2] = 0.0f;
    //    vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
    //    vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
    //    vertex_buffer_data[9*i + 5] = 0.0f; 
    //    vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
    //    vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
    //    vertex_buffer_data[9*i + 8] = 0.0f;
    //}


    //this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    if(this->ud_raha_hu==1)
        draw3DObject(this->object3);
    if(this->halo == 1){
        draw3DObject(this->object4);
        draw3DObject(this->object5);
    }
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {

    this->position.x -= speed;
    this->position.y += yspeed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

void Enemy_Ball::tick(float viscous) {


    if(speed > 0.2f)
        this->speed = 0.2f;

    else if(speed < -0.2f)
        this->speed = -0.2f;

    this->position.x -= viscous*speed;

    // if(std::abs(yspeed) > 0.5f)
    //     this->yspeed = 0.5f;


    if(yspeed > 0.5f)
        this->yspeed = 0.5f;

    else if(yspeed < -0.5f)
        this->yspeed = -0.5f;

    yspeed = yspeed - 0.01; // gravity

    this->position.y += viscous*yspeed ;

    if(this->position.y > 4.5)
        this->position.y = 4.5;

        
    if(this->position.y < -2.75)
        this->position.y = -2.75;


}

Balloon::Balloon(float x, float y, float radius,float speed, color_t color) {
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

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::tick() {

    this->position.x -= speed;
    this->position.y += yspeed;
}

bounding_box_t Balloon::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}
//////////////////////////////////////////////////////// halo



Halo::Halo(float x, float y, float radius,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->speed = speed;
    yspeed = 0;
    
    static const GLfloat vertex_buffer_data3[] = {
        0.1,0.1,0.0,
        0.1,-0.1,0.0,
        -0.1,-0.1,0.0,

        0.1, 0.1, 0.0,
        -0.1, -0.1, 0.0,
        -0.1, 0.1, 0.0,

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color, GL_LINE);
}

void Halo::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->speed == 1)
        draw3DObject(this->object);
}

void Halo::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Halo::tick() {


    //this->position.x -= speed;
    this->position.y += yspeed;
}

bounding_box_t Halo::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}

bool Halo::detect_collision_halo(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}
//////////////////////////////////////////////////////////////////////

Boomerang::Boomerang(float x, float y, float offset,int score_effect, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->init_position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(x, y, 0);
    this->visible = true;
    this->offset = offset;
    this->before = -1.0f;
    this->score_effect = score_effect;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 0.375f;
    this->box.height = 2 * 0.2165f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat boomerang[] = {
        0.0f,0.0f,0.0f,
        -0.25f,0.0f,0.0f,
        0.1f,0.2165f,0.0f,


        0.0f,0.0f,0.0f,
        -0.25f,0.0f,0.0f,
        0.125f,-0.2165f,0.0f,
    };
    
    this->boomerang = create3DObject(GL_TRIANGLES, 2*3, boomerang, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->boomerang);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->rotation += 5.0f;
    this->move_backward();
    this->move_downward();

    this->position.x = this->abs_position.x + 3*this->position.y*this->position.y;

    this->box.x = this->init_position.x + 3*this->position.y*this->position.y + this->offset;
    // this->box.x = this->position.x;
    this->box.y = this->position.y;
    
    // cout << "BOOMER " << " " << this->box.x << " " << this->box.y << "\n"; 

}

// void Boomerang::move_forward() {
//     this->position.x += speed_x;
// }

void Boomerang::move_backward() {
    this->abs_position.x -= 0.009;//GAME_SPEED;
}

void Boomerang::move_downward() {
    this->position.y -= 0.05;//BOOMERANG_FALL;
}

bounding_box_t Boomerang::get_box(){
    return this->box;
}

bool Boomerang::get_visibility(){
    return this->visible;
}

void Boomerang::collided(){
    this->visible =false;
}

float Boomerang::get_x() {
    return this->position.x;
}

bool Boomerang::boomerang_collision(Ball ball){
    if(ball.position.x + 0.38 >= this->position.x && ball.position.x - 0.38 <= this->position.x && ball.position.y + 0.38 >= this->position.y && ball.position.y - 0.38 <= this->position.y){
    //if(now - this->before > 1.0f){
         //cout << "now" << " " << "this->before" << "\n"; 
    //    this->before = now;
        return true;
    }
     //cout << ball.position.y << " " << this->position.y << "\n"; 
    return false;
}

/////////////  special objects

Special::Special(float x, float y, float radius,float speed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radius;
    this->speed = speed;
    yspeed = 0;
    GLfloat vertex_buffer_data[] = {
        0.0,0.2,0.0,
        -0.2,-0.2,0.0,
        0.2,-0.2,0.0,

        0.0,-0.3,0.0,
        -0.2,0.1,0.0,
        0.2,0.1,0.0,
    };
  


    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
}

void Special::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->position.y > 0)
        draw3DObject(this->object);
}

void Special::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
//float y_speed_special = 0;
//float y_acc_special = 0.0008;
void Special::tick(float y_acc_v) {

    this->position.x -= 0.1;
    //this->position.y += yspeed;
	if(this->position.y > 0){
				this->position.y -= this->speed; 
				this->speed += y_acc_v;
			}
    if(this->position.y <= 0)
        this->position.y = -20;

}




//void Special::tick() {
//
//    this->position.x -= 0.1;
//    //this->position.y += yspeed;
//	if(this->position.y > 0){
//				this->position.y -= this->y_acc_special;//y_speed_special; 
//				y_speed_special += this->y_acc_special;
//			}
//}

bounding_box_t Special::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius, this->radius };
    return bbox;
}
bool Special::special_collision(Ball ball) {
    return std::fabs( ( ( ball.position.x - this->position.x )*( ball.position.x - this->position.x ) + ( ball.position.y - this->position.y )*( ball.position.y - this->position.y ) ) < ( ball.radius + this->radius ) * ( ball.radius + this->radius ) );
}
