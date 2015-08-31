
Texture2D texDiffuse;
SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

cbuffer cbConstant
{
	float3 vLightDir = float3(-0.577, 0.577, -0.577);
};

cbuffer cbChangesEveryFrame
{
	matrix Model;
	matrix View;
	matrix Proj;

	float  Time;
};

cbuffer cbUserChanges
{
	float Waviness;
};

struct VS_INPUT
{
	float3 Pos  : POSITION;
	float3 Norm : NORMAL;
	float2 Tex  : TEXCOORD0;
};

struct PS_INPUT
{
	float4 Pos  : SV_POSITION;
	float3 Norm : TEXCOORD0;
	float2 Tex  : TEXCOORD1;
};

cbuffer cbConstant
{
    float3 vLightDir = float3(-0.577,0.577,-0.577);
};
//--------------------------------------------------------------------------------------
// DepthStates
//--------------------------------------------------------------------------------------
DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS_EQUAL;
};

BlendState NoBlending
{
	AlphaToCoverageEnable = FALSE;
	BlendEnable[0] = FALSE;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = ( PS_INPUT )0;
	 
	output.Pos = mul(float4(input.Pos, 1.0f), Model);

	output.Pos.x += sin(output.Pos.y * 0.1f + Time) * Waviness;

	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Proj);
	output.Norm = mul(input.Norm, Model);

	output.Tex = input.Tex;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input): SV_Target
{
	// Calculate lighting assuming light color is <1,1,1,1>
	float fLighting = saturate(dot(input.Norm, vLightDir));
	float4 outputColor = texDiffuse.Sample(samLinear, input.Tex) * fLighting;
	outputColor.a = 1;

	return outputColor;
}


//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Render
{
	pass P0
	{
	  SetVertexShader(CompileShader(vs_4_0, VS()));
	  SetGeometryShader(NULL);
	  SetPixelShader(CompileShader(ps_4_0, PS()));
	  
	  SetDepthStencilState(EnableDepth, 0);
	  SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
    }

}

