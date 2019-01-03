#include "AbstractAlgorithm.h"

AbstractAlgorithm::AbstractAlgorithm(u32 stateSize)
{
	m_StateSize = stateSize;
	m_State = new u8[stateSize];
}


AbstractAlgorithm::~AbstractAlgorithm()
{
	delete[] m_State;
}
