#include "BitField.h"

int BitField::get_BlockIndex(int n)
{
	return n / (BFMultSize * 8);
}
BFMult BitField::get_BlockMask(int bitShift)
{
	if (bitShift > (BFMultSize*BYTE - 1)) throw "incorrect bit has been called";

	return (BFMult)(1 << bitShift);

}

BitField::BitField(int len)
{
	if (BFLen < 0 || BFLen > LenLimit) throw "incorrect size";

	BFLen = len;
	numOfBlocks = BFLen / (BFMultSize * BYTE);
	//Увеличение размера поля
	if ((numOfBlocks * (BFMultSize * BYTE)) < BFLen) ++numOfBlocks;
	pBF = new BFMult[numOfBlocks];

	//обнуление поля
	for (int i = 0; i < numOfBlocks; ++i) pBF[i] = 0;
}
BitField::BitField(const BitField &cpBF) : BFLen{ cpBF.BFLen }, numOfBlocks{ cpBF.numOfBlocks }
{
	pBF = new BFMult[numOfBlocks];
	copy(cpBF.pBF, cpBF.pBF + numOfBlocks, pBF);
}

void BitField :: operator = (const BitField &cpBF)
{
	if (numOfBlocks != cpBF.numOfBlocks)
	{
		delete[]pBF;
		BFLen = cpBF.BFLen;
		numOfBlocks = cpBF.numOfBlocks;
		pBF = new BFMult[BFLen];
	}
	copy(cpBF.pBF, cpBF.pBF + numOfBlocks, pBF);
}

size_t BitField::get_numOfBlocks() const
{
	return numOfBlocks;
}

size_t BitField::size() const
{
	return BFLen;
}

BitField::~BitField()
{
	delete[]pBF;
}

void BitField::load_AllBits()
{
	for (int i = 0; i < numOfBlocks; ++i)
		pBF[i] |= identityMask();
}

void BitField::unload_AllBits()
{
	for (int i = 0; i < numOfBlocks; ++i)
		pBF[i] &= 0;
}

unsigned short BitField::bit_value(int pos)
{
	if (pos < 0 || pos >= BFLen) throw "Out of Bitfield range";
	int blockIndex = get_BlockIndex(pos);
	BFMult mask = get_BlockMask(pos % (BFMultSize*BYTE));
	if (pBF[blockIndex] & mask) return 1;
	return 0;
}

void BitField::load_bit(int pos)
{
	if (pos < 0 || pos >= BFLen) throw "Out of Bitfield range";
	int blockIndex = get_BlockIndex(pos);
	BFMult mask = get_BlockMask(pos % (BFMultSize*BYTE));
	pBF[blockIndex] |= mask;

}
void BitField::unload_bit(int pos)
{
	if (pos < 0 || pos >= BFLen) throw "Out of Bitfield range";
	int blockIndex = get_BlockIndex(pos);
	BFMult mask = get_BlockMask(pos % (BFMultSize*BYTE));
	pBF[blockIndex] &= (~mask);

}

size_t BitField::nonzero_count() const
{
	size_t counter{ 0 };//счетчик ненулевых элементов
	unsigned int blockCounter{ 0 };//счетчик блоков (текущий блок)
	BFMult buf = pBF[blockCounter];
	for (int i = 0; i < BFLen; ++i)
	{
		counter += (buf & 1);
		buf >>= 1;
		if (!( (i + 1 ) % NumOfBitsBFMult) )
		{
			buf = pBF[++blockCounter];
		}

	}
	return counter;
}


bool& BitField:: operator[](size_t idx)
{
	bool val = bit_value(idx) == 1 ? true : false;
	return val;
}