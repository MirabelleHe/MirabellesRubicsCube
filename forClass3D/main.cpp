#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "main.h"

using namespace glm;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

mat4 M = glm::rotate(0.0f, vec3(1, 1, 1));//glm::mat4(1);
vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f);
vec3 in = glm::vec3(0.0f, 0.0f, -1.0f);
vec3 out = glm::vec3(0.0f, 0.0f, 1.0f);
int clockWise = 1;
float angleX = 0.0f;
float angleY = 0.0f;
float rotateAngle = 90.0f;

mat4 trans[] = { translate(2.2f * up + 2.2f * left + 2.2f * in),
				 translate(2.2f * up + 2.2f * in),
				 translate(2.2f * up + 2.2f * right + 2.2f * in),
				 translate(2.2f * right + 2.2f * in),
				 translate(2.2f * in),
				 translate(2.2f * left + 2.2f * in),
				 translate(2.2f * down + 2.2f * left + 2.2f * in),
				 translate(2.2f * down + 2.2f * in),
				 translate(2.2f * down + 2.2f * right + 2.2f * in),
				 translate(2.2f * up + 2.2f * left),
				 translate(2.2f * up),
				 translate(2.2f * up + 2.2f * right),
				 translate(2.2f * right),
				 translate(vec3(0,0,0)),
				 translate(2.2f * left),
				 translate(2.2f * down + 2.2f * left),
				 translate(2.2f * down),
				 translate(2.2f * down + 2.2f * right),
				 translate(2.2f * up + 2.2f * left + 2.2f * out),
				 translate(2.2f * up + 2.2f * out),
				 translate(2.2f * up + 2.2f * right + 2.2f * out),
				 translate(2.2f * right + 2.2f * out),
				 translate(2.2f * out),
				 translate(2.2f * left + 2.2f * out),
				 translate(2.2f * down + 2.2f * left + 2.2f * out),
				 translate(2.2f * down + 2.2f * out),
				 translate(2.2f * down + 2.2f * right + 2.2f * out),
				};
mat4 rotates[27] = {mat4(1)};

int scene[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };
int tmpScene[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Vertex vertices[] =
	{   //blue front
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		//green back
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 0)),
		// bright blue down
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 1)),
		//yellow up
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		//red right
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		//orange left
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0.5f, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0.5f, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0.5f, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0.5f, 0))
	};

	unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh monkey("./res/meshes/monkeyNoUV.obj");
	Shader shader("./res/shaders/basicShader");
	
	vec3 pos = vec3(0,0,-20);
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	
	mat4 P = glm::perspective(60.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	P = P * glm::lookAt(pos, pos + forward, up);
	glfwSetKeyCallback(display.m_window,key_callback);

	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < 28; i++) {
			M = rotate(angleX, vec3(0, 1, 0)) * rotate(angleY, vec3(1, 0, 0)) * trans[i] * rotates[i];
			shader.Bind();
			shader.Update(P * M, M);
			mesh.Draw();
		}
		mesh.Draw();

		display.SwapBuffers();

		glfwPollEvents();
	}

	return 0;
}

void rotateCubeRight() {
	M = glm::rotate(M, 5.0f, up);
	angleX += 5.0f;
}

void rotateCubeLeft() {
	M = glm::rotate(M, 5.0f, down);
	angleX -= 5.0f;
}

void rotateCubeUp() {
	M = glm::rotate(M, 5.0f, right);
	angleY += 5.0f;
}

void rotateCubeDown() {
	M = glm::rotate(M, 5.0f, left);
	angleY -= 5.0f;
}

void rotateRight() {
	if (clockWise) {
		//translate
		trans[scene[0]] = translate(trans[scene[0]], 4.4f*out);
		trans[scene[9]] = translate(trans[scene[9]], 2.2f*out + 2.2f*down);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*down);
		trans[scene[5]] = translate(trans[scene[5]], 2.2f*up + 2.2f*out);
		trans[scene[23]] = translate(trans[scene[23]], 2.2f*down + 2.2f*in);
		trans[scene[6]] = translate(trans[scene[6]], 4.4f*up);	
		trans[scene[15]] = translate(trans[scene[15]], 2.2f*in + 2.2f*up);	
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*in);	

		//rotate
		rotates[scene[0]] = rotate(rotateAngle, right) * rotates[scene[0]];
		rotates[scene[9]] = rotate(rotateAngle, right) * rotates[scene[9]];
		rotates[scene[18]] = rotate(rotateAngle, right) * rotates[scene[18]];
		rotates[scene[5]] = rotate(rotateAngle, right) * rotates[scene[5]];
		rotates[scene[14]] = rotate(rotateAngle, right) * rotates[scene[14]];
		rotates[scene[23]] = rotate(rotateAngle, right) * rotates[scene[23]];
		rotates[scene[6]] = rotate(rotateAngle, right) * rotates[scene[6]];
		rotates[scene[15]] = rotate(rotateAngle, right) * rotates[scene[15]];
		rotates[scene[24]] = rotate(rotateAngle, right) * rotates[scene[24]];

		tmpScene[0] = scene[6];
		tmpScene[9] = scene[5];
		tmpScene[18] = scene[0];
		tmpScene[5] = scene[15];
		tmpScene[14] = scene[14];
		tmpScene[23] = scene[9];
		tmpScene[6] = scene[24];
		tmpScene[15] = scene[23];
		tmpScene[24] = scene[18];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
	else {
		//translate
		trans[scene[0]] = translate(trans[scene[0]], 4.4f*down);
		trans[scene[9]] = translate(trans[scene[9]], 2.2f*in + 2.2f*down);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*in);
		trans[scene[5]] = translate(trans[scene[5]], 2.2f*down + 2.2f*out);
		trans[scene[23]] = translate(trans[scene[23]], 2.2f*up + 2.2f*in);
		trans[scene[6]] = translate(trans[scene[6]], 4.4f*out);
		trans[scene[15]] = translate(trans[scene[15]], 2.2f*up + 2.2f*out);
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*up);

		//rotate
		rotates[scene[0]] = rotate(-rotateAngle, right) * rotates[scene[0]];
		rotates[scene[9]] = rotate(-rotateAngle, right) * rotates[scene[9]];
		rotates[scene[18]] = rotate(-rotateAngle, right) * rotates[scene[18]];
		rotates[scene[5]] = rotate(-rotateAngle, right) * rotates[scene[5]];
		rotates[scene[14]] = rotate(-rotateAngle, right) * rotates[scene[14]];
		rotates[scene[23]] = rotate(-rotateAngle, right) * rotates[scene[23]];
		rotates[scene[6]] = rotate(-rotateAngle, right) * rotates[scene[6]];
		rotates[scene[15]] = rotate(-rotateAngle, right) * rotates[scene[15]];
		rotates[scene[24]] = rotate(-rotateAngle, right) * rotates[scene[24]];

		tmpScene[0] = scene[18];
		tmpScene[9] = scene[23];
		tmpScene[18] = scene[24];
		tmpScene[5] = scene[9];
		tmpScene[14] = scene[14];
		tmpScene[23] = scene[15];
		tmpScene[6] = scene[0];
		tmpScene[15] = scene[5];
		tmpScene[24] = scene[6];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
}

void rotateLeft() {
	if (clockWise) {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*in);	
		trans[scene[11]] = translate(trans[scene[11]], 2.2f*in + 2.2f*down);	
		trans[scene[2]] = translate(trans[scene[2]], 4.4f*down);	
		trans[scene[21]] = translate(trans[scene[21]], 2.2f*up + 2.2f*in);	
		trans[scene[3]] = translate(trans[scene[3]], 2.2f*down + 2.2f*out);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*up);	
		trans[scene[17]] = translate(trans[scene[17]], 2.2f*out + 2.2f*up);	
		trans[scene[8]] = translate(trans[scene[8]], 4.4f*out);	

		//rotate
		rotates[scene[20]] = rotate(rotateAngle, left) * rotates[scene[20]];
		rotates[scene[11]] = rotate(rotateAngle, left) * rotates[scene[11]];
		rotates[scene[2]] = rotate(rotateAngle, left) * rotates[scene[2]];
		rotates[scene[21]] = rotate(rotateAngle, left) * rotates[scene[21]];
		rotates[scene[12]] = rotate(rotateAngle, left) * rotates[scene[12]];
		rotates[scene[3]] = rotate(rotateAngle, left) * rotates[scene[3]];
		rotates[scene[26]] = rotate(rotateAngle, left) * rotates[scene[26]];
		rotates[scene[17]] = rotate(rotateAngle, left) * rotates[scene[17]];
		rotates[scene[8]] = rotate(rotateAngle, left) * rotates[scene[8]];

		tmpScene[20] = scene[26];
		tmpScene[11] = scene[21];
		tmpScene[2] = scene[20];
		tmpScene[21] = scene[17];
		tmpScene[12] = scene[12];
		tmpScene[3] = scene[11];
		tmpScene[26] = scene[8];
		tmpScene[17] = scene[3];
		tmpScene[8] = scene[2];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
	else {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*down);
		trans[scene[11]] = translate(trans[scene[11]], 2.2f*out + 2.2f*down);
		trans[scene[2]] = translate(trans[scene[2]], 4.4f*out);
		trans[scene[21]] = translate(trans[scene[21]], 2.2f*down + 2.2f*in);
		trans[scene[3]] = translate(trans[scene[3]], 2.2f*up + 2.2f*out);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*in);
		trans[scene[17]] = translate(trans[scene[17]], 2.2f*in + 2.2f*up);	
		trans[scene[8]] = translate(trans[scene[8]], 4.4f*up);	

		//rotate
		rotates[scene[20]] = rotate(-rotateAngle, left) * rotates[scene[20]];
		rotates[scene[11]] = rotate(-rotateAngle, left) * rotates[scene[11]];
		rotates[scene[2]] = rotate(-rotateAngle, left) * rotates[scene[2]];
		rotates[scene[21]] = rotate(-rotateAngle, left) * rotates[scene[21]];
		rotates[scene[12]] = rotate(-rotateAngle, left) * rotates[scene[12]];
		rotates[scene[3]] = rotate(-rotateAngle, left) * rotates[scene[3]];
		rotates[scene[26]] = rotate(-rotateAngle, left) * rotates[scene[26]];
		rotates[scene[17]] = rotate(-rotateAngle, left) * rotates[scene[17]];
		rotates[scene[8]] = rotate(-rotateAngle, left) * rotates[scene[8]];

		tmpScene[20] = scene[2];
		tmpScene[11] = scene[3];
		tmpScene[2] = scene[8];
		tmpScene[21] = scene[11];
		tmpScene[12] = scene[12];
		tmpScene[3] = scene[17];
		tmpScene[26] = scene[20];
		tmpScene[17] = scene[21];
		tmpScene[8] = scene[26];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
}

void rotateUp() {
	if (clockWise) {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*left);
		trans[scene[19]] = translate(trans[scene[19]], 2.2f*left + 2.2f*in);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*in);
		trans[scene[11]] = translate(trans[scene[11]], 2.2f*out + 2.2f*left);
		trans[scene[9]] = translate(trans[scene[9]], 2.2f*in + 2.2f*right);	
		trans[scene[2]] = translate(trans[scene[2]], 4.4f*out);
		trans[scene[1]] = translate(trans[scene[1]], 2.2f*right + 2.2f*out);
		trans[scene[0]] = translate(trans[scene[0]], 4.4f*right);

		//rotate
		rotates[scene[20]] = rotate(rotateAngle, down) * rotates[scene[20]];
		rotates[scene[19]] = rotate(rotateAngle, down) * rotates[scene[19]];
		rotates[scene[18]] = rotate(rotateAngle, down) * rotates[scene[18]];
		rotates[scene[11]] = rotate(rotateAngle, down) * rotates[scene[11]];
		rotates[scene[10]] = rotate(rotateAngle, down) * rotates[scene[10]];
		rotates[scene[9]] = rotate(rotateAngle, down) * rotates[scene[9]];
		rotates[scene[2]] = rotate(rotateAngle, down) * rotates[scene[2]];
		rotates[scene[1]] = rotate(rotateAngle, down) * rotates[scene[1]];
		rotates[scene[0]] = rotate(rotateAngle, down) * rotates[scene[0]];

		tmpScene[20] = scene[2];
		tmpScene[19] = scene[11];
		tmpScene[18] = scene[20];
		tmpScene[11] = scene[1];
		tmpScene[10] = scene[10];
		tmpScene[9] = scene[19];
		tmpScene[2] = scene[0];
		tmpScene[1] = scene[9];
		tmpScene[0] = scene[18];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
	else {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*in);
		trans[scene[19]] = translate(trans[scene[19]], 2.2f*right + 2.2f*in);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*right);
		trans[scene[11]] = translate(trans[scene[11]], 2.2f*in + 2.2f*left);
		trans[scene[9]] = translate(trans[scene[9]], 2.2f*out + 2.2f*right);
		trans[scene[2]] = translate(trans[scene[2]], 4.4f*left);
		trans[scene[1]] = translate(trans[scene[1]], 2.2f*left + 2.2f*out);
		trans[scene[0]] = translate(trans[scene[0]], 4.4f*out);

		//rotate
		rotates[scene[20]] = rotate(-rotateAngle, down) * rotates[scene[20]];
		rotates[scene[19]] = rotate(-rotateAngle, down) * rotates[scene[19]];
		rotates[scene[18]] = rotate(-rotateAngle, down) * rotates[scene[18]];
		rotates[scene[11]] = rotate(-rotateAngle, down) * rotates[scene[11]];
		rotates[scene[10]] = rotate(-rotateAngle, down) * rotates[scene[10]];
		rotates[scene[9]] = rotate(-rotateAngle, down) * rotates[scene[9]];
		rotates[scene[2]] = rotate(-rotateAngle, down) * rotates[scene[2]];
		rotates[scene[1]] = rotate(-rotateAngle, down) * rotates[scene[1]];
		rotates[scene[0]] = rotate(-rotateAngle, down) * rotates[scene[0]];

		tmpScene[20] = scene[18];
		tmpScene[19] = scene[9];
		tmpScene[18] = scene[0];
		tmpScene[11] = scene[19];
		tmpScene[10] = scene[10];
		tmpScene[9] = scene[1];
		tmpScene[2] = scene[20];
		tmpScene[1] = scene[11];
		tmpScene[0] = scene[2];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
}

void rotateDown() {
	if (clockWise) {
		//translate
		trans[scene[8]] = translate(trans[scene[8]], 4.4f*left);
		trans[scene[7]] = translate(trans[scene[7]], 2.2f*left + 2.2f*out);
		trans[scene[6]] = translate(trans[scene[6]], 4.4f*out);
		trans[scene[17]] = translate(trans[scene[17]], 2.2f*in + 2.2f*left);
		trans[scene[15]] = translate(trans[scene[15]], 2.2f*out + 2.2f*right);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*in);
		trans[scene[25]] = translate(trans[scene[25]], 2.2f*right + 2.2f*in);
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*right);

		//rotate
		rotates[scene[8]] = rotate(rotateAngle, up) * rotates[scene[8]];
		rotates[scene[7]] = rotate(rotateAngle, up) * rotates[scene[7]];
		rotates[scene[6]] = rotate(rotateAngle, up) * rotates[scene[6]];
		rotates[scene[17]] = rotate(rotateAngle, up) * rotates[scene[17]];
		rotates[scene[16]] = rotate(rotateAngle, up) * rotates[scene[16]];
		rotates[scene[15]] = rotate(rotateAngle, up) * rotates[scene[15]];
		rotates[scene[26]] = rotate(rotateAngle, up) * rotates[scene[26]];
		rotates[scene[25]] = rotate(rotateAngle, up) * rotates[scene[25]];
		rotates[scene[24]] = rotate(rotateAngle, up) * rotates[scene[24]];

		tmpScene[8] = scene[26];
		tmpScene[7] = scene[17];
		tmpScene[6] = scene[8];
		tmpScene[17] = scene[25];
		tmpScene[16] = scene[16];
		tmpScene[15] = scene[7];
		tmpScene[26] = scene[24];
		tmpScene[25] = scene[15];
		tmpScene[24] = scene[6];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
	else {
		//translate
		trans[scene[8]] = translate(trans[scene[8]], 4.4f*out);
		trans[scene[7]] = translate(trans[scene[7]], 2.2f*right + 2.2f*out);
		trans[scene[6]] = translate(trans[scene[6]], 4.4f*right);
		trans[scene[17]] = translate(trans[scene[17]], 2.2f*out + 2.2f*left);
		trans[scene[15]] = translate(trans[scene[15]], 2.2f*in + 2.2f*right);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*left);
		trans[scene[25]] = translate(trans[scene[25]], 2.2f*left + 2.2f*in);
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*in);

		//rotate
		rotates[scene[8]] = rotate(-rotateAngle, up) * rotates[scene[8]];
		rotates[scene[7]] = rotate(-rotateAngle, up) * rotates[scene[7]];
		rotates[scene[6]] = rotate(-rotateAngle, up) * rotates[scene[6]];
		rotates[scene[17]] = rotate(-rotateAngle, up) * rotates[scene[17]];
		rotates[scene[16]] = rotate(-rotateAngle, up) * rotates[scene[16]];
		rotates[scene[15]] = rotate(-rotateAngle, up) * rotates[scene[15]];
		rotates[scene[26]] = rotate(-rotateAngle, up) * rotates[scene[26]];
		rotates[scene[25]] = rotate(-rotateAngle, up) * rotates[scene[25]];
		rotates[scene[24]] = rotate(-rotateAngle, up) * rotates[scene[24]];

		tmpScene[8] = scene[6];
		tmpScene[7] = scene[15];
		tmpScene[6] = scene[24];
		tmpScene[17] = scene[7];
		tmpScene[16] = scene[16];
		tmpScene[15] = scene[25];
		tmpScene[26] = scene[8];
		tmpScene[25] = scene[17];
		tmpScene[24] = scene[26];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
}

void rotateBack() {
	if (clockWise) {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*down);
		trans[scene[19]] = translate(trans[scene[19]], 2.2f*right + 2.2f*down);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*right);
		trans[scene[21]] = translate(trans[scene[21]], 2.2f*down + 2.2f*left);
		trans[scene[23]] = translate(trans[scene[23]], 2.2f*up + 2.2f*right);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*left);
		trans[scene[25]] = translate(trans[scene[25]], 2.2f*left + 2.2f*up);
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*up);

		//rotate
		for (int i = 18; i < 27; i++)
			rotates[scene[i]] = rotate(rotateAngle, in) * rotates[scene[i]];

		tmpScene[20] = scene[18];
		tmpScene[19] = scene[23];
		tmpScene[18] = scene[24];
		tmpScene[21] = scene[19];
		tmpScene[22] = scene[22];
		tmpScene[23] = scene[25];
		tmpScene[26] = scene[20];
		tmpScene[25] = scene[21];
		tmpScene[24] = scene[26];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
	else {
		//translate
		trans[scene[20]] = translate(trans[scene[20]], 4.4f*left);
		trans[scene[19]] = translate(trans[scene[19]], 2.2f*left + 2.2f*down);
		trans[scene[18]] = translate(trans[scene[18]], 4.4f*down);
		trans[scene[21]] = translate(trans[scene[21]], 2.2f*up + 2.2f*left);
		trans[scene[23]] = translate(trans[scene[23]], 2.2f*down + 2.2f*right);
		trans[scene[26]] = translate(trans[scene[26]], 4.4f*up);
		trans[scene[25]] = translate(trans[scene[25]], 2.2f*right + 2.2f*up);
		trans[scene[24]] = translate(trans[scene[24]], 4.4f*right);

		//rotate
		for (int i = 18; i < 27; i++)
			rotates[scene[i]] = rotate(-rotateAngle, in) * rotates[scene[i]];

		tmpScene[20] = scene[26];
		tmpScene[19] = scene[21];
		tmpScene[18] = scene[20];
		tmpScene[21] = scene[25];
		tmpScene[22] = scene[22];
		tmpScene[23] = scene[19];
		tmpScene[26] = scene[24];
		tmpScene[25] = scene[23];
		tmpScene[24] = scene[18];
		for (int i = 0; i < 28; i++)
			scene[i] = tmpScene[i];
	}
}

void rotateFront() {
		if (clockWise) {
			//translate
			trans[scene[0]] = translate(trans[scene[0]], 4.4f*down);
			trans[scene[1]] = translate(trans[scene[1]], 2.2f*left + 2.2f*down);
			trans[scene[2]] = translate(trans[scene[2]], 4.4f*left);
			trans[scene[3]] = translate(trans[scene[3]], 2.2f*up + 2.2f*left);
			trans[scene[5]] = translate(trans[scene[5]], 2.2f*down + 2.2f*right); 
			trans[scene[6]] = translate(trans[scene[6]], 4.4f*right);
			trans[scene[7]] = translate(trans[scene[7]], 2.2f*right + 2.2f*up);
			trans[scene[8]] = translate(trans[scene[8]], 4.4f*up);

			//rotate
			for (int i = 0; i < 9; i++)
				rotates[scene[i]] = rotate(rotateAngle, out) * rotates[scene[i]];

			tmpScene[0] = scene[2];
			tmpScene[1] = scene[3];
			tmpScene[2] = scene[8];
			tmpScene[3] = scene[7];
			tmpScene[4] = scene[4];
			tmpScene[5] = scene[1];
			tmpScene[6] = scene[0];
			tmpScene[7] = scene[5];
			tmpScene[8] = scene[6];
			for (int i = 0; i < 28; i++)
				scene[i] = tmpScene[i];
		}
		else {
			//translate
			trans[scene[0]] = translate(trans[scene[0]], 4.4f*right);
			trans[scene[1]] = translate(trans[scene[1]], 2.2f*right + 2.2f*down);
			trans[scene[2]] = translate(trans[scene[2]], 4.4f*down);
			trans[scene[3]] = translate(trans[scene[3]], 2.2f*down + 2.2f*left);
			trans[scene[5]] = translate(trans[scene[5]], 2.2f*up + 2.2f*right);
			trans[scene[6]] = translate(trans[scene[6]], 4.4f*up);
			trans[scene[7]] = translate(trans[scene[7]], 2.2f*left + 2.2f*up);
			trans[scene[8]] = translate(trans[scene[8]], 4.4f*left);

			//rotate
			for (int i = 0; i < 9; i++)
				rotates[scene[i]] = rotate(-rotateAngle, in) * rotates[scene[i]];

			tmpScene[0] = scene[6];
			tmpScene[1] = scene[5];
			tmpScene[2] = scene[0];
			tmpScene[3] = scene[1];
			tmpScene[4] = scene[4];
			tmpScene[5] = scene[7];
			tmpScene[6] = scene[8];
			tmpScene[7] = scene[3];
			tmpScene[8] = scene[2];
			for (int i = 0; i < 28; i++)
				scene[i] = tmpScene[i];
		}
}

void flipDirection() {
	clockWise = !clockWise;
}


