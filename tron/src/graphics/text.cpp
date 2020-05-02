#include "text.hpp"

Text::Text(const std::string& font, int size)
{

    // Zustände in OpenGL vorbereiten um Zeichen darstellen zu können.
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialisierung der FreeType Library für das Laden von Fonts
    FT_Init_FreeType(&m_lib);
    FT_New_Face(m_lib, font.c_str(), 0, &m_face);
    FT_Set_Pixel_Sizes(m_face, 0, static_cast<FT_UInt>(size));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Anhand der FreeType Library werden alle 128 Zeichen geladen und einem Bild zugeordnet.
    for (unsigned char i = 0; i < s_charset; i++)
    {
        if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
        {
            continue;
        }

        unsigned int    w = m_face->glyph->bitmap.width;
        unsigned int    h = m_face->glyph->bitmap.rows;
        unsigned int    l = m_face->glyph->bitmap_left;
        unsigned int    t = m_face->glyph->bitmap_top;
        unsigned char*  b = m_face->glyph->bitmap.buffer;

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, b);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character c{ texture, glm::ivec2{ w, h }, glm::ivec2{ l, t}, m_face->glyph->advance.x };
        m_chars.insert(std::pair<char, Character>{ i, c });
    }

    // OpenGL aufbereitung der Grafikkarte um alle Zeichen darstellen zu können
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_lib);

    glGenVertexArrays(1, &m_arr);
    glGenBuffers(1, &m_buff);
    glBindVertexArray(m_arr);
    glBindBuffer(GL_ARRAY_BUFFER, m_buff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s_vertices * s_floats, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, s_floats * sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, s_floats * sizeof(float), (const void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::draw(const std::string& text, float x, float y)
{
    // Zugriff auf den Speicher der Grafikkarte um den Text dort hinzuzufügen und auf dem Bildschirm darzustellen.
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_arr);

    // Geht die Zeichenkette durch und zeichnet die dazugehörigen Zeichen
    for (auto i = text.begin(); i != text.end(); ++i)
    {
        Character c = m_chars[*i];
        float px = x + c.offset.x;
        float py = y - (c.size.y - c.offset.y);
        float w = c.size.x;
        float h = c.size.y;

        float vertices[s_vertices][s_floats]
        {
            px,     py + h, 0.0f, 0.0f,
            px,     py,     0.0f, 1.0f,
            px + w, py,     1.0f, 1.0f,

            px,     py + h, 0.0f, 0.0f,
            px + w, py,     1.0f, 1.0f,
            px + w, py + h, 1.0f, 0.0f
        };
        glBindTexture(GL_TEXTURE_2D, c.id);
        glBindBuffer(GL_ARRAY_BUFFER, m_buff);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (c.advance >> 6); 
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
