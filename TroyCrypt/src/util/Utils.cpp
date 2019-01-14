

#include "Utils.h"

#include <iostream>
#include <iomanip>
#include <cctype>
#include <excpt.h>
#include <math.h>

namespace TroyCrypt {

#define HEX_BYTES_PER_LINE 32
//Binary numbers take up 9 places instead of 3 for hex so divide by 3 so that binary numbers also fit necley on the line
#define BIN_BYTES_PER_LINE (HEX_BYTES_PER_LINE / 3)

const char DIGITS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

u64 padToStateSize(u32 stateSize, u64 dataSize)
{
	if (dataSize == 0) return 0;
	u64 largeStateSize = (u64)stateSize;
	u64 numberOfBlocks = (dataSize - 1) / largeStateSize + 1;
	std::cout << "blocks: " << numberOfBlocks << std::endl;
	return numberOfBlocks * largeStateSize;
}

std::unique_ptr<u8[]> padBufferToStateSize(void* buffer, u64 bufferSize, u32 stateSize)
{
	u64 totalSize = padToStateSize(stateSize, bufferSize);
	if (buffer == nullptr) {
		std::unique_ptr<u8[]>(new u8[totalSize]());
	}
	if (totalSize == bufferSize) {
		return std::unique_ptr<u8[]>((u8*)buffer);
	}
	u8* newBuffer = new u8[totalSize];
	memcpy(newBuffer, buffer, bufferSize);
	memset(newBuffer + bufferSize, 0x00, totalSize - bufferSize);
	return std::unique_ptr<u8[]>(newBuffer);
}

std::unique_ptr<u8[]> padStringToStateSize(std::string& string, u32 stateSize)
{
	return padBufferToStateSize((void*)string.c_str(), string.length(), stateSize);
}

void render_printable_chars(const char* buffer, size_t bufsize) {
	for (int i = 0; i < bufsize; i++) {
		char c;
		bool fail = false;
		__try
		{
			c = buffer[i];
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			fail = true;
		}
		if (fail) {
			printf("?");
		} else if (c >= 32 && c <= 126) {//printable
			printf("%c", c);
		} else {//non printable
			printf(".");
		}
	}
}

void bin_dump(const uint8_t* buffer, size_t bufsize, bool showPrintableChars) {
	size_t i = 0;
	const uint8_t* rowBuffer = buffer;
	while (i < bufsize) {
		size_t byteCount = 0;
		for (int j = 0; j < BIN_BYTES_PER_LINE; j++, i++) {
			uint8_t byte;
			bool fail = false;
			__try
			{
				byte = buffer[i];
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				fail = true;
			}
			if (fail) {
				printf("???????? ");
				byteCount++;
			}
			else if (i < bufsize) {
				printf("%c%c%c%c%c%c%c%c ", DIGITS[(byte >> 7) & 0b1], DIGITS[(byte >> 6) & 0b1], DIGITS[(byte >> 5) & 0b1], DIGITS[(byte >> 4) & 0b1],
											DIGITS[(byte >> 3) & 0b1], DIGITS[(byte >> 2) & 0b1], DIGITS[(byte >> 1) & 0b1], DIGITS[(byte >> 0) & 0b1]);
				byteCount++;
			} else {
				printf("         ");
			}
		}

		printf(" | ");
		render_printable_chars((const char*) rowBuffer, byteCount);
		rowBuffer += BIN_BYTES_PER_LINE;
		printf("\n");
	}
}

void hex_dump(const uint8_t* buffer, size_t bufsize, bool showPrintableChars) {
	size_t i = 0;
	const uint8_t* rowBuffer = buffer;
	while (i < bufsize) {
		size_t byteCount = 0;
		for (int j = 0; j < HEX_BYTES_PER_LINE; j++, i++) {
			uint8_t byte;
			bool fail = false;
			__try
			{
				byte = buffer[i];
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				fail = true;
			}
			if (fail) {
				printf("?? ");
				byteCount++;
			} else if (i < bufsize) {
				printf("%c%c ", DIGITS[byte >> 4], DIGITS[byte & 0b00001111]);
				byteCount++;
			} else {
				printf("   ");
			}
		}
		printf(" | ");
		render_printable_chars((const char*) rowBuffer, byteCount);
		rowBuffer += HEX_BYTES_PER_LINE;
		printf("\n");
	}
}

void string_dump(const std::string& buffer, bool showPrintableChars) {
	hex_dump((const uint8_t*) buffer.c_str(), buffer.length(), showPrintableChars);
}


bool buffersEqual(u8* a, u8* b, size_t length)
{
	for (int i = 0; i < length; i++)
	{
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

}