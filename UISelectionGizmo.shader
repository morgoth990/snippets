Shader "UI/SelectionGizmo"
{
    Properties
    {
        [PerRendererData] _MainTex("Sprite Texture", 2D) = "white" {}
        _Color("Tint", Color) = (1,1,1,1)
        _DashColor1("DashColor1", Color) = (1,1,1,1)
        _DashColor2("DashColor2", Color) = (0,0,0,1)
        _DashHeight("Dash Height", Float) = 2
        _DashWidth("Dash Width", Float) = 5
        _DashSpeed("Dash Speed", Float) = 2 

        [HideInInspector]
        _StencilComp("Stencil Comparison", Float) = 8
        [HideInInspector]
        _Stencil("Stencil ID", Float) = 0
        [HideInInspector]
        _StencilOp("Stencil Operation", Float) = 0
        [HideInInspector]
        _StencilWriteMask("Stencil Write Mask", Float) = 255
        [HideInInspector]
        _StencilReadMask("Stencil Read Mask", Float) = 255

        [HideInInspector]
        _ColorMask("Color Mask", Float) = 15

        [Toggle(UNITY_UI_ALPHACLIP)] _UseUIAlphaClip("Use Alpha Clip", Float) = 0
    }

        SubShader
        {
            Tags
            {
                "Queue" = "Transparent"
                "IgnoreProjector" = "True"
                "RenderType" = "Transparent"
                "PreviewType" = "Plane"
                "CanUseSpriteAtlas" = "True"
            }

            Stencil
            {
                Ref[_Stencil]
                Comp[_StencilComp]
                Pass[_StencilOp]
                ReadMask[_StencilReadMask]
                WriteMask[_StencilWriteMask]
            }

            Cull Off
            Lighting Off
            ZWrite Off
            ZTest[unity_GUIZTestMode]
            Blend SrcAlpha OneMinusSrcAlpha
            ColorMask[_ColorMask]

            Pass
            {
                Name "Default"
            CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #pragma target 2.0

                #include "UnityCG.cginc"
                #include "UnityUI.cginc"

                #pragma multi_compile_local _ UNITY_UI_CLIP_RECT
                #pragma multi_compile_local _ UNITY_UI_ALPHACLIP

                struct appdata_t
                {
                    float4 vertex   : POSITION;
                    float4 color    : COLOR;
                    float2 texcoord : TEXCOORD0;
                    UNITY_VERTEX_INPUT_INSTANCE_ID
                };

                struct v2f
                {
                    float4 vertex   : SV_POSITION;
                    fixed4 color : COLOR;
                    float2 texcoord  : TEXCOORD0;
                    float4 worldPosition : TEXCOORD1;
                    UNITY_VERTEX_OUTPUT_STEREO
                };

                sampler2D _MainTex;
                fixed4 _Color;
                fixed4 _TextureSampleAdd;
                float4 _ClipRect;
                float4 _MainTex_ST;

                float _DashHeight;
                float _DashWidth;
                float _DashSpeed;
                fixed4 _DashColor1;
                fixed4 _DashColor2;

                v2f vert(appdata_t v)
                {
                    v2f OUT;
                    UNITY_SETUP_INSTANCE_ID(v);
                    UNITY_INITIALIZE_VERTEX_OUTPUT_STEREO(OUT);
                    OUT.worldPosition = v.vertex;
                    OUT.vertex = UnityObjectToClipPos(OUT.worldPosition);

                    OUT.texcoord = TRANSFORM_TEX(v.texcoord, _MainTex);

                    OUT.color = v.color * _Color;
                    return OUT;
                }

                fixed4 frag(v2f IN) : SV_Target
                {
                    float4 color = tex2D(_MainTex, IN.texcoord);

                    float dx = ddx(IN.texcoord).x;
                    float dy = ddy(IN.texcoord).y;

                    float2 pixelCoord = float2(IN.texcoord.x / dx, IN.texcoord.y / dy);

                    float dashOffset = _Time.y * _DashSpeed;

                    float xC = 0;
                    float yC = 0;
                    float diagC = 0;
                    if (tex2D(_MainTex, IN.texcoord + float2(dx, 0) * _DashHeight).a == 0)
                        xC += 1;
                    if (tex2D(_MainTex, IN.texcoord + float2(-dx, 0) * _DashHeight).a == 0)
                        xC += 1;
                    if (tex2D(_MainTex, IN.texcoord + float2(0, dy) * _DashHeight).a == 0)
                        yC += 1;
                    if (tex2D(_MainTex, IN.texcoord + float2(0, -dy) * _DashHeight).a == 0)
                        yC += 1;
                    if (xC == 0 && yC == 0 && tex2D(_MainTex, IN.texcoord + float2(dx, dy) * _DashHeight).a == 0)
                        diagC += 1;
                    if (xC == 0 && yC == 0 && tex2D(_MainTex, IN.texcoord + float2(-dx, -dy) * _DashHeight).a == 0)
                        diagC += 1;
                    if (xC == 0 && yC == 0 && tex2D(_MainTex, IN.texcoord + float2(-dx, dy) * _DashHeight).a == 0)
                        diagC += 1;
                    if (xC == 0 && yC == 0 && tex2D(_MainTex, IN.texcoord + float2(dx, -dy) * _DashHeight).a == 0)
                        diagC += 1;

                    if (xC == 0 && yC == 0 && diagC == 0)
                        discard;

				#ifdef UNITY_UI_CLIP_RECT
                    color.a *= UnityGet2DClipping(IN.worldPosition.xy, _ClipRect);
				#endif

				#ifdef UNITY_UI_ALPHACLIP
                    clip(color.a - 0.001);
				#endif

                    color.a = ceil(color.a);
                    color.rgb = float4(_DashColor1.rgb, color.a * _DashColor2.a);

                    if ((diagC > 0 || xC == 0) && fmod(floor(pixelCoord.x/ _DashWidth - dashOffset), 2) == 0)
						color.rgb = _DashColor2.rgb;
                    if ((diagC > 0 || yC == 0) && fmod(floor(pixelCoord.y/ _DashWidth + dashOffset), 2) == 0)
						color.rgb = _DashColor2.rgb;
                 

                    return color * IN.color;
                }
            ENDCG
            }
        }
}
