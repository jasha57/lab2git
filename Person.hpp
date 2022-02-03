#ifndef PERSON_HPP
#define PERSON_HPP

class Person{
    private:
    int age;
    int height;
    public:
    Person(){}
    Person(int  _age, int _height){
        age = _age;
        height = _height;
    }
    Person(const Person & p){
        age = p.age;
        height = p.height;
    }
    int GetAge(){
        return age;
    }
    int GetHeight(){
        return height;
    }
    void SetAge(int _age){
        age = _age;
    }
    void SetHeight(int _height){
        height = _height;
    }
};

int ParamGetAge(Person a){
    return a.GetAge();
}

int ParamGetHeight(Person a){
    return a.GetHeight();
}

#endif