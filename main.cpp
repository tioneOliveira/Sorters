#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

string vectorString(vector<int> vector)
{
    int vectorSize = vector.size();
    string vectorItens = "";

    for (int i = 0; i < vectorSize; i++)
    {
        if (i != vectorSize - 1)
        {
            vectorItens = vectorItens + to_string(vector[i]) + ", ";
        }
        else
        {
            vectorItens = vectorItens + to_string(vector[i]);
        };
    };

    return vectorItens;
};

vector<int> createUnorganizedVector(int lenght, int minimun, int maximum)
{
    vector<int> unorganizedVector = {};
    int range = maximum - minimun + 1;
    srand((unsigned)time(NULL));
    for (int i = 0; i < lenght; i++)
    {
        unorganizedVector.push_back(minimun + (rand() % range));
    };
    return unorganizedVector;
};

vector<int> bubbleSort(vector<int> unorganizedVector)
{

    int vectorSize = unorganizedVector.size();

    vector<int> organizedVector = unorganizedVector;

    for (int i = 0; i < vectorSize - 1; i++)
    {
        for (int j = 0; j < vectorSize - 1; j++)
        {
            if (organizedVector[j] > organizedVector[j + 1])
            {
                swap(organizedVector[j], organizedVector[j + 1]);
            };
        };
    };
    return organizedVector;
};

vector<int> insertionSort(vector<int> unorganizedVector)
{
    int vectorSize = unorganizedVector.size();
    vector<int> organizedVector = unorganizedVector;

    for (int i = 1; i < vectorSize; i++)
    {
        int temp = organizedVector[i];
        int j = (i - 1);

        while (j >= 0 && organizedVector[j] > temp)
        {
            organizedVector[j + 1] = organizedVector[j];
            j--;
        };
        organizedVector[j + 1] = temp;
    };
    return organizedVector;
};

vector<int> selectionSort(vector<int> unorganizedVector)
{
    int vectorSize = unorganizedVector.size();
    vector<int> organizedVector = unorganizedVector;

    for (int i = 0; i < vectorSize - 1; i++)
    {
        int minIdx = i;

        for (int j = i + 1; j < vectorSize; j++)
        {
            if (organizedVector[j] < organizedVector[minIdx])
            {
                minIdx = j;
            }
        };
        swap(organizedVector[i], organizedVector[minIdx]);
    };
    return organizedVector;
};

int main()
{
    vector<int> unorganizedVector = createUnorganizedVector(100, 0, 999);
    int vectorSize = unorganizedVector.size();

    cout << "Unsorted: " + vectorString(unorganizedVector) + "\n------------------------------------------"
         << endl;

    auto BSstart = high_resolution_clock::now();
    cout << "Bubble Sort: " + vectorString(bubbleSort(unorganizedVector)) + "\n"
         << endl;
    auto BSstop = high_resolution_clock::now();
    auto BSduration = duration_cast<microseconds>(BSstop - BSstart);
    cout << "Time to Bubble Sort: " + to_string(BSduration.count()) + "\n------------------------------------------" << endl;

    auto ISstart = high_resolution_clock::now();
    cout << "Insertion Sort: " + vectorString(insertionSort(unorganizedVector)) + "\n"
         << endl;
    auto ISstop = high_resolution_clock::now();
    auto ISduration = duration_cast<microseconds>(ISstop - ISstart);
    cout << "Time to Insertion Sort: " + to_string(ISduration.count()) + "\n------------------------------------------" << endl;

    auto SSstart = high_resolution_clock::now();
    cout << "Selection Sort: " + vectorString(selectionSort(unorganizedVector)) + "\n"
         << endl;
    auto SSstop = high_resolution_clock::now();
    auto SSduration = duration_cast<microseconds>(SSstop - SSstart);
    cout << "Time to Selection Sort: " + to_string(SSduration.count()) + "\n------------------------------------------" << endl;
    return 0;
};