#pragma once

#ifndef GRAFEEX_CONTROL_STYLES_H
#define GRAFEEX_CONTROL_STYLES_H

#include "../window/window_style.h"

namespace grafeex{
	namespace window{
		namespace controls{
			class button_style : public window::style{
			public:
				typedef window::style base_type;
				typedef window::object object_type;

				enum class alignment_type : dword_type{
					nil				= 0,
					left			= BS_LEFT,
					center			= BS_CENTER,
					top				= BS_TOP,
					right			= BS_RIGHT,
					vcenter			= BS_VCENTER,
					bottom			= BS_BOTTOM,
				};

				explicit button_style(object_type &object);

				virtual ~button_style();

				button_style &flat(bool enabled);

				bool flat() const;

				button_style &multi_line(bool enabled);

				bool multi_line() const;

				button_style &text_alignment(alignment_type value);

				alignment_type text_alignment() const;
			};

			GRAFEEX_MAKE_OPERATORS(button_style::alignment_type)
		}
	}
}

#endif /* !GRAFEEX_CONTROL_STYLES_H */
