#pragma once
#include <algorithm>

typedef unsigned short BFMult;// “ип, используемый, как блок битового поле
const size_t BFMultSize = sizeof(BFMult);//–азмер блока битового пол€ в байтах
const size_t NumOfBitsBFMult = BFMultSize * 8;// оличетсво битов в блоке битового пол€
constexpr BFMult BYTE = 8;//размер байта
constexpr BFMult identityMask()//единична€ маска дл€ блока битового пол€
{
	BFMult IM = 1;
	for (int i = 1; i < NumOfBitsBFMult; ++i)
		IM = (IM << 1) | 1;
	return IM;
}



using namespace std;

class BitField
{
private:
	const size_t LenLimit{ 1048576 };// ѕредельный размер битового пол€
	BFMult *pBF;//”казатель на массив блоков битового пол€
	size_t BFLen;//длина битового пол€
	size_t numOfBlocks;//количество блоков типа BFMult в поле

	//возвращает номер блока, в котором находитс€ бит
	int get_BlockIndex(int n);
	BFMult get_BlockMask(int bitShift);


public:
	BitField(int len);
	BitField(const BitField &);
	void operator = (const BitField &cpBF);
	bool& operator[](size_t);
	size_t get_numOfBlocks() const;//¬озвращает количество блоков в поле
	size_t size() const;//¬озвращает длину пол€
	void load_AllBits();//¬зведение всех битов пол€
	void unload_AllBits();//«ануление всех битов пол€
	unsigned short bit_value(int);//«начение бита
	void load_bit(int);//взведение бита
	void unload_bit(int);//«ануление всех битов
	size_t nonzero_count() const;// оличество всех ненулевых битов пол€
	~BitField();

};