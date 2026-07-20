#shader vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_UV;
layout (location = 3) in vec3 a_Normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    v_FragPos = vec3(model * vec4(a_Position, 1.0));
    v_Normal = mat3(transpose(inverse(model))) * a_Normal;
    
    gl_Position = projection * view * model * vec4(a_Position, 1.0);
    
    v_Color = a_Color;
    v_TexCoord = a_UV;
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

struct Material {
    vec4 ALBEDO;
    float Specular;
    int Shininess;
    sampler2D TEXTURE;
};

uniform Material material;

uniform vec3 ViewPos;

void main()
{   
    vec4 texColor = texture(material.TEXTURE, v_TexCoord);

    vec3 lightPos = vec3(5.0, 0.5, 5.0);

    vec3 LightColor = vec3(1.0);
    float AmbientStrenght = 0.1;
    vec3 ambient = AmbientStrenght * LightColor;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;

    vec3 viewDir = normalize(ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), float(material.Shininess));

    vec3 specular = material.Specular * spec * LightColor; 

    vec3 result = (ambient + diffuse + specular) * material.ALBEDO.xyz;
    FragColor = vec4(result, 1.0) * texColor;
}