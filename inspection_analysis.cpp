/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Jadiel Ortiz Rodriguez]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: [This file contains the implementation of maintenance order queries, including searching for orders by ID and listing orders by area.]
 * Due Date: [9/nov/2026]
 */
#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};

int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);

int main() {
    const int CAPACITY = 6;
    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };
    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;

    cout << fixed << setprecision(2);
    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        cin >> menuChoice;

        if (menuChoice == 1) {
            int targetId = 0;
            cout << "Enter inspection ID: ";
            cin >> targetId;
            int foundIndex = findInspectionById(inspections, CAPACITY, targetId);
            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        } else if (menuChoice == 2) {
            string targetArea;
            cout << "Enter area: ";
            getline(cin >> ws, targetArea);
            int matchCount = displayInspectionsByArea(inspections, CAPACITY, targetArea);
            cout << "Matches: " << matchCount << endl;
        } else if (menuChoice == 3) {
            int valueCount = copyVibrations(inspections, CAPACITY, sortedVibrations);
            if (valueCount == 0) {
                cout << "No readings available for statistics." << endl;
            } else {
                selectionSort(sortedVibrations, valueCount);
                cout << "Values used: " << valueCount << endl;
                cout << "Mean: " << calculateMean(sortedVibrations, valueCount) << endl;
                cout << "Median: " << calculateMedian(sortedVibrations, valueCount) << endl;
                cout << "Mode: ";
                displayModes(sortedVibrations, valueCount);
            }
        } else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }
    } while (menuChoice != 4);

    return 0;
}

void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration << endl;
}

int findInspectionById(const Inspection inspections[], int capacity, int targetId) {
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].id == targetId) {
            return index; // Stops because an ID identifies one inspection
        }
    }
    return -1; 
}

int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea) {
    int matchCount = 0;
    // TODO: Traverse every position, display every occupied inspection in targetArea, and update matchCount.
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].area == targetArea) {
            displayInspection(inspections[index]);
            matchCount++;
        }
    }
    return matchCount;
}

int copyVibrations(const Inspection inspections[], int capacity, double values[]) {
    int valueCount = 0;
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty) {
            values[valueCount] = inspections[index].vibration;
            valueCount++;
        }
    }
    return valueCount;
}

void selectionSort(double values[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(values[i], values[minIndex]);
        }
    }
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    for (int index = 0; index < count; index++) {
        total += values[index];
    }
    return total / count;
}

double calculateMedian(const double sortedValues[], int count) {
    // TODO: Use the middle value for odd counts or average the two middle values for even counts.
    if (count % 2 == 1) {
        return sortedValues[count / 2]; // Middle value for odd count
    } else {
        return (sortedValues[(count / 2) - 1] + sortedValues[count / 2]) / 2.0; // Average of two middle values for even count
    }
    return 0.0;
}

void displayModes(const double sortedValues[], int count) {
    int maxFrequency = 1;
    int currentFrequency = 1;
    for (int i = 1; i < count; i++) {
        if (sortedValues[i] == sortedValues[i - 1]) {
            currentFrequency++;
        } else {
            if (currentFrequency > maxFrequency) {
                maxFrequency = currentFrequency;
            }
            currentFrequency = 1;
        }
    }
    if (maxFrequency == 1) {
        cout << "N/A" << endl;
    } else {
        for (int i = 0; i < count; i++) {
            if (sortedValues[i] == sortedValues[i - 1]) {
                currentFrequency++;
            } else {
                if (currentFrequency == maxFrequency) {
                    cout << sortedValues[i - 1] << " ";
                }
                currentFrequency = 1;
            }
        }
        if (currentFrequency == maxFrequency) {
            cout << sortedValues[count - 1] << " ";
        }
        cout << endl;
    }
}

/*
 * Test Cases:
 * 1. Inputs: [Write the inputs for the successful ID search] 109
 *    Expected: [Write the expected result] Found inspection ID 109 in the area Assembly with 0.30 vibration.
 *    Observed: [Write the result from your execution] ID: 109 | Area: Assembly | Vibration: 0.30
 * 2. Inputs: [Write the inputs for the ID not found] 999
 *    Expected: [Write the expected result] Since the inspection ID 999 is not found, no results will be displayed.
 *    Observed: [Write the result from your execution] Inspection not found.
 * 3. Inputs: [Write the inputs for the area search] Assembly
 *    Expected: [Write the expected result] Found inspections in the area Assembly with their respective IDs and vibration readings.
 *    Observed: [Write the result from your execution] ID: 101 | Area: Assembly | Vibration: 0.30
 *                                                     ID: 109 | Area: Assembly | Vibration: 0.30
 *                                                     ID: 123 | Area: Assembly | Vibration: 0.15
 * 4. Inputs: [Write the inputs for the statistics option] 3
 *    Expected: [Write the expected result] Calculates and displays the mean, median, and mode of the vibration readings.
 *    Observed: [Write the result from your execution] Mean: 0.24
 *                                                     Median: 0.22
 *                                                     Mode: 0.15 0.30
 */

/*
 * Analysis:
 * 1. Why does findInspectionById return an index instead of the ID?
 * It returns an index instead of the ID because the index allows direct access to the inspection in the array, enabling further operations or retrieval of additional information about that inspection.
 * 2. Why must displayInspectionsByArea continue after its first match?
 * It must continue after its first match to ensure that all inspections in the specified area are displayed, as there may be multiple inspections associated with the same area.
 * 3. Why does copyVibrations use valueCount separately from index?
 * It uses valueCount separately from index to keep track of the number of valid vibration readings copied into the values array, allowing for accurate processing of only the relevant data without being affected by empty slots in the inspections array.
 * 4. Why is selectionSort applied to sortedVibrations instead of inspections?
 * SelectionSort is applied to sortedVibrations instead of inspections because the goal is to sort the vibration readings for statistical analysis, and sorting the entire inspections array would be unnecessary and inefficient. The sortedVibrations array contains only the relevant data needed for calculations like mean, median, and mode.
 * 5. Which two values determine the median when six readings are sorted?
 * Two values that determine the median when six readings are sorted are the third and fourth values in the sorted list. The median is calculated as the average of these two middle values.
 */