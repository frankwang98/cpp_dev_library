// mathutils.hpp

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <iostream>
#include <cmath>
#include <limits>
#include <type_traits>

class MathUtils {
public:
    /* 加法 */
    template <typename T>
    static T add(T a, T b) {
        return a + b;
    }
    /* 减法 */
    template <typename T>
    static T subtract(T a, T b) {
        return a - b;
    }
    /* 乘法 */
    template <typename T>
    static T multiply(T a, T b) {
        return a * b;
    }
    /* 除法 */
    template <typename T>
    static T divide(T a, T b) {
        return a / b;
    }
    /* 取余 */
    template <typename T>
    static T mod(T a, T b) {
        return a % b;
    }
    /* a的b次幂 */
    template <typename T>
    static T power(T a, T b) {
        return std::pow(a, b);
    }
    /* 求根号 */
    template <typename T>
    static T sqrt(T a) {
        return std::sqrt(a);
    }
    /* 取绝对值 */
    template <typename T>
    static T abs(T a) {
        return std::abs(a);
    }
    /* 向上取整 */
    template <typename T>
    static T ceil(T a) {
        return std::ceil(a);
    }
    /* 向下取整 */
    template <typename T>
    static T floor(T a) {
        return std::floor(a);
    }
    /* 四舍五入 */
    template <typename T>
    static T round(T a) {
        return std::round(a);
    }
    /* 舍去尾部 */
    template <typename T>
    static T trunc(T a) {
        return std::trunc(a);
    }
    /* 最小值 */
    template <typename T>
    static T min(T a, T b) {
        return std::min(a, b);
    }
    /* 最大值 */
    template <typename T>
    static T max(T a, T b) {
        return std::max(a, b);
    }
    /* 检查给定值的符号 */
    template <typename T>
    static T sign(T a) {
        return std::signbit(a) ? -1 : 1;
    }
    /* 正弦 */
    template <typename T>
    static T sin(T a) {
        return std::sin(a);
    }
    /* 余弦 */
    template <typename T>
    static T cos(T a) {
        return std::cos(a);
    }
    /* 正切 */
    template <typename T>
    static T tan(T a) {
        return std::tan(a);
    }
    /* 反正弦 */
    template <typename T>
    static T asin(T a) {
        return std::asin(a);
    }
    /* 反余弦 */
    template <typename T>
    static T acos(T a) {
        return std::acos(a);
    }
    /* 反正切 */
    template <typename T>
    static T atan(T a) {
        return std::atan(a);
    }
    /* 返回以弧度表示的 y/x 的反正切 */
    template <typename T>
    static T atan2(T y, T x) {
        return std::atan2(y, x);
    }
    /* 双曲正弦值 */
    template <typename T>
    static T sinh(T a) {
        return std::sinh(a);
    }
    /* 双曲余弦值 */
    template <typename T>
    static T cosh(T a) {
        return std::cosh(a);
    }
    /* 双曲正切值 */
    template <typename T>
    static T tanh(T a) {
        return std::tanh(a);
    }
    /* 双曲反正弦值 */
    template <typename T>
    static T asinh(T a) {
        return std::asinh(a);
    }
    /* 双曲反余弦值 */
    template <typename T>
    static T acosh(T a) {
        return std::acosh(a);
    }
    /* 双曲反正切值 */
    template <typename T>
    static T atanh(T a) {
        return std::atanh(a);
    }
    /* 计算以自然常数e为底的指数 */
    template <typename T>
    static T exp(T a) {
        return std::exp(a);
    }
    /* 返回指定数字的以e为底的对数 */
    template <typename T>
    static T log(T a) {
        return std::log(a);
    }
    /* 返回指定数字的以10为底的对数 */
    template <typename T>
    static T log10(T a) {
        return std::log10(a);
    }
    /* 返回指定数字的以2为底的对数 */
    template <typename T>
    static T log2(T a) {
        return std::log2(a);
    }
    /* 度转弧度 */
    template <typename T>
    static T deg2rad(T a) {
        return a * (M_PI / 180.0);
    }
    /* 弧度转度 */
    template <typename T>
    static T rad2deg(T a) {
        return a * (180.0 / M_PI);
    }

    /* 欧几里得距离 */
    template <typename T>
    static double calculateDistance(T x1, T y1, T x2, T y2) {
        double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
        return distance;
    }
    /* 曼哈顿距离 */
    template <typename T>
    static double calculateManhattanDistance(T x1, T y1, T x2, T y2) {
        double distance = std::abs(x2 - x1) + std::abs(y2 - y1);
        return distance;
    }
    /* 切比雪夫距离 */
    template <typename T>
    static double calculateChebyshevDistance(T x1, T y1, T x2, T y2) {
        double distance = std::max(std::abs(x2 - x1), std::abs(y2 - y1));
        return distance;
    }

};

#endif