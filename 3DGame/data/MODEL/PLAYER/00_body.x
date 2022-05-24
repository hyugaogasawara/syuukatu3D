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
 122;
 -4.80052;20.31336;-2.61003;,
 0.07486;21.22636;-2.61003;,
 0.08714;17.60669;-5.21135;,
 -4.83937;17.66378;-5.20259;,
 -9.30702;17.03100;-3.22927;,
 -9.60876;19.29924;-2.19277;,
 0.10244;12.92536;-6.04863;,
 -4.39917;12.89485;-5.62961;,
 -8.90911;12.73004;-3.49503;,
 -5.19161;20.31335;2.69714;,
 -9.57860;18.60772;0.80854;,
 -9.36142;16.49641;1.72063;,
 -5.15045;18.17965;3.81008;,
 -0.06987;18.12986;3.97621;,
 -0.08132;21.22636;2.69714;,
 -9.43330;14.31308;2.32377;,
 -4.99902;13.61520;4.00727;,
 -0.05275;13.63759;4.33361;,
 -4.42085;3.69412;-4.88357;,
 0.14707;3.69028;-5.02738;,
 -0.17922;0.04700;-6.29556;,
 -4.95266;0.04700;-5.13211;,
 -7.88997;0.03809;-2.01396;,
 -7.30767;3.35151;-2.88198;,
 -4.87742;3.85154;4.53015;,
 -7.09646;3.65398;2.26253;,
 -7.90050;0.03809;1.89205;,
 -4.85243;0.04700;5.15007;,
 -0.16883;0.04700;6.25114;,
 -0.00579;3.79728;4.77282;,
 0.12713;6.93702;-4.82394;,
 -4.43926;6.94407;-4.53423;,
 -7.26046;7.35705;-3.00893;,
 -7.29430;7.31952;2.11971;,
 -5.07561;6.89563;3.81469;,
 -0.02531;6.86456;4.42545;,
 4.56790;20.31336;-2.61003;,
 9.27702;19.29233;-2.06103;,
 9.17656;17.47519;-3.35490;,
 4.80138;17.56444;-5.21786;,
 8.91161;12.75927;-3.42787;,
 4.60921;12.94079;-5.76060;,
 4.64005;20.31336;2.69714;,
 4.58511;18.08225;3.85034;,
 9.23411;16.88950;1.65765;,
 9.25136;18.60772;0.84511;,
 4.36278;13.65871;4.32270;,
 9.24399;13.66048;2.04912;,
 4.30876;3.66324;-4.92940;,
 6.64853;3.57243;-2.90132;,
 5.81678;-0.23111;-3.77541;,
 4.49407;0.04700;-5.16408;,
 4.45388;3.80216;4.62562;,
 4.57482;0.04700;5.07777;,
 7.48743;-0.23111;1.92223;,
 6.63280;3.38812;1.90750;,
 6.72078;7.32105;-2.79374;,
 4.26199;6.92207;-4.62694;,
 4.54362;6.86516;4.03790;,
 6.76015;7.23376;1.86182;,
 9.38352;18.90542;-0.69757;,
 9.25136;18.60772;0.84511;,
 9.23411;16.88950;1.65765;,
 8.86365;16.50999;-0.74887;,
 9.17656;17.47519;-3.35490;,
 9.27702;19.29233;-2.06103;,
 9.24399;13.66048;2.04912;,
 9.21659;13.38200;-0.78010;,
 8.91161;12.75927;-3.42787;,
 -9.57757;18.90542;-0.57718;,
 -9.60876;19.29924;-2.19277;,
 -9.30702;17.03100;-3.22927;,
 -9.42059;16.17227;-0.64255;,
 -9.36142;16.49641;1.72063;,
 -9.57860;18.60772;0.80854;,
 -8.90911;12.73004;-3.49503;,
 -9.34594;13.98496;-0.69479;,
 -9.43330;14.31308;2.32377;,
 7.45173;-0.23111;-1.93098;,
 5.81678;-0.23111;-3.77541;,
 6.64853;3.57243;-2.90132;,
 6.48828;3.71849;-0.83809;,
 6.63280;3.38812;1.90750;,
 7.48743;-0.23111;1.92223;,
 -7.95692;0.03809;-0.72358;,
 -7.90050;0.03809;1.89205;,
 -7.09646;3.65398;2.26253;,
 -7.16294;3.77952;-0.76158;,
 -7.30767;3.35151;-2.88198;,
 -7.88997;0.03809;-2.01396;,
 6.76015;7.23376;1.86182;,
 6.48222;6.88575;-0.81565;,
 6.72078;7.32105;-2.79374;,
 -7.26046;7.35705;-3.00893;,
 -7.19303;6.92491;-0.73908;,
 -7.29430;7.31952;2.11971;,
 -9.57757;18.90542;-0.57718;,
 -5.19161;20.31335;2.69714;,
 -5.12202;20.29851;-0.63734;,
 -4.80052;20.31336;-2.61003;,
 -9.60876;19.29924;-2.19277;,
 -0.08132;21.22636;2.69714;,
 -0.08808;21.21150;-0.65450;,
 0.07486;21.22636;-2.61003;,
 -7.95692;0.03809;-0.72358;,
 -7.88997;0.03809;-2.01396;,
 -4.95266;0.04700;-5.13211;,
 -4.58640;0.04700;-0.80460;,
 -4.85243;0.04700;5.15007;,
 -0.17922;0.04700;-6.29556;,
 0.00075;0.04700;-0.82615;,
 -0.16883;0.04700;6.25114;,
 9.38352;18.90542;-0.69757;,
 9.27702;19.29233;-2.06103;,
 4.56790;20.31336;-2.61003;,
 5.44101;20.10151;-0.68697;,
 4.64005;20.31336;2.69714;,
 7.45173;-0.23111;-1.93098;,
 4.57482;0.04700;5.07777;,
 4.75738;0.04700;-0.84850;,
 4.49407;0.04700;-5.16408;,
 5.81678;-0.23111;-3.77541;;
 
 76;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;3,2,6,7;,
 4;3,7,8,4;,
 4;9,10,11,12;,
 4;9,12,13,14;,
 4;12,11,15,16;,
 4;12,16,17,13;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,25,26,27;,
 4;24,27,28,29;,
 4;7,6,30,31;,
 4;7,31,32,8;,
 4;31,30,19,18;,
 4;31,18,23,32;,
 4;16,15,33,34;,
 4;16,34,35,17;,
 4;34,33,25,24;,
 4;34,24,29,35;,
 4;36,37,38,39;,
 4;36,39,2,1;,
 4;39,38,40,41;,
 4;39,41,6,2;,
 4;42,14,13,43;,
 4;42,43,44,45;,
 4;43,13,17,46;,
 4;43,46,47,44;,
 4;48,49,50,51;,
 4;48,51,20,19;,
 4;52,29,28,53;,
 4;52,53,54,55;,
 4;41,40,56,57;,
 4;41,57,30,6;,
 4;57,56,49,48;,
 4;57,48,19,30;,
 4;46,17,35,58;,
 4;46,58,59,47;,
 4;58,35,29,52;,
 4;58,52,55,59;,
 4;60,61,62,63;,
 4;60,63,64,65;,
 4;63,62,66,67;,
 4;63,67,68,64;,
 4;69,70,71,72;,
 4;69,72,73,74;,
 4;72,71,75,76;,
 4;72,76,77,73;,
 4;78,79,80,81;,
 4;78,81,82,83;,
 4;84,85,86,87;,
 4;84,87,88,89;,
 4;67,66,90,91;,
 4;67,91,92,68;,
 4;91,90,82,81;,
 4;91,81,80,92;,
 4;76,75,93,94;,
 4;76,94,95,77;,
 4;94,93,88,87;,
 4;94,87,86,95;,
 4;96,74,97,98;,
 4;96,98,99,100;,
 4;98,97,101,102;,
 4;98,102,103,99;,
 4;104,105,106,107;,
 4;104,107,108,85;,
 4;107,106,109,110;,
 4;107,110,111,108;,
 4;112,113,114,115;,
 4;112,115,116,61;,
 4;115,114,103,102;,
 4;115,102,101,116;,
 4;117,83,118,119;,
 4;117,119,120,121;,
 4;119,118,111,110;,
 4;119,110,109,120;;
 
 MeshMaterialList {
  1;
  76;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  103;
  -0.278063;0.532578;-0.799401;,
  -0.898843;0.130570;-0.418368;,
  0.287431;0.892264;-0.348206;,
  0.838466;0.087406;-0.537899;,
  0.441148;0.739511;0.508440;,
  0.922568;0.198269;0.330995;,
  -0.468831;0.727121;0.501490;,
  -0.909553;0.166440;0.380803;,
  -0.821348;-0.146639;-0.551257;,
  0.488334;-0.097989;-0.867138;,
  0.503384;-0.004345;0.864052;,
  -0.442601;0.033163;0.896105;,
  0.007625;0.904694;-0.425993;,
  -0.004252;0.204148;-0.978931;,
  0.002479;0.421508;0.906821;,
  -0.000502;0.253919;0.967225;,
  -0.009430;-0.026790;-0.999597;,
  -0.020979;0.033245;0.999227;,
  -0.360814;0.291864;-0.885793;,
  0.365991;0.344413;-0.864541;,
  0.455065;0.241586;0.857060;,
  -0.446966;0.247301;0.859688;,
  -0.001327;0.405462;-0.914111;,
  -0.007415;0.252936;0.967455;,
  -0.893806;0.076569;-0.441868;,
  0.881705;0.055544;-0.468520;,
  0.938836;0.107088;0.327290;,
  -0.914075;0.091232;0.395151;,
  -0.004942;0.142670;-0.989758;,
  -0.006357;0.206173;0.978495;,
  -0.857959;-0.129135;-0.497223;,
  0.886921;-0.166748;-0.430775;,
  0.910789;-0.126801;0.392919;,
  -0.883757;-0.098222;0.457522;,
  -0.008248;-0.056149;-0.998388;,
  -0.018577;0.074390;0.997056;,
  -0.215226;0.882922;-0.417285;,
  -0.414197;0.137248;-0.899780;,
  -0.309803;0.792233;0.525727;,
  -0.452448;0.194099;0.870411;,
  -0.254928;-0.053733;-0.965466;,
  -0.261082;0.030549;0.964833;,
  -0.209025;0.352390;-0.912211;,
  -0.254127;0.251813;0.933815;,
  -0.356296;0.098491;-0.929168;,
  -0.423577;0.156125;0.892304;,
  -0.284865;-0.066139;-0.956283;,
  -0.348335;0.035970;0.936680;,
  0.215891;0.898063;-0.383241;,
  0.432237;0.127872;-0.892648;,
  0.301672;0.794671;0.526776;,
  0.475803;0.200702;0.856347;,
  0.273943;-0.062933;-0.959684;,
  0.274099;0.018263;0.961528;,
  0.208774;0.380804;-0.900779;,
  0.250615;0.256915;0.933374;,
  0.391181;0.096517;-0.915239;,
  0.456185;0.152131;0.876785;,
  0.328763;-0.079711;-0.941043;,
  0.377776;0.020235;0.925676;,
  -0.996590;-0.081557;-0.012562;,
  -0.979257;0.202468;0.007836;,
  0.987513;-0.152705;-0.038726;,
  0.968571;0.176857;-0.174905;,
  -0.986414;-0.162068;-0.026873;,
  0.984334;-0.173952;-0.028762;,
  0.008357;0.999962;-0.002358;,
  0.000000;-1.000000;-0.000000;,
  -0.998088;-0.054881;-0.028433;,
  0.997275;-0.057477;-0.046255;,
  -0.995439;0.094232;0.014883;,
  0.993206;0.082018;-0.082547;,
  -0.987798;-0.155606;0.006447;,
  0.979882;-0.199541;0.003777;,
  -0.234514;0.971085;0.044681;,
  0.001357;-0.999999;-0.000004;,
  0.241118;0.968382;0.064013;,
  -0.062184;-0.998016;0.009854;,
  0.988160;-0.145387;-0.049021;,
  0.996529;-0.048539;-0.067637;,
  0.997485;-0.066380;-0.024858;,
  0.986708;-0.159998;-0.028424;,
  0.984782;-0.166846;-0.048649;,
  0.983449;-0.180967;-0.008902;,
  -0.995139;-0.091259;-0.037020;,
  -0.995295;-0.074962;-0.061387;,
  -0.999387;-0.034712;0.004574;,
  -0.997348;-0.071799;0.011904;,
  -0.989210;-0.146496;0.001262;,
  -0.288377;0.952330;0.099527;,
  -0.250337;0.962588;0.103707;,
  0.008204;0.999934;-0.008039;,
  0.002714;-0.999996;-0.000008;,
  0.002713;-0.999996;-0.000049;,
  0.001357;-0.999999;-0.000025;,
  0.001357;-0.999999;0.000017;,
  0.002714;-0.999996;0.000034;,
  0.285246;0.950667;0.121933;,
  -0.124153;-0.992068;0.019673;,
  -0.100299;-0.994957;-0.001040;,
  -0.050213;-0.998738;-0.000521;,
  -0.074161;-0.997041;0.020244;,
  -0.147883;-0.988181;0.040367;;
  76;
  4;36,12,22,42;,
  4;36,42,18,0;,
  4;42,22,16,40;,
  4;42,40,8,18;,
  4;38,6,21,43;,
  4;38,43,23,14;,
  4;43,21,11,41;,
  4;43,41,17,23;,
  4;44,28,13,37;,
  4;44,37,1,24;,
  4;45,27,7,39;,
  4;45,39,15,29;,
  4;40,16,34,46;,
  4;40,46,30,8;,
  4;46,34,28,44;,
  4;46,44,24,30;,
  4;41,11,33,47;,
  4;41,47,35,17;,
  4;47,33,27,45;,
  4;47,45,29,35;,
  4;48,2,19,54;,
  4;48,54,22,12;,
  4;54,19,9,52;,
  4;54,52,16,22;,
  4;50,14,23,55;,
  4;50,55,20,4;,
  4;55,23,17,53;,
  4;55,53,10,20;,
  4;56,25,3,49;,
  4;56,49,13,28;,
  4;57,29,15,51;,
  4;57,51,5,26;,
  4;52,9,31,58;,
  4;52,58,34,16;,
  4;58,31,25,56;,
  4;58,56,28,34;,
  4;53,17,35,59;,
  4;53,59,32,10;,
  4;59,35,29,57;,
  4;59,57,26,32;,
  4;62,78,79,69;,
  4;62,69,80,81;,
  4;69,79,82,65;,
  4;69,65,83,80;,
  4;60,84,85,68;,
  4;60,68,86,87;,
  4;68,85,8,64;,
  4;68,64,88,86;,
  4;63,3,25,71;,
  4;63,71,26,5;,
  4;61,7,27,70;,
  4;61,70,24,1;,
  4;65,82,32,73;,
  4;65,73,31,83;,
  4;73,32,26,71;,
  4;73,71,25,31;,
  4;64,8,30,72;,
  4;64,72,33,88;,
  4;72,30,24,70;,
  4;72,70,27,33;,
  4;89,6,38,74;,
  4;89,74,36,90;,
  4;74,38,91,66;,
  4;74,66,12,36;,
  4;92,93,94,75;,
  4;92,75,95,96;,
  4;75,94,67,67;,
  4;75,67,67,95;,
  4;97,2,48,76;,
  4;97,76,50,4;,
  4;76,48,12,66;,
  4;76,66,91,50;,
  4;98,99,100,77;,
  4;98,77,101,102;,
  4;77,100,67,67;,
  4;77,67,67,101;;
 }
 MeshTextureCoords {
  122;
  0.248060;0.000000;,
  0.494830;0.000000;,
  0.495430;0.320000;,
  0.240770;0.317100;,
  0.000000;0.314360;,
  0.000000;0.000000;,
  0.496190;0.719540;,
  0.173980;0.720300;,
  0.000000;0.720710;,
  0.752760;0.000000;,
  1.000000;0.000000;,
  1.000000;0.251070;,
  0.761940;0.253100;,
  0.503980;0.255300;,
  0.504540;0.000000;,
  1.000000;0.637850;,
  0.830450;0.637450;,
  0.503140;0.636680;,
  0.117640;0.916760;,
  0.498150;0.916760;,
  0.498970;1.000000;,
  0.172490;1.000000;,
  0.000000;1.000000;,
  0.000000;0.916760;,
  0.897480;0.925010;,
  1.000000;0.924700;,
  1.000000;1.000000;,
  0.830730;1.000000;,
  0.500350;1.000000;,
  0.500920;0.926220;,
  0.497270;0.828610;,
  0.125820;0.828640;,
  0.000000;0.828640;,
  1.000000;0.804930;,
  0.886990;0.805110;,
  0.501840;0.805720;,
  0.686910;0.000000;,
  1.000000;0.000000;,
  1.000000;0.325770;,
  0.683810;0.322160;,
  1.000000;0.718360;,
  0.721070;0.719020;,
  0.315690;0.000000;,
  0.318130;0.257380;,
  0.000000;0.260920;,
  0.000000;0.000000;,
  0.279980;0.636160;,
  0.000000;0.635500;,
  0.740660;0.917160;,
  1.000000;0.917590;,
  1.000000;1.000000;,
  0.698810;1.000000;,
  0.253170;0.926100;,
  0.301790;1.000000;,
  0.000000;1.000000;,
  0.000000;0.925970;,
  1.000000;0.828820;,
  0.742950;0.828710;,
  0.252760;0.805730;,
  0.000000;0.805740;,
  0.459900;0.000000;,
  1.000000;0.000000;,
  1.000000;0.260920;,
  0.500190;0.293330;,
  0.000000;0.325770;,
  0.000000;0.000000;,
  1.000000;0.635500;,
  0.565010;0.671540;,
  0.000000;0.718360;,
  0.529960;0.000000;,
  1.000000;0.000000;,
  1.000000;0.314360;,
  0.494270;0.282350;,
  0.000000;0.251070;,
  0.000000;0.000000;,
  1.000000;0.720710;,
  0.428470;0.673350;,
  0.000000;0.637850;,
  0.436250;1.000000;,
  0.000000;1.000000;,
  0.000000;0.917590;,
  0.487080;0.921680;,
  1.000000;0.925970;,
  1.000000;1.000000;,
  0.556430;1.000000;,
  0.000000;1.000000;,
  0.000000;0.924700;,
  0.505340;0.920690;,
  1.000000;0.916760;,
  1.000000;1.000000;,
  1.000000;0.805740;,
  0.508880;0.817080;,
  0.000000;0.828820;,
  1.000000;0.828640;,
  0.483290;0.816390;,
  0.000000;0.804930;,
  0.000000;0.529960;,
  0.247240;0.000000;,
  0.247680;0.531890;,
  0.248060;1.000000;,
  0.000000;1.000000;,
  0.495460;0.000000;,
  0.495120;0.533560;,
  0.494830;1.000000;,
  0.000000;0.443570;,
  0.000000;0.000000;,
  0.172490;0.000000;,
  0.171150;0.416860;,
  0.169270;1.000000;,
  0.498970;0.000000;,
  0.499250;0.405620;,
  0.499650;1.000000;,
  1.000000;0.540100;,
  1.000000;1.000000;,
  0.686910;1.000000;,
  0.685700;0.536720;,
  0.684310;0.000000;,
  1.000000;0.436250;,
  0.698210;1.000000;,
  0.698560;0.414070;,
  0.698810;0.000000;,
  1.000000;0.000000;;
 }
}
