#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>


void Help(const std::string& programName) {
    std::cout << "Использование:\n"
              << "  " << programName << " -o <операция> <операнды...>\n"
              << "  " << programName << " --operation <операция> <операнды...>\n\n"
              << "Доступные операции:\n"
              << "  mean    - Вычисление среднего арифметического\n"
              << "  median  - Вычисление медианы\n\n"
              << "Ограничения:\n"
              << "  Количество операндов должно быть от 8 до 10.\n"
              << "Пример запуска:\n"
              << "  " << programName << " -o mean 1 2 3 4 5 6 7 8\n";
}

double calcmean(const std::vector<double>& numbers) {
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / numbers.size();
}

double calcmedian(std::vector<double> numbers) {
    std::sort(numbers.begin(), numbers.end());
    size_t size = numbers.size();
    if (size % 2 != 0) {
        return numbers[size / 2];
    } else {
        return (numbers[size / 2 - 1] + numbers[size / 2]) / 2.0;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        Help(argv[0]);
        return 0;
    }

    std::string operation = "";
    std::vector<double> operands;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                std::cerr << "Не указано значение операции.\n";
                return 1;
            }
        } else {
            try {
                size_t idx;
                double val = std::stod(arg, &idx);
                if (idx != arg.length()) {
                    throw std::invalid_argument("Плохой символ в числе");
                }
                operands.push_back(val);
            } catch (const std::exception&) {
                std::cerr << "Некорректный операнд '" << arg << "'. Операнды должны быть числами.\n";
                return 1;
            }
        }
    }

    if (operation.empty()) {
        std::cerr << "Операция не задана.\n";
        return 1;
    }

    if (operands.size() < 8 || operands.size() > 10) {
        std::cerr << "требуется от 8 до 10 операндов, передано: " << operands.size() << ".\n";
        return 1;
    }

    std::cout << std::fixed << std::setprecision(4);
    if (operation == "mean") {
        std::cout << "Результат: " << calcmean(operands) << "\n";
    } else if (operation == "median") {
        std::cout << "Результат: " << calcmedian(operands) << "\n";
    } else {
        std::cerr << "Неизвестная операция '" << operation << "'. Доступны только 'mean' и 'median'.\n";
        return 1;
    }

    return 0;
}

