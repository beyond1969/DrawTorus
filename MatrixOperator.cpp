#include <iostream>
#include <cstdlib>
#include <math.h>
#include "MatrixOperator.h"

using namespace std;

	/* get, set functions */
void Vector3::printVector3() {
		cout << "(" << values[0] << ", " << values[1] << ", " << values[2] << ")" << endl;
	}

Vector3 Vector3::vecNegation() {
	return Vector3(values[0] * -1, values[1] * -1, values[2] * -1);
}
Vector3 Vector3::vecScalarMult(double mult) {
	return Vector3(values[0] * mult, values[1] * mult, values[2] * mult);
}
double Vector3::vecLength() {
	double length = sqrt(
		pow(values[0], 2) + pow(values[1], 2) + pow(values[2], 2));

	return length;
}

	/* get, set functions */
void Matrix3::printMatrix3() {
		cout << "(" << values[0][0] << ", " << values[0][1] << ", " << values[0][2] << ")" << endl;
		cout << "(" << values[1][0] << ", " << values[1][1] << ", " << values[1][2] << ")" << endl;
		cout << "(" << values[2][0] << ", " << values[2][1] << ", " << values[2][2] << ")" << endl;
	}

Matrix3 Matrix3::matNegation() {
	return Matrix3(
		values[0][0] * -1, values[1][0] * -1, values[2][0] * -1,
		values[0][1] * -1, values[1][1] * -1, values[2][1] * -1,
		values[0][2] * -1, values[1][2] * -1, values[2][2] * -1
	);
}

Matrix3 Matrix3::matScalarMult(double mult) {
	return Matrix3(
		values[0][0] * mult, values[1][0] * mult, values[2][0] * mult,
		values[0][1] * mult, values[1][1] * mult, values[2][1] * mult,
		values[0][2] * mult, values[1][2] * mult, values[2][2] * mult
	);
}