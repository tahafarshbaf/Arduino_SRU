#include <iostream>
#include <cmath> 

using namespace std;

double calculateCircleArea(double radius, double pi = 3.14159) {
   
    if (radius < 0) {
        cerr << "Error: Radius cannot be negative." << endl;
        return -1.0; 
    }
   
    double area = pi * radius * radius ;
    return area;
}

int main() {
   
    double radius1 = 5.0;
    double area1 = calculateCircleArea(radius1);
    cout << "Area of circle with radius " << radius1 << " (default pi): " << area1 << endl;

   
    double radius2 = 7.0;
    double customPi = 3.14; 
    double area2 = calculateCircleArea(radius2, customPi);
    cout << "Area of circle with radius " << radius2 << " (custom pi " << customPi << "): " << area2 << endl;

   
    double radius4 = -2.0;
    double area4 = calculateCircleArea(radius4);
    cout << "Area of circle with radius " << radius4 << ": " << area4 << endl;

    return 0;
}
