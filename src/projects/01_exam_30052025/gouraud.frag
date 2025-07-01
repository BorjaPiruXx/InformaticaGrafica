#version 330 core

uniform bool useTextures;
uniform sampler2D material_diffuse;

in vec2 textureCoord;
in vec3 compLight;
out vec4 fragmentColor;

void main()
{
    vec4 textureColor = useTextures ? texture(material_diffuse, textureCoord) : vec4(1.0);
    fragmentColor = vec4(compLight, 1.0) * textureColor;
}
