// movingAverage takes the average of
// a continuously moving window of n most-recent elements
// within a stream of data.

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class MovingAverage {
    int windowSize;
    int oldest = 0;
    int sum = 0;

public:
    vector<int> elements;

    MovingAverage(unsigned int windowSize) : windowSize(windowSize) {
        //windowSize = windowSize;
    }

    void put(int val) {
        if (elements.size() < windowSize) {
            elements.push_back(val);
            sum += val;
        }
        else {
            sum += val - elements[oldest];
            elements[oldest] = val;
            oldest = ++oldest % windowSize;
        }
    }

    float get() {
        return (float)sum / elements.size();
    }

    ~MovingAverage() {

    }
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 9);

    MovingAverage ma = MovingAverage(10);

    for (int i = 0; i < 20; i++) {
        int n = distr(gen);

        ma.put(n);

        cout << "size: " << ma.elements.size() << "\nelements: ";

        for (auto el : ma.elements) cout << el << ' ';

        cout << "\naverage: " << ma.get() << "\n\n";
    }

    return 0;
}