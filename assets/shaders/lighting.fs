#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

// Output fragment color
out vec4 finalColor;

// Uniforms
uniform sampler2D texture0;
uniform vec3 lightDir;

void main()
{
    vec3 normal = normalize(fragNormal);
    float diffuse = max(dot(normal, -lightDir), 0.0);

    vec4 texelColor = texture(texture0, fragTexCoord);
    finalColor = vec4(texelColor.rgb * diffuse, texelColor.a);
}