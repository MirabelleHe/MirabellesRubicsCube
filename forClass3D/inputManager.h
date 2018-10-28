#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include "main.h"

bool doubleAngle = false;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			if(action == GLFW_PRESS)
				glfwSetWindowShouldClose(window,GLFW_TRUE);
			break;
		case GLFW_KEY_RIGHT:
				rotateCubeRight();
			break;
		case GLFW_KEY_LEFT:
				rotateCubeLeft();
			break;
		case GLFW_KEY_UP:
				rotateCubeUp();
			break;
		case GLFW_KEY_DOWN:
				rotateCubeDown();
			break;
		case GLFW_KEY_F:
			if (action == GLFW_PRESS) {
				rotateFront();
				if (doubleAngle)
					rotateFront();
			}
			break;
		case GLFW_KEY_B:
			if (action == GLFW_PRESS) {
				rotateBack();
				if (doubleAngle)
					rotateBack();
			}
			break;
		case GLFW_KEY_R:
			if (action == GLFW_PRESS) {
				rotateRight();
				if (doubleAngle)
					rotateRight();
			}
			break;
		case GLFW_KEY_L:
			if (action == GLFW_PRESS) {
				rotateLeft();
				if (doubleAngle)
					rotateLeft();
			}
			break;
		case GLFW_KEY_U:
			if (action == GLFW_PRESS) {
				rotateUp();
				if (doubleAngle)
					rotateUp();
			}
			break;
		case GLFW_KEY_D:
			if (action == GLFW_PRESS) {
				rotateDown();
				if (doubleAngle)
					rotateDown();
			}
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS)
				flipDirection();
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS)
				doubleAngle = !doubleAngle;
			break;
		default:
			break;
		}
		
	}



