#include "com.h"

grafeex::common::com::com(bool multi_threaded){
	::CoInitializeEx(NULL, multi_threaded ? ::COINIT::COINIT_MULTITHREADED : ::COINIT::COINIT_APARTMENTTHREADED);
}

grafeex::common::com::~com(){
	::CoUninitialize();
}
