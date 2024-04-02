#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

// outpot color from fragment shader
out vec3 color;

//output texture coordinate
out vec2 texCoord;

out vec3 Normal;

//output current position
out vec3 crntPos;

//import the camera function from the main function
uniform mat4 camMatrix;

uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));

	//output position of all vertices
	// old one: gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	//asign color from vertex data
	color = aCol;

	//asign coordinates from vertex data
	texCoord = aTex;

	Normal = aNormal;
}