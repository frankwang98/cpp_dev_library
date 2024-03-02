#include "../src/mathutils/mathutils.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    MathUtils m;
    int result;
    std::cout << "add: " << m.add(1.5, 2.1) << std::endl;

    std::cout << "subtract: " << m.subtract(3, 1) << std::endl
              << "multiply: " << m.multiply(2, 3) << std::endl
              << "divide: " << m.divide(10, 5) << std::endl
              << "mod: " << m.mod(10, 6) << std::endl
              << "power: " << m.power(2, 3) << std::endl
              << "sqrt: " << m.sqrt(100) << std::endl
              << "abs: " << m.abs(-10) << std::endl
              << "round: " << m.round(1.5) << std::endl
              << "ceil: " << m.ceil(1.5) << std::endl
              << "floor: " << m.floor(1.5) << std::endl
              << "trunc: " << m.trunc(1.5) << std::endl
              << "max: " << m.max(1, 2) << std::endl
              << "min: " << m.min(1, 2) << std::endl
              << "sign: " << m.sign(-5) << std::endl
              << "sin: " << m.sin(1.5) << std::endl
              << "cos: " << m.cos(1.5) << std::endl
              << "tan: " << m.tan(1.5) << std::endl
              << "asin: " << m.asin(1.5) << std::endl
              << "acos: " << m.acos(1.5) << std::endl
              << "atan: " << m.atan(1.5) << std::endl
              << "atan2: " << m.atan2(1.5, 2.5) << std::endl
              << "log: " << m.log(100) << std::endl
              << "log10: " << m.log10(100) << std::endl
              << "log2: " << m.log2(100) << std::endl
              << "exp: " << m.exp(1.5) << std::endl
              << "deg2rad: " << m.deg2rad(180.0) << std::endl
              << "rad2deg: " << m.rad2deg(1.5) << std::endl
              << "----- calculate end..." << std::endl;

    double x1 = 2.0, y1 = 3.0, x2 = 5.0, y2 = 7.0;
    std::cout << "calculateDistance: " << m.calculateDistance(x1, y1, x2, y2) << std::endl
              << "calculateManhattanDistance: " << m.calculateManhattanDistance(x1, y1, x2, y2) << std::endl
              << "calculateChebyshevDistance: " << m.calculateChebyshevDistance(x1, y1, x2, y2) << std::endl
              << "----- calculate end..." << std::endl;

    return 0;
}