#ifndef COMPLEX_
#define COMPLEX_
#include<string>
#include<stdexcept>
#include<iostream>
#include<sstream>

/**
*
* @class Complex that creates and complex number and does complex math
*
*/
class Complex {
	double real = 0; // private member variables real and imagianry
	double imaginary = 0;
public:
	/**
	constexpr constructor creating complex object
	@param none, one or two doubles
	@return complex object
	*/
	constexpr Complex(double _real = 0, double _imaginary = 0) : real(_real), imaginary(_imaginary) {};


	/**
	constructor creating complex object
	@param ref to const string
	@return complex object
	*/
	Complex(const std::string& input);

	Complex& operator=(const Complex& other) {
		// Check for self-assignment
		if (this == &other) {
			return *this; // Return the current instance (no-op)
		}

		// Assign values from the other instance
		real = other.real;
		imaginary = other.imaginary;

		// Return the current instance for chaining
		return *this;
	}


	/**
	constexpr unary operator adding complex object
	@param ref to const complex
	@return ref to complex

	*/
	constexpr Complex& operator+=(const Complex& addition);


	/**
	constexpr operator returning object
	@param nothing
	@return complex

	*/
	constexpr Complex operator+() const;


	/**
	constexpr prefix increment operator for real
	@param nothing
	@return ref to complex

	*/
	constexpr Complex& operator++();


	/**
	constexpr post fix increment operator for real
	@param int
	@return ref to complex

	*/
	constexpr Complex& operator++(int);

	/**
	constexpr unary operator subtracting complex object
	@param ref to const complex
	@return ref to complex

	*/
	constexpr Complex& operator-=(const Complex& subtract);

	/**
	constexpr operator returning negated object marked const
	@param nothing
	@return complex

	*/
	constexpr Complex operator-() const;


	/**
	constexpr prefix decrement operator for real
	@param nothing
	@return ref to complex

	*/
	constexpr Complex& operator--();

	/**
	constexpr post fix decrement operator for real
	@param int
	@return ref to complex

	*/
	constexpr Complex operator--(int);

	/**
	constexpr unary operator multiplying complex object
	@param ref to const complex
	@return ref to complex

	*/
	constexpr Complex& operator*=(const Complex& multiply);

	/**
	constexpr unary operator dividing complex object
	@param ref to const complex
	@return ref to complex

	*/
	constexpr Complex& operator/=(const Complex& div);

	/**
	constexpr operator returning conjugated object marked const
	@param nothing
	@return complex

	*/
	constexpr Complex operator~() const;

	/**
	constexpr  call operator returning 0 object
	@param nothing
	@return ref to complex

	*/
	constexpr Complex& operator()();


	/**
	subscript operator returning variable
	@param ref to const string
	@return ref to double

	*/
	double& operator[](const std::string& input);


	/**
	subscript operator returning variable marked const
	@param ref to const string
	@return double

	*/
	double operator[](const std::string& input)const;

	/**
	friend operator couting complex
	@param ref to ostream, ref to const complex
	@return ref to ostream

	*/
	friend std::ostream& operator<<(std::ostream& out, const Complex& _complex);

	/**
	friend operator reading from stream
	@param ref to istream, ref to complex
	@return ref to istreamm

	*/
	friend std::istream& operator >>(std::istream& in, Complex& _complex);


	/**
	operator converting to string marked const
	@param nothing
	@return string

	*/
	operator std::string() const;

	/**
	friend constexpr operator less than comparison
	@param ref to const complex, ref to const complex
	@return bool

	*/
	friend constexpr bool operator<(const Complex& one, const Complex& two);

};
/**
constexpr binary operator adding to complexs
@param complex, ref to const complex
@return complex
*/
constexpr Complex operator+(Complex left, const Complex& right);

/**
constexpr binary operator subtratcing to complexs
@param complex, ref to const complex
@return complex
*/
constexpr Complex operator-(Complex left, const Complex& right);

/**
constexpr binary operator multiplying to complexs
@param complex, ref to const complex
@return complex
*/
constexpr Complex operator*(Complex left, const Complex& right);

/**
constexpr binary operator dividing to complexs
@param complex, ref to const complex
@return complex
*/
constexpr Complex operator/(Complex left, const Complex& right);

/**
constexpr operator equals comparison
@param ref to const complex, ref to const complex
@return bool

*/
constexpr bool operator==(const Complex& one, const Complex& two);

/**
constexpr operator greater than comparison
@param ref to const complex, ref to const complex
@return bool

*/
constexpr bool operator>(const Complex& one, const Complex& two);

/**
constexpr operator less than or equals comparison
@param ref to const complex, ref to const complex
@return bool

*/
constexpr bool operator<=(const Complex& one, const Complex& two);

/**
constexpr operator greater than or equal comparison
@param ref to const complex, ref to const complex
@return bool

*/
constexpr bool operator>=(const Complex& one, const Complex& two);

/**
constexpr operator not equals comparison
@param ref to const complex, ref to const complex
@return bool

*/
constexpr bool operator!=(const Complex& one, const Complex& two);

constexpr Complex operator ""_i(long double u);


constexpr Complex& Complex::operator+=(const Complex& addition) {
	real += addition.real; //+= real and imaginary parts
	imaginary += addition.imaginary;
	return *this; //return this object
}

constexpr Complex Complex::operator+() const {
	return *this; // retunr this object
}

constexpr Complex& Complex::operator++() {
	++real; // add to real and return
	return *this;
}
constexpr Complex& Complex::operator++(int) {
	Complex one(*this); //create a copy of this 
	++(*this); // add to this object
	return one; //return the copy
}

constexpr Complex& Complex::operator-=(const Complex& subtract) {
	real -= subtract.real; //subtract real and imaginary parts
	imaginary -= subtract.imaginary;
	return *this; // return this
}
constexpr Complex Complex::operator-() const {
	return Complex(-real, -imaginary); // retuen object with negated real and imaginary
}
constexpr Complex& Complex::operator--() {
	real--; //subtract real
	return *this; //return this
}
constexpr Complex Complex::operator--(int) {
	Complex one(*this); //create copy of this
	--(*this); // subtract
	return one; //return copy
}
constexpr Complex& Complex::operator*=(const Complex& multiply) {
	double fake_real = ((real * multiply.real) - (imaginary * multiply.imaginary));// create temp and do math
	double fake_imaginary = (imaginary * multiply.real) + (real * multiply.imaginary); // create temp and do math
	real = fake_real; //initalize varibales to temps
	imaginary = fake_imaginary;
	return *this; // return this
}

constexpr Complex& Complex::operator/=(const Complex& div) {
	double fake_real = ((real * div.real) + (imaginary * div.imaginary)) / ((div.real * div.real) + (div.imaginary * div.imaginary)); // create temps and do math
	double fake_imaginary = (((imaginary * div.real) - (real * div.imaginary)) / ((div.real * div.real) + (div.imaginary * div.imaginary)));
	real = (fake_real); //initalize variables to temps
	imaginary = fake_imaginary;
	return *this; //return this
}

constexpr Complex Complex::operator~() const {
	return Complex(real, -imaginary); // return object with negated imaginary
}

constexpr Complex& Complex::operator()() {
	real = 0;
	imaginary = 0;
	return *this; // return this with values set to 0
}

constexpr bool operator<(const Complex& one, const Complex& two) {
	if (one.real < two.real) { //if real one is less than real two
		return true; // return true
	}
	else if (one.real > two.real) {
		return false; // otherwise return false
	}
	else if ((one.real == two.real)) { // if they are equal
		if (one.imaginary < two.imaginary) { // and imaginary one is less then imaginary two
			return true; // return true
		}
		else if (one.imaginary > two.imaginary) { // otherwise return false
			return false;
		}
		else {
			return false;
		}
	}
	else {}
	return false;
}

constexpr bool operator==(const Complex& one, const Complex& two) {
	return!((one < two) || (two < one)); //return bool of this
}

constexpr bool operator>(const Complex& one, const Complex& two) {
	return!(one < two); // return opposite of < operator
}

constexpr bool operator<=(const Complex& one, const Complex& two) {
	return (one == two || one < two);//return bool of this
}

constexpr bool operator>=(const Complex& one, const Complex& two) {
	return (one == two || one > two);//return bool of this
}
constexpr bool operator!=(const Complex& one, const Complex& two) {
	return !(one == two);//return opposite of == operator
}
constexpr Complex operator-(Complex left, const Complex& right) {
	return left -= right; // return object of this subtraction
}

constexpr Complex operator+(Complex left, const Complex& right) {
	return left += right;// return object of this addition
}
constexpr Complex operator/(Complex left, const Complex& right) {
	return left /= right; // return object of this division
}

constexpr Complex operator*(Complex left, const Complex& right) {
	return left *= right; // return object of this multiplication
}

constexpr Complex operator ""_i(long double u) {
	return Complex(0, static_cast<double>(u)); //return object with u as a double and real as 0
}
#endif
