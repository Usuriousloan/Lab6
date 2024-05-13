#include <iostream>
#include <string>
#include <set>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

class Point {
protected:
    double x, y;
    std::string color;

public:
    Point(double x = 0, double y = 0, std::string color = "чорний");
    virtual ~Point() {}

    void move(double dx, double dy);
    void setColor(const std::string& newColor);

    virtual void resize(double factor) = 0;
    virtual void rotate(double angle) = 0;
    virtual void display() const = 0;
};

class IsoscelesTriangle : public Point {
private:
    double base, height;

public:
    IsoscelesTriangle(double x, double y, double base, double height, std::string color = "чорний");
    
    void resize(double factor) override;
    void rotate(double angle) override;
    void display() const override;
};

class Circle : public Point {
private:
    double radius;

public:
    Circle(double x, double y, double radius, std::string color = "чорний");
    
    void resize(double factor) override;
    void rotate(double angle) override;
    void display() const override;
};

Point::Point(double x, double y, std::string color) : x(x), y(y), color(color) {}

void Point::move(double dx, double dy) {
    x += dx;
    y += dy;
}

void Point::setColor(const std::string& newColor) {
    color = newColor;
}

IsoscelesTriangle::IsoscelesTriangle(double x, double y, double base, double height, std::string color) 
    : Point(x, y, color), base(base), height(height) {}

void IsoscelesTriangle::resize(double factor) {
    base *= factor;
    height *= factor;
}

void IsoscelesTriangle::rotate(double angle) {
    std::cout << "Трикутник обернувся на " << angle << " градусів." << std::endl;
}

void IsoscelesTriangle::display() const {
    std::cout << "Рівнобедрений трикутник на (" << x << ", " << y << ") з основою " << base 
              << " і висотою " << height << " кольору " << color << std::endl;
}

Circle::Circle(double x, double y, double radius, std::string color) 
    : Point(x, y, color), radius(radius) {}

void Circle::resize(double factor) {
    radius *= factor;
}

void Circle::rotate(double angle) {
    std::cout << "Коло обернулося на " << angle << " градусів." << std::endl;
}

void Circle::display() const {
    std::cout << "Коло на (" << x << ", " << y << ") з радіусом " << radius << " кольору " << color << std::endl;
}

void showMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Перемістити\n";
    std::cout << "2. Змінити колір\n";
    std::cout << "3. Змінити розмір\n";
    std::cout << "4. Обернути\n";
    std::cout << "5. Показати\n";
    std::cout << "6. Вийти\n";
}

bool isValidColor(const std::string& color) {
    static const std::set<std::string> validColors = {"червоний", "зелений", "синій", "чорний", "білий", "жовтий", "фіолетовий", "помаранчевий"};
    return validColors.find(color) != validColors.end();
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    Point* shapes[2];
    shapes[0] = new IsoscelesTriangle(0, 0, 10, 20, "червоний");
    shapes[1] = new Circle(0, 0, 10, "синій");

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неправильне введення, будь ласка, введіть число.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                double dx, dy;
                std::cout << "Введіть dx та dy: ";
                std::cin >> dx >> dy;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неправильне введення, будь ласка, введіть числа.\n";
                    break;
                }
                for (int i = 0; i < 2; i++) {
                    shapes[i]->move(dx, dy);
                }
                break;
            }
            case 2: {
                std::string color;
                std::cout << "Введіть новий колір: ";
                std::cin >> color;
                while (!isValidColor(color)) {
                    std::cout << "Неправильний колір. Введіть правильний колір (червоний, зелений, синій, чорний, білий, жовтий, фіолетовий, помаранчевий): ";
                    std::cin >> color;
                }
                for (int i = 0; i < 2; i++) {
                    shapes[i]->setColor(color);
                }
                break;
            }
            case 3: {
                double factor;
                std::cout << "Введіть коефіцієнт зміни розміру: ";
                std::cin >> factor;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неправильне введення, будь ласка, введіть число.\n";
                    break;
                }
                for (int i = 0; i < 2; i++) {
                    shapes[i]->resize(factor);
                }
                break;
            }
            case 4: {
                double angle;
                std::cout << "Введіть кут обертання: ";
                std::cin >> angle;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неправильне введення, будь ласка, введіть число.\n";
                    break;
                }
                for (int i = 0; i < 2; i++) {
                    shapes[i]->rotate(angle);
                }
                break;
            }
            case 5:
                for (int i = 0; i < 2; i++) {
                    shapes[i]->display();
                }
                break;
            case 6:
                for (int i = 0; i < 2; i++) {
                    delete shapes[i];
                }
                return 0;
            default:
                std::cout << "Неправильний вибір, будь ласка, спробуйте ще раз.\n";
        }
    }

    return 0;
}



