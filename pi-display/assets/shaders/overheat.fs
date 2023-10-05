#version 330 core
in vec2 fragTexCoord;
uniform int overheat;
out vec4 fragColor;
uniform sampler2D screenTexture;
void main()
{
    vec2 uv = fragTexCoord;
    vec3 col = texture(screenTexture, uv).rgb;

    vec3 overheatColor = vec3(1.0, 0.0, 0.0);
    float overheatAmount = float(overheat) / 100.0;

    // get center
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(uv, center);
    float overheatDist = 0.5;

    col = mix(col, overheatColor, dist * overheatAmount);

    fragColor = vec4(col, 1.0);
}
