#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>
#include <Atom/Graphics/Color.hpp>
#include <Atom/Graphics/Text/Label.hpp>

namespace atom
{
	Label::Label(const std::string &text, const float x, const float y,
		const Color &color, Font* font) : m_Font(font)
	{
		m_Text = text;
		m_Position = Vector3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string &text, const float x, const float y,
		const Color &color, const std::string& font) : m_Font(FontManager::Get(font))
	{
		m_Text = text;
		m_Position = Vector3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string &text, const float x, const float y,
		const Color &color, const std::string& font, unsigned int size) : m_Font(FontManager::Get(font, size))
	{
		m_Text = text;
		m_Position = Vector3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawString(this);
	}

	void Label::SetText(const std::string &text)
	{
		m_Text = text;
	}

	void Label::SetPosition(const Vector3 &pos)
	{
		m_Position = pos;
	}

	void Label::SetPosition(const float x, const float y)
	{
		m_Position.x = x;
		m_Position.y = y;
	}
}
