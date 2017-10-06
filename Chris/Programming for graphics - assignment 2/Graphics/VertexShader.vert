//vertex shader
#version 400 

in vec3 vp;

in vec3 vertexColor;



out vec3 Colour;

void main()
 {

	
	Colour = vec3(vp.x +0.3,vp.y + 0.3,vp.z +0.3);
	//cube is rotated at a 45 degree angle by its x and z coordinates
 	gl_Position = vec4(vp.x,vp.y -0.5,vp.z, 1.0); 
};

