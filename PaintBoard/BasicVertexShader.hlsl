#include "Header.hlsli"
PSInput main(VSInput input)
{
    PSInput output;
    float4 pos = float4(input.pos, 1.0f);
    output.posProj = pos;
    output.color = input.color;
    return output;
}