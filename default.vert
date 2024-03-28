#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

layout (location = 2) in vec2 aTex;

// outpot color from fragment shader
out vec3 color;

//output texture coordinate
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
	//output position of all vertices
	// old one: gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	gl_Position = camMatrix * vec4(aPos, 1.0);
	//asign color from vertex data
	color = aCol;

	//asign coordinates from vertex data
	texCoord = aTex;
}