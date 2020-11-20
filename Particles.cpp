#include "Particles.h"

double BenchMarkFunciton(double *x) {
	/*double a = 0.;
	double b = 1.;
	return pow((a - x[0]), 2) + b * pow((x[1] - x[0] * x[0]), 2);*/
	return pow((x[0] - 2),2)+pow( (x[1] - 1),2)+3.;
}

Particles::Particles()
{
	this->particles.resize(NUMBER_PARTICLES);
	init();
}

void Particles::PSO()
{
	for (int it = 0; it < ITERATION; it++) {
		for (int parti = 0; parti < NUMBER_PARTICLES; parti++) {

			if (particles[parti].OptiamlCost > BenchMarkFunciton(particles[parti].position)) {
				particles[parti].OptiamlCost = BenchMarkFunciton(particles[parti].position);
				for (int var = 0; var < NUMBER_VARIABLES; var++)
					particles[parti].OptimalPosition[var] = particles[parti].position[var];
			}

			if (globalOptimalCost[it] > particles[parti].OptiamlCost) {
				globalOptimalCost[it] = particles[parti].OptiamlCost;
				for (int var = 0; var < NUMBER_VARIABLES; var++)
					globalOptimalPosition[var] = particles[parti].OptimalPosition[var];
			}
		}
		for (int parti = 0; parti < NUMBER_PARTICLES; parti++) {
			for (int var = 0; var < NUMBER_VARIABLES; var++) {
				particles[parti].velocity[var] = w * wDamp * particles[parti].velocity[var]
					+ b * r*(particles[parti].OptimalPosition[var] - particles[parti].position[var])
					+ c * r*(globalOptimalPosition[var] - particles[parti].position[var]);
				particles[parti].velocity[var] =
					bound(-MAX_VElOCITY, particles[parti].velocity[var], MAX_VElOCITY);

				particles[parti].position[var] += particles[parti].velocity[var];
				particles[parti].position[var] =
					bound(MIN_POSITION, particles[parti].position[var], MAX_POSITION);
			}
		}
	}
	std::cout << "optimal postion: ";
	for (int var = 0; var < NUMBER_VARIABLES; var++)
		std::cout << globalOptimalPosition[var] << "	";
	std::cout << std::endl;
	output();
}

void Particles::init()
{
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		for (int j = 0; j < NUMBER_VARIABLES; j++) {
			particles[i].position[j] =
				MIN_POSITION + (MAX_POSITION - MIN_POSITION)*rand() / double(RAND_MAX);
			particles[i].velocity[j] = 0.;
		} 

		particles[i].OptiamlCost = std::numeric_limits<double>::max();
		
	}
	for (int it = 0; it < ITERATION; it++) {
		globalOptimalCost[it] = std::numeric_limits<double>::max();
	}
}

double Particles::bound(double min, double x, double max)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else return x;

}

void Particles::output()
{
	ofstream outputfile;
	outputfile.open("myfile.txt");
	if (outputfile.fail()) {
		perror("myfile.txt");
	}

	//outputfile << "Iteration	" <<"OptimalCost" << endl;

	for (int it = 0; it < ITERATION; it++) {
		std::cout << "ite " << it
			<< "	Global optimal cost: " << globalOptimalCost[it]
			<< std::endl;

		outputfile << it << "	" << globalOptimalCost[it] << std::endl;
	}

	outputfile.close();
}
