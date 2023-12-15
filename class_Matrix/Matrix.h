#pragma once
#include<iostream>
#include<vector>


class Matrix
{
private:
	int n; // number of rows
	int m; // number of columns 
	std::vector<std::vector<double>> a;

public:
	Matrix(int n_ = 0, int m_ = 0) : n(n_), m(m_),
		a(n_, std::vector<double>(m_, 0)) {} 

	double& operator () (int i, int j) 
	{
		if (i < 0 || i > n || j < 0 || j > m)
			throw "Invalid range";
		return a[i][j];
	}
	// overloaded function call operator 
       // как упражнение (вообще в методах можно писать объект[i][j] (вместо объект.a[i][j])),  
       // так как в vector есть operator[]

#include "Egor.h"
#include "Aleksey.h"
#include "Masha.h"
#include "Peize.h"
};
