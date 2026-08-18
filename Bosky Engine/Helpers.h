#pragma once
#include "pch.h"

namespace Helpers {

	  void ThrowIfFailed(HRESULT hr);
	
	  std::wstring GetHresultErrorMessage(HRESULT hr);

};