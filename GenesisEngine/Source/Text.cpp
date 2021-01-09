/*#include "Application.h"
#include "Text.h"
#include "GameObject.h"
#include "RectTransform.h"
#include "glew/include/glew.h"
#include "GnJSON.h"

#include "FontImporter.h"

Text::Text() : Component(nullptr)
{
	type = ComponentType::TEXT;
	is_UI = true;
	SetUpText();
}

Text::Text(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::TEXT;
	is_UI = true;

    ui_transform = _gameObject->GetRectTransform();

	SetUpText();
}

Text::~Text()
{
}

void Text::Update()
{
    RenderText("HOLA", 10);
}

void Text::OnEditor()
{
}

void Text::Draw()
{
    
}

void Text::Save(GnJSONArray& save_array)
{
}

void Text::Load(GnJSONObj& load_object)
{
}

void Text::SetUpText()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE_0);
    glBindVertexArray(VAO);
}

void Text::RenderText(std::string text, float scale)
{
    std::string::const_iterator c;
    glUniform3f(glGetUniformLocation(,), color.x, color.y, color.z);
    std::map<char, Character> Characters = App->fonts->GetCharachters();

    glActiveTexture(GL_TEXTURE_0);
    glBindVertexArray(VAO);

    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float3 pos = ui_transform->GetPosition();

        float xpos = pos.x + ch.Bearing.x * scale;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

*/