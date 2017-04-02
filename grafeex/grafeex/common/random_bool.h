#pragma once

#ifndef GRAFEEX_RANDOM_BOOL_H
#define GRAFEEX_RANDOM_BOOL_H

#include <random>

namespace grafeex{
	namespace common{
		template <class engine_type = std::mt19937, class seeder_type = std::random_device>
		class basic_random_bool{
		public:
			typedef engine_type engine_type;
			typedef std::uniform_int_distribution<int> distribution_type;
			typedef seeder_type seeder_type;

			explicit basic_random_bool(typename engine_type::result_type seed = (seeder_type())())
				: engine_(seed){}

			bool generate(){
				return (distribution_type(0, 1)(engine_) != 0);
			}

		private:
			engine_type engine_;
		};

		typedef basic_random_bool<> random_bool;
	}
}

#endif /* !GRAFEEX_RANDOM_BOOL_H */
