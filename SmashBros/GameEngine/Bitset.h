
#pragma once

namespace GameEngine
{
	typedef unsigned char Byte;
	class Bitset
	{
	private:
		Byte byte;
		
	public:
		static const Byte BITMASK_ONE   = 1;
		static const Byte BITMASK_TWO   = 2;
		static const Byte BITMASK_THREE = 4;
		static const Byte BITMASK_FOUR  = 8;
		static const Byte BITMASK_FIVE  = 16;
		static const Byte BITMASK_SIX   = 32;
		static const Byte BITMASK_SEVEN = 64;
		static const Byte BITMASK_EIGHT = 128;
		
		Bitset();
		Bitset(Byte byte);
		Bitset(char bits[8]);
		~Bitset();
		
		bool get(unsigned int index);
		void set(unsigned int index, bool toggle);
		
		Byte&getByte();
		
		Bitset& operator=(const Bitset&bitset);
	};
}