#include <stdio.h>
#include <math.h>
#include "MeanShift.h"

#define EPSILON 0.001

double euclidean_distance(const vector<double> &point_a, const vector<double> &point_b){
	double total = 0;
	for (int i = 0; i < (int)point_a.size(); i++){
		total += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
	}
	return sqrt(total);
}

double gaussian_kernel(double distance, double kernel_bandwidth){
	double temp = exp(-(distance*distance) / (kernel_bandwidth));
	return temp;
}

void MeanShift::set_kernel(double(*_kernel_func)(double, double)) {
	if (!_kernel_func){
		kernel_func = gaussian_kernel;
	}
	else {
		kernel_func = _kernel_func;
	}
}

vector<double> MeanShift::shift_point(const vector<double> &point, const vector<vector<double> > &points, double kernel_bandwidth) {
	vector<double> shifted_point = point;
	for (int dim = 0; dim < (int)shifted_point.size(); dim++){
		shifted_point[dim] = 0;
	}
	double total_weight = 0;
	for (int i = 0; i < (int)points.size(); i++){
		vector<double> temp_point = points[i];
		double distance = euclidean_distance(point, temp_point);
		double weight = kernel_func(distance, kernel_bandwidth);
		for (int j = 0; j < (int)shifted_point.size(); j++){
			shifted_point[j] += temp_point[j] * weight;
		}
		total_weight += weight;
	}

	for (int i = 0; i < (int)shifted_point.size(); i++){
		shifted_point[i] /= total_weight;
	}
	return shifted_point;
}

vector<vector<double> > MeanShift::cluster(vector<vector<double> > points, double kernel_bandwidth){
	// Set the kernel
	kernel_func = gaussian_kernel;

	std::vector<bool> stop_moving;
	//stop_moving.reserve(points.size());
	stop_moving.resize(points.size());
	vector<vector<double> > shifted_points = points;
	double max_shift_distance;
	do {
		max_shift_distance = 0;
		for (int i = 0; i < (int)shifted_points.size(); i++){
			if (!stop_moving[i]) {
				vector<double>point_new = shift_point(shifted_points[i], points, kernel_bandwidth);
				double shift_distance = euclidean_distance(point_new, shifted_points[i]);
				if (shift_distance > max_shift_distance){
					max_shift_distance = shift_distance;
				}
				if (shift_distance <= EPSILON) {
					stop_moving[i] = true;
				}
				shifted_points[i] = point_new;
			}
		}
		printf("max_shift_distance: %f\n", max_shift_distance);
	} while (max_shift_distance > EPSILON);
	return shifted_points;
}