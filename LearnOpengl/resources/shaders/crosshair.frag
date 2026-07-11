#version 330 core

out vec4 CrossColor;

uniform bool hit;

void main() {
    if(hit){
        CrossColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
        CrossColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

}