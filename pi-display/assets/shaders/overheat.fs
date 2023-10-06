#version 120

varying vec2 fragTexCoord;
uniform int overheat;
uniform sampler2D screenTexture;

void main()
{
    vec2 uv = fragTexCoord;
    vec3 col = texture2D(screenTexture, uv).rgb;
    vec3 overheatColor = vec3(1.0, 0.0, 0.0);
    float overheatValue = overheat;
    if (overheatValue > 100) {
        overheatValue = 100;
    }
    float overheatAmount = overheatValue / 100.0;
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(uv, center) - 0.3;
    float overheatDist = 0.5;
    col = mix(col, overheatColor, dist * overheatAmount);
    gl_FragColor = vec4(col, 1.0);
}
