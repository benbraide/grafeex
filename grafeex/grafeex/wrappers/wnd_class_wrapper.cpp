#include "wnd_class_wrapper.h"

grafeex::wrappers::wnd_class::wnd_class()
	: base_type(value_type{ sizeof(value_type) }), id_(0){}

grafeex::wrappers::wnd_class::~wnd_class(){
	destroy();
}

grafeex::wrappers::wnd_class::operator const wchar_t *() const{
	return name_.c_str();
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::name(const std::wstring &value){
	if (!is_created())
		value_.lpszClassName = (name_ = value).c_str();
	return *this;
}

const std::wstring &grafeex::wrappers::wnd_class::name() const{
	return name_;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::styles(styles_type value){
	if (!is_created())
		value_.style = value;
	return *this;
}

grafeex::wrappers::wnd_class::styles_type grafeex::wrappers::wnd_class::styles() const{
	return value_.style;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::procedure(procedure_type value){
	if (!is_created())
		value_.lpfnWndProc = value;
	return *this;
}

grafeex::wrappers::wnd_class::procedure_type grafeex::wrappers::wnd_class::procedure() const{
	return value_.lpfnWndProc;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::instance(instance_type value){
	if (!is_created())
		value_.hInstance = value;
	return *this;
}

grafeex::wrappers::wnd_class::instance_type grafeex::wrappers::wnd_class::instance() const{
	return value_.hInstance;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::background_brush(brush_type value){
	if (!is_created())
		value_.hbrBackground = value;
	return *this;
}

grafeex::wrappers::wnd_class::brush_type grafeex::wrappers::wnd_class::background_brush() const{
	return value_.hbrBackground;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::cursor(cursor_type value){
	if (!is_created())
		value_.hCursor = value;
	return *this;
}

grafeex::wrappers::wnd_class::cursor_type grafeex::wrappers::wnd_class::cursor() const{
	return value_.hCursor;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::icon(icon_type value){
	if (!is_created())
		value_.hIcon = value;
	return *this;
}

grafeex::wrappers::wnd_class::icon_type grafeex::wrappers::wnd_class::icon() const{
	return value_.hIcon;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::small_icon(icon_type value){
	if (!is_created())
		value_.hIconSm = value;
	return *this;
}

grafeex::wrappers::wnd_class::icon_type grafeex::wrappers::wnd_class::small_icon() const{
	return value_.hIconSm;
}

grafeex::wrappers::wnd_class &grafeex::wrappers::wnd_class::menu(const std::wstring &value){
	if (!is_created())
		value_.lpszClassName = (menu_ = value).c_str();
	return *this;
}

const std::wstring &grafeex::wrappers::wnd_class::menu() const{
	return menu_;
}

bool grafeex::wrappers::wnd_class::create(){
	return (id_ == static_cast<id_type>(0) && (id_ = ::RegisterClassExW(&value_)) != static_cast<id_type>(0));
}

bool grafeex::wrappers::wnd_class::destroy(){
	if (id_ != static_cast<id_type>(0) && ::UnregisterClassW(value_.lpszClassName, value_.hInstance) != FALSE){
		id_ = 0;
		value_ = value_type{ sizeof(value_type) };
	}

	return (id_ == static_cast<id_type>(0));
}

bool grafeex::wrappers::wnd_class::is_created() const{
	return (id_ != static_cast<id_type>(0));
}
