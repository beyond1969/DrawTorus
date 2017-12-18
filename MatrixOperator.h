#pragma once

class Vector3 {
private:
	/*
	(x,y,z)			([0],[1],[2])
	*/
	double values[3];

public:
	Vector3() {
		values[0] = 0; values[1] = 0; values[2] = 0;
	}
	Vector3(double x, double y, double z) {
		values[0] = x; values[1] = y; values[2] = z;
	}
	~Vector3() {}

	/* get, set functions */
	void printVector3();
	double getVector31() const {
		return values[0];
	}
	double getVector32() const {
		return values[1];
	}
	double getVector33() const {
		return values[2];
	}
	void setVector3(double x, double y, double z) {
		values[0] = x; values[1] = y; values[2] = z;
	}
	void setVector31(double x) {
		values[0] = x;
	}
	void setVector32(double y) {
		values[1] = y;
	}
	void setVector33(double z) {
		values[2] = z;
	}

	// operators
	Vector3 operator+(const Vector3& right) {
		double x, y, z;
		x = this->values[0] + right.getVector31();
		y = this->values[1] + right.getVector32();
		z = this->values[2] + right.getVector33();

		return Vector3(x, y, z);
	}
	Vector3 operator-(const Vector3& right) {
		double x, y, z;
		x = this->values[0] - right.getVector31();
		y = this->values[1] - right.getVector32();
		z = this->values[2] - right.getVector33();

		return Vector3(x, y, z);
	}
	double operator%(const Vector3& right) {
		double x, y, z;
		x = this->values[0] * right.getVector31();
		y = this->values[1] * right.getVector32();
		z = this->values[2] * right.getVector33();

		return (x + y + z);
	}
	Vector3 operator*(const Vector3& right) {
		double x, y, z;
		x = (this->values[1] * right.getVector33()) - (this->values[2] * right.getVector32());
		y = (this->values[2] * right.getVector31()) - (this->values[0] * right.getVector33());
		z = (this->values[0] * right.getVector32()) - (this->values[1] * right.getVector31());

		return Vector3(x, y, z);
	}

	Vector3 vecNegation();
	Vector3 vecScalarMult(double mult);
	double vecLength();
};

class Matrix3 {
private:
	double values[3][3];

public:
	/*
	(a11, a12, a13)			([0][0], [0][1], [0][2])
	(a21, a22, a23)			([1][0], [1][1], [1][2])
	(a31, a32, a33)			([2][0], [2][1], [2][2])
	*/
	Matrix3() {
		values[0][0] = 0; values[0][1] = 0; values[0][2] = 0;
		values[1][0] = 0; values[1][1] = 0; values[1][2] = 0;
		values[2][0] = 0; values[2][1] = 0; values[2][2] = 0;
	}
	Matrix3(int i) {
		values[0][0] = 1; values[0][1] = 0; values[0][2] = 0;
		values[1][0] = 0; values[1][1] = 1; values[1][2] = 0;
		values[2][0] = 0; values[2][1] = 0; values[2][2] = 1;
	}
	Matrix3(double a11, double a12, double a13,
		double a21, double a22, double a23,
		double a31, double a32, double a33) {
		values[0][0] = a11; values[0][1] = a12; values[0][2] = a13;
		values[1][0] = a21; values[1][1] = a22; values[1][2] = a23;
		values[2][0] = a31; values[2][1] = a32; values[2][2] = a33;
	}
	~Matrix3() {}

	/* get, set functions */
	void printMatrix3();
	// Column Vecters
	Vector3 getCol1() const {
		return Vector3(values[0][0], values[1][0], values[2][0]);
	}
	Vector3 getCol2() const {
		return Vector3(values[0][1], values[1][1], values[2][1]);
	}
	Vector3 getCol3() const {
		return Vector3(values[0][2], values[1][2], values[2][2]);
	}
	void setCol1(double x, double y, double z) {
		values[0][0] = x; values[1][0] = y; values[2][0] = z;
	}
	void setCol2(double x, double y, double z) {
		values[0][1] = x; values[1][1] = y; values[2][1] = z;
	}
	void setCol3(double x, double y, double z) {
		values[0][2] = x; values[1][2] = y; values[2][2] = z;
	}
	// Row Vecters
	Vector3 getRow1() const {
		return Vector3(values[0][0], values[0][1], values[0][2]);
	}
	Vector3 getRow2() const {
		return Vector3(values[1][0], values[1][1], values[1][2]);
	}
	Vector3 getRow3() const {
		return Vector3(values[2][0], values[2][1], values[2][2]);
	}
	void setRow1(double x, double y, double z) {
		values[0][0] = x; values[0][1] = y; values[0][2] = z;
	}
	void setRow2(double x, double y, double z) {
		values[1][0] = x; values[1][1] = y; values[1][2] = z;
	}
	void setRow3(double x, double y, double z) {
		values[2][0] = x; values[2][1] = y; values[2][2] = z;
	}
	// Component-wise
	double getMatrix11() const { return values[0][0]; }	double getMatrix12() const { return values[0][1]; }	double getMatrix13() const { return values[0][2]; }
	double getMatrix21() const { return values[1][0]; }	double getMatrix22() const { return values[1][1]; }	double getMatrix23() const { return values[1][2]; }
	double getMatrix31() const { return values[2][0]; }	double getMatrix32() const { return values[2][1]; }	double getMatrix33() const { return values[2][2]; }
	void setMatrix11(double c) { values[0][0] = c; }	void setMatrix12(double c) { values[0][1] = c; }	void setMatrix13(double c) { values[0][2] = c; }
	void setMatrix21(double c) { values[1][0] = c; }	void setMatrix22(double c) { values[1][1] = c; }	void setMatrix23(double c) { values[1][2] = c; }
	void setMatrix31(double c) { values[2][0] = c; }	void setMatrix32(double c) { values[2][1] = c; }	void setMatrix33(double c) { values[2][2] = c; }

	// operators
	Matrix3 operator+(const Matrix3& right) {
		Vector3 row1; Vector3 row2; Vector3 row3;
		row1 = this->getRow1() + right.getRow1();
		row2 = this->getRow2() + right.getRow2();
		row3 = this->getRow3() + right.getRow3();

		return Matrix3(row1.getVector31(), row1.getVector32(), row1.getVector33(),
			row2.getVector31(), row2.getVector32(), row2.getVector33(),
			row3.getVector31(), row3.getVector32(), row3.getVector33());
	}
	Matrix3 operator-(const Matrix3& right) {
		Vector3 row1; Vector3 row2; Vector3 row3;
		row1 = this->getRow1() - right.getRow1();
		row2 = this->getRow2() - right.getRow2();
		row3 = this->getRow3() - right.getRow3();

		return Matrix3(row1.getVector31(), row1.getVector32(), row1.getVector33(),
			row2.getVector31(), row2.getVector32(), row2.getVector33(),
			row3.getVector31(), row3.getVector32(), row3.getVector33());
	}
	Vector3 operator*(const Vector3& right) {
		double x, y, z;
		x = this->getRow1() % right;
		y = this->getRow2() % right;
		z = this->getRow3() % right;

		return Vector3(x, y, z);
	}
	Matrix3 operator*(const Matrix3& right) {
		double a11, a12, a13, a21, a22, a23, a31, a32, a33;
		a11 = this->getRow1() % right.getCol1(); a12 = this->getRow1() % right.getCol2(); a13 = this->getRow1() % right.getCol3();
		a21 = this->getRow2() % right.getCol1(); a22 = this->getRow2() % right.getCol2(); a23 = this->getRow2() % right.getCol3();
		a31 = this->getRow3() % right.getCol1(); a32 = this->getRow3() % right.getCol2(); a33 = this->getRow3() % right.getCol3();

		return Matrix3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
	}
	Matrix3 Matrix3::matNegation();
	Matrix3 Matrix3::matScalarMult(double mult);
};