#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "../include/figure.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"
#include "../include/romb.h"

class FigureArray {
private:
    std::vector<std::unique_ptr<Figure>> figures;

public:
    //  онструкторы и операторы присваивани€ генерируютс€ автоматически
    
    void addFigure(std::unique_ptr<Figure> fig) {
        figures.push_back(std::move(fig));
    }

    void removeFigure(int index) {
        if (index >= 0 && index < figures.size()) {
            figures.erase(figures.begin() + index);
        }
    }

    double totalArea() const {
        double total = 0;
        for (const auto& fig : figures) {
            total += fig->area();
        }
        return total;
    }

    void printAll() const {
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i + 1 << ":\n";
            std::cout << *figures[i] << "\n";
            auto center = figures[i]->getCenter();
            std::cout << "Center: (" << center.first << ", " << center.second << ")\n";
            std::cout << "Area: " << figures[i]->area() << "\n\n";
        }
    }

    size_t size() const {
        return figures.size();
    }
};

void showMenu() {
    std::cout << "\n=== Figure Manager ===\n";
    std::cout << "1. Add Rectangle\n";
    std::cout << "2. Add Trapezoid\n";
    std::cout << "3. Add Romb\n";
    std::cout << "4. Remove Figure\n";
    std::cout << "5. Show All Figures\n";
    std::cout << "6. Show Total Area\n";
    std::cout << "7. Clear All\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

int main() {
    FigureArray figures;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                auto rect = std::make_unique<Rectangle>();
                std::cin >> *rect;
                figures.addFigure(std::move(rect));
                std::cout << "Rectangle added.\n";
                break;
            }
            case 2: {
                auto trap = std::make_unique<Trapezoid>();
                std::cin >> *trap;
                figures.addFigure(std::move(trap));
                std::cout << "Trapezoid added.\n";
                break;
            }
            case 3: {
                auto romb = std::make_unique<Romb>();
                std::cin >> *romb;
                figures.addFigure(std::move(romb));
                std::cout << "Romb added.\n";
                break;
            }
            case 4: {
                if (figures.size() == 0) {
                    std::cout << "No figures to remove.\n";
                    break;
                }
                std::cout << "Enter index to remove (1-" << figures.size() << "): ";
                int index;
                std::cin >> index;
                figures.removeFigure(index - 1);
                std::cout << "Figure removed.\n";
                break;
            }
            case 5:
                if (figures.size() == 0) {
                    std::cout << "No figures to display.\n";
                } else {
                    figures.printAll();
                }
                break;
            case 6:
                std::cout << "Total area of all figures: " << figures.totalArea() << "\n";
                break;
            case 7:
                figures = FigureArray(); // ќчистка через присваивание
                std::cout << "All figures cleared.\n";
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (choice != 0);

    return 0;
}