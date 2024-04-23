
#include <iostream>
#include <string>
#include <vector>
#include <ctime>  
#include <algorithm> 

class Matrix
{
private:
	int n; // число строк           
	int m; // число столбцов       

	std::vector <std::vector<double>> a;

public:

	Matrix(int n_ = 0, int m_ = 0) : n(n_), m(m_),
		a(n_, std::vector<double>(m_, 0)) {}

	double& operator () (int i, int j);  
	const double& operator () (int i, int j) const;  
	Matrix operator () (int i1, int i2, int j1, int j2) const;  
	Matrix operator*(const Matrix& b);
	Matrix operator-(const Matrix& b);  
	Matrix operator+(const Matrix& b);  
	Matrix &operator=(const Matrix&) = default;
	 

	double MatrixNorm() const;



	void transform();   // реализовать
	Matrix simple_iter_method(Matrix & x_0, double prec); // реализовать 


	friend std::ostream& operator << (std::ostream& st, Matrix& a);
	friend std::istream& operator >> (std::istream& st, Matrix& a);

};


Matrix Matrix::operator () (int i1, int i2, int j1, int j2) const
{
	Matrix b;
	b.n = i2 - i1 + 1;
	b.m = j2 - j1 + 1;
	b.a.resize(b.n);
	for (int i = 0; i < n; ++i)
		b.a[i].resize(b.m);

	for (int i = i1; i <= i2; ++i)
		copy(a[i].begin() + j1, a[i].begin() + j2 + 1, b.a[i - i1].begin());  
		// параметры copy --  итераторы;  2-й параметр -- диапазон на 1 больше 

	return b;
}

 
double& Matrix::operator () (int i, int j)
// перегруженная операция вызова функции  
{
	if (i < 0 || i > n || j < 0 || j > m)
		throw "Invalid range";
	return a[i][j];
}

const double& Matrix::operator () (int i, int j) const
// перегруженная операция вызова функции  
{
	if (i < 0 || i > n || j < 0 || j > m)
		throw "Invalid range";
	return a[i][j];
}

Matrix Matrix::operator*(const Matrix& b)
{
	if (this->m != b.n)
	{
		std::cout << "multiplication error";
		return *this;
	}
	else
	{
		Matrix c;
		c.n = this->n;
		c.m = b.m;
		c.a.resize(n);
		for (int i = 0; i <= n - 1; ++i)
		{
			c.a[i].resize(b.m);
		}
		double q = 0;
		for (int i = 0; i <= this->n - 1; ++i)
		{
			for (int j = 0; j <= b.m - 1; ++j)
			{
				for (int k = 0; k <= this->m - 1; ++k)
				{
					q += this->a[i][k] * b.a[k][j];
				}
				c.a[i][j] = q;
				q = 0;
			}
		}
		return c;
	}
}

Matrix Matrix::operator-(const Matrix& b)
{
	if (this->m != b.m || this->n != b.n)
	{
		std::cout << "incorrect sizes";
		return *this;
	}
	else
	{
		Matrix c;
		c.n = this->n;
		c.m = this->m;
		c.a.resize(c.n);
		for (int i = 0; i < n; ++i)
			c.a[i].resize(c.m);

		for (int i = 0; i < c.n; ++i)
			for (int j = 0; j < c.m; ++j)
				c(i, j) = (*this)(i, j) - b(i, j);

		return c;
	}
}


Matrix Matrix::operator+(const Matrix& b)
{
	if (this->m != b.m || this->n != b.n)
	{
		std::cout << "incorrect sizes";
		return *this;
	}
	else
	{
		Matrix c;
		c.n = this->n;
		c.m = this->m;
		c.a.resize(c.n);
		for (int i = 0; i < n; ++i)
			c.a[i].resize(c.m);

		for (int i = 0; i < c.n; ++i)
			for (int j = 0; j < c.m; ++j)
				c(i, j) = (*this)(i, j) + b(i, j);

		return c;
	}
}


double Matrix::MatrixNorm() const
{
	double max = -1;
	for (int i = 0; i < n; ++i)
	{
		double ti = 0;
		for (int j = 0; j < m; ++j)
		{
			ti += abs(this->a[i][j]);
		}
		if (max < ti)
		{
			max = ti;
		}
	}
	return max;
}

std::ostream& operator << (std::ostream& st, Matrix& a)
{
	st << std::endl;
	for (int i = 0; i <= a.n - 1; ++i)
	{
		for (int j = 0; j <= a.m - 1; ++j)
		{
			st << a.a[i][j] << "\t";
		}
		st << std::endl;
	}
	return st;
}

std::istream& operator >> (std::istream& st, Matrix& a)
{
	st >> a.n >> a.m;
	std::vector<std::vector<double>> b(a.n);
	for (int i = 0; i <= a.n - 1; ++i)
	{
		b[i].resize(a.m);
		for (int j = 0; j <= a.m - 1; ++j)
		{
			double k;
			st >> k;
			b[i][j] = k;
		}
	}
	a.a = b;
	return st;
}


int main()
{
	srand(time(NULL));
	int n = 3;

	Matrix A(n, n + 1);
	Matrix x_0(n, 1), x(n, 1);


	A(0, 0) = 7;  A(0, 1) = 2;  A(0, 2) = 1;  A(0, 3) = 15;
	A(1, 0) = 4;  A(1, 1) = 9;  A(1, 2) = 1;  A(1, 3) = 26;
	A(2, 0) = 2;  A(2, 1) = 3;  A(2, 2) = 6;  A(2, 3) = 32;

	x_0(0, 0) = 0;  x_0(1, 0) = 0; x_0(2, 0) = 0;

	 

	std::cout << "x_0: " << std::endl; 
	std::cout << x_0 << std::endl;

	A.transform();
	try 
	{ 
		x = A.simple_iter_method(x_0, 1e-6); 
	}

	catch (std::string s)
	{
		std::cout << s << std::endl;
	}

	std::cout << "x: " << std::endl;
	std::cout << x << std::endl;


	return EXIT_SUCCESS;
}
 
