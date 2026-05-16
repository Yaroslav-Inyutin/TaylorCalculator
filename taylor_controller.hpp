#pragma once
#include <string>

class TaylorController {
public:
    void runRemainder(const std::string& input, bool useReduction, double x, unsigned n);
    void runDegree(const std::string& input, bool useReduction, double x, double acc);
    void runInterval(const std::string& input, bool useReduction, double dx, double acc, unsigned n);
};
