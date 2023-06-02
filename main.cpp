/**@mainpage Отчёт к Лабораторной работе №4 
 * @brief Методы программирования. Лабораторная работа №4. Недомолкин И. Э. СКБ201
 * @section intro Введение
 * Отчёт к лабораторной работе №4 по методам программирования. Включающий в себя документацию по коду сгенерированную doxygen, ссылку на репозиторий с кодом программы и результатами её работы, а так же графики. 
 * @section description Описание 
 * Для гспч я использовал среднеквадратичный метод с добавление значущих нулей в случае если получившееся число ментше нужно нам джлины. А так же линейный когруэнтный метод с увеличением поступаемого числа значемыми нулями при уменьшении этого самого числа
 * @section Link Исходный код программы
 * Ссылка на репозиторий Github с кодов, данными и результатами https://github.com/Nedomolkin-Ilya/Programming-Techniques-lab-4.
 * @section Report Отчёт
 * Полученные данные (Result1) демонстрируют тот факт что выборки весьма однородны. Эксперементальные значения приближены к теоретическим. Критерий Хи-квадрат также указывает на то, что наше распределенеи можно с высокой степенью уверенности назвать равновномерным. Так как полученые эксперементацльные занчения незначительно больше, равнвны или вообще меньше теоретически занчений с высокой степенью доверия. (Result2) демонстрирует, что встроеный гпсч быстрее.
 * @section Image График
 * \image latex myplot.png "Время на генерацию определённого количества случайных чисел"
 */
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <random>
#include <cstdio>

#define uint unsigned long long

using namespace std;

const uint gen_size = 50;
const uint gen_numb = 10;
const uint max_nuber = 1000000;

const long int se[10] = {753197,643712,783146,216793,731964,123456,951753,456123,156345,689463};
const int size_of_gen[10] = {1000, 10000, 50000, 100000, 200000, 300000, 400000, 500000, 800000, 1000000};
ofstream ou("Result.txt");

class MyGen1 {
private:
	uint state;
	uint div, mod;

public:
	
	MyGen1(uint start, uint length){
		/*
		* @param start Отсчётное значение (seed)
		* @param length Длина генерируемого числа
		*/
		div = 1;
		mod = 1;
		for (uint i = 0; i < length / 2; i++) div = div * 10;
		for (uint i = 0; i < length; i++) mod = mod * 10;
		state = start % mod;
	}

	uint next(){
		/**
		* return Случайное число
		*/
		return state = state * state / div % mod;
	}
};

class MyGen2 {
private:
	uint a = 434611;
	uint b = 76132;
	uint start, state, mod;
public:
	MyGen2(uint start, uint length){
		/*
		* @param start Отсчётное значение (seed)
		* @param length Длина генерируемого числа
		*/
		for (uint i = 0; i < length; i++) mod = mod * 10;
		state = start % mod;
	}

	uint next(){
		/**
		* return Случайное число
		*/
		return state = (state*a-b) % mod;
	}
};

double midl(vector<uint>& v) {
    unsigned long long sum = 0;

    for (auto& n : v)
        sum += n;
    /**
	* return Математическое ожидание
	*/
    return sum / static_cast<double>(v.size());
}

double otkl(double midl, vector<uint>& v) {
    double sum = 0;

    for (auto& n : v)
        sum = sum+(n-midl)*(n-midl);

    /**
	* return Случайное число
	*/
    return sqrt(sum / v.size());
}

double coef(double otkl, double midl) {
	/**
	* return Коэффициент вариации
	*/
    return otkl / midl;
}

double chi2(vector<uint>& vec) {
    unsigned int k;
    double p;
    vector<double> v;

    for (int i = 0; i < vec.size(); ++i) v.push_back(vec[i] / static_cast<double>(max_nuber - 1));

    
    k = 1+3.322*log(v.size());
    p = 1 / static_cast<double>(k);

    vector<unsigned int> ni(k, 0);

    for (auto& u : v) for (int j = 0; j < k; ++j) if (p*j <= u && p * (j + 1) > u) ni[j] = ni[j] +1;

    double chi = 0;

    for (auto& u : ni) chi = chi + ((static_cast<double>(u) - p * v.size()) * (static_cast<double>(u) - p * v.size())) / (p * v.size());
    /**
	* return Эксперементальное значение Хи-квадрата
	*/
    return chi;
}

void about_gen(vector<uint>& v) {
    double mi;
    double dis;
    double coe;
    double chi;

	mi = midl(v);
	dis = otkl(mi, v);
	coe = coef(dis, mi);
	chi = chi2(v);

    ou << "Midle: " << mi << "\nOtkl: " << dis << "\nCoEf: " << coe << "\nChi^2: " << chi << '\n' << endl;
}


int main() {
	std::vector<uint>* first = new std::vector<uint>[gen_numb];
	std::vector<uint>* second = new std::vector<uint>[gen_numb];
	std::chrono::steady_clock::time_point start, end;
	// ou << "My firs generater\n";
	// for (int i = 0; i < gen_numb; i++){
	// 	MyGen1 first_gen( se[i],  6);
	// 	for (int j = 0; j < gen_size; j++){
	// 		uint my_gen = first_gen.next();
	// 		first[i].push_back(my_gen);
	// 	}
	// 	about_gen(first[i]);
	// }


	// ou << "My second generater\n";
	// for (int i = 0; i < gen_numb; i++){
	// 	MyGen1 sec_gen( se[i],  6);
	// 	for (int j = 0; j < gen_size; j++){
	// 		uint my_gen = sec_gen.next();
	// 		second[i].push_back(my_gen);
	// 	}
	// 	about_gen(second[i]);
	// }

	// ou << "mt19937 cpp generater\n";

	// mt19937 mt_rand(time(NULL));
	// for (int i = 0; i < gen_numb; i++){
	// 	vector<uint> CPPrand(gen_size);
	// 	for (int j = 0; j < gen_size; ++j){ 
	// 		CPPrand[j] = mt_rand() % max_nuber;
	// 	}
    // 	about_gen(CPPrand);
    // }
	// return 0;


	start = std::chrono::steady_clock::now();
	ou << "My firs generater\n";
	for (int i = 0; i < gen_numb; i++){
		MyGen1 first_gen( se[i],  6);
		for (int j = 0; j < size_of_gen[i]; j++){
			uint my_gen = first_gen.next();
			first[i].push_back(my_gen);
		}
		end = std::chrono::steady_clock::now();
		ou << "Size " << size_of_gen[i] << " time " << chrono::duration_cast<chrono::microseconds>(end - start).count() << '\n';
		start = end;
		//about_gen(first[i]);
	}


	ou << "My second generater\n";
	for (int i = 0; i < gen_numb; i++){
		MyGen1 sec_gen( se[i],  6);
		for (int j = 0; j < size_of_gen[i]; j++){
			uint my_gen = sec_gen.next();
			second[i].push_back(my_gen);
		}
		end = std::chrono::steady_clock::now();
		ou << "Size " << size_of_gen[i] << " time " << chrono::duration_cast<chrono::microseconds>(end - start).count() << '\n';
		start = end;
		//about_gen(second[i]);
	}

	ou << "mt19937 cpp generater\n";

	mt19937 mt_rand(time(NULL));
	for (int i = 0; i < gen_numb; i++){
		vector<uint> CPPrand(size_of_gen[i]);
		for (int j = 0; j < size_of_gen[i]; ++j){ 
			CPPrand[j] = mt_rand() % max_nuber;
		}
		end = std::chrono::steady_clock::now();
		ou << "Size " << size_of_gen[i] << " time " << chrono::duration_cast<chrono::microseconds>(end - start).count() << '\n';
		start = end;
    	//about_gen(CPPrand);
    }

    return 0;
}

	// ou << "My firs generater\n";
	// for (int i = 0; i < gen_numb; i++){
	// 	MyGen1 first_gen( se[i],  6);
	// 	for (int j = 0; j < size_of_gen[i]; j++){
	// 		uint my_gen = first_gen.next();
	// 		first[i].push_back(my_gen);
	// 	}
	// 	about_gen(first[i]);
	// }


	// ou << "My second generater\n";
	// for (int i = 0; i < gen_numb; i++){
	// 	MyGen1 sec_gen( se[i],  6);
	// 	for (int j = 0; j < size_of_gen[i]; j++){
	// 		uint my_gen = sec_gen.next();
	// 		second[i].push_back(my_gen);
	// 	}
	// 	about_gen(second[i]);
	// }

	// ou << "mt19937 cpp generater\n";

	// mt19937 mt_rand(time(NULL));
	// for (int i = 0; i < gen_numb; i++){
	// 	vector<uint> CPPrand(size_of_gen[i]);
	// 	for (int j = 0; j < size_of_gen[i]; ++j){ 
	// 		CPPrand[j] = mt_rand() % max_nuber;
	// 	}
    // 	about_gen(CPPrand);
    // }