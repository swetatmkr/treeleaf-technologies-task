#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point3D {
    double x, y, z;

    Point3D(double x = 0.0, double y = 0.0, double z = 0.0)
        : x(x), y(y), z(z) {}
};

struct Box {
    Point3D vertices[8]; // Array to hold the 8 vertices of the box

    Box() {}

    // Constructor to initialize box with vertices
    Box(const vector<Point3D>& corners) {
        if (corners.size() >= 8) {
            for (int i = 0; i < 8; ++i) {
                vertices[i] = corners[i];
            }
        }
    }
};

// Function to rotate box around X-axis
void rotateX(Box& box, double angle_degrees) {
    double angle_rad = angle_degrees * M_PI / 180.0;
    double cos_theta = cos(angle_rad);
    double sin_theta = sin(angle_rad);

    for (int i = 0; i < 8; ++i) {
        double y = box.vertices[i].y;
        double z = box.vertices[i].z;
        box.vertices[i].y = y * cos_theta - z * sin_theta;
        box.vertices[i].z = y * sin_theta + z * cos_theta;
    }
}

// Function to rotate box around Y-axis
void rotateY(Box& box, double angle_degrees) {
    double angle_rad = angle_degrees * M_PI / 180.0;
    double cos_theta = cos(angle_rad);
    double sin_theta = sin(angle_rad);

    for (int i = 0; i < 8; ++i) {
        double x = box.vertices[i].x;
        double z = box.vertices[i].z;
        box.vertices[i].x = x * cos_theta + z * sin_theta;
        box.vertices[i].z = -x * sin_theta + z * cos_theta;
    }
}

// Function to rotate box around Z-axis
void rotateZ(Box& box, double angle_degrees) {
    double angle_rad = angle_degrees * M_PI / 180.0;
    double cos_theta = cos(angle_rad);
    double sin_theta = sin(angle_rad);

    for (int i = 0; i < 8; ++i) {
        double x = box.vertices[i].x;
        double y = box.vertices[i].y;
        box.vertices[i].x = x * cos_theta - y * sin_theta;
        box.vertices[i].y = x * sin_theta + y * cos_theta;
    }
}

// Function to scale box uniformly
void scale(Box& box, double scale_factor) {
    for (int i = 0; i < 8; ++i) {
        box.vertices[i].x *= scale_factor;
        box.vertices[i].y *= scale_factor;
        box.vertices[i].z *= scale_factor;
    }
}

// Function to print vertices of the box
void printVertices(const Box& box) {
    for (int i = 0; i < 8; ++i) {
        cout << "Vertex " << i+1 << ": ("
             << box.vertices[i].x << ", "
             << box.vertices[i].y << ", "
             << box.vertices[i].z << ")" << endl;
    }
    cout << endl;
}

int main() {
    // Example box vertices (assuming a unit cube)
    vector<Point3D> corners = {
        Point3D(0, 0, 0), Point3D(1, 0, 0),
        Point3D(1, 1, 0), Point3D(0, 1, 0),
        Point3D(0, 0, 1), Point3D(1, 0, 1),
        Point3D(1, 1, 1), Point3D(0, 1, 1)
    };

    Box box(corners);

    double angleX, angleY, angleZ;
    cout << "Enter rotation angle around X-axis (in degrees): ";
    cin >> angleX;
    // Rotate around X-axis
    rotateX(box, angleX);
    cout << "\nVertices after rotation around X-axis:\n";
    printVertices(box);

    cout << "Enter rotation angle around Y-axis (in degrees): ";
    cin >> angleY;
    // Rotate around Y-axis
    rotateY(box, angleY);
    cout << "\nVertices after rotation around Y-axis:\n";
    printVertices(box);

    cout << "Enter rotation angle around Z-axis (in degrees): ";
    cin >> angleZ;
    // Rotate around Z-axis
    rotateZ(box, angleZ);
    cout << "\nVertices after rotation around Z-axis:\n";
    printVertices(box);

    double scaleFactor;
    cout << "Enter scaling factor: ";
    cin >> scaleFactor;
    // Scale the box uniformly
    scale(box, scaleFactor);
    cout << "\nVertices after scaling:\n";
    printVertices(box);

    return 0;
}
