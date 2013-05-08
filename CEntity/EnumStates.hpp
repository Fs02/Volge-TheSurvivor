#pragma once
#include "../stdafx.h"

namespace STATE
{
	enum {
			IDLE		= 1,
			STEADY		= 1 << 1,
			FORWARD		= 1 << 2,
			BACKWARD	= 1 << 3,
			LEFT		= 1 << 4,
			RIGHT		= 1 << 5,
			ATTACK		= 1 << 6,
			RELOAD		= 1 << 7, 
			THROW		= 1 << 8
	};
}