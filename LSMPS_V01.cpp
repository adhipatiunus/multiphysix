#include <bits/stdc++.h>
#include "eigen-3.3.7/Eigen/Dense"

using namespace std;
using namespace Eigen;

const double p = 2;
const double max_x = 20;
const double max_y = 20;
const int size_x = 100;
const int size_y = 100;
const double h = max_x / size_x;
const int N = size_x * size_y;
const double r_e = 3.5 * h;
const double r_s = 1.3 * h;


struct particle
{
	double x, y;
	particle *parent;
	deque<pair<double, particle *>> children;

	particle()
	{
		this->parent = NULL;
	}

	double dist2d(const particle &p)
	{
		double dx, dy, dist;
		dx = this->x - p.x;
		dy = this->y - p.y;
		dist = sqrt(pow(dx,2) + pow(dy,2));
		return dist;
	}

	void set_neighbor(particle *theParent)
	{
		double distance;
		parent = theParent;
		distance = dist2d(*parent);
		if (distance < r_e)
			parent->children.push_back(make_pair(distance, this));
	}
};

double factorial(const int &a);
double weight(const double &x, const double &r_e);
double fxy(const particle &p);
double dfxydx(const particle &p);

int main()
{
	clock_t t = clock();
	// Declaring constants and polynomial approximation limit
	vector< pair<int, int> > power_coeffs(2 * p + 1);
	power_coeffs[0] = make_pair(1,0);
	power_coeffs[1] = make_pair(0,1);
	power_coeffs[2] = make_pair(2,0);
	power_coeffs[3] = make_pair(0,2);
	power_coeffs[4] = make_pair(1,1);

	// Calculate Matrix H_rs
	
	MatrixXd H_rs = MatrixXd::Zero(2 * p + 1, 2 * p + 1);
	int power, factor;

	for (int i = 0; i < 2 * p + 1; i++)
	{
		power = power_coeffs[i].first + power_coeffs[i].second;
		factor = factorial(power_coeffs[i].first) * factorial(power_coeffs[i].second);
		H_rs(i,i) = pow(1/r_s, power) * factor;
	}
	
	// generate points

	vector<particle> particle(N);

	int k = 0;
	
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			particle[k].x = j * h;
			particle[k].y = i * h;
			k++;
		}
	}

	double dist;
	int n;
	double w, dx, dy, cx, cy;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j) continue;			
			particle[j].set_neighbor(&particle[i]);
		}
	}
	// calculate matrix
	vector<MatrixXd> storage(N);
	//vector<double> dWdx_Result;
	MatrixXd M;
	MatrixXd b;

	MatrixXd P;
	MatrixXd PT;

	for (int i = 0; i < N; i++)
	{
		M = MatrixXd::Zero(2 * p + 1, 2 * p + 1);
		b = MatrixXd::Zero(2 * p + 1, 1);

		P = MatrixXd::Zero(2 * p + 1, 1);
		PT = MatrixXd::Zero(1, 2 * p + 1);
		n = particle[i].children.size();
		for (int j = 0; j < n; j++)
		{
			dx = (particle[i].children[j].second->x - particle[i].x) / r_s;
			dy = (particle[i].children[j].second->y - particle[i].y) / r_s;
			dist = particle[i].children[j].first / r_e;
			w = weight(dist, r_e);
			for (int k = 0; k < 2 * p + 1; k++)
			{
				cx = power_coeffs[k].first;
				cy = power_coeffs[k].second;
				P(k,0) = pow(dx, cx) * pow(dy, cy);
				PT(0,k) = P(k,0);
			}
			M += w * P * PT;
			b += w * P * (fxy(*particle[i].children[j].second) - fxy(particle[i]));
		}
		M = M.inverse();
		M = M * b;
		M = H_rs * M;
		storage[i] = M;
	}

	vector<double> dWdx_Result(N);

	for (int i = 0; i < N; i++)
	{
		dWdx_Result[i] = storage[i](1,0);
		//cout << i << '\n';
	}

	clock_t tf = clock();

	vector<double> dWdx(N);
	vector<double> W(N);

	for (int i = 0; i < N; i++)
	{
		W[i] = fxy(particle[i]);
		dWdx[i] = dfxydx(particle[i]);
	}

	// print file
	FILE *fp;
    char fileName[1024];

    sprintf(fileName,"function.txt");
    fp = fopen(fileName,"w");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\n",particle[i].x, particle[i].y, W[i], dWdx[i], dWdx_Result[i]);
    }

    printf("Computation Time %f s\n", double(tf-t) / CLOCKS_PER_SEC);

	return 0;
}

double factorial(const int &a)
{
	if (a <= 1) 
		return 1;
	else return 
		a * factorial(a - 1);
}

double weight(const double &x, const double &r_e)
{
	if (x < r_e)
		return (r_e / x - 1);
	else
		return 0;
}

double fxy(const particle &p)
{
	return (p.x * p.y + 2 * p.x + 2 * p.y + pow(p.x, 2) - 2 * pow(p.y, 2));
}

double dfxydx(const particle &p)
{
	return (p.y + 2 + 2 * p.x);
}