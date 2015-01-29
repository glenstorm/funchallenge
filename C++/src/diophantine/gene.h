#ifndef _GENE_H_GUARD_
#define _GENE_H_GUARD_

#include <array>

static const int GeneNumber = 4;

typedef int alleyVal;
typedef std::array<alleyVal, GeneNumber> DiafAllelesType;

/// @class Gene
/// @brief ������� �����
class Gene
{
private:
	/// ����� - https://ru.wikipedia.org/wiki/������
	/// ���������� ��� ������������ ���������, � �������� 4 ������������ ������� ��� � 4 ������.
	DiafAllelesType alleles;
	/// ����������� ������������.
	int fitness_;
	/// ����������� ��������� ���������.
	float likelihood_;

public:
	///  
	bool operator==(const Gene &gn)
	{
		for (int i = 0; i < GeneNumber; i++)
		{
			if (gn.alleles[i] != alleles[i])
				return false;
		}
		return true;
	}

	/// ��������� ����� ��� ��������� ������������ ����������.
	DiafAllelesType getAlleles() const
	{
		return std::move(alleles);
	}
	/// ������������� ������������ ������.
	void setAllel(int idx, alleyVal val)
	{
		alleles[idx] = val;
	}
	/// ������ ������������ ������.
	alleyVal getAllel(int idx)
	{
		return alleles[idx];
	}
	/// ������ ����������� ������������ � ����.
	int getFitness() const
	{
		return fitness_;
	}
	/// ������������� ����������� ������������ � ����.
	void setFitness(int val)
	{
		fitness_ = val;
	}

	float getLikehood() const
	{
		return likelihood_;
	}

	void setLikeHood(float val)
	{
		likelihood_ = val;
	}

};

#endif
// _GENE_H_GUARD_

