#pragma once

#include <Atom/Graphics/Renderables/Renderable2D.hpp>
#include <Atom/Graphics/Text/Font.hpp>

namespace Atom
{
	class Label : public Renderable2D
	{
	private:
		Font* m_Font;
		std::string m_Text;

	public:
		Label(const std::string &text, const float x, const float y, const Color &color, Font* font);
		Label(const std::string &text, const float x, const float y, const Color &color, const std::string& fontname);
		Label(const std::string &text, const float x, const float y, const Color &color, const std::string& fontname, unsigned int size);

		void Submit(Renderer2D* renderer) const override;
		void SetText(const std::string &text);
		void SetPosition(const Vector3 &pos);
		void SetPosition(const float x, const float y);

		friend class Renderer2D;
	};
}
