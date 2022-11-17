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

		int fitness_calc();
		void fitness_update();
		void init_gen();
		void main();

		//個体情報 (gen, fitness) gen = (x1, ..., xn) (xiは操作情報や経過時間など)
		typedef struct
		{
    		double fitness;//適合度
    		vector<vector<int>> gen;///fitnessの引数に当たるもの　操作情報など
		}biont;

		//比較
		static bool compare(const biont &a, const biont &b)
		{
    		return a.fitness > b.fitness;
		}
	
	private:

		//初期状態時の個体数
		int biont_number;

		//biont.genの要素数
		int gen_len;

		//親の数
		int parents_number;
		
		vector<biont> parents;
        vector<biont> childlen;

		//適合度更新用のタイマー
		int timer;

		int current_biont;
		int current_time;

		unsigned int isJump[2];

};

#endif