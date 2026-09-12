#include<iostream>
using std::string;
class Employee {
public:
    string Name;
    string Company;
    int Age;

    void IntroduceYourself() {
        std::cout << "Name - " << Name << std::endl;
        std::cout << "Company - " << Company << std::endl;
        std::cout << "Age - " << Age << std::endl;

    }
    Employee(string name, string company, int age) {
        Name = name;
        Company = company;
        Age = age;
    }
};
int main()
{
    Employee employee1 = Employee("Saldina", "YT-CodeBeauty", 25);
    // employee1.Name = "Saldina";
    // employee1.Company = "YT-CodeBeauty";
    // employee1.Age = 25;
    employee1.IntroduceYourself();

    Employee employee2 = Employee("Raj", "Amazon", 17);
    // employee2.Name = "Raj";
    // employee2.Company = "Amazon";
    // employee2.Age = 19;
    employee2.IntroduceYourself();

}




