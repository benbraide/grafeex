#pragma once

#ifndef GRAFEEX_DIALOG_TEMPLATE_H
#define GRAFEEX_DIALOG_TEMPLATE_H

#include "../common/windows_headers.h"

namespace grafeex{
	namespace structures{
		struct dialog_template{
			typedef ::WORD word_type;
			typedef ::DWORD dword_type;
			typedef ::LPCDLGTEMPLATEW native_type;

			dword_type styles;
			dword_type extended_styles;
			word_type item_count;
			short x;
			short y;
			short width;
			short height;
			const wchar_t *menu_name;
			const wchar_t *class_name;
			const wchar_t *caption;
		};
	}
}

#endif /* !GRAFEEX_DIALOG_TEMPLATE_H */
