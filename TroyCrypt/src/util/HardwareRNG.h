//This class uses the Intel RdRand CPU instruction for 
//the random number generator that is compliant with security 
//and cryptographic standards:
//
//  http://en.wikipedia.org/wiki/RdRand
//
#pragma once

#include <stdint.h>

class HardwareRNG
{
public:
	void getBytes(void* buffer, size_t bytes);
};