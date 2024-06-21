#pragma once
#include "TriscelData.h"
namespace math {

	struct rect {
		unsigned int x, y;
		rect(int x, int y) {
			this->x = x;
			this->y = y;
		}
		rect(int x, int y, TriscelData& data) {
			this->x = x;
			this->y = y;
		}
	};

}