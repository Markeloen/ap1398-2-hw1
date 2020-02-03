//
// Created by mohammadhossein on 1/30/20.
//
//#include "aphw1.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>

std::vector<std::vector<double>> getData(const char* filename) {
    std::ifstream file{ filename };
    std::vector<std::vector<double>> data;
    char delimiter;
    double features[8]{ 1 };
    while (!file.eof())
    {
        for (size_t i = 1; i < 8; i++)
            file >> features[i] >> delimiter;
        features[3] /= 100;
        features[4] /= 100;
        data.push_back(std::vector<double>(features, features + 8));
    }
    return data;
}

void displayDataset(std::vector<std::vector<double>> dataset) {
    std::cout << std::left << std::setw(14) << "Bias";
    std::cout << std::left << std::setw(14) << "Class";
    std::cout << std::left << std::setw(14) << "TA";
    std::cout << std::left << std::setw(14) << "Coding";
    std::cout << std::left << std::setw(14) << "Studying";
    std::cout << std::left << std::setw(14) << "Background";
    std::cout << std::left << std::setw(14) << "Mind";
    std::cout << std::left << std::setw(14) << "Grade";
    std::cout << std::endl;
    std::cout << std::string(105, '*') << std::endl;

    for (size_t i = 0; i < dataset.size(); i++)
    {
        for (size_t j = 0; j < dataset[i].size(); j++)
        {
            if(!(j-3) || !(j-4))
                std::cout << std::left << std::setw(14) << std::setprecision(3) << 100 * dataset[i][j];
            else
                std::cout << std::left << std::setw(14) << std::setprecision(3) << dataset[i][j];
        }
        std::cout << std::endl;
    }
}

double grade(std::vector<double> w, std::vector<double> x) {
    double result{};
    for (size_t i = 0; i < w.size(); i++)
        result += x[i] * w[i];
    return result;
}

double J(std::vector<double> w, std::vector<std::vector<double>> dataset) {
    size_t m{ dataset.size() };
    double result{};
    for (size_t i = 0; i < m; i++)
        result += (grade(w, dataset[i]) - dataset[i][7]) * (grade(w, dataset[i]) - dataset[i][7]);
    result /= (2 * m);
    return result;
}

std::vector<double> train(std::vector<std::vector<double>> dataset, std::vector<double> w, double alpha = 0.01, size_t max_iters = 500, double min_cost = 0.001, bool disp = false)
{
    size_t m{ dataset.size() };
    for (size_t i = 0; i < max_iters; i++)
    {
        double old_cost{ J(w, dataset) };
        std::vector<double> partials( 7, 0 );
        for (size_t j = 0; j < 7; j++)
        {
            for (size_t k = 0; k < m; k++)
            {
                partials[j] += (grade(w, dataset[k]) - dataset[k][7]) * dataset[k][j];
            }
            partials[j] /= m;
        }

        for (size_t j = 0; j < 7; j++)
        {
            w[j] -= alpha * partials[j];
        }

        double new_cost{ J(w, dataset) };

        if (disp) {
            std::cout << std::setw(5) << "Iteration " << std::setw(10) << i
                      << std::setw(5) << "Old J: " << std::setw(10) << old_cost
                      << std::setw(5) << "New J: " << std::setw(10) << old_cost
                      << std::endl;
        }

        if (new_cost < min_cost)
            break;
    }
    if (disp){
        std::cout << "Updated weights are: \n";
        for (size_t i = 0; i < 7; i++)
        {
            std::cout <<  w[i] << std::setw(15);
        }
        std::cout << std::endl;
    }

    return w;
}

void displayOutput(std::vector<std::vector<double>> dataset, std::vector<double> w) {
    std::cout << std::setw(15) << "No"
              << std::setw(15) << "Real Grade"
              << std::setw(15) << "Estimated Grade"
              << std::endl;
    std::cout << std::string(50, '*') << std::endl;
    for (size_t i = 0; i < dataset.size(); i++)
    {
        std::cout << std::setw(15) << i+1 << std::setw(15) << dataset[i][7] << std::setw(12) << grade(w, dataset[i]) << std::endl;
    }
}

void predict(std::vector<double> w) {
    std::vector<double> student(7, 1);
    std::cout << "Enter the class attention value (between 0 and 1): " << std::endl;
    std::cin >> student[1];
    std::cout << "Enter the TA class attention value (between 0 and 1): " << std::endl;
    std::cin >> student[2];
    std::cout << "Enter coding hours in a week: " << std::endl;
    std::cin >> student[3];
    student[3] /= 100;
    std::cout << "Enter studying hours in a week: " << std::endl;
    std::cin >> student[4];
    student[4] /= 100;
    std::cout << "Enter background value (between 0 and 1): " << std::endl;
    std::cin >> student[5];
    std::cout << "Enter talent value (between 0 and 1): " << std::endl;
    std::cin >> student[6];
    double student_grade{ grade(w, student) };
    if (student_grade > 20)
        std::cout << "Estimated grade for this student is: " << 20 << std::endl;
    else if (student_grade < 0)
        std::cout << "Estimated grade for this student is: " << 0 << std::endl;
    else
        std::cout << "Estimated grade for this student is: " << student_grade << std::endl;
}

void save(std::vector<double> w, const char* name){
    std::ofstream file{name};
    for (size_t i = 0; i < w.size() - 1; i++) {
        file << w[i] <<",";
    }
    file<<w[w.size()-1];
    std::cout<<"Saved successfully!"<<std::endl;
}

std::vector<double> load(const char* name){
    std::ifstream file{name};
    std::vector<double> w;
    double x;
    char temp;
    while(!file.eof()){
        file >> x;
        w.push_back(x);
        file >>temp;
    }
    std::cout<<"Weights loaded successfully!"<<std::endl;
    return w;
}
