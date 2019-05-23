#include "Eratosthenes.h"
BitField Eratosthenes(const BitField& inpBF)
{
	BitField curBF(inpBF);
	curBF.unload_bit(0);
	unsigned int startBit = 2;
	while (startBit < (curBF.size() / 2 + 1))
	{
		if (curBF.bit_value(startBit))
		{
			int pos = startBit;
			while (pos < curBF.size())
			{
				pos += startBit;
				if (pos < curBF.size())
				{
					curBF.unload_bit(pos);
				}
			}
		}
		++startBit;
	}
	return curBF;
}