#include "stock_gdi_object.h"

grafeex::gdi::shared_object grafeex::gdi::stock_object::get(int index){
	return GetStockObject(index);
}

grafeex::gdi::shared_object grafeex::gdi::stock_object::get(index index){
	return get(static_cast<int>(index));
}
