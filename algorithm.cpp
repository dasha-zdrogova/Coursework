#include <iostream>
#include <cmath>

using namespace std;

double DELTA = 10e-3;
long long INF = 10e10;

class Vector {
public:
    double x;
    double y;

    Vector (double x = INF, double y = INF): x(x), y(y) {}

    double squared_norm () {
        return x*x + y*y;
    }
};

Vector operator - (Vector v1, Vector v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

Vector operator + (Vector v1, Vector v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator * (int n, Vector v) {
    return Vector(n*v.x, n*v.y);
}

double dot_product (Vector v1, Vector v2) {
        return v1.x*v2.x + v1.y*v2.y;
}

// Предполагаем, что z и x лежат в одном множестве
Vector new_point(Vector x, Vector y, Vector z) {
    double product = dot_product(y - x, z - x);
    Vector new_x = x;
    if ((product >= (x - z).squared_norm() && (z - y).squared_norm() + DELTA*DELTA >= (x - y).squared_norm()) ||
    product <= DELTA*sqrt((z-x).squared_norm()))
        new_x = x;
    if (product > (z - x).squared_norm() && (z - y).squared_norm() + DELTA*DELTA <= (x - y).squared_norm()) 
        new_x = z;
    if (DELTA*(z - x).squared_norm() < product && product <= (z - x).squared_norm())
        new_x = x + ((product / (z - x).squared_norm()) * (z - x));
    //cout << (y-new_x).squared_norm() << endl;
    return new_x;    
}


int main() {
    int n;

    double x_c, y_c;
    Vector x, y, new_x, new_y;
    int number_of_set;
    freopen("test_data.txt", "r", stdin);
    freopen("answer.txt", "w", stdout);
    cin >> n;

    cin >> x_c >> y_c >> number_of_set;
    x = Vector(x_c, y_c);
    cin >> x_c >> y_c >> number_of_set;
    y = Vector(x_c, y_c);

    for (int i = 2; i < 2*n; ++i) {
        cin >> x_c >> y_c >> number_of_set;
        Vector z = Vector(x_c, y_c);
        if (number_of_set == 0) x = new_point(x, y, z);
        if (number_of_set == 1) y = new_point(y, x, z);
    }

    if ((y-x).squared_norm() < 1 ) {
        cout << -1 << endl;
        exit(0);
    }
    
    // Построение серединного перпендикуляра
    double x_m = (x.x + y.x) / 2;
    double y_m = (x.y + y.y) / 2;
    double k = -1 / ((y.y - x.y) / (y.x - x.x));

    double a = k;
    double b = y_m - k*x_m;
    cout << a << endl;
    cout << b << endl;
    cout << x.x << " " << x.y << endl;
    cout << y.x << " " << y.y << endl;
    return 0;
}