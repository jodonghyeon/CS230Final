/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.cpp
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    May 8, 2024
*/

#include "Font.h"
#include "Engine.h"

CS230::Font::Font(const std::filesystem::path& file_name) : texture(file_name) {
    const unsigned int white = 0xFFFFFFFF;

    original_image = LoadImage(file_name.string().c_str());

    //The top left pixel MUST be white (0xFFFFFFFF)
    unsigned int color = GetPixel({ 0, 0 });
    if (color == white) {
        FindCharRects();
    }
    else {
        Engine::GetLogger().LogError("Font " + file_name.string() + " could not be loaded");
        return;
    }
    UnloadImage(original_image);
}

CS230::Texture* CS230::Font::PrintToTexture(const std::string& text, unsigned int color) {
    const Math::ivec2 text_size = MeasureText(text);
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.StartRenderTextureMode(text_size.x, text_size.y);
    Math::TransformationMatrix matrix;
    for (const char c : text) {
        DrawChar(matrix, c, color);
    }
    return texture_manager.EndRenderTextureMode();
}


void CS230::Font::FindCharRects() {
    unsigned int check_color = GetPixel({ 0, 0 });
    unsigned int next_color;

    int height = texture.GetSize().y;

    int x = 1;
    for (int index = 0; index < num_chars; index++) {
        int width = 0;

        do {
            width++;
            next_color = GetPixel({ x + width, 0 });
        } while (check_color == next_color);

        check_color = next_color;

        char_rects[index].point_1 = { x + width - 1, 1 };
        char_rects[index].point_2 = { x, char_rects[index].point_1.y + height - 1 };
        x += width;
    }
}

Math::irect& CS230::Font::GetCharRect(char c) {
    if (c >= ' ' && c <= 'z') {
        return char_rects[c - ' '];
    }
    else {
        Engine::GetLogger().LogError("Char '" + std::to_string(c) + "' not found");
        return char_rects[0];
    }
}

Math::ivec2 CS230::Font::MeasureText(std::string text)
{
    Math::ivec2 char_rect = { 0,0 };
    for (int index = 0; index < text.length(); ++index)
    {
        Math::ivec2 temp_char_rect = GetCharRect(text[index]).Size();
        char_rect.x += temp_char_rect.x;
        char_rect.y = (char_rect.y >= temp_char_rect.y) ? char_rect.y : temp_char_rect.y;
    }
    return char_rect;
}

void CS230::Font::DrawChar(Math::TransformationMatrix& matrix, char c, unsigned int color) {
    const Math::irect& display_rect = GetCharRect(c);
    const Math::ivec2 top_left_texel = { display_rect.point_2.x, display_rect.point_1.y };
    if (c != ' ') {
        const auto to_center = Math::TranslationMatrix(Math::vec2(-display_rect.Size().x / 2.0, -display_rect.Size().y / 2.0));
        const auto flip = Math::ScaleMatrix(Math::vec2{ 1, -1 });
        const auto to_bottomleft = Math::TranslationMatrix(Math::vec2(display_rect.Size().x / 2.0, display_rect.Size().y / 2.0));
        const auto flip_quad = to_bottomleft * flip * to_center;
        texture.Draw(matrix * flip_quad, top_left_texel, display_rect.Size(), color);
    }
    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}

unsigned int CS230::Font::GetPixel(Math::ivec2 texel) {
    Color raylib_color = GetImageColor(original_image, texel.x, texel.y);
    unsigned int color = ((static_cast<unsigned int>(raylib_color.r) << 24) & 0xFF000000) |
        ((static_cast<unsigned int>(raylib_color.g) << 16) & 0x00FF0000) |
        ((static_cast<unsigned int>(raylib_color.b) << 8) & 0x0000FF00) |
        ((static_cast<unsigned int>(raylib_color.a) << 0) & 0x000000FF);
    return color;
}
