/*
texture0: 文字のテクスチャ（フォントのビットマップ） です。 
outlineColor: 縁取りの色です。
outlineThickness: 縁取りの太さです。
fragTexCoord: 現在のピクセルのテクスチャ座標です。
fragColor: 現在のピクセルの色です。
texture(texture0, fragTexCoord).a: 現在のピクセルのアルファ値を取得します。 
textureSize(texture0, 0): テクスチャのサイズを取得します。
outlineAlpha: 縁取りのアルファ値を計算します。周囲のピクセルのアルファ値を調べ、 最も高い値を採用します。 
if (outlineAlpha > alpha): 縁取りのアルファ値が現在のピクセルのアルファ値より高い場合、 縁取りを描画します。 
finalColor = outlineColor;: 縁取りの色を設定します。
finalColor = texture(texture0, fragTexCoord) * fragColor;: 文字本体の色を設定します。
*/
/*
シェーダーの適用範囲: BeginShaderMode() と EndShaderMode() の間で描画されたものにシェーダーが適用されます。 
シェーダーのuniform変数: シェーダーのuniform変数は、C++ コードから値を設定できます。 
テクスチャサイズ: シェーダーコードでは、テクスチャサイズを取得して、 ピクセル単位でずらすようにしています。  応用
縁取りの色を変える: outlineColor を変更することで、黒以外の色で縁取りを施すことができます。 
縁取りの太さを変える: outlineThickness を変更することで、縁取りの太さを調整できます。 
*/

#include "raylib.h"

int main(void) {
    // ウィンドウの初期化
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib - Text with Outline (Shader)");

    // シェーダーの読み込み
    Shader shader = LoadShader(0, "outline.fs");

    // シェーダーのuniform変数のロケーションを取得
    int outlineColorLoc = GetShaderLocation(shader, "outlineColor");
    int outlineThicknessLoc = GetShaderLocation(shader, "outlineThickness");

    // 縁取りの色と太さを設定
    float outlineColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 黒
    float outlineThickness = 1.0f;

    // シェーダーにuniform変数を設定
    SetShaderValue(shader, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, outlineThicknessLoc, &outlineThickness, SHADER_UNIFORM_FLOAT);

    // フォントの読み込み
    Font font = LoadFont("resources/fonts/alagard.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // シェーダーを適用して描画
            BeginShaderMode(shader);
                DrawTextEx(font, "Hello, Shader Outline!", (Vector2){ 100, 100 }, 40, 2, RED);
                DrawTextEx(font, "Another Text", (Vector2){ 100, 200 }, 30, 1, BLUE);
            EndShaderMode();

        EndDrawing();
    }

    // フォントとシェーダーのアンロード
    UnloadFont(font);
    UnloadShader(shader);

    CloseWindow();

    return 0;
}