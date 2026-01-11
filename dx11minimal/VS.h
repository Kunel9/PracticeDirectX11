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

float4 getNewPoint(float4 currentPos)
{
    float newValue = 3.1415926535 * (currentPos.x / arrayTest[0]);
    currentPos.x = cos(newValue) * 4;
    currentPos.z = sin(newValue) * 4;
    return currentPos;
}

VS_OUTPUT VS(uint vID : SV_VertexID)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    int quadIndex = vID / 6; 
    int pointIndex = vID % 6;
    int rowIndex = quadIndex / arrayTest[0];
    int colIndex = quadIndex % arrayTest[0];
    
    float2 quad[6] = {
        -1, -1, 
        1, -1, 
        -1, 1, 
        1, -1, 
        1, 1,
        -1, 1};
    
    float2 p = quad[pointIndex];
    p.x += 2 * colIndex;
    p.y += 2 * rowIndex;
    float4 pos = float4(p, 0, 5);
    pos.x -= arrayTest[0];
    pos.y -= arrayTest[0];
    
    //
    pos = getNewPoint(pos);
    //

    output.pos = mul(pos, mul(view[0], proj[0]));
    output.uv = float2(1, -1) * quad[pointIndex] / 2. + .5;
    
    return output;
}
