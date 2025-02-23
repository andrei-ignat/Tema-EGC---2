#version 330 core

// Input de la Vertex Shader
in vec2 frag_position;  // Pozi?ia (x, z) a fragmentului

out vec4 final_color;   // Culoarea finalã a fragmentului

uniform float u_time;
uniform vec3 color_low;
uniform vec3 color_high;
uniform float drone_y;
uniform float color11;
uniform float color21;
uniform float color31;


// Func?ia de generare random pentru noise
float random(vec2 st) {
     return fract(sin(dot(st.xy, vec2(329.21318, 1930.33))) * 2008.54565123);
}

// Func?ia de noise 2D
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f); // Interpolare cubicã

    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main() {
    // Aplicãm noise pe coordonatele (x, z) pentru a ob?ine o valoare de culoare
    float n = noise(frag_position * 0.1); // Scãdem valoarea pentru a ob?ine un zgomot mai blând



    // Definim culori pentru a face interpolarea
    vec3 colorA = vec3(0.1f, 0.3f, 0.1f);
    vec3 colorB = vec3(0.0f, 0.5f, 0.0f);

    float altitudeFactor = clamp(3322 / 100.0, 0.0, 1.0);


    vec3 terrain_color = mix(colorA, colorB, altitudeFactor); // Normalizãm noise-ul

    // Setãm culoarea finalã
    final_color = vec4(colorA, 1.0);
}
