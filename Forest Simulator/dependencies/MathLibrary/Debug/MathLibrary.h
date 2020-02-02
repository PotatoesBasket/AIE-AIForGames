#pragma once

const float PI = 3.141592653f;

const float DegToRad(float degrees);
const float RadToDeg(float radians);

class Binary
{
public:
	/*Returns the decimal conversion of given binary string.*/
	int binToDec(const char* binaryString);

	/*Writes the given decimal value as binary into given string.
	- Requires length of binary string it will be contained in.*/
	void decToBin(char* binaryString, int length, int value);

	/*Set one bit in given bitfield.
	- Leftmost position is index 0*/
	void setBit(char& bitfield, char bit, char value);

	/*Returns value at given position (bit) in bitfield.
	- Leftmost position is index 0*/
	char checkBit(char& bitfield, char bit);
};

class Vector2
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float data[2];
	};

	Vector2() : x{ 0 }, y{ 0 } {}
	Vector2(float x, float y) : x{ x }, y{ y } {}
	Vector2(const Vector2& other) : x{ other.x }, y{ other.y } {}

	Vector2& operator = (const Vector2& other);

	//Math operators
	Vector2 operator + (const Vector2& other) const;
	Vector2& operator += (const Vector2& other);

	Vector2 operator - (const Vector2& other) const;
	Vector2& operator -= (const Vector2& other);

	Vector2 operator * (float scalar) const;
	friend Vector2 operator * (float scalar, const Vector2& v);
	Vector2& operator *= (float scalar);

	Vector2 operator / (float scalar) const;
	Vector2& operator /= (float scalar);

	//Sub-script operator
	float operator [] (int index) const;
	float& operator [] (int index);

	//Casting to array of floats
	operator float* ();
	operator const float* () const;
	
	//Returns distance between this and other vector
	float distance(const Vector2& other) const;
	//Returns distance between this and other vector squared
	float distanceSqr(const Vector2& other) const;

	//Returns length of vector
	float magnitude() const;
	//Returns length of vector squared
	float magnitudeSqr() const;

	//Normalises vector
	void normalise();
	//Returns a normalised version of vector
	Vector2 normalised() const;

	//Returns the dot product of this and other vector
	float dot(const Vector2& other) const;
};

class Vector3
{
public:
	union
	{
		struct
		{
			float x, y;
			union
			{
				float z, t; //t = translation for homogeneous coordinates
			};
		};
		float data[3];
	};

	Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
	Vector3(const Vector2& other) : x{ other.x }, y{ other.y }, z{ 0 } {}
	Vector3(const Vector3& other) : x{ other.x }, y{ other.y }, z{ other.z } {}

	Vector3& operator = (const Vector2& other);
	Vector3& operator = (const Vector3& other);

	//Math operators
	Vector3 operator + (const Vector3& other) const;
	Vector3& operator += (const Vector3& other);
	
	Vector3 operator - (const Vector3& other) const;
	Vector3& operator -= (const Vector3& other);

	Vector3 operator * (float scalar) const;
	friend Vector3 operator * (float scalar, const Vector3& v);
	Vector3& operator *= (float scalar);

	Vector3 operator / (float scalar) const;
	Vector3& operator /= (float scalar);

	//Sub-script operator
	float operator [] (int index) const;
	float& operator [] (int index);

	//Casting to array of floats
	operator float* ();
	operator const float* () const;
	
	//Returns distance between this and other vector
	float distance(const Vector3& other) const;
	//Returns distance between this and other vector squared
	float distanceSqr(const Vector3& other) const;

	//Returns length of vector
	float magnitude() const;
	//Returns length of vector squared
	float magnitudeSqr() const;

	//Normalises vector
	void normalise();
	//Returns a normalised version of vector
	Vector3 normalised() const;

	//Returns the dot product of this and other vector
	float dot(const Vector3& other) const;

	/*Returns a vector that is perpendicular to this and other vector
	- Is not normalised, length is the dot product of given vectors.*/
	Vector3 cross(const Vector3& other) const;
};

class Vector4
{
public:
	union
	{
		struct
		{
			float x, y, z;
			union
			{
				float w, t; //t = translation for homogeneous coordinates
			};
		};
		float data[4];
	};

	Vector4() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}
	Vector4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}
	Vector4(const Vector3& other) : x{ other.x }, y{ other.y }, z{ other.z }, w{ 0 } {}
	Vector4(const Vector4& other) : x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w } {}

	Vector4& operator = (const Vector3& other);
	Vector4& operator = (const Vector4& other);

	//Math operators
	Vector4 operator + (const Vector4& other) const;
	Vector4& operator += (const Vector4& other);

	Vector4 operator - (const Vector4& other) const;
	Vector4& operator -= (const Vector4& other);

	Vector4 operator * (float scalar) const;
	friend Vector4 operator * (float scalar, const Vector4& v);
	Vector4& operator *= (float scalar);

	Vector4 operator / (float scalar) const;
	Vector4& operator /= (float scalar);

	//Sub-script operator
	float operator [] (int index) const;
	float& operator [] (int index);

	//Casting to array of floats
	operator float* ();
	operator const float* () const;

	//Returns distance between this and other vector
	float distance(const Vector4& other) const;
	//Returns distance between this and other vector squared
	float distanceSqr(const Vector4& other) const;

	//Returns length of vector
	float magnitude() const;
	//Returns length of vector squared
	float magnitudeSqr() const;

	//Normalises vector
	void normalise();
	//Returns a normalised version of vector
	Vector4 normalised() const;

	//Returns the dot product of this and other vector
	float dot(const Vector4& other) const;

	/*Returns a vector that is perpendicular to this and other vector
	- Is not normalised, length is the dot product of given vectors.*/
	Vector4 cross(const Vector4& other) const;
};

class Matrix2
{
public:
	union
	{
		struct
		{
			Vector2 xAxis, yAxis;
		};
		Vector2 axis[2];
		float data[2][2];
		float floats[4];
	};

	static const Matrix2 identity;

	Matrix2() : xAxis{ 0, 0 }, yAxis{ 0, 0 } {}
	Matrix2(Vector2 xAxis, Vector2 yAxis);
	Matrix2(float XX, float XY, float YX, float YY);
	Matrix2(const Matrix2& other) : xAxis{ other.xAxis }, yAxis{ other.yAxis } {}

	Matrix2& operator = (const Matrix2& other);

	//Multiplication
	Vector2 operator * (const Vector2& v) const;
	Matrix2 operator * (const Matrix2& other) const;

	//Sub-script operator
	Vector2& operator [] (int index);
	const Vector2& operator [] (int index) const;

	//Casting to array of floats
	operator float* ();
	operator const float* () const;

	//Returns a version of the matrix that is flipped diagonally
	Matrix2 transposed() const;

	//Rotating
	void setRotate(float radians);
	void rotate(float radians);

	//Scaling
	void setScaled(float x, float y);
	void setScaled(const Vector2& v);
	void scale(float x, float y);
	void scale(const Vector2& v);
};

class Matrix3
{
public:
	union
	{
		struct
		{
			Vector3 xAxis, yAxis;
			union
			{
				Vector3 zAxis, translation;
			};
		};
		Vector3 axis[3];
		float data[3][3];
		float floats[9];
	};

	static const Matrix3 identity;

	Matrix3() : xAxis{ 0, 0, 0 }, yAxis{ 0, 0, 0 }, zAxis{ 0, 0, 0 } {}
	Matrix3(Vector3 xAxis, Vector3 yAxis, Vector3 zAxis);
	Matrix3(float XX, float XY, float XZ,
		float YX, float YY, float YZ,
		float ZX, float ZY, float ZZ);
	Matrix3(const Matrix3& other);

	Matrix3& operator = (const Matrix3& other);

	//Multiplication
	Vector3 operator * (const Vector3& v) const;
	Matrix3 operator * (const Matrix3& other) const;
	
	//Sub-script operator
	Vector3& operator [] (int index);
	const Vector3& operator [] (int index) const;

	//Casting to array of floats
	operator float* ();
	operator const float* () const;

	//Returns the current angle the object has been rotated on its Z axis in radians
	float getRotation() const;
	//Returns a version of the matrix that is flipped diagonally
	Matrix3 transposed() const;

	//Positioning
	void setPosition(float x, float y);
	void setPosition(const Vector3& v);
	void move(float x, float y);
	void move(const Vector3& v);

	//Rotating
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
	void rotate(float pitch, float yaw, float roll);

	//Scaling
	void scale(float x, float y, float z);
	void scale(const Vector3& v);

private:
	//Creates new matrices to multiply working matrix by
	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setScaled(float x, float y, float z);
	void setScaled(const Vector3& v);
};

class Matrix4
{
public:
	union
	{
		struct
		{
			Vector4 xAxis, yAxis, zAxis, translation;
		};
		Vector4 axis[4];
		float data[4][4];
		float floats[16];
	};

	static const Matrix4 identity;

	Matrix4();
	Matrix4(Vector4 xAxis, Vector4 yAxis, Vector4 zAxis, Vector4 translation);
	Matrix4(float XX, float XY, float XZ, float XW, float YX, float YY, float YZ, float YW,
		float ZX, float ZY, float ZZ, float ZW, float TX, float TY, float TZ, float TW);
	Matrix4(const Matrix4& other);

	Matrix4& operator = (const Matrix4& other);

	//Multiplication
	Vector4 operator * (const Vector4& v) const;
	Matrix4 operator * (const Matrix4& other) const;

	//Sub-script operator
	Vector4& operator [] (int index);
	const Vector4& operator [] (int index) const;

	//Casting to array of floats
	operator float* ();
	operator const float* () const;

	//Returns a version of the matrix that is flipped diagonally
	Matrix4 transposed() const;

	//Positioning
	void setPosition(float x, float y, float z);
	void setPosition(const Vector4& v);
	void move(float x, float y, float z);
	void move(const Vector4& v);

	//Rotating
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
	void rotate(float pitch, float yaw, float roll);

	//Scaling
	void scale(float x, float y, float z);
	void scale(const Vector4& v);

private:
	//Creates new matrices to multiply working matrix by
	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setScaled(float x, float y, float z);
	void setScaled(const Vector4& v);
};