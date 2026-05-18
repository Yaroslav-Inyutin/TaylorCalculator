#pragma once
#include <string>
#include <ostream>
class TaylorController {
public:
    void runRemainder(const std::string& input, bool useReduction, double x, unsigned n, std::ostream& out);
    void runDegree(const std::string& input, bool useReduction, double x, double acc, std::ostream& out);
    void runInterval(const std::string& input, bool useReduction, double dx, double acc, unsigned n, std::ostream& out);
};
