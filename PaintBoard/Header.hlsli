struct VSInput
{
    float3 pos : POSITION;
    float3 color : COLOR;
};

struct PSInput
{
    float4 posProj : SV_Position;
    float3 color : COLOR;
};