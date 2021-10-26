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
class lecturer : protected teacher
{
protected:
	int attendance;
	bool grades_for_free_exam;
public:
	void setAttendance(int input)
	{
		if (input > 100) attendance = 100;
		else if (input < 0) attendance = 0;
		else attendance = input;
	}
	void setGrades_for_free_exam(bool input) { grades_for_free_exam = input; }
	int getAttendance() { return attendance; }
	bool getGrades_for_free_exam() { return grades_for_free_exam; }
};
