
#include "Bitset.h"

namespace GameEngine
{
	Bitset::Bitset()
	{
		byte = 0;
	}
	
	Bitset::Bitset(Byte byte)
	{
		this->byte = byte;
	}
	
	Bitset::Bitset(char bits[8])
	{
		byte = 0;
		for(int i=0; i<8; i++)
		{
			if(bits[i]=='1')
			{
				set(i, true);
			}
		}
	}
	
	Bitset::~Bitset()
	{
		//
	}
	
	bool Bitset::get(unsigned int index)
	{
		return ((byte & (1 << index))!=0);
	}
	
	void Bitset::set(unsigned int index, bool toggle)
	{
		if(toggle)
		{
			byte |= (1 << index);
		}
		else
		{
			byte &= ~(1 << index);
		}
	}
	
	Byte& Bitset::getByte()
	{
		return byte;
	}
	
	Bitset& Bitset::operator=(const Bitset&bitset)
	{
		byte = bitset.byte;
		return *this;
	}
}