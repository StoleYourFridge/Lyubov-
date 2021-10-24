#include <iostream>
#include <string>

class teacher {
protected:
	int age;
	char sex;
	string schoolSub;
	int salary;
public:
	teacher(){}
	~teacher(){}
	void setAge(int input) { age = input }
	void setSalary(int input) { salary = input; }
	void setSchoolSub(string input) { schoolSub = input; }
	void setSex(char input) { sex = input; }
	int getAge() { return age; }
	int getSalary() { return salary; }
	string getSchoolSub() { return schoolSub; }
	char getSex() { return sex; }
};
