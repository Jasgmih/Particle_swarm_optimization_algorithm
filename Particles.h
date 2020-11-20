#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;
#define NUMBER_PARTICLES 20
#define NUMBER_VARIABLES 2
#define ITERATION 1000
#define MAX_VElOCITY 3.
#define MAX_POSITION 20.
#define MIN_POSITION -20.

class Particle
{
public:
	double position[NUMBER_VARIABLES];
	double velocity[NUMBER_VARIABLES];
	double OptimalPosition[NUMBER_VARIABLES];
	double OptiamlCost;
};


class Particles
{
public:
	Particles();
	void PSO();
	
private:
	vector <Particle> particles;
	double globalOptimalCost[ITERATION];
	double globalOptimalPosition[NUMBER_VARIABLES];
	double w = 0.9;
	double b = 2.;
	double c = 2.;
	double wDamp = 0.99;
	double r = rand() / double(RAND_MAX);

private:
	void init();
	double bound(double min, double x, double max);
	void output();
	
	

};

