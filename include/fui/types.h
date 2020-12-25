#pragma once

namespace fungal
{
	typedef unsigned int UINT;
	typedef unsigned long ULONG;

	struct key_event
	{
		UINT code;
		UINT ascii;
		ULONG control;
	};
}
