cbuffer global : register(b5)
{
    float4 gConst[32];
};

cbuffer frame : register(b4)
{
    float4 time;
    float4 aspect;
};

cbuffer camera : register(b3)
{
    float4x4 world[2];
    float4x4 view[2];
    float4x4 proj[2];
};

cbuffer drawMat : register(b2)
{
    float4x4 model;
    float hilight;
};

cbuffer drawerV : register(b0)
{
    float arrayTest[32];
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 vpos : POSITION0;
    float4 wpos : POSITION1;
    float4 vnorm : NORMAL1;
    float2 uv : TEXCOORD0;
};

float3 rotY(float3 pos, float a)
{
    float3x3 m =
    {
        cos(a), 0, sin(a),
        0, 1, 0,
        -sin(a), 0, cos(a)
    };
    pos = mul(pos, m);
    return pos;
}

VS_OUTPUT VS(uint vID : SV_VertexID)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    //float2 quad[6] = { -1, -1, 1, -1, -1, 1, 1, -1, 1, 1, -1, 1 };

    float2 quad[512];

    int current = 0;
    int step_x = 2;
    quad[0] = float2(-1, -1);

    for (int i = 0; i < vID; ++i) {

        current = i * 6;
        
        quad[current] = float2(-1 + step_x * i, -1);
        quad[current+1] = float2(1 + step_x * i, -1);
        quad[current+2] = float2(-1 + step_x * i, 1);
        quad[current+3] = float2(1 + step_x * i, -1);
        quad[current+4] = float2(1 + step_x * i, 1);
        quad[current+5] = float2(-1 + step_x * i, 1);
   
    }

    float2 p = quad[vID];
    float4 pos = float4(quad[vID], 0, 5);
    pos.x -= arrayTest[0];
    output.pos = mul(pos, mul(view[0], proj[0]));
    output.uv = float2(1, -1) * p / 2. + .5;
    return output;
}
