xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

    Frame RootFrame {

      FrameTransformMatrix {
        1.000000,0.000000,0.000000,0.000000,
        0.000000,1.000000,0.000000,0.000000,
        0.000000,0.000000,-1.000000,0.000000,
        0.000000,0.000000,0.000000,1.000000;;
      }
      Frame Torus {

        FrameTransformMatrix {
          1.000000,0.000000,0.000000,0.000000,
          0.000000,1.000000,0.000000,0.000000,
          0.000000,0.000000,1.000000,0.000000,
          0.000000,0.000000,0.000000,1.000000;;
        }
Mesh {
240;
1.048800; 0.000000; 0.084500;,
1.097600; 0.000000; 0.000000;,
0.888000; 0.645100; 0.000000;,
0.848500; 0.616500; 0.084500;,
0.848500; 0.616500; 0.084500;,
0.769500; 0.559100; 0.084500;,
0.951200; 0.000000; 0.084500;,
1.048800; 0.000000; 0.084500;,
0.769500; 0.559100; 0.084500;,
0.730100; 0.530400; 0.000000;,
0.902400; 0.000000; 0.000000;,
0.951200; 0.000000; 0.084500;,
0.730100; 0.530400; 0.000000;,
0.769500; 0.559100; -0.084500;,
0.951200; 0.000000; -0.084500;,
0.902400; 0.000000; 0.000000;,
0.769500; 0.559100; -0.084500;,
0.848500; 0.616500; -0.084500;,
1.048800; 0.000000; -0.084500;,
0.951200; 0.000000; -0.084500;,
1.097600; 0.000000; 0.000000;,
1.048800; 0.000000; -0.084500;,
0.848500; 0.616500; -0.084500;,
0.888000; 0.645100; 0.000000;,
0.339200; 1.043900; 0.000000;,
0.324100; 0.997500; 0.084500;,
0.848500; 0.616500; 0.084500;,
0.888000; 0.645100; 0.000000;,
0.324100; 0.997500; 0.084500;,
0.293900; 0.904600; 0.084500;,
0.769500; 0.559100; 0.084500;,
0.848500; 0.616500; 0.084500;,
0.293900; 0.904600; 0.084500;,
0.278900; 0.858200; 0.000000;,
0.730100; 0.530400; 0.000000;,
0.769500; 0.559100; 0.084500;,
0.278900; 0.858200; 0.000000;,
0.293900; 0.904600; -0.084500;,
0.769500; 0.559100; -0.084500;,
0.730100; 0.530400; 0.000000;,
0.293900; 0.904600; -0.084500;,
0.324100; 0.997500; -0.084500;,
0.848500; 0.616500; -0.084500;,
0.769500; 0.559100; -0.084500;,
0.324100; 0.997500; -0.084500;,
0.339200; 1.043900; 0.000000;,
0.888000; 0.645100; 0.000000;,
0.848500; 0.616500; -0.084500;,
-0.339200; 1.043900; 0.000000;,
-0.324100; 0.997500; 0.084500;,
0.324100; 0.997500; 0.084500;,
0.339200; 1.043900; 0.000000;,
-0.324100; 0.997500; 0.084500;,
-0.293900; 0.904600; 0.084500;,
0.293900; 0.904600; 0.084500;,
0.324100; 0.997500; 0.084500;,
-0.293900; 0.904600; 0.084500;,
-0.278900; 0.858200; 0.000000;,
0.278900; 0.858200; 0.000000;,
0.293900; 0.904600; 0.084500;,
-0.278900; 0.858200; 0.000000;,
-0.293900; 0.904600; -0.084500;,
0.293900; 0.904600; -0.084500;,
0.278900; 0.858200; 0.000000;,
-0.293900; 0.904600; -0.084500;,
-0.324100; 0.997500; -0.084500;,
0.324100; 0.997500; -0.084500;,
0.293900; 0.904600; -0.084500;,
-0.324100; 0.997500; -0.084500;,
-0.339200; 1.043900; 0.000000;,
0.339200; 1.043900; 0.000000;,
0.324100; 0.997500; -0.084500;,
-0.888000; 0.645100; 0.000000;,
-0.848500; 0.616500; 0.084500;,
-0.324100; 0.997500; 0.084500;,
-0.339200; 1.043900; 0.000000;,
-0.848500; 0.616500; 0.084500;,
-0.769500; 0.559100; 0.084500;,
-0.293900; 0.904600; 0.084500;,
-0.324100; 0.997500; 0.084500;,
-0.769500; 0.559100; 0.084500;,
-0.730100; 0.530400; 0.000000;,
-0.278900; 0.858200; 0.000000;,
-0.293900; 0.904600; 0.084500;,
-0.730100; 0.530400; 0.000000;,
-0.769500; 0.559100; -0.084500;,
-0.293900; 0.904600; -0.084500;,
-0.278900; 0.858200; 0.000000;,
-0.769500; 0.559100; -0.084500;,
-0.848500; 0.616500; -0.084500;,
-0.324100; 0.997500; -0.084500;,
-0.293900; 0.904600; -0.084500;,
-0.848500; 0.616500; -0.084500;,
-0.888000; 0.645100; 0.000000;,
-0.339200; 1.043900; 0.000000;,
-0.324100; 0.997500; -0.084500;,
-1.097600; -0.000000; 0.000000;,
-1.048800; -0.000000; 0.084500;,
-0.848500; 0.616500; 0.084500;,
-0.888000; 0.645100; 0.000000;,
-1.048800; -0.000000; 0.084500;,
-0.951200; -0.000000; 0.084500;,
-0.769500; 0.559100; 0.084500;,
-0.848500; 0.616500; 0.084500;,
-0.951200; -0.000000; 0.084500;,
-0.902400; -0.000000; 0.000000;,
-0.730100; 0.530400; 0.000000;,
-0.769500; 0.559100; 0.084500;,
-0.902400; -0.000000; 0.000000;,
-0.951200; -0.000000; -0.084500;,
-0.769500; 0.559100; -0.084500;,
-0.730100; 0.530400; 0.000000;,
-0.951200; -0.000000; -0.084500;,
-1.048800; -0.000000; -0.084500;,
-0.848500; 0.616500; -0.084500;,
-0.769500; 0.559100; -0.084500;,
-1.048800; -0.000000; -0.084500;,
-1.097600; -0.000000; 0.000000;,
-0.888000; 0.645100; 0.000000;,
-0.848500; 0.616500; -0.084500;,
-0.888000; -0.645100; 0.000000;,
-0.848500; -0.616500; 0.084500;,
-1.048800; -0.000000; 0.084500;,
-1.097600; -0.000000; 0.000000;,
-0.848500; -0.616500; 0.084500;,
-0.769500; -0.559100; 0.084500;,
-0.951200; -0.000000; 0.084500;,
-1.048800; -0.000000; 0.084500;,
-0.769500; -0.559100; 0.084500;,
-0.730100; -0.530400; 0.000000;,
-0.902400; -0.000000; 0.000000;,
-0.951200; -0.000000; 0.084500;,
-0.730100; -0.530400; 0.000000;,
-0.769500; -0.559100; -0.084500;,
-0.951200; -0.000000; -0.084500;,
-0.902400; -0.000000; 0.000000;,
-0.769500; -0.559100; -0.084500;,
-0.848500; -0.616500; -0.084500;,
-1.048800; -0.000000; -0.084500;,
-0.951200; -0.000000; -0.084500;,
-0.848500; -0.616500; -0.084500;,
-0.888000; -0.645100; 0.000000;,
-1.097600; -0.000000; 0.000000;,
-1.048800; -0.000000; -0.084500;,
-0.339200; -1.043900; 0.000000;,
-0.324100; -0.997500; 0.084500;,
-0.848500; -0.616500; 0.084500;,
-0.888000; -0.645100; 0.000000;,
-0.324100; -0.997500; 0.084500;,
-0.293900; -0.904600; 0.084500;,
-0.769500; -0.559100; 0.084500;,
-0.848500; -0.616500; 0.084500;,
-0.293900; -0.904600; 0.084500;,
-0.278900; -0.858200; 0.000000;,
-0.730100; -0.530400; 0.000000;,
-0.769500; -0.559100; 0.084500;,
-0.278900; -0.858200; 0.000000;,
-0.293900; -0.904600; -0.084500;,
-0.769500; -0.559100; -0.084500;,
-0.730100; -0.530400; 0.000000;,
-0.293900; -0.904600; -0.084500;,
-0.324100; -0.997500; -0.084500;,
-0.848500; -0.616500; -0.084500;,
-0.769500; -0.559100; -0.084500;,
-0.324100; -0.997500; -0.084500;,
-0.339200; -1.043900; 0.000000;,
-0.888000; -0.645100; 0.000000;,
-0.848500; -0.616500; -0.084500;,
0.339200; -1.043900; 0.000000;,
0.324100; -0.997500; 0.084500;,
-0.324100; -0.997500; 0.084500;,
-0.339200; -1.043900; 0.000000;,
0.324100; -0.997500; 0.084500;,
0.293900; -0.904600; 0.084500;,
-0.293900; -0.904600; 0.084500;,
-0.324100; -0.997500; 0.084500;,
0.293900; -0.904600; 0.084500;,
0.278900; -0.858200; 0.000000;,
-0.278900; -0.858200; 0.000000;,
-0.293900; -0.904600; 0.084500;,
0.278900; -0.858200; 0.000000;,
0.293900; -0.904600; -0.084500;,
-0.293900; -0.904600; -0.084500;,
-0.278900; -0.858200; 0.000000;,
0.293900; -0.904600; -0.084500;,
0.324100; -0.997500; -0.084500;,
-0.324100; -0.997500; -0.084500;,
-0.293900; -0.904600; -0.084500;,
0.324100; -0.997500; -0.084500;,
0.339200; -1.043900; 0.000000;,
-0.339200; -1.043900; 0.000000;,
-0.324100; -0.997500; -0.084500;,
0.888000; -0.645100; 0.000000;,
0.848500; -0.616500; 0.084500;,
0.324100; -0.997500; 0.084500;,
0.339200; -1.043900; 0.000000;,
0.848500; -0.616500; 0.084500;,
0.769500; -0.559100; 0.084500;,
0.293900; -0.904600; 0.084500;,
0.324100; -0.997500; 0.084500;,
0.769500; -0.559100; 0.084500;,
0.730100; -0.530400; 0.000000;,
0.278900; -0.858200; 0.000000;,
0.293900; -0.904600; 0.084500;,
0.730100; -0.530400; 0.000000;,
0.769500; -0.559100; -0.084500;,
0.293900; -0.904600; -0.084500;,
0.278900; -0.858200; 0.000000;,
0.769500; -0.559100; -0.084500;,
0.848500; -0.616500; -0.084500;,
0.324100; -0.997500; -0.084500;,
0.293900; -0.904600; -0.084500;,
0.848500; -0.616500; -0.084500;,
0.888000; -0.645100; 0.000000;,
0.339200; -1.043900; 0.000000;,
0.324100; -0.997500; -0.084500;,
1.097600; 0.000000; 0.000000;,
1.048800; 0.000000; 0.084500;,
0.848500; -0.616500; 0.084500;,
0.888000; -0.645100; 0.000000;,
1.048800; 0.000000; 0.084500;,
0.951200; 0.000000; 0.084500;,
0.769500; -0.559100; 0.084500;,
0.848500; -0.616500; 0.084500;,
0.951200; 0.000000; 0.084500;,
0.902400; 0.000000; 0.000000;,
0.730100; -0.530400; 0.000000;,
0.769500; -0.559100; 0.084500;,
0.902400; 0.000000; 0.000000;,
0.951200; 0.000000; -0.084500;,
0.769500; -0.559100; -0.084500;,
0.730100; -0.530400; 0.000000;,
0.951200; 0.000000; -0.084500;,
1.048800; 0.000000; -0.084500;,
0.848500; -0.616500; -0.084500;,
0.769500; -0.559100; -0.084500;,
1.048800; 0.000000; -0.084500;,
1.097600; 0.000000; 0.000000;,
0.888000; -0.645100; 0.000000;,
0.848500; -0.616500; -0.084500;;
60;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;,
4; 64, 67, 66, 65;,
4; 68, 71, 70, 69;,
4; 72, 75, 74, 73;,
4; 76, 79, 78, 77;,
4; 80, 83, 82, 81;,
4; 84, 87, 86, 85;,
4; 88, 91, 90, 89;,
4; 92, 95, 94, 93;,
4; 96, 99, 98, 97;,
4; 100, 103, 102, 101;,
4; 104, 107, 106, 105;,
4; 108, 111, 110, 109;,
4; 112, 115, 114, 113;,
4; 116, 119, 118, 117;,
4; 120, 123, 122, 121;,
4; 124, 127, 126, 125;,
4; 128, 131, 130, 129;,
4; 132, 135, 134, 133;,
4; 136, 139, 138, 137;,
4; 140, 143, 142, 141;,
4; 144, 147, 146, 145;,
4; 148, 151, 150, 149;,
4; 152, 155, 154, 153;,
4; 156, 159, 158, 157;,
4; 160, 163, 162, 161;,
4; 164, 167, 166, 165;,
4; 168, 171, 170, 169;,
4; 172, 175, 174, 173;,
4; 176, 179, 178, 177;,
4; 180, 183, 182, 181;,
4; 184, 187, 186, 185;,
4; 188, 191, 190, 189;,
4; 192, 195, 194, 193;,
4; 196, 199, 198, 197;,
4; 200, 203, 202, 201;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;,
4; 228, 231, 230, 229;,
4; 232, 235, 234, 233;,
4; 236, 239, 238, 237;;
  MeshMaterialList {
    0;
    60;
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
    }  //End of MeshMaterialList
  MeshNormals {
240;
    0.490432; 0.000000; 0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.809015; 0.587756; 0.000000;,
    0.396771; 0.288247; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    -0.396771; -0.288247; 0.871456;,
    -0.490432; 0.000000; 0.871456;,
    0.490432; 0.000000; 0.871456;,
    -0.396771; -0.288247; 0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -0.490432; 0.000000; 0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -0.396771; -0.288247; -0.871456;,
    -0.490432; 0.000000; -0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.396771; -0.288247; -0.871456;,
    0.396771; 0.288247; -0.871456;,
    0.490432; 0.000000; -0.871456;,
    -0.490432; 0.000000; -0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.490432; 0.000000; -0.871456;,
    0.396771; 0.288247; -0.871456;,
    0.809015; 0.587756; 0.000000;,
    0.309000; 0.951048; 0.000000;,
    0.151555; 0.466414; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    0.809015; 0.587756; 0.000000;,
    0.151555; 0.466414; 0.871456;,
    -0.151555; -0.466414; 0.871456;,
    -0.396771; -0.288247; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    -0.151555; -0.466414; 0.871456;,
    -0.309000; -0.951048; 0.000000;,
    -0.809015; -0.587756; 0.000000;,
    -0.396771; -0.288247; 0.871456;,
    -0.309000; -0.951048; 0.000000;,
    -0.151555; -0.466414; -0.871456;,
    -0.396771; -0.288247; -0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -0.151555; -0.466414; -0.871456;,
    0.151555; 0.466414; -0.871456;,
    0.396771; 0.288247; -0.871456;,
    -0.396771; -0.288247; -0.871456;,
    0.151555; 0.466414; -0.871456;,
    0.309000; 0.951048; 0.000000;,
    0.809015; 0.587756; 0.000000;,
    0.396771; 0.288247; -0.871456;,
    -0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; 0.871456;,
    0.151555; 0.466414; 0.871456;,
    0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; 0.871456;,
    0.151555; -0.466414; 0.871456;,
    -0.151555; -0.466414; 0.871456;,
    0.151555; 0.466414; 0.871456;,
    0.151555; -0.466414; 0.871456;,
    0.309000; -0.951048; 0.000000;,
    -0.309000; -0.951048; 0.000000;,
    -0.151555; -0.466414; 0.871456;,
    0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; -0.871456;,
    -0.151555; -0.466414; -0.871456;,
    -0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; -0.871456;,
    -0.151555; 0.466414; -0.871456;,
    0.151555; 0.466414; -0.871456;,
    -0.151555; -0.466414; -0.871456;,
    -0.151555; 0.466414; -0.871456;,
    -0.309000; 0.951048; 0.000000;,
    0.309000; 0.951048; 0.000000;,
    0.151555; 0.466414; -0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.396771; 0.288247; 0.871456;,
    -0.151555; 0.466414; 0.871456;,
    -0.309000; 0.951048; 0.000000;,
    -0.396771; 0.288247; 0.871456;,
    0.396771; -0.288247; 0.871456;,
    0.151555; -0.466414; 0.871456;,
    -0.151555; 0.466414; 0.871456;,
    0.396771; -0.288247; 0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; 0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.396771; -0.288247; -0.871456;,
    0.151555; -0.466414; -0.871456;,
    0.309000; -0.951048; 0.000000;,
    0.396771; -0.288247; -0.871456;,
    -0.396771; 0.288247; -0.871456;,
    -0.151555; 0.466414; -0.871456;,
    0.151555; -0.466414; -0.871456;,
    -0.396771; 0.288247; -0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; -0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.490432; 0.000000; 0.871456;,
    -0.396771; 0.288247; 0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.490432; 0.000000; 0.871456;,
    0.490432; 0.000000; 0.871456;,
    0.396771; -0.288247; 0.871456;,
    -0.396771; 0.288247; 0.871456;,
    0.490432; 0.000000; 0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.809015; -0.587756; 0.000000;,
    0.396771; -0.288247; 0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.490432; 0.000000; -0.871456;,
    0.396771; -0.288247; -0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.490432; 0.000000; -0.871456;,
    -0.490432; 0.000000; -0.871456;,
    -0.396771; 0.288247; -0.871456;,
    0.396771; -0.288247; -0.871456;,
    -0.490432; 0.000000; -0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.809015; 0.587756; 0.000000;,
    -0.396771; 0.288247; -0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -0.396771; -0.288247; 0.871456;,
    -0.490432; 0.000000; 0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.396771; -0.288247; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    0.490432; 0.000000; 0.871456;,
    -0.490432; 0.000000; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    0.809015; 0.587756; 0.000000;,
    1.000000; 0.000000; 0.000000;,
    0.490432; 0.000000; 0.871456;,
    0.809015; 0.587756; 0.000000;,
    0.396771; 0.288247; -0.871456;,
    0.490432; 0.000000; -0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.396771; 0.288247; -0.871456;,
    -0.396771; -0.288247; -0.871456;,
    -0.490432; 0.000000; -0.871456;,
    0.490432; 0.000000; -0.871456;,
    -0.396771; -0.288247; -0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -0.490432; 0.000000; -0.871456;,
    -0.309000; -0.951048; 0.000000;,
    -0.151555; -0.466414; 0.871456;,
    -0.396771; -0.288247; 0.871456;,
    -0.809015; -0.587756; 0.000000;,
    -0.151555; -0.466414; 0.871456;,
    0.151555; 0.466414; 0.871456;,
    0.396771; 0.288247; 0.871456;,
    -0.396771; -0.288247; 0.871456;,
    0.151555; 0.466414; 0.871456;,
    0.309000; 0.951048; 0.000000;,
    0.809015; 0.587756; 0.000000;,
    0.396771; 0.288247; 0.871456;,
    0.309000; 0.951048; 0.000000;,
    0.151555; 0.466414; -0.871456;,
    0.396771; 0.288247; -0.871456;,
    0.809015; 0.587756; 0.000000;,
    0.151555; 0.466414; -0.871456;,
    -0.151555; -0.466414; -0.871456;,
    -0.396771; -0.288247; -0.871456;,
    0.396771; 0.288247; -0.871456;,
    -0.151555; -0.466414; -0.871456;,
    -0.309000; -0.951048; 0.000000;,
    -0.809015; -0.587756; 0.000000;,
    -0.396771; -0.288247; -0.871456;,
    0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; 0.871456;,
    -0.151555; -0.466414; 0.871456;,
    -0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; 0.871456;,
    -0.151555; 0.466414; 0.871456;,
    0.151555; 0.466414; 0.871456;,
    -0.151555; -0.466414; 0.871456;,
    -0.151555; 0.466414; 0.871456;,
    -0.309000; 0.951048; 0.000000;,
    0.309000; 0.951048; 0.000000;,
    0.151555; 0.466414; 0.871456;,
    -0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; -0.871456;,
    0.151555; 0.466414; -0.871456;,
    0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; -0.871456;,
    0.151555; -0.466414; -0.871456;,
    -0.151555; -0.466414; -0.871456;,
    0.151555; 0.466414; -0.871456;,
    0.151555; -0.466414; -0.871456;,
    0.309000; -0.951048; 0.000000;,
    -0.309000; -0.951048; 0.000000;,
    -0.151555; -0.466414; -0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.396771; -0.288247; 0.871456;,
    0.151555; -0.466414; 0.871456;,
    0.309000; -0.951048; 0.000000;,
    0.396771; -0.288247; 0.871456;,
    -0.396771; 0.288247; 0.871456;,
    -0.151555; 0.466414; 0.871456;,
    0.151555; -0.466414; 0.871456;,
    -0.396771; 0.288247; 0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.309000; 0.951048; 0.000000;,
    -0.151555; 0.466414; 0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.396771; 0.288247; -0.871456;,
    -0.151555; 0.466414; -0.871456;,
    -0.309000; 0.951048; 0.000000;,
    -0.396771; 0.288247; -0.871456;,
    0.396771; -0.288247; -0.871456;,
    0.151555; -0.466414; -0.871456;,
    -0.151555; 0.466414; -0.871456;,
    0.396771; -0.288247; -0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.309000; -0.951048; 0.000000;,
    0.151555; -0.466414; -0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.490432; 0.000000; 0.871456;,
    0.396771; -0.288247; 0.871456;,
    0.809015; -0.587756; 0.000000;,
    0.490432; 0.000000; 0.871456;,
    -0.490432; 0.000000; 0.871456;,
    -0.396771; 0.288247; 0.871456;,
    0.396771; -0.288247; 0.871456;,
    -0.490432; 0.000000; 0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.809015; 0.587756; 0.000000;,
    -0.396771; 0.288247; 0.871456;,
    -1.000000; 0.000000; 0.000000;,
    -0.490432; 0.000000; -0.871456;,
    -0.396771; 0.288247; -0.871456;,
    -0.809015; 0.587756; 0.000000;,
    -0.490432; 0.000000; -0.871456;,
    0.490432; 0.000000; -0.871456;,
    0.396771; -0.288247; -0.871456;,
    -0.396771; 0.288247; -0.871456;,
    0.490432; 0.000000; -0.871456;,
    1.000000; 0.000000; 0.000000;,
    0.809015; -0.587756; 0.000000;,
    0.396771; -0.288247; -0.871456;;
60;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;,
4; 64, 67, 66, 65;,
4; 68, 71, 70, 69;,
4; 72, 75, 74, 73;,
4; 76, 79, 78, 77;,
4; 80, 83, 82, 81;,
4; 84, 87, 86, 85;,
4; 88, 91, 90, 89;,
4; 92, 95, 94, 93;,
4; 96, 99, 98, 97;,
4; 100, 103, 102, 101;,
4; 104, 107, 106, 105;,
4; 108, 111, 110, 109;,
4; 112, 115, 114, 113;,
4; 116, 119, 118, 117;,
4; 120, 123, 122, 121;,
4; 124, 127, 126, 125;,
4; 128, 131, 130, 129;,
4; 132, 135, 134, 133;,
4; 136, 139, 138, 137;,
4; 140, 143, 142, 141;,
4; 144, 147, 146, 145;,
4; 148, 151, 150, 149;,
4; 152, 155, 154, 153;,
4; 156, 159, 158, 157;,
4; 160, 163, 162, 161;,
4; 164, 167, 166, 165;,
4; 168, 171, 170, 169;,
4; 172, 175, 174, 173;,
4; 176, 179, 178, 177;,
4; 180, 183, 182, 181;,
4; 184, 187, 186, 185;,
4; 188, 191, 190, 189;,
4; 192, 195, 194, 193;,
4; 196, 199, 198, 197;,
4; 200, 203, 202, 201;,
4; 204, 207, 206, 205;,
4; 208, 211, 210, 209;,
4; 212, 215, 214, 213;,
4; 216, 219, 218, 217;,
4; 220, 223, 222, 221;,
4; 224, 227, 226, 225;,
4; 228, 231, 230, 229;,
4; 232, 235, 234, 233;,
4; 236, 239, 238, 237;;
}  //End of MeshNormals
MeshVertexColors {
240;
0;1.000000;1.000000;1.000000;1.000000;,
1;1.000000;1.000000;1.000000;1.000000;,
2;1.000000;1.000000;1.000000;1.000000;,
3;1.000000;1.000000;1.000000;1.000000;,
4;1.000000;1.000000;1.000000;1.000000;,
5;1.000000;1.000000;1.000000;1.000000;,
6;1.000000;1.000000;1.000000;1.000000;,
7;1.000000;1.000000;1.000000;1.000000;,
8;1.000000;1.000000;1.000000;1.000000;,
9;1.000000;1.000000;1.000000;1.000000;,
10;1.000000;1.000000;1.000000;1.000000;,
11;1.000000;1.000000;1.000000;1.000000;,
12;1.000000;1.000000;1.000000;1.000000;,
13;1.000000;1.000000;1.000000;1.000000;,
14;1.000000;1.000000;1.000000;1.000000;,
15;1.000000;1.000000;1.000000;1.000000;,
16;1.000000;1.000000;1.000000;1.000000;,
17;1.000000;1.000000;1.000000;1.000000;,
18;1.000000;1.000000;1.000000;1.000000;,
19;1.000000;1.000000;1.000000;1.000000;,
20;1.000000;1.000000;1.000000;1.000000;,
21;1.000000;1.000000;1.000000;1.000000;,
22;1.000000;1.000000;1.000000;1.000000;,
23;1.000000;1.000000;1.000000;1.000000;,
24;1.000000;1.000000;1.000000;1.000000;,
25;1.000000;1.000000;1.000000;1.000000;,
26;1.000000;1.000000;1.000000;1.000000;,
27;1.000000;1.000000;1.000000;1.000000;,
28;1.000000;1.000000;1.000000;1.000000;,
29;1.000000;1.000000;1.000000;1.000000;,
30;1.000000;1.000000;1.000000;1.000000;,
31;1.000000;1.000000;1.000000;1.000000;,
32;1.000000;1.000000;1.000000;1.000000;,
33;1.000000;1.000000;1.000000;1.000000;,
34;1.000000;1.000000;1.000000;1.000000;,
35;1.000000;1.000000;1.000000;1.000000;,
36;1.000000;1.000000;1.000000;1.000000;,
37;1.000000;1.000000;1.000000;1.000000;,
38;1.000000;1.000000;1.000000;1.000000;,
39;1.000000;1.000000;1.000000;1.000000;,
40;1.000000;1.000000;1.000000;1.000000;,
41;1.000000;1.000000;1.000000;1.000000;,
42;1.000000;1.000000;1.000000;1.000000;,
43;1.000000;1.000000;1.000000;1.000000;,
44;1.000000;1.000000;1.000000;1.000000;,
45;1.000000;1.000000;1.000000;1.000000;,
46;1.000000;1.000000;1.000000;1.000000;,
47;1.000000;1.000000;1.000000;1.000000;,
48;1.000000;1.000000;1.000000;1.000000;,
49;1.000000;1.000000;1.000000;1.000000;,
50;1.000000;1.000000;1.000000;1.000000;,
51;1.000000;1.000000;1.000000;1.000000;,
52;1.000000;1.000000;1.000000;1.000000;,
53;1.000000;1.000000;1.000000;1.000000;,
54;1.000000;1.000000;1.000000;1.000000;,
55;1.000000;1.000000;1.000000;1.000000;,
56;1.000000;1.000000;1.000000;1.000000;,
57;1.000000;1.000000;1.000000;1.000000;,
58;1.000000;1.000000;1.000000;1.000000;,
59;1.000000;1.000000;1.000000;1.000000;,
60;1.000000;1.000000;1.000000;1.000000;,
61;1.000000;1.000000;1.000000;1.000000;,
62;1.000000;1.000000;1.000000;1.000000;,
63;1.000000;1.000000;1.000000;1.000000;,
64;1.000000;1.000000;1.000000;1.000000;,
65;1.000000;1.000000;1.000000;1.000000;,
66;1.000000;1.000000;1.000000;1.000000;,
67;1.000000;1.000000;1.000000;1.000000;,
68;1.000000;1.000000;1.000000;1.000000;,
69;1.000000;1.000000;1.000000;1.000000;,
70;1.000000;1.000000;1.000000;1.000000;,
71;1.000000;1.000000;1.000000;1.000000;,
72;1.000000;1.000000;1.000000;1.000000;,
73;1.000000;1.000000;1.000000;1.000000;,
74;1.000000;1.000000;1.000000;1.000000;,
75;1.000000;1.000000;1.000000;1.000000;,
76;1.000000;1.000000;1.000000;1.000000;,
77;1.000000;1.000000;1.000000;1.000000;,
78;1.000000;1.000000;1.000000;1.000000;,
79;1.000000;1.000000;1.000000;1.000000;,
80;1.000000;1.000000;1.000000;1.000000;,
81;1.000000;1.000000;1.000000;1.000000;,
82;1.000000;1.000000;1.000000;1.000000;,
83;1.000000;1.000000;1.000000;1.000000;,
84;1.000000;1.000000;1.000000;1.000000;,
85;1.000000;1.000000;1.000000;1.000000;,
86;1.000000;1.000000;1.000000;1.000000;,
87;1.000000;1.000000;1.000000;1.000000;,
88;1.000000;1.000000;1.000000;1.000000;,
89;1.000000;1.000000;1.000000;1.000000;,
90;1.000000;1.000000;1.000000;1.000000;,
91;1.000000;1.000000;1.000000;1.000000;,
92;1.000000;1.000000;1.000000;1.000000;,
93;1.000000;1.000000;1.000000;1.000000;,
94;1.000000;1.000000;1.000000;1.000000;,
95;1.000000;1.000000;1.000000;1.000000;,
96;1.000000;1.000000;1.000000;1.000000;,
97;1.000000;1.000000;1.000000;1.000000;,
98;1.000000;1.000000;1.000000;1.000000;,
99;1.000000;1.000000;1.000000;1.000000;,
100;1.000000;1.000000;1.000000;1.000000;,
101;1.000000;1.000000;1.000000;1.000000;,
102;1.000000;1.000000;1.000000;1.000000;,
103;1.000000;1.000000;1.000000;1.000000;,
104;1.000000;1.000000;1.000000;1.000000;,
105;1.000000;1.000000;1.000000;1.000000;,
106;1.000000;1.000000;1.000000;1.000000;,
107;1.000000;1.000000;1.000000;1.000000;,
108;1.000000;1.000000;1.000000;1.000000;,
109;1.000000;1.000000;1.000000;1.000000;,
110;1.000000;1.000000;1.000000;1.000000;,
111;1.000000;1.000000;1.000000;1.000000;,
112;1.000000;1.000000;1.000000;1.000000;,
113;1.000000;1.000000;1.000000;1.000000;,
114;1.000000;1.000000;1.000000;1.000000;,
115;1.000000;1.000000;1.000000;1.000000;,
116;1.000000;1.000000;1.000000;1.000000;,
117;1.000000;1.000000;1.000000;1.000000;,
118;1.000000;1.000000;1.000000;1.000000;,
119;1.000000;1.000000;1.000000;1.000000;,
120;1.000000;1.000000;1.000000;1.000000;,
121;1.000000;1.000000;1.000000;1.000000;,
122;1.000000;1.000000;1.000000;1.000000;,
123;1.000000;1.000000;1.000000;1.000000;,
124;1.000000;1.000000;1.000000;1.000000;,
125;1.000000;1.000000;1.000000;1.000000;,
126;1.000000;1.000000;1.000000;1.000000;,
127;1.000000;1.000000;1.000000;1.000000;,
128;1.000000;1.000000;1.000000;1.000000;,
129;1.000000;1.000000;1.000000;1.000000;,
130;1.000000;1.000000;1.000000;1.000000;,
131;1.000000;1.000000;1.000000;1.000000;,
132;1.000000;1.000000;1.000000;1.000000;,
133;1.000000;1.000000;1.000000;1.000000;,
134;1.000000;1.000000;1.000000;1.000000;,
135;1.000000;1.000000;1.000000;1.000000;,
136;1.000000;1.000000;1.000000;1.000000;,
137;1.000000;1.000000;1.000000;1.000000;,
138;1.000000;1.000000;1.000000;1.000000;,
139;1.000000;1.000000;1.000000;1.000000;,
140;1.000000;1.000000;1.000000;1.000000;,
141;1.000000;1.000000;1.000000;1.000000;,
142;1.000000;1.000000;1.000000;1.000000;,
143;1.000000;1.000000;1.000000;1.000000;,
144;1.000000;1.000000;1.000000;1.000000;,
145;1.000000;1.000000;1.000000;1.000000;,
146;1.000000;1.000000;1.000000;1.000000;,
147;1.000000;1.000000;1.000000;1.000000;,
148;1.000000;1.000000;1.000000;1.000000;,
149;1.000000;1.000000;1.000000;1.000000;,
150;1.000000;1.000000;1.000000;1.000000;,
151;1.000000;1.000000;1.000000;1.000000;,
152;1.000000;1.000000;1.000000;1.000000;,
153;1.000000;1.000000;1.000000;1.000000;,
154;1.000000;1.000000;1.000000;1.000000;,
155;1.000000;1.000000;1.000000;1.000000;,
156;1.000000;1.000000;1.000000;1.000000;,
157;1.000000;1.000000;1.000000;1.000000;,
158;1.000000;1.000000;1.000000;1.000000;,
159;1.000000;1.000000;1.000000;1.000000;,
160;1.000000;1.000000;1.000000;1.000000;,
161;1.000000;1.000000;1.000000;1.000000;,
162;1.000000;1.000000;1.000000;1.000000;,
163;1.000000;1.000000;1.000000;1.000000;,
164;1.000000;1.000000;1.000000;1.000000;,
165;1.000000;1.000000;1.000000;1.000000;,
166;1.000000;1.000000;1.000000;1.000000;,
167;1.000000;1.000000;1.000000;1.000000;,
168;1.000000;1.000000;1.000000;1.000000;,
169;1.000000;1.000000;1.000000;1.000000;,
170;1.000000;1.000000;1.000000;1.000000;,
171;1.000000;1.000000;1.000000;1.000000;,
172;1.000000;1.000000;1.000000;1.000000;,
173;1.000000;1.000000;1.000000;1.000000;,
174;1.000000;1.000000;1.000000;1.000000;,
175;1.000000;1.000000;1.000000;1.000000;,
176;1.000000;1.000000;1.000000;1.000000;,
177;1.000000;1.000000;1.000000;1.000000;,
178;1.000000;1.000000;1.000000;1.000000;,
179;1.000000;1.000000;1.000000;1.000000;,
180;1.000000;1.000000;1.000000;1.000000;,
181;1.000000;1.000000;1.000000;1.000000;,
182;1.000000;1.000000;1.000000;1.000000;,
183;1.000000;1.000000;1.000000;1.000000;,
184;1.000000;1.000000;1.000000;1.000000;,
185;1.000000;1.000000;1.000000;1.000000;,
186;1.000000;1.000000;1.000000;1.000000;,
187;1.000000;1.000000;1.000000;1.000000;,
188;1.000000;1.000000;1.000000;1.000000;,
189;1.000000;1.000000;1.000000;1.000000;,
190;1.000000;1.000000;1.000000;1.000000;,
191;1.000000;1.000000;1.000000;1.000000;,
192;1.000000;1.000000;1.000000;1.000000;,
193;1.000000;1.000000;1.000000;1.000000;,
194;1.000000;1.000000;1.000000;1.000000;,
195;1.000000;1.000000;1.000000;1.000000;,
196;1.000000;1.000000;1.000000;1.000000;,
197;1.000000;1.000000;1.000000;1.000000;,
198;1.000000;1.000000;1.000000;1.000000;,
199;1.000000;1.000000;1.000000;1.000000;,
200;1.000000;1.000000;1.000000;1.000000;,
201;1.000000;1.000000;1.000000;1.000000;,
202;1.000000;1.000000;1.000000;1.000000;,
203;1.000000;1.000000;1.000000;1.000000;,
204;1.000000;1.000000;1.000000;1.000000;,
205;1.000000;1.000000;1.000000;1.000000;,
206;1.000000;1.000000;1.000000;1.000000;,
207;1.000000;1.000000;1.000000;1.000000;,
208;1.000000;1.000000;1.000000;1.000000;,
209;1.000000;1.000000;1.000000;1.000000;,
210;1.000000;1.000000;1.000000;1.000000;,
211;1.000000;1.000000;1.000000;1.000000;,
212;1.000000;1.000000;1.000000;1.000000;,
213;1.000000;1.000000;1.000000;1.000000;,
214;1.000000;1.000000;1.000000;1.000000;,
215;1.000000;1.000000;1.000000;1.000000;,
216;1.000000;1.000000;1.000000;1.000000;,
217;1.000000;1.000000;1.000000;1.000000;,
218;1.000000;1.000000;1.000000;1.000000;,
219;1.000000;1.000000;1.000000;1.000000;,
220;1.000000;1.000000;1.000000;1.000000;,
221;1.000000;1.000000;1.000000;1.000000;,
222;1.000000;1.000000;1.000000;1.000000;,
223;1.000000;1.000000;1.000000;1.000000;,
224;1.000000;1.000000;1.000000;1.000000;,
225;1.000000;1.000000;1.000000;1.000000;,
226;1.000000;1.000000;1.000000;1.000000;,
227;1.000000;1.000000;1.000000;1.000000;,
228;1.000000;1.000000;1.000000;1.000000;,
229;1.000000;1.000000;1.000000;1.000000;,
230;1.000000;1.000000;1.000000;1.000000;,
231;1.000000;1.000000;1.000000;1.000000;,
232;1.000000;1.000000;1.000000;1.000000;,
233;1.000000;1.000000;1.000000;1.000000;,
234;1.000000;1.000000;1.000000;1.000000;,
235;1.000000;1.000000;1.000000;1.000000;,
236;1.000000;1.000000;1.000000;1.000000;,
237;1.000000;1.000000;1.000000;1.000000;,
238;1.000000;1.000000;1.000000;1.000000;,
239;1.000000;1.000000;1.000000;1.000000;;
}  //End of MeshVertexColors
  }  // End of the Mesh Torus 
  }  // SI End of the Object Torus 
}  // End of the Root Frame
