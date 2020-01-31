#include <iostream>
#include "aphw1.h"
#include <vector>

int main() {
    std::vector<std::vector<double>> dataset{ getData("AP-Data.csv") };
    displayDataset(dataset);
    std::vector<double> w(7, 0.1);
    w = train(dataset, w, 0.3, 1000, 0.1, true);
    //predict(w);
    save(w, "w.csv");
    std::vector<double> w1 = load("w.csv");
    displayOutput(dataset, w1);
}