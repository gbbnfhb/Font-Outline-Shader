#version 330 core

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 outlineColor;
uniform float outlineThickness;

void main() {
    // 文字のアルファ値を取得
    float alpha = texture(texture0, fragTexCoord).a;

    // 縁取りのアルファ値を計算
    float outlineAlpha = 0.0;
    if (alpha == 0.0) { // 現在のピクセルが透明な場合のみ、周囲を調べる
        for (float dx = -outlineThickness; dx <= outlineThickness; dx += 1.0) {
            for (float dy = -outlineThickness; dy <= outlineThickness; dy += 1.0) {
                if (dx == 0.0 && dy == 0.0) continue;
                outlineAlpha = max(outlineAlpha, texture(texture0, fragTexCoord + vec2(dx, dy) * (1.0 / textureSize(texture0, 0))).a);
            }
        }
    }

    // 縁取りを描画
    if (outlineAlpha > 0.0 && alpha == 0.0) {
        finalColor = outlineColor;
    } else {
        // 文字本体を描画
        finalColor = texture(texture0, fragTexCoord) * fragColor;
    }
}