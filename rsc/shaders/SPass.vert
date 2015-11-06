#version 410

layout(location = 0) in vec4 Position;

uniform mat4 LightMatrix;
uniform mat4 Model;

void main(){
	gl_Position = LightMatrix * Position * Model;
}