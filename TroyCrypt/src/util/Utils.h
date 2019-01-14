#pragma once
#include "../TroyCrypt.h"
#include <memory>
#include <string>

namespace TroyCrypt {

u64 padToStateSize(u32 stateSize, u64 dataSize);

std::unique_ptr<u8[]> padBufferToStateSize(void* buffer, u64 bufferSize, u32 stateSize);
std::unique_ptr<u8[]> padStringToStateSize(std::string& string, u32 stateSize);

void render_printable_chars(const char* buffer, size_t bufsize);
void hex_dump(const uint8_t* buffer, size_t bufsize, bool showPrintableChars = true);
void bin_dump(const uint8_t* buffer, size_t bufsize, bool showPrintableChars = true);
void string_dump(const std::string& buffer, bool showPrintableChars = true);

bool buffersEqual(u8* a, u8* b, size_t length);

}