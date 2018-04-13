#pragma once

#include "border.h"
#include "insets.h"
#include "theme.h"

#include <functional>
#include <optional>
#include <utility>

namespace ag
{
	class box;

	/* Base class for UI components. */
	class component
	{
		friend class box;

	public:
		/* Parent reference type. */
		using parent_ref = std::reference_wrapper<box>;

		/* Type of this component's style struct. */
		struct style_type
		{
			/* Style property. */
			template <typename T>
			struct prop : std::function<T ()>
			{
				using std::function<T ()>::function;

				/* Initialize this property with the given value. */
				template <typename ... Args>
				prop(Args && ... args): prop{[v = T(std::forward<Args>(args)...)] { return v; }}
				{}
			};

			/* Visibility flag. */
			prop<bool> visible{true};

			/* Position coordinates. */
			prop<float> x{0.0f}, y{0.0f};

			/* Dimensions. */
			prop<float> width{0.0f}, height{0.0f};

			/* Corners' radius. */
			prop<float> radius{0.0f};
			
			/* Background color. */
			prop<color> bg_color{color{}};

			/* Margin. */
			prop<insets> margin{0.0f};

			/* Border. */
			prop<border> border{::ag::border{}};

			/* Padding. */
			prop<insets> padding{0.0f};

			/* Text font. */
			prop<font> text_font{get_theme().text_font()};

			/* Text color. */
			prop<color> text_color{get_theme().text_color()};

			/* Text alignment. */
			prop<font::alignment> text_align{font::alignment::left};

			/* Line height. */
			prop<float> line_height{get_theme().line_height()};
		};

		/* Destructor. */
		virtual ~component() = default;
		
		/* Get this component's style. */
		virtual style_type &style() = 0;

		/* Get this component's style. */
		virtual const style_type &style() const = 0;

		/* Draw this component on the screen. */
		virtual void draw() const;

		/* Get parent of this component. */
		const std::optional<parent_ref> &parent() const;

		/* Get width of this component. */
		float width() const;

		/* Get height of this component. */
		float height() const;

		/* Hide this component. */
		component &hide();

		/* Show this component. */
		component &show();

	private:
		/* Parent of this component. */
		std::optional<parent_ref> parent_;
	};
}
