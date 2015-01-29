#ifndef _GENE_H_GUARD_
#define _GENE_H_GUARD_

#include <array>

static const int GeneNumber = 4;

typedef int alleyVal;
typedef std::array<alleyVal, GeneNumber> DiafAllelesType;

/// @class Gene
/// @brief Цепочка генов
class Gene
{
private:
	/// Аллеи - https://ru.wikipedia.org/wiki/Аллели
	/// Специально для диафантового уравнения, у которого 4 коэффициента заводим ДНК с 4 генами.
	DiafAllelesType alleles;
	/// Коэффециент выживаемости.
	int fitness_;
	/// Вероятность оказаться родителем.
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

	/// Открываем аллеи для изменения генетическим алгоритмом.
	DiafAllelesType getAlleles() const
	{
		return std::move(alleles);
	}
	/// Устанавливаем определенный аллель.
	void setAllel(int idx, alleyVal val)
	{
		alleles[idx] = val;
	}
	/// Узнаем определенный аллель.
	alleyVal getAllel(int idx)
	{
		return alleles[idx];
	}
	/// Узнаем коэффициент выживаемости у гена.
	int getFitness() const
	{
		return fitness_;
	}
	/// Устанавливаем коэффициент выживаемости у гена.
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

