#include "window_manager.h"
#include "application_object.h"

#include "../window/message_window.h"
#include "../window/modal_dialog_window.h"
#include "../controls/control_object.h"

grafeex::application::window_manager::window_manager(object &app_instance)
	: active_dialog_(nullptr), recent_owner_(nullptr){
	typedef std::wstring::size_type size_type;

	common::random_string random_string;
	::GetClassInfoExW(nullptr, WC_DIALOG, dialog_class_);

	auto instance = (window_manager::app_instance = &app_instance)->instance_;
	if (instance == nullptr)
		instance = ::GetModuleHandleW(nullptr);

	dialog_class_.styles(dialog_class_.styles() | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS);
	dialog_class_.procedure(window_manager::entry_);
	dialog_class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));
	dialog_class_.instance(instance);
	dialog_class_.create();

	class_.procedure(window_manager::entry_);
	if (class_.name().empty())//Use a random string
		class_.name(random_string.generate_alnum(std::make_pair<size_type, size_type>(9, 18)));

	if (class_.cursor() == nullptr)
		class_.cursor(dialog_class_.cursor());

	class_.instance(instance);
	class_.create();

	msg_hook_value_ = ::SetWindowsHookExW(WH_GETMESSAGE, msg_hook_, nullptr, app_instance.id_);
}

grafeex::application::window_manager::~window_manager(){
	::UnhookWindowsHookEx(msg_hook_value_);
}

void grafeex::application::window_manager::on_nc_create(window_type &target, const hwnd_type &owner){
	target.value_ = owner;
	target.initialize_();
}

void grafeex::application::window_manager::on_create(window_type &target){
	auto is_control = (dynamic_cast<window::controls::object *>(&target) != nullptr);
	auto is_message = (!is_control && dynamic_cast<window::message *>(&target) != nullptr);

	lock_.lock();
	windows_.push_back(target);

	if (target.parent() == nullptr && (!is_control && !is_message))//Add to top level list
		top_level_windows_.push_back(target);

	lock_.unlock();
}

void grafeex::application::window_manager::on_nc_destroy(window_type &target){
	hwnd_type target_value = target;

	target.uninitialize_();
	target.reset_persistent_styles_();

	target.system_menu_ = nullptr;
	target.menu_ = nullptr;//Destroy menu
	target.value_ = nullptr;//Reset
	target.renderer_ = nullptr;//Release renderer
	target.mouse_state_.object_info_.parent = nullptr;

	lock_.lock();
	if (target.parent() == nullptr){
		auto entry = std::find(top_level_windows_.begin(), top_level_windows_.end(), target_value);
		if (entry != top_level_windows_.end())//Remove from top level list
			top_level_windows_.erase(entry);

		entry = std::find(windows_.begin(), windows_.end(), target_value);
		if (entry != windows_.end())//Remove from list
			windows_.erase(entry);
	}

	if (active_dialog_ == &target)
		active_dialog_ = nullptr;

	lock_.unlock();
	if (true){
		auto tree_parent = dynamic_cast<gui::object_tree *>(target.parent());
		if (tree_parent != nullptr)//Remove from parent
			tree_parent->remove(target);
	}
}

void grafeex::application::window_manager::on_close(window_type &target){
	auto dialog = dynamic_cast<window::dialog *>(&target);
	if (dialog != nullptr){
		if (dialog->is_modal()){//Complete in different thread
			app_instance->pool_.add([dialog]{
				dialog->end();//Cancel modal if applicable
				dialog->destroy();//Destroy dialog
			});
		}
		else//Destroy dialog
			dialog->destroy();
	}
}

void grafeex::application::window_manager::on_changed_position(window_type &target, uint_type flags){
	if (!GRAFEEX_IS(flags, SWP_NOSIZE))
		target.sized_();

	if (!GRAFEEX_IS(flags, SWP_NOMOVE))
		target.moved_();
}

void grafeex::application::window_manager::focus(window_type &target){
	if (!target.is_dialog()){
		auto dialog_parent = target.get_dialog_parent_();
		if (dialog_parent != nullptr)
			active_dialog_ = dialog_parent;
	}
	else//Object is dialog
		active_dialog_ = &target;
}

void grafeex::application::window_manager::blur(window_type &target){
	if (active_dialog_ != nullptr && active_dialog_ != &target){
		if (active_dialog_ == target.get_dialog_parent_())
			active_dialog_ = nullptr;
	}
	else if (active_dialog_ != nullptr)//Object is dialog
		active_dialog_ = nullptr;
}

bool grafeex::application::window_manager::flash(window_type &target, beep_type beep, uint_type count) const{
	return (::MessageBeep(static_cast<uint_type>(beep)) != FALSE && flash_only(target, count));
}

bool grafeex::application::window_manager::flash_only(window_type &target, uint_type count) const{
	app_instance->pool_.add([this, &target, count]{
		flash_info_type info{
			sizeof(flash_info_type),
			target,
			FLASHW_CAPTION,
			1,
			50
		};

		auto was_active = false;
		for (auto i = 0u; i < (count * 2); ++i){
			was_active = (::FlashWindowEx(&info) != FALSE);
			::Sleep(50);
		}

		if (was_active)
			::FlashWindowEx(&info);
	});

	return true;
}

bool grafeex::application::window_manager::modal_consume(const msg_type &msg, window_type &target) const{
	auto owner = msg.owner().get_owner();
	if (owner == nullptr)//Consume
		return true;

	if (owner == &target || is_ancestor(*owner, target))
		return false;//Pass message to target or offspring

	switch (msg.code()){
	case WM_NCLBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEACTIVATE:
		if (is_related(*owner, target))
			flash(target, beep_type::warning, 10);
		break;
	case WM_NCHITTEST:
		return false;
	default:
		break;
	}
	
	return true;
}

bool grafeex::application::window_manager::modal_consume(const msg_type &msg) const{
	auto modal_loop = dynamic_cast<threading::modal_loop *>(app_instance->pump);
	return (modal_loop == nullptr) ? false : modal_consume(msg, *modal_loop->modal_dialog_);
}

bool grafeex::application::window_manager::is_ancestor(const window_type &offspring, const window_type &ancestor) const{
	if (&offspring == &ancestor)
		return false;

	auto parent = offspring.parent();
	while (parent != nullptr && parent != &ancestor)
		parent = parent->parent();

	return (parent != nullptr);
}

bool grafeex::application::window_manager::is_related(const window_type &target, const window_type &with) const{
	if (&target == &with)
		return true;

	auto target_top_ancestor = top_ancestor(target);
	return (target_top_ancestor != nullptr && target_top_ancestor == top_ancestor(with));
}

grafeex::application::window_manager::window_type *grafeex::application::window_manager::top_ancestor(const window_type &target) const{
	auto parent = target.parent(), valid_parent = parent;
	while (parent != nullptr){
		valid_parent = parent;
		parent = parent->parent();
	}

	if (valid_parent == nullptr)
		return const_cast<window_type *>(&target);

	return dynamic_cast<window_type *>(valid_parent);
}

grafeex::application::window_manager *grafeex::application::window_manager::instance = nullptr;
grafeex::application::object *grafeex::application::window_manager::app_instance = nullptr;

grafeex::application::window_manager::hwnd_type grafeex::application::window_manager::create_(
	window_type &owner, const create_info_type &info){
	auto hook = ::SetWindowsHookExW(WH_CBT, hook_, nullptr, app_instance->id_);//Install hook to intercept window creation

	auto &target_default_class = (dynamic_cast<window::dialog *>(&owner) != nullptr) ? dialog_class_ : class_;
	auto target_class = (info.lpszClass == nullptr) ? target_default_class.operator const wchar_t *() : info.lpszClass;

	auto value = ::CreateWindowExW(
		info.dwExStyle,
		target_class,
		info.lpszName,
		info.style,
		info.x,
		info.y,
		info.cx,
		info.cy,
		info.hwndParent,
		info.hMenu,
		(info.hInstance == nullptr) ? app_instance->instance_ : info.hInstance,
		recent_owner_ = reinterpret_cast<void *>(&owner)
	);

	::UnhookWindowsHookEx(hook);//Uninstall hook
	return value;
}

grafeex::application::window_manager::result_type CALLBACK grafeex::application::window_manager::entry_(
	hwnd_type::value_type window_handle, uint_type msg, wparam_type wparam, lparam_type lparam){
	auto target = hwnd_type(window_handle).get_owner();
	if (target == nullptr){//Unidentified window
		if (app_instance->pump->cache_.code() == msg)
			app_instance->pump->status_.is_posted = false;

		return ::CallWindowProcW(::DefWindowProcW, window_handle, msg, wparam, lparam);
	}

	auto is_sent = !app_instance->pump->status_.is_posted;
	if (is_sent || app_instance->pump->cache_.code() != msg){//Sent on same thread
		msg_type msg_object(msg_type::value_type{//Populate message
			window_handle,
			msg,
			wparam,
			lparam,
			0,
			point_type{ -1 }
		});

		if (instance->modal_consume(msg_object))
			return 0;

		return app_instance->dispatch_(msg_object, is_sent, *target);
	}

	app_instance->pump->status_.is_posted = false;
	if (instance->modal_consume(app_instance->pump->cache_))
		return 0;

	return app_instance->dispatch_(app_instance->pump->cache_, is_sent, *target);
}

grafeex::application::window_manager::result_type CALLBACK grafeex::application::window_manager::hook_(int code, wparam_type wparam, lparam_type lparam){
	if (code == HCBT_CREATEWND){//Respond to window creation
		auto info = reinterpret_cast<create_hook_info_type *>(lparam)->lpcs;
		if (instance->recent_owner_ != nullptr && info->lpCreateParams == instance->recent_owner_){//Ensure target is valid
			auto owner_window = reinterpret_cast<window_type *>(instance->recent_owner_);
			hwnd_type target_hwnd(reinterpret_cast<hwnd_type::value_type>(wparam));

			target_hwnd.set_data(owner_window);//Store window object in handle
			if (dynamic_cast<window::controls::object *>(owner_window) != nullptr)//Replace window procedure
				target_hwnd.set_data<procedure_type>(&window_manager::entry_, hwnd_type::data_index::procedure);

			instance->recent_owner_ = nullptr;//Reset
		}
	}

	return ::CallNextHookEx(nullptr, code, wparam, lparam);
}

grafeex::application::window_manager::result_type CALLBACK grafeex::application::window_manager::msg_hook_(int code, wparam_type wparam, lparam_type lparam){
	if (code == HC_ACTION && wparam == PM_REMOVE)
		app_instance->status_.is_posted = true;

	return ::CallNextHookEx(nullptr, code, wparam, lparam);
}
