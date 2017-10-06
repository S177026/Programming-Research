//fragment shader
#version 430 core

in vec3 Colour;

out  vec4 frag_colour;



void main() {
	
    frag_colour = vec4( Colour, 1.0 );
}
