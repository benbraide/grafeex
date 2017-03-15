#include "hnd_wrapper.h"

grafeex::wrappers::hnd::hnd(value_type value)
	: base_type(value){}

bool grafeex::wrappers::hnd::create(const create_info_type &info, hnd parent){
	return ((value_ = ::CreateWindowExW(
		info.dwExStyle,
		info.lpszClass,
		info.lpszName,
		info.style,
		info.x,
		info.y,
		info.cx,
		info.cy,
		parent,
		info.hMenu,
		info.hInstance,
		info.lpCreateParams
	)) != nullptr);
}

bool grafeex::wrappers::hnd::destroy(){
	return (::DestroyWindow(value_) != FALSE);
}

bool grafeex::wrappers::hnd::invalidate(const rect_type &rect, bool erase){
	return (::InvalidateRect(value_, rect, erase ? TRUE : FALSE) != FALSE);
}

bool grafeex::wrappers::hnd::validate(const rect_type &rect){
	return (::ValidateRect(value_, rect) != FALSE);
}

bool grafeex::wrappers::hnd::minimize(){
	return (::CloseWindow(value_) != FALSE);
}

bool grafeex::wrappers::hnd::show(show_mode mode){
	return (::ShowWindow(value_, static_cast<int>(mode)) != FALSE);
}

bool grafeex::wrappers::hnd::show_asyn(show_mode mode){
	return (::ShowWindowAsync(value_, static_cast<int>(mode)) != FALSE);
}

bool grafeex::wrappers::hnd::restore_minimized(){
	return (::OpenIcon(value_) != FALSE);
}

bool grafeex::wrappers::hnd::move(const point_type &offset, const size_type &size, bool repaint){
	return (::MoveWindow(value_, offset.get_x(), offset.get_y(), size.get_width(), size.get_height(), repaint ? TRUE : FALSE) != FALSE);
}

bool grafeex::wrappers::hnd::position(const point_type &offset, const size_type &size, position_type type, hnd after){
	return (::SetWindowPos(value_, after, offset.get_x(), offset.get_y(), size.get_width(), size.get_height(),
		static_cast<uint_type>(type)) != FALSE);
}

bool grafeex::wrappers::hnd::place(const placement_info_type &info){
	return (::SetWindowPlacement(value_, &info) != FALSE);
}

bool grafeex::wrappers::hnd::bring_to_top(){
	return (::BringWindowToTop(value_) != FALSE);
}

bool grafeex::wrappers::hnd::update(){
	return (::UpdateWindow(value_) != FALSE);
}

bool grafeex::wrappers::hnd::switch_to_this(bool cause_is_alt_tab){
	::SwitchToThisWindow(value_, cause_is_alt_tab ? TRUE : FALSE);
	return true;
}

grafeex::wrappers::hnd grafeex::wrappers::hnd::activate(){
	return ::SetActiveWindow(value_);
}

bool grafeex::wrappers::hnd::draw_menu_bar(){
	return (::DrawMenuBar(value_) != FALSE);
}

bool grafeex::wrappers::hnd::set_as_foreground(){
	return (::SetForegroundWindow(value_) != FALSE);
}

bool grafeex::wrappers::hnd::set_layered_attributes(const color_type &color, layered_attributes_option options){
	return (::SetLayeredWindowAttributes(value_, color.rgb(), color.alpha(), static_cast<dword_type>(options)) != FALSE);
}

grafeex::wrappers::hnd grafeex::wrappers::hnd::set_parent(hnd parent){
	return ::SetParent(value_, parent);
}

bool grafeex::wrappers::hnd::set_text(const std::wstring &value){
	return (::SetWindowTextW(value_, value.c_str()) != FALSE);
}

grafeex::wrappers::hnd grafeex::wrappers::hnd::get_parent() const{
	return ::GetParent(value_);
}

std::wstring grafeex::wrappers::hnd::get_text() const{
	std::wstring value;

	value.resize(get_text_length());
	if (::GetWindowTextW(value_, const_cast<wchar_t *>(value.c_str()), static_cast<int>(value.size())) == FALSE)
		return L"";

	return value;
}

int grafeex::wrappers::hnd::get_text_length() const{
	return ::GetWindowTextLengthW(value_);
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::get_update_rect() const{
	rect_type value;
	::GetUpdateRect(value_, value, false);
	return value;
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::get_rect() const{
	rect_type value;
	::GetWindowRect(value_, value);
	return value;
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::get_client_rect() const{
	rect_type value;
	::GetClientRect(value_, value);
	return value;
}

grafeex::wrappers::hnd::point_type grafeex::wrappers::hnd::client_to_screen(point_type value) const{
	::ClientToScreen(value_, value);
	return value;
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::client_to_screen(rect_type value) const{
	return rect_type{ client_to_screen(value.get_top_left()), client_to_screen(value.get_bottom_right()) };
}

grafeex::wrappers::hnd::point_type grafeex::wrappers::hnd::screen_to_client(point_type value) const{
	::ScreenToClient(value_, value);
	return value;
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::screen_to_client(rect_type value) const{
	return rect_type{ screen_to_client(value.get_top_left()), screen_to_client(value.get_bottom_right()) };
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::adjust_rect(const rect_type &value) const{
	return adjust_rect(value, get_data<dword_type>(data_index::styles),
		get_data<dword_type>(data_index::extended_styles), ::GetMenu(value_) != nullptr);
}

bool grafeex::wrappers::hnd::is_visible() const{
	return (::IsWindowVisible(value_) != FALSE);
}

bool grafeex::wrappers::hnd::is_maximized() const{
	return (::IsZoomed(value_) != FALSE);
}

bool grafeex::wrappers::hnd::is_minimized() const{
	return (::IsIconic(value_) != FALSE);
}

bool grafeex::wrappers::hnd::is_frozen() const{
	return (::IsHungAppWindow(value_) != FALSE);
}

bool grafeex::wrappers::hnd::is_foreground() const{
	return (::GetForegroundWindow() == value_);
}

grafeex::wrappers::hnd grafeex::wrappers::hnd::get_active(){
	return ::GetActiveWindow();
}

grafeex::wrappers::hnd::rect_type grafeex::wrappers::hnd::adjust_rect(rect_type value, dword_type styles, dword_type extended_styles, bool has_menu){
	::AdjustWindowRectEx(value, styles, has_menu ? TRUE : FALSE, extended_styles);
	return value;
}
