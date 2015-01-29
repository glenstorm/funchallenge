#include <cstdlib>
#include <ctime>

#include "diophantine.h"


CDiophantine::CDiophantine(int a, int b, int c, int d, int res)
	:ca(a)
	, cb(b)
	, cc(c)
	, cd(d)
	, result(res)
	, maxIteration_(50)
{}


int
CDiophantine::Solve()
{
	int fitness = -1;

	// Создаем начальную популяцию.
	srand((unsigned)time(NULL));
	for (int i = 0; i < maxPop; i++) {
		for (int j = 0; j < 4; j++) {
			population_[i].setAllel(j, rand() % (result + 1)); // Коэффициенты должны
		}
	}

	// Вдруг уже есть решение?
	if (fitness = CreateFitnesses()) {
		return fitness;
	}

	// Repeat until solution found, or over some number iterations.
	for (int i = 0; i < maxIteration_, fitness == 0; ++i)
	{
		GenerateLikelihoods();						    
		CreateNewPopulation();

		if (fitness = CreateFitnesses()){
			return fitness;
		}
	}

	return -1;
}


int 
CDiophantine::Fitness(Gene &gn)
{
	int total = ca * gn.getAlleles()[0] + cb * gn.getAlleles()[1] + cc * gn.getAlleles()[2] + cd * gn.getAlleles()[3];

	// Вычисляем насколько решение на данных генах отклоняется от заявленного регшения уравнения.
	gn.setFitness(abs(total - result));
	return gn.getFitness();
}


int 
CDiophantine::CreateFitnesses()
{
	float avgfit = 0;
	int fitness = 0;
	for (int i = 0; i < maxPop; i++)
	{
		fitness = Fitness(population_[i]);
		avgfit += fitness;
		if (fitness == 0)
		{
			return i;
		}
	}

	return 0;
}


float
CDiophantine::MultInv()
{
	float sum = 0;
	for (int i = 0; i < maxPop; i++)
	{
		sum += 1 / ((float)population_[i].getFitness());
	}

	return sum;
}


void
CDiophantine::GenerateLikelihoods()
{
	float multinv = MultInv();
	float last = 0;
	for (int i = 0; i < maxPop; i++)
	{
		last = last + ((1 / ((float)population_[i].getFitness()) / multinv) * 100);
		population_[i].setLikeHood(last);
	}
}


int
CDiophantine::GetIndex(float val)
{
	float last = 0;
	for (int i = 0; i < maxPop; i++)
	{
		if (last <= val && val <= population_[i].getLikehood())
			return i;
		else last = population_[i].getLikehood();
	}
	return 4;    // :) magic number 
}


Gene
CDiophantine::Breed(int p1, int p2)
{
	int crossover = rand() % 3 + 1;			// Create the crossover point (not first).
	int first = rand() % 100;					// Which parent comes first?

	Gene child = population_[p1];			// Child is all first parent initially.

	int initial = 0, final = 3;				// The crossover boundaries.
	if (first < 50)
		initial = crossover;			      // If first parent first. start from crossover.
	else
		final = crossover + 1;						// Else end at crossover.

	for (int i = initial; i < final; i++)
	{
		// Crossover!
		child.setAllel(i, population_[p2].getAllel(i));
		if (rand() % 101 < 5)
			child.setAllel(i, rand() % (result + 1));
	}

	return child;									    // Return the kid...
}


void 
CDiophantine::CreateNewPopulation()
{
	Gene temppop[maxPop];

	for (int i = 0; i < maxPop; i++)
	{
		int parent1 = 0, parent2 = 0, iterations = 0;
		while (parent1 == parent2 || population_[parent1] == population_[parent2])
		{
			parent1 = GetIndex((float)(rand() % 101)); // Находим особь для скрещивания.
			parent2 = GetIndex((float)(rand() % 101));
			if (++iterations > 25) break; //  ???
		}

		temppop[i] = Breed(parent1, parent2);		// Create a child.
	}

	for (int i = 0; i < maxPop; i++)
		population_[i] = temppop[i];
}


