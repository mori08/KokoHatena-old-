Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}

cbuffer Region : register(b1)
{
    float4 g_rect;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR0;
    float2 uv       : TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
    float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

    float2 pos = float2(input.position.x, input.position.y);

    if (
        pos.x > g_rect.x && pos.x < g_rect.x + g_rect.z &&
        pos.y > g_rect.y && pos.y < g_rect.y + g_rect.w
        )
    {
        texColor = float4(1 - texColor.r, 1 - texColor.g, 1 - texColor.b, texColor.a);
    }

    return (texColor * input.color) + g_colorAdd;
}