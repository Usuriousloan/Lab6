#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

public:
    // Конструктор за замовчуванням
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Конструктор копіювання
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

    // Операція присвоювання
    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
            reduce();
        }
        return *this;
    }

    // Операція віднімання
    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Операція множення
    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Операція порівняння (рівність)
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Виведення дробу
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }
};

void showMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Віднімання\n";
    std::cout << "2. Множення\n";
    std::cout << "3. Порівняння\n";
    std::cout << "4. Вийти\n";
}

bool isValidChoice(int choice) {
    return choice >= 1 && choice <= 4;
}

int main() {
    try {
        Fraction f1(3, 4); // 3/4
        Fraction f2(2, 5); // 2/5

        int choice;
        while (true) {
            showMenu();
            std::cin >> choice;

            if (std::cin.fail() || !isValidChoice(choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неправильне введення, будь ласка, введіть число від 1 до 4.\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    Fraction result = f1 - f2;
                    std::cout << "Результат віднімання: " << result << std::endl;
                    break;
                }
                case 2: {
                    Fraction result = f1 * f2;
                    std::cout << "Результат множення: " << result << std::endl;
                    break;
                }
                case 3: {
                    bool equal = f1 == f2;
                    std::cout << (equal ? "Дроби рівні" : "Дроби не рівні") << std::endl;
                    break;
                }
                case 4:
                    return 0;
                default:
                    std::cout << "Неправильний вибір, будь ласка, спробуйте ще раз.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}
