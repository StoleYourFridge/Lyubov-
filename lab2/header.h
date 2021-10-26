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
class practical_teacher : private teacher
{
protected:
	bool grades_for_free_credit;
	bool attitude_to_attendance;

public:
	void setGrades_for_free_credit(bool input) { grades_for_free_credit = input; }
	void setAttitude_to_attendance(bool input) { attitude_to_attendance = input; }
	bool getGrades_for_free_credit() { return grades_for_free_credit; }
	bool getAttitude_to_attendance() { return attitude_to_attendance; }
};