#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int bothTextures;
uniform float elapsedTime;  // Timpul primit din aplica?ie
uniform int isEarth;        // Variabil� pentru identificarea globului p�m�ntesc

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    vec2 modifiedTexcoord = texcoord;

    // Dac� obiectul este globul p�m�ntesc, modific�m coordonata OX �n func?ie de timp
    if (true) {
        modifiedTexcoord.x += elapsedTime; // Textura ciclic� pe coordonata OX
    }

    vec4 color1 = texture(texture_1, modifiedTexcoord);
    vec4 color2 = texture(texture_2, modifiedTexcoord);

    vec4 color = color1;
    if (bothTextures == 1) {
        color = mix(color1, color2, 0.5f);
    }
    
    // Dac� alpha este prea mic, elimin�m fragmentul
    if (color.a < 0.5f) discard;
    
    out_color = color;
}
