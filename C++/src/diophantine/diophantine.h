#include "gene.h"

/// ���������� ������ (���������)
static const int maxPop = 25;

/// @class CDiophantine
/// @brief �������� ������������ ���������.
class CDiophantine
{
public:
	/// ����������� � �������������� ��� a,b,c,d + ���������.
	explicit CDiophantine(int, int, int, int, int);
	// ������ ���������. ���� ���������� -1, �� ������� ������� ��������� �� ������ �����.
	int Solve();
	// ����������� ��� �� �������.
	Gene GetGene(int i) { return population_[i]; }

protected:
	/// ������������ ��� ������ ������������ ���������.
	int ca, cb, cc, cd;
	/// ���������� ���������.
	int result;              
	/// ������� ��������� ������(�����).
	std::array<Gene, maxPop> population_;
	/// Fitness function. �������, ����������� ������������ �����.
	int Fitness(Gene &);
	/// Generate likelihoods. ����������� ������ ����� ���� � �������� �������������
	void GenerateLikelihoods();
	/// Creates the multiplicative inverse.
	float MultInv();
	/// ��������� ����������� ������������ ��� ���� ������ � ���������.
	int CreateFitnesses();
	/// ��������� ����������� ������������ ��� ���� ������ � ���������.
	void CreateNewPopulation();
	/// 
	int GetIndex(float val);
	/// �����������.
	Gene Breed(int p1, int p2);   

private:
	int maxIteration_;
};

