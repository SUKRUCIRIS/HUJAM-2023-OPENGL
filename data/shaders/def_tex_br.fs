#version 400 core
out vec4 FragColor;
in vec2 texCoord;
flat in int texture_id;

uniform sampler2D textures[32];

void main(){
	FragColor = texture(textures[texture_id], texCoord);
	if(FragColor.a<1.0){
		discard;
	}
}