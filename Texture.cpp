#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

	//asign type to texture
	type = texType;

	//storage of width, height and number of collor chanel of the image
	int widthImg, heightImg, NumColCh;
	//flip the image, without it will be upside down
	stbi_set_flip_vertically_on_load(true);
	//read the image file to store it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &NumColCh, 0);

	//generate opengl texture object
	glGenTextures(1, &ID);
	//assign texture to slot
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	//algorithm that can resize image
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//configure the way texture repeat
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//assign the imeage data
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	//generate mipmaps
	glGenerateMipmap(texType);

	//delete image data bc its already opengl texture object
	stbi_image_free(bytes);
	//unbind texture
	glBindTexture(texType, 0);

	
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//texture need to be activate before changing the value of a uniform
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}