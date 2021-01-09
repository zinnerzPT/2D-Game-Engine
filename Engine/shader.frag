#version 330 core

in vec2 ex_TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec2 textOffset;

void main(void) {

	FragColor = texture(texture1, ex_TexCoord + textOffset);
	if(FragColor.r == 1.0 && FragColor.g == 0.0 && FragColor.b == 1.0){
		discard;
	}
}