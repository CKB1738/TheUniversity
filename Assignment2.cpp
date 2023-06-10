#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;

static const char SEPARATOR = ',';

class A2ListItem {
private:
    static int instances;
public:
    A2ListItem() {
        instances++;
    }
    virtual int get_id() = 0;
    virtual void print() = 0;
    virtual void print_all() = 0;
    virtual ~A2ListItem() {
        instances--;
    }
    static int countInstances() {
        return instances;
    }
};
int A2ListItem::instances = 0;

class A2List {
private:
    std::vector<A2ListItem*> data;
    static bool compareItems(A2ListItem* a, A2ListItem* b) {
        return a->get_id() < b->get_id();
    }
    bool sorted;
    void sort() {
        std::sort(data.begin(), data.end(), compareItems);
        sorted = true;
    }
protected:
    void destroy_contents() {
        for (auto i = data.begin(); i != data.end(); ++i) {
            delete (*i);
        }
    }
public:
    A2List() {
        sorted = true;
    }
    void add(A2ListItem* value) {
        data.push_back(value);
        sorted = false;
    }
    A2ListItem* find_by_key(int key) {
        auto result = find_if(data.begin(), data.end(),
            [key](A2ListItem* item) {
                return item->get_id() == key;
            }
        );
        if (result == data.end())
            return nullptr;
        else
            return *result;
    }
    void print() {
        if (!sorted)
            sort();
        for (auto i = data.begin(); i != data.end(); ++i) {
            (*i)->print();
        }
    }
    void print_all() {
        if (!sorted)
            sort();
        for (auto i = data.begin(); i != data.end(); ++i) {
            (*i)->print_all();
        }
    }
    virtual ~A2List() = 0;
};
A2List::~A2List() {}

/*** Your classes go here ***/

class A2list1 : public A2List {
public:
    A2list1() :A2List(){};
    
};

//person class
class Person : public A2ListItem {
private:
    int ID;
    string name; 

public:

    Person(int id, string pname) {
        ID = id;
        name = pname;
    }

    int get_id() {
		return ID;

    }
	
    string getname() {
		return name;
    }

    void print() {
		std::cout << "Person: " << name << std::endl;

    }

    void print_all() {
		std::cout << "Person: " << name << std::endl;
		std::cout << "ID" << ID << std::endl;

    }
};

//course class
class Course : A2ListItem {
private:
    int course_num;
    std::string course_name;
    A2List *courseList;

public:
	Course(int num, string name) {
		course_num = num;
		course_name = name;
		courseList = new A2list1();
	}
    int get_id() {
		return course_num;

    }

    void print() {
		std::cout << "Course: " << course_name << std::endl;

    }

    void print_all() {
        std::cout << "Course ID: " << course_num << std::endl;
        std::cout << "Course: " << course_name << std::endl;
        //std::cout << "Courses: " << courseList << std::endl;

    }
};
//student class
class Student : public Person {
private:
    A2list1 *courseList = new A2list1();
public:
    //constructor
    Student(int number, string s_name) : Person(number, s_name) {}
	
	//methods
        void addcourse(Course * scourse){
            ;
			courseList->add((A2ListItem*)scourse);
    }


    void print() {
		std::cout << "Student: " << Person::getname() << std::endl;

    }

    void print_all() {
		std::cout << "Student: " << Person::get_id() << std::endl;
        std::cout << "Student: " << Person::getname() << std::endl;
       // std::cout << "Student: " <<  << std::endl;
		
       
    }
};

class Employee : public Person {
public:
	//constructor
	Employee(int number, string e_name) : Person(number, e_name) {
	}
	//methods
    virtual int weekly_pay() = 0; 

    int get_id() { 
        return Person::get_id();

    }

    void print() {
		std::cout << "Employee: " << Person::getname() << std::endl;

    }

    void print_all() {
		std::cout << "Employee: " << Person::get_id() << std::endl;
        std::cout << "Employee: " << Person::getname() << std::endl;
        //std::cout << "Employee: " << name << std::endl;
		
    }
};

class Instructor : public Person {

	//variables
private:
    int salary = 0;
    A2List *instructor_course;
	
public:
	//constructor
	Instructor(int number, string i_name, int a_salary) : Person(number, i_name) {
		salary = a_salary;
		instructor_course = new A2list1();
		}
	//methods
    int getsalary() {
        return salary;
    }

    static int weekly_Pay(int salary) {
        int wpay;
        wpay = salary / 52;
        return wpay;
    }
	
    int get_id() {
        return Person::get_id();

    }

    void print() {
        std::cout << "Instructor name: " << Person::getname() << std::endl;

    }

    void print_all() {
        std::cout << "Instructor ID: " << Person::get_id() << std::endl;
        std::cout << "instructor name: " << Person::getname() << std::endl;
        std::cout << "Instructor Weekly Pay: " << weekly_Pay(getsalary()) << std::endl;

    }
};

class Administrator : public Person {
	//variables
private:
    int hourly_wage;
    int hourperweek;

public:
	//constructor
	Administrator(int number, string a_name, double hw, int hperweek) : Person(number, a_name) {
		hourly_wage = hw;
		hourperweek = hperweek;
		}

	//methods
    int gethourlywage() {
        return hourly_wage;
    }
    int gethourperweek() {
        return hourperweek;
    }

  static  int weekly_pay(int hourwage, int hourperweek ) {
        int w_pay;
        w_pay = hourwage * hourperweek;
        return w_pay;
    }
  int get_id() {
      return Person::get_id();

  }

  void print() {
      std::cout << "Administrator: " << Person::getname() << std::endl;

  }

  void print_all() {
      std::cout << "Administrator number: " << Person::get_id() << std::endl;
      std::cout << "Administrator name: " << Person::getname() << std::endl;
      std::cout << "Administrator Weekly Pay: " << weekly_pay(gethourlywage(), gethourperweek()) << std::endl;

  }
};

// modify the main program as necessary
int main(int argc, char* argv[]) {
    /**if (argc < 2) {
        std::cout << "usage: " << argv[0] << " inputfile.txt\n";
        std::exit(0);
    }**/

    std::string line;
    std::ifstream input("a2q2.txt");

    while (std::getline(input, line)) {
        std::istringstream stream(line);
        int number;
        std::string token;
        std::getline(stream, token, SEPARATOR);
        std::string name;
        //A2ListItem* courses;
       // A2List* s_courses;

        // do not print any output until you've read everything in!
        if (token == "student") {
            //std::cout << "student";
            
			A2list1 *list1 = new A2list1();
            int num = 0;
            

            std::getline(stream, token, SEPARATOR);
            number = std::stoi(token);
            //std::cout << " number: " << number;

            std::getline(stream, token, SEPARATOR);
            name = token;
           // std::cout << " name: " << token << std::endl;

            while (std::getline(stream, token, SEPARATOR)) {
                int course = std::stoi(token);
                //list1->add((A2ListItem*) course);
				//std::cout << " course: " << course << std::endl;
                num++;
               // std::cout << "  course: " << course << std::endl;
            }
			

            Student student = Student(number, name);
            student.print_all();
        }
        else if (token == "course") {
            // ...
           // std::cout << "course";

            std::getline(stream, token, SEPARATOR);
            number = std::stoi(token);
           // std::cout << " number: " << number;

            std::getline(stream, token, SEPARATOR);
           // std::cout << " name: " << token << std::endl;

            Course course = Course(number, token);
            course.print_all();

        }
        
        else if (token == "instructor") {
            //std::cout << "instructor";

            std::getline(stream, token, SEPARATOR);
            number = std::stoi(token);
            //std::cout << " number: " << number;

            std::getline(stream, token, SEPARATOR);
			name = token;
            //std::cout << " name: " << token << std::endl;

            std::getline(stream, token, SEPARATOR);
            int i_salary = std::stoi(token);
           // std::cout << "Weekly pay: " << Instructor::weekly_Pay(i_salary) << std::endl;

            while (std::getline(stream, token, SEPARATOR)) {
                int course = std::stoi(token);
                //std::cout << "  course: " << course << std::endl;
            }
			Instructor instructor = Instructor(number, name, i_salary);
            instructor.print_all();
        }
        else {
            //std::cout << "administrator";

            std::getline(stream, token, SEPARATOR);
            number = std::stoi(token);
            //std::cout << " number: " << number;

            std::getline(stream, token, SEPARATOR);
			name = token;
           // std::cout << " name: " << token << std::endl;

            std::getline(stream, token, SEPARATOR);
            int h_wage = std::stoi(token);
            std::getline(stream, token, SEPARATOR);
            int h_perweek = std::stoi(token);
            //std::cout << "Weekly pay: " << Administrator::weekly_pay(h_wage, h_perweek) << std::endl;

			Administrator administrator = Administrator(number, name, h_wage, h_perweek);
            administrator.print_all();

            /***while (std::getline(stream, token, SEPARATOR)) {
                int course = std::stoi(token);
                std::cout << "  course: " << course << std::endl;
            }*/
        }
    }

    // This should be the last line of your program
    std::cout << "\nNumber of objects leaked: " << A2ListItem::countInstances() << std::endl;
}