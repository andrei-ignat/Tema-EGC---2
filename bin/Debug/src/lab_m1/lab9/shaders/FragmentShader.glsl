#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int bothTextures;
uniform float elapsedTime;  // Timpul primit din aplica?ie
uniform int isEarth;        // Variabilã pentru identificarea globului pãmântesc

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    vec2 modifiedTexcoord = texcoord;

    // Dacã obiectul este globul pãmântesc, modificãm coordonata OX în func?ie de timp
    if (true) {
        modifiedTexcoord.x += elapsedTime; // Textura ciclicã pe coordonata OX
    }

    vec4 color1 = texture(texture_1, modifiedTexcoord);
    vec4 color2 = texture(texture_2, modifiedTexcoord);

    vec4 color = color1;
    if (bothTextures == 1) {
        color = mix(color1, color2, 0.5f);
    }
    
    // Dacã alpha este prea mic, eliminãm fragmentul
    if (color.a < 0.5f) discard;
    
    out_color = color;
}
