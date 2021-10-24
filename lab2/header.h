#include <iostream>

#pragma once
using namespace std;

enum SEX { // gender
	male = 1,
	female = 2
};

class teacher {
public:
	teacher(){}
	~teacher(){}
		
	void setterName( std::string nameTeacher) {
			this->name = nameTeacher;
	}

	void setterAge(int ageTeacher) {
		this->age = ageTeacher;
	}

	void setterSalary(int salaryTeacher ) {
		this->salary = salaryTeacher;
	}

	void setterSchoolSub(std::string schoolSub) {
		this->schoolSub = schoolSub;
	}

	void setterSexTeacher(SEX sexTeahcer) { 
		this->sex = sexTeahcer;
	}


	std::string getterName() {
		return this->name;
	}

	int getterAge(int ageTeacher) {
		return this->age;
	}

	std::string getterSchoolSub() {
		return this->schoolSub;
	}

	int getterSalary() {
		return this->salary;
	}

	SEX getterSexTeacher() {
		return this->sex;
	}


	protected:
		int age;
		SEX sex; 
		std::string name;
		std::string schoolSub;
		int salary;
};
