#include "Complex.h"
#include<string>
#include<stdexcept>
#include<iostream>
#include<sstream>

Complex::Complex(const std::string& input) { // constructor with string input
	std::stringstream in(input);//string stream with an input
	real = 0; //initialize both real and imaginary
	imaginary = 0;
	double temp = 0; // create a temp and intialize to 0

	if (in.peek() == '-') { // if next char is minus
		in.get(); //get to move stream buffer
		if (in.peek() == 'i') {
			--imaginary; // check if the next one is i and --imaginary
			in.get();
			in.get();
		}
		else {
			in.unget(); //otherwise unget to move buffer back 
		}
	}
	else if (in.peek() == 'i') { // else if next char is 1
		++imaginary; // ++imaginary
		in.get(); // move buffer past the i
		in.get();
	}
	else {}
	while (in.peek() == 'i') { // while peek is i
		in.unget(); //move back to check sign
		if (in.peek() == '-') { // if minus subtract imaginary
			--imaginary;
		}
		else { //otherwise ++imaginary
			++imaginary;
		}
		in.get(); //move past the i
		in.get();
		in.get();
	}

	if (in.eof()) { // if the file is over
		if (imaginary == 0) { // if imaginary is 0 then the string was empty so we throw exception
			throw std::logic_error("bad string: " + input);
		}
		else {
			return; //otherwise return to end the construction
		}
	}
	else {}
	in >> temp; // read in a temp
	if (in.fail()) { // if it failed throw exception
		throw std::logic_error("bad string: " + input);
	}
	else {}
	while (!in.eof()) { //while file is not at eof
		if (in.eof()) { // check if file is eof. for some reason i had to do this despite the while loop otherwise it wouldnt work
			break;
		}
		else if (in.peek() == 'i') { // if peek is i 
			imaginary += temp; //add temp to imaginary
			temp = 0; // set temp to 0
			in.get();
			if (in.peek() == '+') { //if next char is +
				in.get();
				if (in.peek() == 'i') {//check if next is i 
					++imaginary; // add imaginary 
					in.get();
					in.get();
				}
				else {
					in.unget(); //otherwise unget
				}
			}
			else if (in.peek() == '-') {// if peek is minus
				in.get();
				if (in.peek() == 'i') { // if is i 
					--imaginary; //subtract imaginary
					in.get();
					in.get();
				}
				else {
					in.unget(); //otherwise move back 
				}
			}
			else {}

		}
		else if (in.peek() == '+') { // if peek is +
			in.get();
			if (in.peek() == 'i') { // if next is i 
				++imaginary; // plus imaginary
				in.get();
				in.get();
			}
			else {
				in.unget(); //otherwise unget and add real to temp
				real += temp;
				temp = 0; //set temp to 0
			}
		}
		else if (in.peek() == '-') { //if peek is -
			in.get();
			if (in.peek() == 'i') { // if next is i
				--imaginary;//subtract imaginary
				in.get();
				in.get();
			}
			else {
				in.unget(); //otherwise unget and add temp to real
				real += temp;
				temp = 0; //set temp to 0
			}
		}
		else if (in.fail()) {
			throw std::logic_error("bad string: " + input); //if stream failed then throw exception
		}
		else {
			real += temp; //otherwise add temp to real
			temp = 0;
		}
		in >> temp; // read in temp

	}
	real += temp; // add temp to real in case of real variable being last double read 
};




double& Complex::operator[](const std::string& input) { //subscript operator returnong reference
	if (input == "real") { // if string is real
		return real; //return real
	}
	else if (input == "imag") { //if string is imag
		return imaginary; // return imaginary
	}
	else {
		throw std::out_of_range("invalid index: " + input); //otherwise throw exception
	}

}

double Complex::operator[](const std::string& input) const { //subscript operator marked as const returning value
	if (input == "real") {// if string is real
		return real;//return real
	}
	else if (input == "imag") {//if string is imag
		return imaginary;// return imaginary
	}
	else {
		throw std::out_of_range("invalid index: " + input);//otherwise throw exception
	}

}


std::ostream& operator<<(std::ostream& out, const Complex& _complex) {
	std::string return_string = _complex; //convert complex to string 
	out << return_string; // out the string
	return out; // return out
}
std::istream& operator >>(std::istream& in, Complex& _complex) {
	in >> _complex.real >> _complex.imaginary; // read in the real and imaginary numbers
	if (in.fail()) { // if fail throw exception
		throw std::runtime_error("read error");
	}
	return in; // return in
}

Complex::operator std::string() const {

	std::stringstream in; //define some temp variables
	std::string real1;
	std::string imaginary1;

	in << real; // read in real
	real1 = in.str(); // initalize real to what was read
	in << imaginary; // read in imaginary
	imaginary1 = in.str(); //intialize imaginary to what was read
	int pos = real1.size(); //int from size of real string size
	imaginary1.erase(0, pos); // erase the first bit as it will read both numbers 
	std::string return_string;
	if (real == 0) { // if real is 0
		if (imaginary == 0) { // check imaginary and make the return_string
			return_string = '0';
		}
		else if (imaginary == 1) {
			return_string = 'i';
		}
		else if (imaginary == -1) {
			return_string = "-i";
		}
		else if (imaginary > 0) {
			return_string = imaginary1 + 'i';
		}
		else if (imaginary < 0) {
			return_string = imaginary1 + 'i';
		}
		else {}
	}
	else if (real != 0) { // if real is not 0
		if (imaginary == 0) { // check imaginary and make th ereturn string
			return_string = real1;
		}
		else if (imaginary == 1) {
			return_string = real + '+i';
		}
		else if (imaginary == -1) {
			return_string = real + '-i';
		}
		else if (imaginary > 0) {
			return_string = real1 + '+' + imaginary1 + 'i';
		}
		else if (imaginary < 0) {
			return_string = real1 + imaginary1 + 'i';
		}
		else {}

	}
	else {}

	return return_string; // return return string

}
