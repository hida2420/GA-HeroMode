#ifndef GENETICALGORISM_H_
#define GENETICALGORISM_H_

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class GeneticAlgorism
{
	public:
		//!Constructor
		GeneticAlgorism();

		//!Destructor
		~GeneticAlgorism();

		void fitness_calc();
		void init_gen();
	
	private:

		//個体情報 (gen, fitness) gen = (x1, ..., xn) (xiは操作情報や経過時間など)
		typedef struct
		{
    		double fitness;//適合度
    		vector<vector<int>> gen;///fitnessの引数に当たるもの　操作情報など
		}biont;

		//初期状態時の個体数
		int biont_number;

		//biont.genの要素数
		int gen_len;

		//親の数
		int parents_number;
		
		vector<biont> parents;
        vector<biont> childlen;

};

#endif