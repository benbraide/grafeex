#pragma once

#ifndef GRAFEEX_GUI_GRID_MEMBER_H
#define GRAFEEX_GUI_GRID_MEMBER_H

namespace grafeex{
	namespace gui{
		class grid_member{
		public:
			virtual ~grid_member() = default;

			virtual void refresh() = 0;
		};
	}
}

#endif /* !GRAFEEX_GUI_GRID_MEMBER_H */
