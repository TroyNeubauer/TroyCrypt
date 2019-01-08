

#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cctype>

namespace TroyCrypt {

#define BYTES_PER_LINE 32

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

	std::ostream& render_printable_chars(std::ostream& os, const char* buffer, size_t bufsize) {
		os << " | ";
		for (size_t i = 0; i < bufsize; ++i)
		{
			if (std::isprint((unsigned char) buffer[i]))
			{
				os << buffer[i];
			}
			else
			{
				os << ".";
			}
		}
		return os;
	}

	std::ostream& hex_dump(std::ostream& os, const uint8_t* buffer, size_t bufsize, bool showPrintableChars)
	{
		auto oldFormat = os.flags();
		auto oldFillChar = os.fill();

		os << std::hex;
		os.fill('0');
		bool printBlank = false;
		size_t i = 0;
		for (; i < bufsize; ++i)
		{
			if (i % BYTES_PER_LINE == 0)
			{
				if (i != 0 && showPrintableChars)
				{
					render_printable_chars(os, reinterpret_cast<const char*>(&buffer[i] - BYTES_PER_LINE), BYTES_PER_LINE);
				}
				os << std::endl;
				printBlank = false;
			}
			if (printBlank)
			{
				os << ' ';
			}
			os << std::setw(2) << std::right << unsigned(buffer[i]);
			if (!printBlank)
			{
				printBlank = true;
			}
		}
		if (i % BYTES_PER_LINE != 0 && showPrintableChars)
		{
			for (size_t j = 0; j < BYTES_PER_LINE - (i % BYTES_PER_LINE); ++j)
			{
				os << "   ";
			}
			render_printable_chars(os, reinterpret_cast<const char*>(&buffer[i] - (i % BYTES_PER_LINE)), (i % BYTES_PER_LINE));
		}

		os << std::endl << std::endl;

		os.fill(oldFillChar);
		os.flags(oldFormat);

		return os;
	}

	std::ostream& hex_dump(std::ostream& os, const std::string& buffer, bool showPrintableChars)
	{
		return hex_dump(os, reinterpret_cast<const uint8_t*>(buffer.data()), buffer.length(), showPrintableChars);
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