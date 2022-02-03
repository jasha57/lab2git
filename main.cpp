#include <iostream>
#include <fstream>
#include <string>
#include "Person.hpp"
#include "Histogram.hpp"

int main(){
    std::cout << "Hello in Mashalab2" << std::endl;
    std::cout << "My lab is about Histogram" << std::endl;
    std::cout << "Enter filename for data reading (data is about human race)" << std::endl;
    std::string filename;
    std::cin >> filename;
    std::fstream fin(filename);
    if(!fin.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return 0;
    }
    int n = 0;
    fin >> n;
    Person * data = new Person[n];
    for(int i = 0; i < n; i++){
        int age, height;
        fin >> age >> height;
        data[i].SetAge(age);
        data[i].SetHeight(height);
    }
    std::cout << "Enter histogram parameter(1 - age, 2 -height)" << std::endl;
    int param = 0;
    int __step = 0;
    std::cin >> param;
    std::cout << "Enter histogram step" << std::endl;
    std::cin >> __step;
    if(param == 1){
        ManagerHistogram<Person, int> AgeHistogram(data, n);
        dHistogram<int> his = AgeHistogram.GenerateHistogram(ParamGetAge, __step);
        std::ofstream fout("AgeHistogram.txt");
        int s = his.minimal();
        int e = his.maxmimal();
        for(; s < e; s += __step){
            fout << "[" << s << ";" << s + __step << ") \t";
            fout << his.info(s,s + __step) << std::endl;
        }
        fout.close();
    }else if(param == 2){
        ManagerHistogram<Person, int> HeightHistogram(data, n);
        dHistogram<int> his = HeightHistogram.GenerateHistogram(ParamGetHeight, __step);
        std::ofstream fout("HeightHistogram.txt");
        int s = his.minimal();
        int e = his.maxmimal();
        for(; s < e; s += __step){
            fout << "[" << s << ";" << s + __step << ") \t";
            fout << his.info(s,s + __step) << std::endl;
        }
        fout.close();
    }


    fin.close();
    return 0;
}