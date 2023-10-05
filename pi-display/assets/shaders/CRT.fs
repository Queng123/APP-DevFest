// #version 330 core
// in vec2 fragTexCoord;
// out vec4 fragColor;
// uniform vec2 resolution;
// uniform sampler2D screenTexture;
// void main()
// {
//     vec2 uv = fragTexCoord;
//     vec3 col = texture(screenTexture, uv).rgb;

//     // CRT effect
//     uv = uv * 2.0 - 1.0;
//     float aspectRatio = resolution.x / resolution.y;
//     uv.x *= aspectRatio;
//     float scanline = sin(uv.y * 300.0 + 2.0) * 0.04;
//     uv.x += scanline;

//     // Simulate RGB sub-pixel arrangement
//     vec3 rgb = texture(screenTexture, uv).rgb;

//     // Add some distortion
//     col += vec3(sin(uv.y * 300.0), cos(uv.y * 300.0), sin(uv.y * 300.0)) * 0.2;

//     // Gamma correction
//     col = pow(col, vec3(1.5));


//     // Output to screen

//     fragColor = vec4(col, 1.0);
// }
#version 330 core

uniform sampler2D screenTexture;
out vec4 fragColor;
in vec2 fragTexCoord;

uniform vec2      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)

vec2 curve(vec2 uv)
{
	uv = (uv - 0.5) * 2.0;
	uv *= 1.1;	
	uv.x *= 1.0 + pow((abs(uv.y) / 5.0), 2.0);
	uv.y *= 1.0 + pow((abs(uv.x) / 4.0), 2.0);
	uv  = (uv / 2.0) + 0.5;
	uv =  uv *0.92 + 0.04;
	return uv;
}
void main( )

{


    vec2 uv = fragTexCoord;
    uv = curve( uv );
    vec3 col;
	float x =  sin(0.3*iTime+uv.y*21.0)*sin(0.7*iTime+uv.y*29.0)*sin(0.3+0.33*iTime+uv.y*31.0)*0.0017;

    col.r = texture(screenTexture,vec2(x+uv.x+0.001,uv.y+0.001)).x+0.05;
    col.g = texture(screenTexture,vec2(x+uv.x+0.000,uv.y-0.002)).y+0.05;
    col.b = texture(screenTexture,vec2(x+uv.x-0.002,uv.y+0.000)).z+0.05;
    col.r += 0.08*texture(screenTexture,0.75*vec2(x+0.025, -0.027)+vec2(uv.x+0.001,uv.y+0.001)).x;
    col.g += 0.05*texture(screenTexture,0.75*vec2(x+-0.022, -0.02)+vec2(uv.x+0.000,uv.y-0.002)).y;
    col.b += 0.08*texture(screenTexture,0.75*vec2(x+-0.02, -0.018)+vec2(uv.x-0.002,uv.y+0.000)).z;

    col = clamp(col*0.6+0.4*col*col*1.0,0.0,1.0);

    float vig = (0.0 + 1.0*16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y));
	col *= vec3(pow(vig,0.3));

    col *= vec3(0.95,1.05,0.95);
	col *= 2.8;

	float scans = clamp( 0.35+0.35*sin(3.5*iTime+uv.y*iResolution.y*1.5), 0.0, 1.0);
	
	float s = pow(scans,1.7);
	col = col*vec3( 0.4+0.7*s) ;

    col *= 1.0+0.01*sin(110.0*iTime);
	if (uv.x < 0.0 || uv.x > 1.0)
		col *= 0.0;
	if (uv.y < 0.0 || uv.y > 1.0)
		col *= 0.0;
	
	col*=1.0-0.65*vec3(clamp((mod(fragTexCoord.x, 2.0)-1.0)*2.0,0.0,1.0));
	
    float comp = smoothstep( 0.1, 0.9, sin(iTime) );
 
	// Remove the next line to stop cross-fade between original and postprocess

    fragColor = vec4(col,1.0);
}
