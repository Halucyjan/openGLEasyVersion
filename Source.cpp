#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Vertex Shader source code
//Fragment Shader source code


int main() {
	glfwInit();
	//giving hints that what version of glfw we using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//teling glfw that we will use core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
			-0.5f, -0.5f * float(sqrt(3))	  / 3, 0.0f, //lower left corner
			 0.5f, -0.5f * float(sqrt(3))	  / 3, 0.0f, //lower right corner
			 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper corner
			-0.5f / 2, 0.5f * float(sqrt(3))	 / 6, 0.0f, //inner left
			 0.5f / 2, 0.5f * float(sqrt(3))	 / 6, 0.0f, //inner right
			 0.0f,    -0.5f * float(sqrt(3)) * 2 / 6, 0.0f, //inner down

	};

	GLuint indices[] = {
		0,3,5, //lower left triangle
		3,2,4, //lower right triangle
		5,4,1 //upper triangle
	};

	//creating window, and check for error
	GLFWwindow* window = glfwCreateWindow(800, 800, "title", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// introduce our window to our current context
	glfwMakeContextCurrent(window);

	//load glad
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	

	//create references to vertex array object and vertex buffer object
	GLuint VAO, VBO, EBO;

	//generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	
	glGenBuffers(1, &EBO);

	//make the VAO cuurent vertex array object
	glBindVertexArray(VAO);

	
	// introduce vertecies int VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	

	

	//bind buffer VBO to 0 in casse we accidently modify it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//the same with VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//set background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// clean back buffor and assing new collor
	glClear(GL_COLOR_BUFFER_BIT);
	//change buffer
	glfwSwapBuffers(window);

	//game loop
	while (!glfwWindowShouldClose(window)) {
		//clear buffer, and put background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		////tell opengl which shader program we will use
		//glUseProgram(shaderProgram);
		//bind VAO so opengl know to use it
		glBindVertexArray(VAO);
			//draw triangle
			//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swap buffers
		glfwSwapBuffers(window);

		//take care of events
		glfwPollEvents();
	}

	//destructors of objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	//destructors of window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}