#version 330 core

layout (location = 0) in vec2 v_frame;
layout (location = 1) in vec2 v_ipos;
layout (location = 2) in vec2 v_iscale;
layout (location = 3) in vec4 v_iuv;

out vec2 f_uv;

void main()
{
    gl_Position = vec4((v_frame + vec2(-.5, -.5)) * v_iscale + v_ipos, 0.0, 1.0);
    f_uv = v_iuv.xy + v_frame * v_iuv.zw;
}

#--
#version 330 core

uniform sampler2D texturepack;

in vec2 f_uv;

out vec4 p_color;

void main()
{
    p_color = mix(texture(texturepack, f_uv), vec4(f_uv, 0, 1), .1);
}