#include "control_object.h"

grafeex::window::controls::object::object(control_type type)
	: class_name_(get_class_name(type)){
	previous_procedure_ = get_procedure(class_name_.c_str());
	persistent_styles_.basic = (WS_VISIBLE | WS_TABSTOP);
	init_common_(type);
}

grafeex::window::controls::object::~object(){
	destroy();
}

grafeex::window::object::dword_type grafeex::window::controls::object::black_listed_styles(bool is_extended) const {
	return (base_type::black_listed_styles(is_extended) | (is_extended ? (WS_EX_APPWINDOW | WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME) : ~0ul));
}

grafeex::window::object::dword_type grafeex::window::controls::object::get_initializer(control_type type){
	switch (type){
	case control_type::button:
	case control_type::edit:
	case control_type::static_:
	case control_type::list_box:
	case control_type::combo_box:
	case control_type::scroll_bar:
		return ICC_STANDARD_CLASSES;
	case control_type::tool_bar:
	case control_type::status_bar:
	case control_type::track_bar:
		return ICC_BAR_CLASSES;
	case control_type::date_time_picker:
	case control_type::up_down:
		return ICC_DATE_CLASSES;
	case control_type::tab:
	case control_type::tool_tip:
		return ICC_TAB_CLASSES;
	case control_type::list_view:
	case control_type::header:
		return ICC_LISTVIEW_CLASSES;
	case control_type::tree_view:
		return ICC_TREEVIEW_CLASSES;
	case control_type::hyperlink:
		return ICC_LINK_CLASS;
	case control_type::progress:
		return ICC_PROGRESS_CLASS;
	case control_type::hot_key:
		return ICC_HOTKEY_CLASS;
	case control_type::pager:
		return ICC_PAGESCROLLER_CLASS;
	case control_type::animate:
		return ICC_ANIMATE_CLASS;
	case control_type::combo_box_ex:
		return ICC_USEREX_CLASSES;
	case control_type::ip:
		return ICC_INTERNET_CLASSES;
	case control_type::rebar:
		return ICC_COOL_CLASSES;
	case control_type::native_font:
		return ICC_NATIVEFNTCTL_CLASS;
	default:
		break;
	}

	return 0;
}

const wchar_t *grafeex::window::controls::object::get_class_name(control_type type){
	switch (type){
	case control_type::button:
		return WC_BUTTONW;
	case control_type::edit:
		return WC_EDITW;
	case control_type::static_:
		return WC_STATICW;
	case control_type::list_box:
		return WC_LISTBOXW;
	case control_type::combo_box:
		return WC_COMBOBOXW;
	case control_type::scroll_bar:
		return WC_SCROLLBARW;
	case control_type::tool_bar:
		return TOOLBARCLASSNAMEW;
	case control_type::status_bar:
		return STATUSCLASSNAMEW;
	case control_type::track_bar:
		return TRACKBAR_CLASSW;
	case control_type::date_time_picker:
		return DATETIMEPICK_CLASSW;
	case control_type::up_down:
		return UPDOWN_CLASSW;
	case control_type::tab:
		return WC_TABCONTROLW;
	case control_type::tool_tip:
		return TOOLTIPS_CLASSW;
	case control_type::list_view:
		return WC_LISTVIEWW;
	case control_type::header:
		return WC_HEADERW;
	case control_type::tree_view:
		return WC_TREEVIEWW;
	case control_type::hyperlink:
		return WC_LINK;
	case control_type::progress:
		return PROGRESS_CLASSW;
	case control_type::hot_key:
		return HOTKEY_CLASSW;
	case control_type::pager:
		return WC_PAGESCROLLERW;
	case control_type::animate:
		return ANIMATE_CLASSW;
	case control_type::combo_box_ex:
		return WC_COMBOBOXEXW;
	case control_type::ip:
		return WC_IPADDRESSW;
	case control_type::rebar:
		return REBARCLASSNAMEW;
	case control_type::native_font:
		return WC_NATIVEFONTCTLW;
	default:
		break;
	}

	return L"";
}

grafeex::window::object::procedure_type grafeex::window::controls::object::get_procedure(const wchar_t *class_name){
	wrappers::wnd_class class_object;
	::GetClassInfoExW(nullptr, class_name, class_object);
	return class_object.procedure();
}

bool grafeex::window::controls::object::init_common_(control_type type){
	auto initializer = get_initializer(type);
	if (!GRAFEEX_IS(initialized_controls_, initializer)){
		init_info_type info{
			sizeof(init_info_type),
			initializer
		};

		if (::InitCommonControlsEx(&info) == FALSE)
			return false;

		GRAFEEX_SET(initialized_controls_, initializer);
	}

	return true;
}

bool grafeex::window::controls::object::create_(const std::wstring &caption, const point_type &offset, const size_type &size,
	dword_type styles, dword_type extended_styles){
	return base_type::create_(caption, offset, size, styles, extended_styles, class_name_.c_str());
}

grafeex::window::object::dword_type grafeex::window::controls::object::initialized_controls_ = 0;
