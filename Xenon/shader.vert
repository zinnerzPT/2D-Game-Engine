#version 330
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1

in vec3 in_Position;
in vec2 in_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 ex_TexCoord;

out vec3 viewPosition;

void main(void) {

	gl_Position = projection * view * model * vec4(in_Position, 1.0);

	// pass to fragment shader
	ex_TexCoord = in_TexCoord;
}
