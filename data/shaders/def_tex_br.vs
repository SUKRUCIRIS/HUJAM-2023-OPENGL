#version 400 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;
layout(location = 3) in float text_id;

out vec2 texCoord;
flat out int texture_id;
uniform mat4 camera;

void main(){
    gl_Position = camera * vec4(pos, 1.0f);
	texCoord = tex;
	texture_id = int(text_id);
}