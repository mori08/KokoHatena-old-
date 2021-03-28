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
    float g_blur;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR0;
    float2 uv       : TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
    if (g_r < 0.01)
    {
        return float4(0, 0, 0, 0);
    }

    float2 pos = float2(input.position.x,input.position.y);
    float dist = length(pos - g_center);
    float4 rtn = g_color;

    if (dist < (1-g_blur/2) * g_r)
    {
        return rtn;
    }
    if (dist > (1+g_blur/2) * g_r)
    {
        rtn.w = 0;
        return rtn;
    }

    float a = (dist - (1+g_blur/2) * g_r) / (g_blur * g_r);
    rtn.w *= a * a;
    return rtn;
}