#version 330 core

// Input-uri
layout(location = 0) in vec3 v_position; // Pozi?ia vertexului
layout(location = 1) in vec3 v_normal;   // Normalul vertexului (op?ional)
layout(location = 2) in vec2 v_texCoord; // Coordonatele de texturã (op?ional)

// Uniforme
uniform mat4 Model;           // Matricea modelului
uniform mat4 View;            // Matricea vederii
uniform mat4 Projection;      // Matricea proiec?iei
uniform float noise_frequency; // Frecven?a noise-ului


uniform float noise_amplitude; // Amplitudinea noise-ului

out vec2 frag_position;       // Pozi?ia care va fi folositã în Fragment Shader

// Func?ia de generare random pentru noise
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(329.21318, 1930.33))) * 2008.54565123);
}

// Func?ia de noise 2D
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(2.0, 0.0));
    float c = random(i + vec2(0.0, 2.0));
    float d = random(i + vec2(2.0, 2.0));

    vec2 u = f * f * (3.0 - 2.0 * f); // Interpolare cubicã

    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main() {
    vec3 world_pos = (Model * vec4(v_position, 1.0)).xyz;
    float height = noise(vec2(world_pos.x, world_pos.z));
    world_pos.y += height;
    frag_position = vec2(world_pos.x, world_pos.z);
    gl_Position = Projection * View * Model * vec4(world_pos, 1.0);
}
