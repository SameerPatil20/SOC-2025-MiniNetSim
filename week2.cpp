#include <iostream>       
#include <string>         

using namespace std;   

enum ShapeType { RectangleID = 0, SquareID = 1, CircleID = 2, EllipseID = 3 };

class Shape {
protected:
    int x = 0, y = 0;
    string color = "black"; 
public:
    virtual ~Shape() = default; // Destructor

    virtual int getShape() const = 0;

    virtual double getArea() const = 0;

    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }

    pair<int,int> getPosition()
    {
        return { x, y };
    }

    void setColor(string c)
    {     
        color = c;
    }
    string getColor()
    {
        return color;
    }
};

class Rectangle : public Shape {
protected:
    int length;   
    int breadth;  
public:
    Rectangle(int l, int b, const string& col = "black") {
        if (l <= 0 || b <= 0)
            throw invalid_argument("Dimensions must be positive");
        length = l;
        breadth = b;
        color = col;
    }

    int getShape() const override 
    {
        return RectangleID;
    }

    int getLength() const 
    {
        return length;
    }
    int getBreadth() const 
    {
        return breadth;
    }

    double getArea() const override
    {
        return length * breadth;
    }

    bool isSquare() const 
    {
        return length == breadth; 
    }
};

class Square : public Rectangle {
public:

    Square(int side, const string& col = "black")
        : Rectangle(side, side, col) {}

    int getShape() const override 
    {
        return SquareID;
    }

    int getBreadth() const 
    {
        return length;
    }
};


class Circle : public Shape {
protected:
    int radius; 
public:
    Circle(int r, const string& col = "black") {
        if (r <= 0)
            throw invalid_argument("Radius must be positive");
        radius = r;
        color = col;
    }

    int getShape() const override 
    {
        return CircleID; 
    }

    int getRadii() const 
    { 
        return radius;
    }

    double getArea() const override 
    {
        return 3.141592653589793 * radius * radius;
    }
};

class Ellipse : public Shape {
protected:
    int xLength;  
    int yLength;  
public:
    Ellipse(int a, int b, const string& col = "black") {
        if (a <= 0 || b <= 0)
            throw invalid_argument("Axes must be positive");
        xLength = a;
        yLength = b;
        color = col;
    }

    int getShape() const override 
    {
        return EllipseID;
    }

    int getXLength() const 
    {
        return xLength;
    }
    int getYLength() const 
    {
        return yLength; 
    }

    double getArea() const override 
    {
        return 3.141592653589793 * xLength * yLength;
    }
};


int main() {
    try {
        Rectangle rect(4, 5, "red");
        cout << "Rectangle area: " << rect.getArea() << "\n";
        cout << "Is square? " << (rect.isSquare() ? "Yes" : "No") << "\n";

        Square sq(5, "blue");
        cout << "Square area: " << sq.getArea() << "\n";

        Circle c(3, "green");
        cout << "Circle area: " << c.getArea() << "\n";

        Ellipse el(3, 2, "yellow");
        cout << "Ellipse area: " << el.getArea() << "\n";

        Shape* shapes[] = { &rect, &sq, &c, &el };
        for (auto* s : shapes) {
            cout << "Shape ID: " << s->getShape()
                 << ", Color: " << s->getColor()
                 << ", Area: " << s->getArea() << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
