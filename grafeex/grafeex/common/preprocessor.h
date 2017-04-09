#pragma once

#ifndef GRAFEEX_PREPROCESSOR_H
#define GRAFEEX_PREPROCESSOR_H

#define GRAFEEX_MAKE_OPERATORS_(x, t)\
	inline constexpr x operator |(x l, x r){\
		return (x)((t)(l) | (t)(r));\
	}\
\
	inline constexpr x operator &(x l, x r){\
		return (x)((t)(l) & (t)(r));\
	}\
\
	inline constexpr x operator ~(x r){\
		return (x)(~(t)(r));\
	}\
\
	inline x operator |=(x &l, x r){\
		return (l = (x)((t)(l) | (t)(r)));\
	}\
\
	inline x operator &=(x &l, x r){\
		return (l = (x)((t)(l) & (t)(r)));\
	}\
\
	inline x operator <<(x &l, t r){\
		return (x)((t)(l) << (r));\
	}\
\
	inline x operator >>(x &l, t r){\
		return (x)((t)(l) >> (r));\
	}

#define GRAFEEX_MAKE_OPERATORS(x) GRAFEEX_MAKE_OPERATORS_(x, unsigned int)

#define GRAFEEX_MAKE_OPERATORS_EX(x) GRAFEEX_MAKE_OPERATORS_(x, unsigned long long)

#ifndef MAKEDWORD
#define MAKEDWORD(l, h) ((::DWORD)MAKELONG(l, h))
#endif // !MAKEDWORD


#ifndef RGBA
#define RGBA(r, g, b, a) ((::COLORREF)( (((::DWORD)(::BYTE)(a)) << 24) | RGB(r, g, b) ))
#endif // !RGBA

#define GetAValue(rgba) (LOBYTE((rgba) >> 24))

#define GRAFEEX_MAKE_DIALOG_TEMPLATE(s, es, cls, t) { (s), (es), 0, 0, 0, 0, 0, L"", (cls), (t) }
#define GRAFEEX_MAKE_DIALOG_TEMPLATE2(s, es, t) GRAFEEX_MAKE_DIALOG_TEMPLATE((s), (es), nullptr_t, (t))

#define GRAFEEX_MAKE_MOUSE_POSITION(value) { GET_X_LPARAM(value), GET_Y_LPARAM(value) }
#define GRAFEEX_SPLIT_WORD(value) { LOWORD(value), HIWORD(value) }

#define GRAFEEX_SET(source, target) ((source) |= (target))
#define GRAFEEX_REMOVE(source, target) ((source) &= ~(target))

#define GRAFEEX_SET_V(source, target) ((source) | (target))
#define GRAFEEX_REMOVE_V(source, target) ((source) & ~(target))

#define GRAFEEX_IS(source, target) (((source) & (target)) == (target))
#define GRAFEEX_IS_ANY(source, target) (((source) & (target)) != static_cast<decltype(target)>(0))

#define GRAFEEX_CONVERT_ENUM_(x, t, v) (x)(t)(v)
#define GRAFEEX_CONVERT_ENUM(x, v) GRAFEEX_CONVERT_ENUM_(x, int, v)

#define GRAFEEX_EQUAL_ENUMS_(x, t, l, r) ((l) == (x)(t)(r))
#define GRAFEEX_EQUAL_ENUMS(x, l, r) GRAFEEX_EQUAL_ENUMS_(x, int, l, r)

#define GRAFEEX_INCREMENT_ENUM_(x, t, v) (v) = (x)((t)(v) + (t)1)
#define GRAFEEX_INCREMENT_ENUM(x, v) GRAFEEX_INCREMENT_ENUM_(x, int, v)

#define GRAFEEX_DECREMENT_ENUM_(x, t, v) (v) = (x)((t)(v) - (t)1)
#define GRAFEEX_DECREMENT_ENUM(x, v) GRAFEEX_DECREMENT_ENUM_(x, int, v)

#endif /* !GRAFEEX_PREPROCESSOR_H */
