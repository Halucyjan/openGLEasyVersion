#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader to source
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile vertex shader to machine code
	glCompileShader(vertexShader);

	//create fragent shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragemnt shader to source
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile fragment shader to machine code
	glCompileShader(fragmentShader);

	ID = glCreateProgram();

	//attach vertex and fragment shader to shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	
	//link up all shader together into shader program
	glLinkProgram(ID);

	//delete vertex and fragmetn shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}