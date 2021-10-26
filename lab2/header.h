#include <iostream>
#include <string>

namespace teachers
{
	class teacher {
	protected:
		int age;
		char sex;
		string schoolSub;
		int salary;
	public:
		teacher() {}
		~teacher() {}
		void setAge(int input) { age = input }
		void setSalary(int input) { salary = input; }
		void setSchoolSub(string input) { schoolSub = input; }
		void setSex(char input) { sex = input; }
		int getAge() { return age; }
		virtual int getSalary() { return salary; }
		string getSchoolSub() { return schoolSub; }
		char getSex() { return sex; }
	};

	class practical_teacher : virtual private teacher
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

	class lecturer : virtual protected teacher
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

	class professor : public lecturer, public practical_teacher
	{
	protected:
		int degree;
	public:
		void setDegree(int input)
		{
			if (degree > 4) degree = 4;
			else if (degree < 1) degree = 1;
			else degree = input;
		};
		int getDegree() { return degree; }
		int getSalary() override { return salary + 100; }
	};
};
