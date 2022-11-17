/****************************************************************************
 * Copyright (C) 2022 hida1822
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "GeneticAlgorism.h"
#include "../MemoryFunctions.h"
#include <iostream>
#include <random>
 
std::random_device rd;
std::mt19937 gen(rd());
 
//整数乱数を範囲を定めて決定できるrandom関数
int random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

MemoryFunctions mem_functions;

//Constructor for the MunuFunctions class.
GeneticAlgorism::GeneticAlgorism()
{
    //個体数20はマリオブラザーズAIを参考にした値
    biont_number = 20;
    parents.resize(biont_number);
    childlen.resize(biont_number);


    //親個体の数は総個体数の半分
    parents_number = 20/2;

    //遺伝子の数は、
    //・ジャンプするかどうか(1=ジャンプ)
    //・8方向のどこに向かうか(移動の操作を0～7に割り当てる)
    //・イカ状態になるかどうか(1=イカ状態)
    //・経過時間
    //やりたいことは、1秒後にはこういう操作をする、2秒後にはこういうことをするっていうことを設定したい
    gen_len = 4;
    mem_functions.write(0, 0);
}

//Destructor for the GuiButton class.
GeneticAlgorism::~GeneticAlgorism()
{

}

//適合度の計算(すなわち評価関数)
void GeneticAlgorism::fitness_calc()
{

}

//初期遺伝子の設定
void GeneticAlgorism::init_gen()
{
    //初期状態における遺伝子の状態をランダムに決定する

    //個体の数だけfor文を回す
    for (int i = 0; i < biont_number; i++)
    {
        parents[i].gen.resize(4);

        //ジャンプするかどうかについての遺伝子に
        //ランダムでジャンプするかどうかの情報を挿入していく
        //まずは1秒分
        parents[i].gen[0].push_back(random(0, 1));

        //↑と同じことをどんどんやっていく
        parents[i].gen[1].push_back(random(0, 3));
        parents[i].gen[2].push_back(random(0, 1));
        parents[i].gen[3].push_back(0);
    }
}

