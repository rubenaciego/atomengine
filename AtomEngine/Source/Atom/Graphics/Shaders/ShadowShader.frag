R"(#version 400 core

layout(location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 texCoord;
	float texID;
	vec4 color;
} fs_in;

uniform sampler2D u_Textures[16];
uniform vec2 resolution;
uniform int shadow = 0;

const float THRESHOLD = 0.75;
const float PI = 3.14f;

float sample_data(vec2 coord, float r)
{
	return step(r, texture(u_Textures[int(fs_in.texID - 0.5)], coord).r);
}

void main()
{
	if (shadow == 1)
	{
		vec2 norm = fs_in.texCoord.st * 2.0 - 1.0;
		float theta = atan(norm.y, -norm.x);
		float r = length(norm);
		float coord = (theta) / (2.0*PI);
	
		//the tex coord to sample our 1D lookup texture	
		//always 0.0 on y axis
		vec2 tc = vec2(coord, 0.0);
	
		//the center tex coord, which gives us hard shadows
		float center = sample_data(tc, r);        
	
		//we multiply the blur amount by our distance from center
		//this leads to more blurriness as the shadow "fades away"
		float blur = (1./resolution.x)  * smoothstep(0., 1., r); 
	
		//now we use a simple gaussian blur
		float sum = 0.0;
	
		sum += sample_data(vec2(tc.x - 4.0*blur, tc.y), r) * 0.05;
		sum += sample_data(vec2(tc.x - 3.0*blur, tc.y), r) * 0.09;
		sum += sample_data(vec2(tc.x - 2.0*blur, tc.y), r) * 0.12;
		sum += sample_data(vec2(tc.x - 1.0*blur, tc.y), r) * 0.15;
	
		sum += center * 0.16;
	
		sum += sample_data(vec2(tc.x + 1.0*blur, tc.y), r) * 0.15;
		sum += sample_data(vec2(tc.x + 2.0*blur, tc.y), r) * 0.12;
		sum += sample_data(vec2(tc.x + 3.0*blur, tc.y), r) * 0.09;
		sum += sample_data(vec2(tc.x + 4.0*blur, tc.y), r) * 0.05;
	
		//sum of 1.0 -> in light, 0.0 -> in shadow
 	
 		//multiply the summed amount by our distance, which gives us a radial falloff
 		//then multiply by vertex (light) color  
 		color = fs_in.color * vec4(vec3(1.0), sum * smoothstep(1.0, 0.0, r));
	}
	else
	{
		color = fs_in.color;

		if (fs_in.texID > 0.0)
			color *= texture(u_Textures[int(fs_in.texID - 0.5)], fs_in.texCoord);

		float distance = 1.0f;

		for (float y = 0.0f; y < resolution.y; y++)
		{
			vec2 norm = vec2(fs_in.texCoord.s, y/resolution.y) * 2.0 - 1.0;
			float theta = PI*1.5 + norm.x * PI; 
			float r = (1.0 + norm.y) * 0.5;
		
			//coord which we will sample from occlude map
			vec2 coord = vec2(-r * sin(theta), -r * cos(theta))/2.0 + 0.5;
		
			//sample the occlusion map
			vec4 data = texture(u_Textures[int(fs_in.texID - 0.5)], coord);
		
			//the current distance is how far from the top we've come
			float dst = y/resolution.y;
		
			//if we've hit an opaque fragment (occluder), then get new distance
			//if the new distance is below the current, then we'll use that for our ray
			float caster = data.a;
			if (caster > THRESHOLD) {
				distance = min(distance, dst);
				//NOTE: we could probably use "break" or "return" here
				break;
  			}
		}

		color = fs_in.color * vec4(vec3(distance), 1.0f);
	}
}
)"
