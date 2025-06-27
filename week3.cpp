#include <iostream>       
#include <string>         
#include <vector>
#include <SFML/Graphics.hpp>
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
    virtual void draw(sf::RenderWindow& window) const = 0;
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

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rectShape(sf::Vector2f(length, breadth));
        rectShape.setPosition(x, y);
        rectShape.setFillColor(sf::Color::White);
        window.draw(rectShape);
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

    void draw(sf::RenderWindow& window) const override {
        Rectangle::draw(window);
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

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape circle(radius);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);
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

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape ellipse(1.f);
        ellipse.setScale(xLength, yLength);
        ellipse.setPosition(x, y);
        ellipse.setFillColor(sf::Color::White);
        window.draw(ellipse);
    }
};

class Canvas {
private:
    vector<Shape*> shapes;

public:
    void addShape(Shape* s) {
        shapes.push_back(s);
    }

    void displayCanvas() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Shape Canvas");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black);
            for (auto s : shapes)
                s->draw(window);
            window.display();
        }
    }
};


int main() {
    try {
        Canvas canvas;

        Rectangle* rect = new Rectangle(100, 50);
        rect->setPosition(50, 50);

        Square* square = new Square(60);
        square->setPosition(200, 50);

        Circle* circle = new Circle(40);
        circle->setPosition(350, 50);

        Ellipse* ellipse = new Ellipse(30, 20);
        ellipse->setPosition(500, 50);

        canvas.addShape(rect);
        canvas.addShape(square);
        canvas.addShape(circle);
        canvas.addShape(ellipse);

        canvas.displayCanvas();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}