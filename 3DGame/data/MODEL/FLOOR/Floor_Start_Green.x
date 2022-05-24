xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 320;
 -612.87711;-1.96752;-802.80197;,
 613.63380;-1.96752;-802.80197;,
 613.63380;-66.63629;-802.80197;,
 -612.87711;-66.63629;-802.80197;,
 613.63380;-1.96752;-802.80197;,
 613.63380;-1.96752;802.80197;,
 613.63380;-66.63629;802.80197;,
 613.63380;-66.63629;-802.80197;,
 613.63380;-1.96752;802.80197;,
 -612.87711;-1.96752;802.80197;,
 -612.87711;-66.63629;802.80197;,
 613.63380;-66.63629;802.80197;,
 -612.87711;-1.96752;802.80197;,
 -612.87711;-1.96752;-802.80197;,
 -612.87711;-66.63629;-802.80197;,
 -612.87711;-66.63629;802.80197;,
 613.63380;-1.96752;-802.80197;,
 -612.87711;-1.96752;-802.80197;,
 -612.87711;-66.63629;-802.80197;,
 613.63380;-66.63629;-802.80197;,
 298.15794;3.49297;-716.19532;,
 613.63380;3.49297;-443.27774;,
 613.63380;3.49297;-802.80197;,
 298.15794;3.49297;-802.80197;,
 298.15794;-69.41648;-716.19532;,
 298.15794;-69.41648;-802.80197;,
 613.63380;-69.41648;-802.80197;,
 613.63380;-69.41648;-443.27774;,
 -297.40125;3.49297;-716.19532;,
 -297.40125;3.49297;-802.80197;,
 -612.87711;3.49297;-802.80197;,
 -612.87711;3.49297;-443.27774;,
 -297.40125;-69.41648;-716.19532;,
 -612.87711;-69.41648;-443.27774;,
 -612.87711;-69.41648;-802.80197;,
 -297.40125;-69.41648;-802.80197;,
 298.15794;3.49297;716.19532;,
 298.15794;3.49297;802.80197;,
 613.63380;3.49297;802.80197;,
 613.63380;3.49297;443.27774;,
 298.15794;-69.41648;716.19532;,
 613.63380;-69.41648;443.27774;,
 613.63380;-69.41648;802.80197;,
 298.15794;-69.41648;802.80197;,
 -297.40125;3.49297;716.19532;,
 -612.87711;3.49297;443.27774;,
 -612.87711;3.49297;802.80197;,
 -297.40125;3.49297;802.80197;,
 -297.40125;-69.41648;716.19532;,
 -297.40125;-69.41648;802.80197;,
 -612.87711;-69.41648;802.80197;,
 -612.87711;-69.41648;443.27774;,
 615.23687;3.62772;-802.80197;,
 615.23687;3.62772;-444.04796;,
 615.23687;-72.23154;-444.04796;,
 615.23687;-72.23154;-802.80197;,
 -614.48014;3.62772;-802.80197;,
 -614.48014;-72.23154;-802.80197;,
 -614.48014;-72.23154;-444.04796;,
 -614.48014;3.62772;-444.04796;,
 615.23687;3.62772;802.80197;,
 615.23687;-72.23154;802.80197;,
 615.23687;-72.23154;444.04796;,
 615.23687;3.62772;444.04796;,
 -614.48014;3.62772;802.80197;,
 -614.48014;3.62772;444.04796;,
 -614.48014;-72.23154;444.04796;,
 -614.48014;-72.23154;802.80197;,
 -612.87711;3.25125;-803.90568;,
 -295.59998;3.25125;-803.90568;,
 -295.59998;-71.85505;-803.90568;,
 -612.87711;-71.85505;-803.90568;,
 -612.87711;3.25125;803.90568;,
 -612.87711;-71.85505;803.90568;,
 -295.59998;-71.85505;803.90568;,
 -295.59998;3.25125;803.90568;,
 613.63380;3.25125;-803.90568;,
 613.63380;-71.85505;-803.90568;,
 296.35667;-71.85505;-803.90568;,
 296.35667;3.25125;-803.90568;,
 613.63380;3.25125;803.90568;,
 296.35667;3.25125;803.90568;,
 296.35667;-71.85505;803.90568;,
 613.63380;-71.85505;803.90568;,
 287.11299;-1.11783;668.71129;,
 612.65802;-1.11783;390.67081;,
 612.88116;-1.11783;352.73282;,
 287.33638;-1.11783;630.77374;,
 287.11299;-67.48598;668.71129;,
 287.33638;-67.48598;630.77374;,
 612.88116;-67.48598;352.73282;,
 612.65802;-67.48598;390.67081;,
 287.11299;-1.11783;-668.71129;,
 287.33638;-1.11783;-630.77374;,
 612.88116;-1.11783;-352.73282;,
 612.65802;-1.11783;-390.67081;,
 287.11299;-67.48598;-668.71129;,
 612.65802;-67.48598;-390.67081;,
 612.88116;-67.48598;-352.73282;,
 287.33638;-67.48598;-630.77374;,
 -286.35630;-1.11783;668.71129;,
 -286.57969;-1.11783;630.77374;,
 -612.12447;-1.11783;352.73282;,
 -611.90133;-1.11783;390.67081;,
 -286.35630;-67.48598;668.71129;,
 -611.90133;-67.48598;390.67081;,
 -612.12447;-67.48598;352.73282;,
 -286.57969;-67.48598;630.77374;,
 -286.35630;-1.11783;-668.71129;,
 -611.90133;-1.11783;-390.67081;,
 -612.12447;-1.11783;-352.73282;,
 -286.57969;-1.11783;-630.77374;,
 -286.35630;-67.48598;-668.71129;,
 -286.57969;-67.48598;-630.77374;,
 -612.12447;-67.48598;-352.73282;,
 -611.90133;-67.48598;-390.67081;,
 614.38355;0.37094;-390.59341;,
 614.38355;0.37094;-353.37547;,
 614.38355;-68.97473;-353.37547;,
 614.38355;-68.97473;-390.59341;,
 -613.62691;0.37094;-390.59341;,
 -613.62691;-68.97473;-390.59341;,
 -613.62691;-68.97473;-353.37547;,
 -613.62691;0.37094;-353.37547;,
 614.38355;0.37094;390.59341;,
 614.38355;-68.97473;390.59341;,
 614.38355;-68.97473;353.37547;,
 614.38355;0.37094;353.37547;,
 -613.62691;0.37094;390.59341;,
 -613.62691;0.37094;353.37547;,
 -613.62691;-68.97473;353.37547;,
 -613.62691;-68.97473;390.59341;,
 168.69026;0.33325;-682.86124;,
 168.69025;0.33325;-802.77042;,
 132.06642;0.33325;-802.77042;,
 132.06646;0.33325;-682.86124;,
 168.69026;-68.93707;-682.86124;,
 132.06646;-68.93707;-682.86124;,
 132.06642;-68.93707;-802.77042;,
 168.69025;-68.93707;-802.77042;,
 168.69026;0.33325;682.86124;,
 132.06646;0.33325;682.86124;,
 132.06642;0.33325;802.77042;,
 168.69025;0.33325;802.77042;,
 168.69026;-68.93707;682.86124;,
 168.69025;-68.93707;802.77042;,
 132.06642;-68.93707;802.77042;,
 132.06646;-68.93707;682.86124;,
 18.69027;0.33325;-532.86124;,
 18.69024;0.33325;-802.77042;,
 -17.93358;0.33325;-802.77042;,
 -17.93355;0.33325;-532.86124;,
 18.69027;-68.93707;-532.86124;,
 -17.93355;-68.93707;-532.86124;,
 -17.93358;-68.93707;-802.77042;,
 18.69024;-68.93707;-802.77042;,
 18.69027;0.33325;532.86124;,
 -17.93355;0.33325;532.86124;,
 -17.93358;0.33325;802.77042;,
 18.69024;0.33325;802.77042;,
 18.69027;-68.93707;532.86124;,
 18.69024;-68.93707;802.77042;,
 -17.93358;-68.93707;802.77042;,
 -17.93355;-68.93707;532.86124;,
 -131.30973;0.33325;-682.86124;,
 -131.30977;0.33325;-802.77042;,
 -167.93357;0.33325;-802.77042;,
 -167.93356;0.33325;-682.86124;,
 -131.30973;-68.93707;-682.86124;,
 -167.93356;-68.93707;-682.86124;,
 -167.93357;-68.93707;-802.77042;,
 -131.30977;-68.93707;-802.77042;,
 -131.30973;0.33325;682.86124;,
 -167.93356;0.33325;682.86124;,
 -167.93357;0.33325;802.77042;,
 -131.30977;0.33325;802.77042;,
 -131.30973;-68.93707;682.86124;,
 -131.30977;-68.93707;802.77042;,
 -167.93357;-68.93707;802.77042;,
 -167.93356;-68.93707;682.86124;,
 168.69026;0.31777;803.05626;,
 132.06646;0.31777;803.05626;,
 132.06642;-69.12990;803.05626;,
 168.69025;-69.12990;803.05626;,
 18.69027;0.31777;803.05626;,
 -17.93355;0.31777;803.05626;,
 -17.93358;-69.12990;803.05626;,
 18.69024;-69.12990;803.05626;,
 -131.30973;0.31777;803.05626;,
 -167.93356;0.31777;803.05626;,
 -167.93357;-69.12990;803.05626;,
 -131.30977;-69.12990;803.05626;,
 168.69026;0.31777;-803.05626;,
 168.69025;-69.12990;-803.05626;,
 132.06642;-69.12990;-803.05626;,
 132.06646;0.31777;-803.05626;,
 18.69027;0.31777;-803.05626;,
 18.69024;-69.12990;-803.05626;,
 -17.93358;-69.12990;-803.05626;,
 -17.93355;0.31777;-803.05626;,
 -131.30973;0.31777;-803.05626;,
 -131.30977;-69.12990;-803.05626;,
 -167.93357;-69.12990;-803.05626;,
 -167.93356;0.31777;-803.05626;,
 -496.73336;0.33325;-168.31189;,
 -616.64273;0.33325;-168.31187;,
 -616.64273;0.33325;-131.68804;,
 -496.73336;0.33325;-131.68808;,
 -496.73336;-68.93707;-168.31189;,
 -496.73336;-68.93707;-131.68808;,
 -616.64273;-68.93707;-131.68804;,
 -616.64273;-68.93707;-168.31187;,
 495.22008;0.33325;-168.31197;,
 495.22008;0.33325;-131.68811;,
 615.12926;0.33325;-131.68811;,
 615.12926;0.33325;-168.31194;,
 495.22008;-68.93707;-168.31197;,
 615.12926;-68.93707;-168.31194;,
 615.12926;-68.93707;-131.68811;,
 495.22008;-68.93707;-131.68811;,
 -346.73338;0.33325;-18.31190;,
 -616.64273;0.33325;-18.31187;,
 -616.64273;0.33325;18.31195;,
 -346.73338;0.33325;18.31193;,
 -346.73338;-68.93707;-18.31190;,
 -346.73338;-68.93707;18.31193;,
 -616.64273;-68.93707;18.31195;,
 -616.64273;-68.93707;-18.31187;,
 345.22007;0.33325;-18.31195;,
 345.22007;0.33325;18.31187;,
 615.12926;0.33325;18.31188;,
 615.12926;0.33325;-18.31194;,
 345.22007;-68.93707;-18.31195;,
 615.12926;-68.93707;-18.31194;,
 615.12926;-68.93707;18.31188;,
 345.22007;-68.93707;18.31187;,
 -496.73336;0.33325;131.68811;,
 -616.64273;0.33325;131.68814;,
 -616.64273;0.33325;168.31197;,
 -496.73336;0.33325;168.31194;,
 -496.73336;-68.93707;131.68811;,
 -496.73336;-68.93707;168.31194;,
 -616.64273;-68.93707;168.31197;,
 -616.64273;-68.93707;131.68814;,
 495.22008;0.33325;131.68804;,
 495.22008;0.33325;168.31187;,
 615.12926;0.33325;168.31189;,
 615.12926;0.33325;131.68806;,
 495.22008;-68.93707;131.68804;,
 615.12926;-68.93707;131.68806;,
 615.12926;-68.93707;168.31189;,
 495.22008;-68.93707;168.31187;,
 615.41510;0.31777;-168.31197;,
 615.41510;0.31777;-131.68814;,
 615.41510;-69.12990;-131.68811;,
 615.41510;-69.12990;-168.31194;,
 615.41510;0.31777;-18.31195;,
 615.41510;0.31777;18.31187;,
 615.41510;-69.12990;18.31188;,
 615.41510;-69.12990;-18.31194;,
 615.41510;0.31777;131.68804;,
 615.41510;0.31777;168.31187;,
 615.41510;-69.12990;168.31189;,
 615.41510;-69.12990;131.68806;,
 -616.92848;0.31777;-168.31189;,
 -616.92848;-69.12990;-168.31187;,
 -616.92848;-69.12990;-131.68804;,
 -616.92848;0.31777;-131.68806;,
 -616.92848;0.31777;-18.31188;,
 -616.92848;-69.12990;-18.31187;,
 -616.92848;-69.12990;18.31195;,
 -616.92848;0.31777;18.31194;,
 -616.92848;0.31777;131.68811;,
 -616.92848;-69.12990;131.68814;,
 -616.92848;-69.12990;168.31197;,
 -616.92848;0.31777;168.31194;,
 169.82002;0.34252;-447.35352;,
 170.04341;0.34252;-409.41600;,
 495.58819;0.34252;-131.37505;,
 495.36505;0.34252;-169.31305;,
 -169.06333;0.34252;-447.35352;,
 -494.60836;0.34252;-169.31305;,
 -494.83150;0.34252;-131.37505;,
 -169.28672;0.34252;-409.41600;,
 169.82002;0.34252;447.35352;,
 495.36505;0.34252;169.31305;,
 495.58819;0.34252;131.37505;,
 170.04341;0.34252;409.41600;,
 -169.06333;0.34252;447.35352;,
 -169.28672;0.34252;409.41600;,
 -494.83150;0.34252;131.37505;,
 -494.60836;0.34252;169.31305;,
 169.82002;-69.25980;-447.35352;,
 495.36505;-69.25980;-169.31305;,
 495.58819;-69.25980;-131.37505;,
 170.04341;-69.25980;-409.41600;,
 -169.06333;-69.25980;-447.35352;,
 -169.28672;-69.25980;-409.41600;,
 -494.83150;-69.25980;-131.37505;,
 -494.60836;-69.25980;-169.31305;,
 169.82002;-69.25980;447.35352;,
 170.04341;-69.25980;409.41600;,
 495.58819;-69.25980;131.37505;,
 495.36505;-69.25980;169.31305;,
 -169.06333;-69.25980;447.35352;,
 -494.60836;-69.25980;169.31305;,
 -494.83150;-69.25980;131.37505;,
 -169.28672;-69.25980;409.41600;,
 -63.15609;0.33325;-188.99529;,
 -99.51644;0.33325;-188.99499;,
 -99.51644;0.33325;188.99544;,
 -63.15609;0.33325;188.99512;,
 -63.79683;0.33325;-189.10105;,
 -94.14332;0.33325;-169.04690;,
 203.34422;0.33325;19.77042;,
 233.69087;0.33325;-0.28373;,
 -63.79683;0.33325;189.10105;,
 233.66382;0.33325;0.12514;,
 200.32732;0.33325;-18.49712;,
 -97.13334;0.33325;170.47892;;
 
 81;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;316,317,318,319;;
 
 MeshMaterialList {
  4;
  81;
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.541000;0.541000;0.541000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;1.000000;0.180392;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;1.000000;0.180392;;
  }
  Material {
   1.000000;0.000000;0.051000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   1.000000;0.000000;0.051000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\���Ɖۑ莑��\\PNG\\���l.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  81;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;23,23,23,23;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;;
 }
 MeshTextureCoords {
  320;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}