#include "gdi_client_dc.h"

grafeex::gdi::client_dc::client_dc(hwnd_type owner)
	: base_type(::GetDC(owner)), owner_(owner){}

grafeex::gdi::client_dc::~client_dc(){
	if (value_ != nullptr)
		::ReleaseDC(owner_, value_);
}
