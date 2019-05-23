#pragma once
#include <algorithm>

typedef unsigned short BFMult;// ���, ������������, ��� ���� �������� ����
const size_t BFMultSize = sizeof(BFMult);//������ ����� �������� ���� � ������
const size_t NumOfBitsBFMult = BFMultSize * 8;//���������� ����� � ����� �������� ����
constexpr BFMult BYTE = 8;//������ �����
constexpr BFMult identityMask()//��������� ����� ��� ����� �������� ����
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
	const size_t LenLimit{ 1048576 };// ���������� ������ �������� ����
	BFMult *pBF;//��������� �� ������ ������ �������� ����
	size_t BFLen;//����� �������� ����
	size_t numOfBlocks;//���������� ������ ���� BFMult � ����

	//���������� ����� �����, � ������� ��������� ���
	int get_BlockIndex(int n);
	BFMult get_BlockMask(int bitShift);


public:
	BitField(int len);
	BitField(const BitField &);
	void operator = (const BitField &cpBF);
	bool& operator[](size_t);
	size_t get_numOfBlocks() const;//���������� ���������� ������ � ����
	size_t size() const;//���������� ����� ����
	void load_AllBits();//��������� ���� ����� ����
	void unload_AllBits();//��������� ���� ����� ����
	unsigned short bit_value(int);//�������� ����
	void load_bit(int);//��������� ����
	void unload_bit(int);//��������� ���� �����
	size_t nonzero_count() const;//���������� ���� ��������� ����� ����
	~BitField();

};