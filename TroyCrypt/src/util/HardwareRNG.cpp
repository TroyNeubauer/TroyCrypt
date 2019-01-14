#include "HardwareRNG.h"

#include <immintrin.h>
#include <cstring>

void HardwareRNG::getBytes(void* buffer, size_t bytes)
{
	if (bytes == 0) return;
	uint64_t bytesWritten = 0;

	uint64_t value;
	//Round up to the next mutiple of 8
	uint64_t* buf64 = (uint64_t*)(((uint64_t) buffer + 7) & ~7);
	if ((uint8_t*) buf64 != buffer) {//We have bytes before the mutiple of 8 to copy
		bytesWritten = (size_t) buf64 - (size_t) buffer;
		while (!_rdrand64_step(&value));//Generate a random number
		memcpy(buffer, &value, bytesWritten);//Copy however many bytes we have before the mutiple of 8
	}
	uint64_t wordsToWrite = (bytes - bytesWritten) / 8;
	bytesWritten += wordsToWrite * sizeof(uint64_t);
	for (int i = 0; i < wordsToWrite; i++) {
		while (!_rdrand64_step(&value));
		buf64[i] = value;
	}
	if (bytesWritten < bytes) {
		while (!_rdrand64_step(&value));
		memcpy((uint8_t*) buffer + wordsToWrite * sizeof(uint64_t), &value, bytes - bytesWritten);
	}

}