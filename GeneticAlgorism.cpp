
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
    //タイマー初期設定
    timer = 0;

    //現在操作中の個体
    current_biont = 0;
    current_time = 0;

    //isJump:ジャンプしているかどうか
    isJump[0] = 0x0;
    isJump[1] = 0x1;

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
    //・どれだけゴールに近づいたか
    //の5つ
    //やりたいことは、1秒後にはこういう操作をする、2秒後にはこういうことをするっていうことを設定したい
    gen_len = 3;
}

//Destructor for the GuiButton class.
GeneticAlgorism::~GeneticAlgorism()
{

}

//初期遺伝子の生成
void GeneticAlgorism::init_gen()
{
    //初期状態における遺伝子の状態をランダムに決定する

    //個体の数だけfor文を回す
    for (int i = 0; i < biont_number; i++)
    {
        parents[i].gen.resize(gen_len);

        //ジャンプするかどうかについての遺伝子に
        //ランダムでジャンプするかどうかの情報を挿入していく
        //まずは1秒分
        parents[i].gen[0].push_back(random(0, 1));

        //↑と同じことをどんどんやっていく
        parents[i].gen[1].push_back(random(0, 7));
        parents[i].gen[2].push_back(random(0, 1));
    }
}

//適合度の計算(すなわち評価関数)
int GeneticAlgorism::fitness_calc()
{
    return 0;
}

//全個体分の操作を行う
void GeneticAlgorism::main()
{
    int frame = 60;

    //やりたいこと：
    //60フレーム(これは後で修正する)ごとに、遺伝子に組み込まれた情報に従ってプレイヤーの操作を行う
    //gen[3]、すなわち組み込まれた経過時間(回数)まで操作を行う
    //初期状態の場合はgen[3] = {0}なので、一回だけ操作を行う
    //全ての操作が終了すると、適合度の計算を行う
    //そしてスタート地点に戻る

    timer++;

    //60フレームごとに処理
    if(timer >= frame)
    {
        //ジャンプ操作
        mem_functions.write(0, isJump[parents[current_biont].gen[0][current_time]]);

        //8方向操作
        mem_functions.write(0, move8[parents[current_biont].gen[1][current_time]]);

        //イカ状態かどうか
        mem_functions.write(0, isSquid[parents[current_biont].gen[2][current_time]]);

        //次の操作へ
        current_time++;

        //組み込まれた経過時間に到達したら
        if(current_time == ((int)parents[0].gen[0].size())+1)
        {
            //経過時間をリセット
            current_time = 0;

            //適合度を求める
            //[仮] (目的地の3次元座標) - (プレイヤーの座標)
            parents[current_biont].fitness = 0;

            //次の個体へ
            current_biont++;

            //スタート地点に戻る(死ぬ)
            mem_functions.write(0, 0);
        }

        //全ての個体の操作が終わると終了
        if(current_biont == biont_number+1)
        {
            current_biont = 0;
            timer = 0;
            return;
        }
        timer = 0;
    }

}

//世代の更新
void GeneticAlgorism::update_generation()
{
    // 適合度の大きい順、
    // すなわち進んだ距離が大きい順、
    // すなわち優れた個体順にソート
    sort(parents.begin(), parents.end(), GeneticAlgorism::compare);

    // 交配後にランダムな値を遺伝子に追加すればよき？
    // 交叉
    // 優れた親を保存
    for (int i = 0; i < parents_number; i++)
    {
        childlen[i].gen = parents[i].gen;
    }


    // 優れた親から子を生成
    for (int cur_biont = parents_number; cur_biont < biont_number; cur_biont += 2)
    {

        // 二点交叉
        int p_i = cur_biont - parents_number;

        //子供に親の遺伝子情報をそのまま引き継ぐ
        childlen[cur_biont].gen = parents[p_i].gen;
        childlen[cur_biont + 1].gen = parents[p_i + 1].gen;

        int left = rand() % gen_len, right = rand() % gen_len;
        if (left > right)
            swap(left, right);

        for (int cur_gen = left; cur_gen <= right; cur_gen++)
        {
            childlen[cur_biont].gen[cur_gen] = parents[p_i + 1].gen[cur_gen];
            childlen[cur_biont + 1].gen[cur_gen] = parents[p_i].gen[cur_gen];
        }
    }
    // 突然変異
    for (int i = parents_number; i < biont_number; i++)
    {
        for (int j = 0; j < gen_len; j++)
        {
            if(rand() % gen_len)
            {
                for(int k = 0 ; k < (int)childlen[i].gen[j].size(); i++)
                {
                    if(k == 1)
                    {
                        childlen[i].gen[j][k] = random(0, 7);
                    }
                    else
                    {
                        childlen[i].gen[j][k] = random(0, 1);
                    }
                    
                }

            }
        }
    }

    // 世代交代
    for (int i = 0; i < biont_number; i++)
    {
        parents[i].gen = childlen[i].gen;
    }
}
