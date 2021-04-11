Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}

cbuffer Light : register(b1)
{
    float4 g_color;
    float2 g_center;
    float g_r;
    float g_direction;
    float g_angle;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR0;
    float2 uv       : TEXCOORD0;
};


float4 PS(PSInput input) : SV_TARGET
{
    if (g_r < 1.0)
    {
        return float4(0, 0, 0, 0);
    }

    float2 pos = float2(input.position.x, input.position.y);
    float2 sub = pos - g_center;
    float2 v1 = float2(cos(g_direction), sin(g_direction));
    float2 v2 = float2(sub.x / length(sub), sub.y / length(sub));
    float angle = acos(clamp(dot(v1, v2), -1.0, 1.0));

    float4 rtn = g_color;

    float angleA = clamp((g_angle - angle)*length(sub)*0.5 + 1.0, 0.0, 1.0);
    float distA = clamp((g_r - length(sub))*0.5 + 1.0, 0.0, 1.0);
    rtn *= angleA * distA;
    return rtn;
}