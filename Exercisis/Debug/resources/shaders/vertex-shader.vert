#version 150

	//vec3 means a vector of 3 positions that will manage x, y, z
in vec3 vertexPosition;
	//vec4 means a vector of 4 positions that will manage RGBA		
in vec4 vertexColor;

	//Send the position and the color of the vertex to the fragment shader
out vec3 fragmentPosition;
out vec4 fragmentColor;


void main() {
		//Does not alter the vertices at all
	gl_Position = vec4(vertexPosition, 1);

		//We need to create the output variables that will go to the fragment shader, so, we assign the in variables to the new out variables	
	fragmentPosition=vertexPosition;
	fragmentColor=vertexColor;	

}