#shader vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_UV;
layout (location = 3) in vec3 a_Normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(a_Position, 1.0);
    
    v_Color = a_Color;
    v_TexCoord = a_UV;
    v_Normal = a_Normal;
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    
    FragColor = v_Color;
}