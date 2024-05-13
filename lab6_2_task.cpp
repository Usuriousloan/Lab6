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
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}

    Fraction& operator=(const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
            reduce();
        }
        return *this;
    }

    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }
};

void showMenu() {
    std::cout << "\n============================\n";
    std::cout << "         МЕНЮ\n";
    std::cout << "============================\n";
    std::cout << "1. Віднімання\n";
    std::cout << "2. Множення\n";
    std::cout << "3. Порівняння\n";
    std::cout << "4. Вийти\n";
    std::cout << "============================\n";
    std::cout << "Введіть ваш вибір: ";
}

bool isValidChoice(int choice) {
    return choice >= 1 && choice <= 4;
}

int main() {
    try {
        Fraction f1(3, 4);
        Fraction f2(2, 5);
        Fraction result;
        bool equal;

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
                    result = f1 - f2;
                    std::cout << "\n============================\n";
                    std::cout << "Результат віднімання: " << result << std::endl;
                    std::cout << "============================\n";
                    break;
                }
                case 2: {
                    result = f1 * f2;
                    std::cout << "\n============================\n";
                    std::cout << "Результат множення: " << result << std::endl;
                    std::cout << "============================\n";
                    break;
                }
                case 3: {
                    equal = (f1 == f2);
                    std::cout << "\n============================\n";
                    std::cout << (equal ? "Дроби рівні" : "Дроби не рівні") << std::endl;
                    std::cout << "============================\n";
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
