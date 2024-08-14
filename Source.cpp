#include"Model.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main(){
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800 
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	Shader outliningProgram("outlining.vert", "outlining.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Enables the stencil buffer
	glEnable(GL_STENCIL_TEST);
	// sets rules for outcome of stenil test
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Load in a model

	Model crow("models/crow/scene.gltf");
	Model crowOutline("models/crow-outline/scene.gltf");

	// Main while loop
	while (!glfwWindowShouldClose(window)){
		// Specify the color of the background
		glClearColor(1.0f,1.0f,1.0f,1.0f);//(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// make stancil buffer always pass the test
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//enable modify for stencil buffer
		glStencilMask(0xFF);
		// Draw a model
		crow.Draw(shaderProgram, camera);

		//make it only the pixels without value 1 pass the test
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//disable modifying stencil buffer
		glStencilMask(0x00);
		//disable depth buffer
		glDisable(GL_DEPTH_TEST);

		//	first method of drawing outline
		//outliningProgram.Activate();
		//glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 1.08f);
		//crow.Draw(shaderProgram, camera);
		// 
		//	second method of drawing outline
		//outliningProgram.Activate();
		//glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
		//crow.Draw(shaderProgram, camera);

		//	third method of drawing outline
		crowOutline.Draw(outliningProgram, camera);

		//enable modifying stencil buffer
		glStencilMask(0xFF);
		//	clear stencil buffer
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		//	enable depth buffer
		glEnable(GL_DEPTH_TEST);


		//crowOutline.Draw(shaderProgram, camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	outliningProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}