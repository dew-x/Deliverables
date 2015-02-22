#version 150
//The fragment shader operates on each pixel in a given polygon

//We declare the input variables that come from the vertex shader
	//fragment position: It's an interpolation of the position of the vertex, so, the pixel position
	//fragment color: It's an interpolation of the color based on the triangles vertices
in vec3 fragmentPosition;
in vec4 fragmentColor;
	

//It will output a color into the screen.
//Program works with 4 colors, which will be directly send to the screen. That's why the color that we have to send has 4 components (RGBA)
out vec4 finalColor;

//Variables that are managed from the application
	//time value for changing the color
uniform float time;

void main() {
	//Assign the color based on the color the vertices
	//finalColor = fragmentColor;
		
	//Color is randomly changed based on the time.
	//Each component in the vector goes from 0 to 1. cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1 you simply do (cos(x)+1)*0,5
	/*finalColor=fragmentColor + vec4(1.0*(cos(time)+1)*0.5,
							1.0*(cos(time+2.0)+1)*0.5,
							1.0*(sin(time+1.0)+1)*0.5,
							0.0);*/
							
	//Color is changed based on time and position
	//Information in vectors can be accessed by numbers [0], [1] ...or by r,g,b,a or x,y,z
	finalColor=vec4(fragmentColor.r*(cos(fragmentPosition.x + time) +1.0)*0.5,
				fragmentColor.g*(cos(fragmentPosition.y+ time) +1.0)*0.5,
				fragmentColor.b*(cos(fragmentPosition.x*0.5 + time) +1.0)*0.5,
				fragmentColor.a);
	
	/*finalColor=vec4(fragmentColor.r*(cos(fragmentPosition.x*4.0 + time) +1.0)*0.5,
				fragmentColor.g*(cos(fragmentPosition.y*8.0 + time) +1.0)*0.5,
				fragmentColor.b*(cos(fragmentPosition.x*2.5 + time) +1.0)*0.5,
				fragmentColor.a)*textureColor;*/		
	//Other version that generates some kind of hypnotic effect
	
	/*finalColor = vec4(fragmentColor.r * (0.5 * cos(time * fragmentPosition.x + time * fragmentPosition.y) + 0.5), 
		fragmentColor.g * (0.5 * cos(time * fragmentPosition.x + time * fragmentPosition.y) + 0.5), 
		fragmentColor.b * (0.5 * cos(time * fragmentPosition.x + time * fragmentPosition.y) + 0.5), 
		1.0);*/
	
}