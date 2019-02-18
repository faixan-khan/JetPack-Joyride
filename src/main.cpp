#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "objects.h"
#include<bits/stdc++.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
vector<Ground> background;
/**************************
* Customizable functions *
**************************/
int main_score=0,f,b_flag=0,timing=0;
int v_timer = 0, v_timing = 0;
int r_timer = 0, r_timing = 0;
const int ENEMY_COUNT = 40;
int up_flag = 0;
float viscous = 1;
int dead_balls[ENEMY_COUNT];
int dead_enemy_count = 0;
//ballon
int ballon_count = 0,timer=0;
float y_speed_ballon = 0;
float y_acc_ballon = 0.004;
//  Objects

Coins coin[50];
Enemy_Ball myball;
Balloon ballon[20];
Ball balls[ENEMY_COUNT];
//Ball ballon;
Ground ground1, ground2, ground3, ground4, ground5, ground6, ground7, ground8;
//Plank enemy_plank[ENEMY_COUNT/2];
Trampoline trampoline;
Magnet magnet;
Pool pool;
Spike spike;
Evil evil[10];
Evil_move evil_move[4];
Halo halo;
int life=1;
Boomerang boomerang;
Ring ring[5];
Special special;
Viserion viserion;
V_Balloon v_balloon;



float screen_zoom = 1, screen_center_x = 0, screen_center_y = 1.0;
double mouse_x = 0.0, mouse_y=0.0;
int mouse_action = 0;

int level = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Eye - Location of camera. Don't change unless you are sure!!
	// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	// glm::vec3 target (0, 0, 0);
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	// glm::vec3 up (0, 1, 0);

	// Compute Camera matrix (view)
	// Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!

	Matrices.view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render the order is important for overwriting the objects

	background[0].draw(VP);
	background[1].draw(VP);
	background[2].draw(VP);
	background[3].draw(VP);
	background[4].draw(VP);
	background[5].draw(VP);
	background[6].draw(VP);
	background[7].draw(VP);
	//ground2.draw(VP);
	//ground3.draw(VP);
	//ground4.draw(VP);
// use this as a trampoline
//	trampoline.draw(VP);
	
	//if(level > 0)
	magnet.draw(VP);
	halo.draw(VP);
	ring[1].draw(VP);
	ring[2].draw(VP);
	pool.draw(VP);
	spike.draw(VP);
	boomerang.draw(VP);
	for(int i=1;i<10;i++)
		evil[i].draw(VP);
	for(int i=1;i<4;i++){
		if(evil_move[i].buj_gaya == 0)
			evil_move[i].draw(VP);
	}
	
	//for(int i=0;i<=99999999;i++){
	//	if(i==99999999)
	myball.draw(VP);
	special.draw(VP);
	viserion.draw(VP);
	v_balloon.draw(VP);
	//for(int i=1;i<=10;i++){
	////	ballon[i]       = Enemy_Ball(myball.position.x+0.05,myball.position.y,0.1,0,COLOR_RED);
	//}
	if(f && timer==0){
		//cout << timer << endl;
		ballon_count++;
			if(ballon_count<19 && timer == 0){
				ballon[ballon_count]       = Balloon(myball.position.x+0.05,myball.position.y+0.8,0.1,0.2,COLOR_RED);
				if(viserion.exist == 0)
					magnet 	  	  			   = Magnet(myball.position.x+3,myball.position.y, 1, 1, COLOR_BLUE);
				b_flag=1;
				y_speed_ballon = 0;
				boomerang	  = Boomerang(myball.position.x,4,0.1,0,COLOR_BLUE);
				//magnet		  = Magnet(myball.position.x+4,myball.position.y,1, 1, COLOR_RED);
		//		cout << ballon_count << endl;
			}
		timer=1;
	}
	if(v_timer == 0 && viserion.damage < 7){
		v_balloon.position.x = viserion.position.x;
		v_balloon.position.y = viserion.position.y+0.5;//     = V_Balloon(viserion.position.x,viserion.position.y,0.1,1,COLOR_GREEN);
		int lmao = rand()%10+1;
		special.position.x = myball.position.x+lmao;
		special.position.y = 4;
		special.speed = 0;
		//special.y_speed_special = 0;
    	//special.y_acc_special = 0.0008;
		v_balloon.speed = 0;
		v_timer = 1;
	}
	if(v_timer == 1 && viserion.damage < 7){
		v_timing++;
		if(v_timing > 100){
			v_timer = 0;
			v_timing = 0;
		}
	}
	if(r_timer == 0 && viserion.damage >= 7){
		int lmao = rand()%10+1;
		special.position.x = myball.position.x+lmao;
		special.position.y = 4;
		special.speed = 0;
		// coins magnet evil evil move ring
			int mag =  rand()%  20+120;
			magnet.position.x =  mag;
			magnet.position.y = rand()%2+1;
		halo.position.x = 130;
		int hh = rand()%3+1;
		r_timer = 1;
		cout << 111111111 << endl;
		int hoh = rand()%5+3;
		evil[1].position.x = myball.position.x+hoh;
		evil[1].position.y = hh;
		evil_move[1].position.x = myball.position.x+hoh+2;
		int lol = rand()%7+1;
		for(int i=1;i<10;i++){
			int h = rand() % 4 + 1;
			coin[i].position.x = myball.position.x + lol + i;
		}
	}
	if(r_timer == 1){
		r_timing++;
		if(r_timing > 1000){
			r_timer = 0;
			r_timing = 0;
		}
	}










	if(timer == 1){
		timing++;
		if(timing > 100){
			timer = 0;
			timing = 0;
		}
	}	
	for(int i=1;i<=ballon_count;i++){
		if(ballon[i].speed != 0){
			ballon[i].draw(VP);
			ballon[i].position.x += 0.1	;
			if(ballon[i].position.y > 0){
				ballon[i].position.y -= y_speed_ballon; 
				y_speed_ballon += y_acc_ballon;
			}
		}
	}
	for(int j=1;j<=ballon_count;j++){
		if(ground1.detect_collision_balloon(ballon[j]) || ground2.detect_collision_balloon(ballon[j]) || ballon[j].position.y <= 0){
			ballon[j].position.y = -20;
			ballon[j].radius = 0;
			
		}
	}
	for(int i = 1 ; i<= ballon_count;i++){
		if(viserion.detect_collision_viserions(ballon[i])){
			ballon[i].position.y = -20;
			ballon[i].radius = 0;
			viserion.damage += 1;
			cout << viserion.damage << endl;
		}
	}
	for(int i=1;i<=27;i++){
			
		coin[i].draw(VP);
	}
	for(int i=1;i<=27;i++){
		if(coin[i].detect_collision_coin(myball)){
			
			if(coin[i].eaten == 0)
			main_score++;
			coin[i].eaten = 1;
		}
	}

	
	if(special.special_collision(myball)){
		main_score += 10;
		special.position.y = -20;
		special.radius = 0;
		//cout << 1111 << endl;
	}
}


void tick_input(GLFWwindow *window) {
	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int up    = glfwGetKey(window, GLFW_KEY_UP);
	int down    = glfwGetKey(window, GLFW_KEY_DOWN);
	int a 	= glfwGetKey(window, GLFW_KEY_A);
	int s 	= glfwGetKey(window, GLFW_KEY_S);
	int d 	= glfwGetKey(window, GLFW_KEY_D);
	int w 	= glfwGetKey(window, GLFW_KEY_W);
		f   = glfwGetKey(window, GLFW_KEY_F);

	if(a && screen_center_x > -1){
		screen_center_x -= 0.05;
		reset_screen(2);
	}
	
	if(s){
		screen_center_y -= 0.01;
		reset_screen(2);
	}

	if(d){
		screen_center_x += 0.05;
		reset_screen(2);
	}

	if(w){
		screen_center_y += 0.01;
		reset_screen(2);
		evil_move[1]	  = Evil_move(myball.position.x+3,1,5,2,COLOR_GREEN);

	}

	// Accelerate on key press and friction on no key press 
	if (left  && myball.position.x > -6.5 && myball.inside_ring == 0) {
		myball.speed += 0.001;
		//cout << myball.position.x << endl;
	}
	else if (right  && myball.inside_ring == 0) {
		if(myball.position.x < -4)
			myball.speed -= 0.001;
	}
		//else{
			// background[0].position.x -= 0.04;
			// background[1].position.x -= 0.04;
			// background[2].position.x -= 0.04;
			// background[3].position.x -= 0.04;
			// background[4].position.x -= 0.04;
			// background[5].position.x -= 0.04;
			// background[6].position.x -= 0.04;
			// background[7].position.x -= 0.04;
			// magnet.position.x -= 0.04;
			// spike.position.x -= 0.04;
			// halo.position.x -= 0.04;
			// ring[1].position.x -= 0.04;
			// ring[2].position.x -= 0.04;
			// viserion.position.x -= 0.04;
			// for(int i=1;i<10;i++)
			// 	evil[i].position.x -= 0.04;
			// for(int i=1;i<4;i++)
			// 	evil_move[i].position.x -= 0.04;
			// //evil.x1 -= 0.05;
			// for(int i=1;i<=27;i++)
			// 	coin[i].position.x -= 0.04;
			

		//}
		 //cout << myball.position.x << endl;
		// cout << myball.position.y << endl;
		 //cout << evil.position.x << endl;
		// cout << evil.position.y << endl;
	//}
	else {
			myball.speed = 0;
	}

			background[0].position.x -= 0.03;
			background[1].position.x -= 0.03;
			background[2].position.x -= 0.03;
			background[3].position.x -= 0.03;
			background[4].position.x -= 0.03;
			background[5].position.x -= 0.03;
			background[6].position.x -= 0.03;
			background[7].position.x -= 0.03;
			magnet.position.x -= 0.03;
			spike.position.x -= 0.03;
			halo.position.x -= 0.03;
			ring[1].position.x -= 0.03;
			ring[2].position.x -= 0.03;
			if(viserion.position.x -  myball.position.x > 3){
				viserion.exist = 0;
				viserion.position.x -= 0.03;
			}
			else
			{
				viserion.exist = 1;
			}
			
			for(int i=1;i<10;i++)
				evil[i].position.x -= 0.03;
			for(int i=1;i<4;i++)
				evil_move[i].position.x -= 0.03;
			//evil.x1 -= 0.05;
			for(int i=1;i<=27;i++)
				coin[i].position.x -= 0.03;
	// For making myball jump
	if (up == GLFW_PRESS && myball.position.y < 3.8 && myball.inside_ring == 0) {// and !up_flag) {
		up_flag = 1;
		myball.ud_raha_hu = 1;
		myball.yspeed = 0.10f;
	}


}

bool tick_elements() {
	myball.tick(viscous);
	halo.tick();
	special.tick(0.004);
	
	if(myball.position.x > -1){
		myball.speed += 0.0001;
	}
	//cout << myball.position.x << endl;
	if(magnet.detect_collision(myball) && myball.halo == 0){
			boomerang	  = Boomerang(myball.position.x,4,0.1,1,COLOR_RED);
			cout << 10101 << endl;
			if(magnet.position.y > 1)
				myball.yspeed = -0.05f;
			else{
				cout << 123 << endl;
				myball.position.x -= 0.5;
			}
		}	

	if(spike.detect_collision(myball)){
		myball.yspeed = 0.5f;
		main_score--;
	}


	if(ground1.detect_collision(myball) || ground2.detect_collision(myball) || ground5.detect_collision(myball) || ground6.detect_collision(myball))
	{
		// printf("Ground Collision\n");
		myball.yspeed = -0.5*myball.yspeed;
		myball.position.y = 0;
		
		up_flag = 0;
		myball.ud_raha_hu = 0;

	}
	for(int i=1;i<=2;i++){
		if(ring[i].detect_collision_ring(myball)){
			myball.inside_ring = 1;
			float x1 = ring[i].position.x;
			float y1 = ring[i].position.y;
			float x2 = myball.position.x;
			float y2 = myball.position.y;
			float r = ring[i].radius;
			float b = (x1-x2)*(x1-x2);
			float cc = sqrt(b);
			float h = (r*r)- b;
			h = sqrt(h);

				myball.position.x += 0.05;
			if(myball.position.y >= 0 && cc < r){
				myball.position.y = h;
			}
			else{
				myball.position.y = 0;
				myball.inside_ring = 0;
			}
			//cout << myball.position.y << endl;
			//cout << "lmao" << endl;
			//myball.position.x 
			// make it traverse the ring circumference
		}
	}
	if(v_balloon.detect_collision_V(myball)){
		myball.position.x = -6;
	}
	if(viserion.detect_collision_viserion(myball) && viserion.damage <7){
		life = 0;
	}
	if(boomerang.boomerang_collision(myball)){
			if(main_score > 10 && boomerang.score_effect == 1)
				main_score = main_score-10;
			else if(main_score < 10 && boomerang.score_effect == 1)
				main_score = 0;
			else if(boomerang.score_effect == 0)
				main_score = main_score + 10;
		}
	if(halo.detect_collision_halo(myball)){
		myball.halo = 1;
		halo.speed = 0;
	}
	for(int i=1;i<4;i++){
		if(evil_move[i].detect_collision_evil_move(myball) && evil_move[i].buj_gaya == 0){
			if(myball.halo == 1)
				myball.halo = 0;
				
			else{
				if(main_score>0)
					main_score--;
				myball.position.x = -6;
			}
		
		}
	}
	for(int i=1;i<=ballon_count;i++){
		for(int j=1;j<4;j++){
			if(evil_move[j].detect_collision_evil_move_balloon(ballon[i])){
				if(evil_move[j].buj_gaya == 0){
					ballon[i].radius = 0;
					ballon[i].position.y = -20;
				}
				evil_move[j].buj_gaya = 1;
			}
		}
	}
	for(int i=1;i<10;i++){
		if(evil[i].detect_collision_evil(myball) && myball.inside_ring == 0){
			boomerang	  = Boomerang(myball.position.x,4,0.1,1,COLOR_RED);
			if(myball.halo == 1)
				evil[i].eaten = 1;
			else
				main_score = 0;
		}
	}
	if(background[0].position.x <= -23){
		
		background.push_back(Ground(24,-1.0,30,1.4,0.0,0.0,COLOR_GREEN));
		background.push_back(Ground(24,-1.0,30,1.4,0.0,0.0,COLOR_GREEN));
		background.push_back(Ground(24,-3,30,4,0.0,0.0,COLOR_BROWN));
		background.push_back(Ground(24,3,30,6,0.0,0.0,COLOR_BLACK));
		background.erase(background.begin());
		background.erase(background.begin());
		background.erase(background.begin());	
		background.erase(background.begin());

	}
	
	// if( std::fabs(pool.detect_collision(myball) ) <= 0.4f  && pool.position.y > myball.position.y )
	// {

	// 	// slope of the replecting plane 
	// 	float m  = (pool.position.x - myball.position.x)/(pool.position.y - myball.position.y);
	// 	myball.speed = (myball.speed*(1 - m*m) + 2*m*myball.yspeed)/(1 + m*m);
	// 	myball.yspeed =(myball.yspeed*(m*m - 1) + 2*m*myball.speed)/(1 + m*m);

	// 	up_flag = 0;
	// 	myball.ud_raha_hu = 0;

	// }


	if (pool.position.y > myball.position.y)
		viscous = 0.6;

	else
		viscous = 1;
		// printf("No Collision detected\n");




	return false;    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models
	main_score = 0;

	myball       = Enemy_Ball(-1, 0,0.2,0.0, COLOR_RED);
	for(int i=1;i<10;i++){
		int h = rand() % 4 + 1;
		coin[i] = Coins(i,h,0.15,COLOR_GREEN);
		coin[9+i] = Coins(i+30,h,0.15,COLOR_YELLOW);
		coin[18+i] = Coins(60+4*i,h,0.15,COLOR_YELLOW);

	}
	//coin          = Coins(2, 2, 0.15, 0, COLOR_YELLOW);
	ground1       = Ground(-6,-1.0,30,1.4,0.0,0.0,COLOR_GREEN);
	ground2       = Ground(-6,-1.0,30,1.4,0.0,0.0,COLOR_GREEN);
	ground3       = Ground(-6,-3,30,4,0.0,0.0,COLOR_BROWN);
	ground4		  = Ground(-6,3,30,6,0.0,0.0,COLOR_BLACK);
	ground5       = Ground(24,-1.0,30,1.4,0.0,0.0,COLOR_RED);
	ground6       = Ground(24,-1.0,30,1.4,0.0,0.0,COLOR_RED);
	ground7       = Ground(24,-3,30,4,0.0,0.0,COLOR_BROWN);
	ground8		  = Ground(24,3,30,6,0.0,0.0,COLOR_BLACK);
	
	background.push_back(ground1);
	background.push_back(ground2);
	background.push_back(ground3);
	background.push_back(ground4);
	background.push_back(ground5);
	background.push_back(ground6);
	background.push_back(ground7);
	background.push_back(ground8);

	//trampoline 	  = Trampoline(6,-0.25,COLOR_BLACK);

	magnet 	  	  = Magnet(25,3, 1, 1, COLOR_RED);
	pool 		  = Pool(0,-1,COLOR_BROWN);
	spike		  = Spike(10,0,2,0.01,2,COLOR_BLUE);
	halo		  = Halo(6,4,0.1,1,COLOR_RED);
	boomerang	  = Boomerang(-1,4,0.1,1,COLOR_RED);
	ring[1]          = Ring(80,0,3,COLOR_GREEN);
	ring[2]		  = Ring(5,0,3,COLOR_BLUE);
	special       = Special(9,4,0.4,0.02,COLOR_YELLOW);
	viserion	  = Viserion(120,myball.position.y+0.4,COLOR_BLUE);	
	ring[3]		  = Ring(135,0,3,COLOR_BLUE);	
	v_balloon     = V_Balloon(viserion.position.x,viserion.position.y,0.1,0,COLOR_GREEN);
	for(int i=2;i<10;i++){
		int hh = rand()%3+1;
		evil[i]			  = Evil(60+5*i,hh,COLOR_GREEN);
	}
		evil[1] 		  = Evil(15, 1, COLOR_GREEN);
	for(int i=1;i<4;i++)
		evil_move[i]	  = Evil_move(40+i*8,1,5,2,COLOR_GREEN);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
	srand(time(0));
	int width  = 1600;
	int height = 800;

	window = initGLFW(width, height);

	initGL (window, width, height);

	/* Draw in loop */
	for(int i=0;!glfwWindowShouldClose(window) && dead_enemy_count < ENEMY_COUNT;i++) {
		// Process timers
			if(life <= 0)
				break;
			//if(viserion.damage > 7)
			//	break;
		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands
			draw();
			
			//viserion	  = Viserion(10,myball.position.y+0.4,COLOR_BLUE);
			viserion.position.y = myball.position.y+0.4;
			
			//for(int i=1;i<=4;i++)
				boomerang.tick();

			
			for(int i=1;i<=3;i++)
				evil_move[i].tick();

			v_balloon.tick(0.004);
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();

			tick_input(window);
			
			reset_screen(2);

			level = main_score/1000;
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();

		
		// if(mouse_action==1){
		// 	printf("x:%lf y:%lf\n",myball.position.x,myball.position.y);
		// 	printf("mx:%lf my:%lf\n",mouse_x,mouse_y);


		// 	// myball.position.x = mouse_x;
		// 	// myball.position.y = mouse_y;
 	// 	}


	// This is used to display the score
		if( i%100000 == 0){
			std::string  str_score = " Score:" + std::to_string(main_score);
    		const char *dis_score = str_score.c_str();
			glfwSetWindowTitle(window,dis_score);
					
		}
	
	}



	quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	// checking that the center of the circle is less than their sum of radius
	// (width or height) = radius of the circle
	return ( ( ( a.x- b.x )*( a.x- b.x ) + ( a.y- b.y )*( a.y- b.y ) ) < ( a.width + b.width ) * ( a.height + b.height ) );    
}

/* Also takes care of the projection matrix on window resize
https://stackoverflow.com/questions/3267243/in-opengl-how-can-i-adjust-for-the-window-being-resized */

void reset_screen(float ratio) {
	float top    = screen_center_y + 4 / screen_zoom;
	float bottom = screen_center_y - 4 / screen_zoom;
	float left   = screen_center_x - 4 / screen_zoom;
	float right  = screen_center_x + 4 / screen_zoom;
	Matrices.projection = glm::ortho(left*ratio, right*ratio, bottom, top, 0.1f, 500.0f);
}
