#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

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

int partition(vector<int> &vec, int low, int high)
{
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (vec[j] <= pivot)
        {
            i++;
            swap(vec[i], vec[j]);
        };
    };
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

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

void bubbleSort(vector<int> &unorganizedVector)
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
};

void insertionSort(vector<int> &unorganizedVector)
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
};

void selectionSort(vector<int> &unorganizedVector)
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
};

void quickSort(vector<int> &vec, int low, int high)
{
    if (low < high)
    {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    };
};

long long measureSortTime(void (*sortFunc)(vector<int> &), vector<int> &unorganizedVector)
{
    vector<int> vecCopy = unorganizedVector;
    auto start = high_resolution_clock::now();
    sortFunc(vecCopy);
    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count();
};

long long measureQuickSortTime(void (*sortFunc)(vector<int> &, int, int), vector<int> &unorganizedVector)
{
    vector<int> vecCopy = unorganizedVector;
    auto start = high_resolution_clock::now();
    sortFunc(vecCopy, 0, vecCopy.size() - 1);
    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count();
};

string tests(int vectorSize, int timesToRun)
{

    long long bubbleSortClock = 0;
    long long insertionSortClock = 0;
    long long selectionSortClock = 0;
    long long quickSortClock = 0;

    for (int i = 0; i < timesToRun; i++)
    {
        vector<int> unorganizedVector = createUnorganizedVector(vectorSize, 0, 999);

        bubbleSortClock += measureSortTime(bubbleSort, unorganizedVector);
        insertionSortClock += measureSortTime(insertionSort, unorganizedVector);
        selectionSortClock += measureSortTime(selectionSort, unorganizedVector);
        quickSortClock += measureQuickSortTime(quickSort, unorganizedVector);

        cout << "Run: " + to_string(i + 1) + " of " + to_string(timesToRun) + " for Vector Size: " + to_string(vectorSize) << endl;
    };

    return "Results for Vector Size: " + to_string(vectorSize) + "\n\nBubble Sort: " + to_string(bubbleSortClock / timesToRun) +
           " \nInsertion Sort: " + to_string(insertionSortClock / timesToRun) + " \nSelection Sort: " + to_string(selectionSortClock / timesToRun) +
           " \nQuick Sort: " + to_string(quickSortClock / timesToRun) + "\n\n----------------------------------\n";
};

int main()
{
    string textForFile = "";
    ofstream testResultFile("sortTest.txt");

    int timesToRun = 100;

    textForFile += tests(10, timesToRun);
    textForFile += tests(100, timesToRun);
    textForFile += tests(1000, timesToRun);
    textForFile += tests(10000, timesToRun);
    testResultFile << textForFile;
};
