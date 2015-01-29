#include "gene.h"

/// Количество особей (популяция)
static const int maxPop = 25;

/// @class CDiophantine
/// @brief Решатель диафантового уравнения.
class CDiophantine
{
public:
	/// Конструктор с коэфиициентами для a,b,c,d + результат.
	explicit CDiophantine(int, int, int, int, int);
	// Решаем уравнение. Если возвращаем -1, то решения данного уравнения не смогли найти.
	int Solve();
	// Возщвращаем ген по индексу.
	Gene GetGene(int i) { return population_[i]; }

protected:
	/// Коэффициэнты при членах диофантового уравнения.
	int ca, cb, cc, cd;
	/// Руззультат уравнения.
	int result;              
	/// Текущая популяция особей(генов).
	std::array<Gene, maxPop> population_;
	/// Fitness function. Функция, вычисляющая выживаемость особи.
	int Fitness(Gene &);
	/// Generate likelihoods. Вероятность выбора этого гена в качестве родительского
	void GenerateLikelihoods();
	/// Creates the multiplicative inverse.
	float MultInv();
	/// Вычисляем коэффициент выживаемости для всех особей в популяции.
	int CreateFitnesses();
	/// Вычисляем коэффициент выживаемости для всех особей в популяции.
	void CreateNewPopulation();
	/// 
	int GetIndex(float val);
	/// Размножение.
	Gene Breed(int p1, int p2);   

private:
	int maxIteration_;
};

