//
// Created by ayttekao on 4/16/21.
//

#ifndef FUNDI_6_MONOM_H
#define FUNDI_6_MONOM_H

#include <map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <set>

class Monom : public TeX_convertible
{
private:
    std::map<char, uint16_t> variables;
    int coefficient;
public:
    Monom() { coefficient = 0; }
    explicit Monom(char* cString)
    {
        char one[] = "1";
        std::vector<char*> tmpValues;
        char *pch = std::strtok(cString, " ^");
        while (pch != nullptr)
        {
            if (std::isalpha(*pch) and std::isalpha(*tmpValues[tmpValues.size() - 1]))
                tmpValues.push_back(one);

            tmpValues.push_back(pch);
            pch = std::strtok(nullptr, " ^*");
        }
        if (std::isalpha(*tmpValues[tmpValues.size() - 1]))
            tmpValues.push_back(one);
        coefficient = std::stoi(tmpValues[0]);
        for (int count = 1; count < tmpValues.size(); count += 2)
            variables.insert(std::pair<char, uint16_t>(*tmpValues[count], std::stoi(tmpValues[count + 1])));
    }
    Monom(const Monom& originalMonom)
    {
        coefficient = originalMonom.coefficient;
        variables = originalMonom.variables;
    }
    Monom& operator=(const Monom& rightMonom)
    {
        if (this == &rightMonom)
            return *this;
        else if (rightMonom.coefficient == 0)
        {
            coefficient = 0;
            variables.clear();
        }
        else
        {
            variables = rightMonom.variables;
            coefficient = rightMonom.coefficient;
        }
        return *this;
    }
    Monom& operator+=(const Monom& rightMonom)
    {
        if (variables != rightMonom.variables)
            throw std::invalid_argument("Monomials must have the same variables!");
        else if ((coefficient += rightMonom.coefficient) == 0)
            variables.clear();

        return *this;
    }
    Monom operator+(const Monom& rightMonom) const
    {
        return Monom(*this) += rightMonom;
    }
    Monom& operator-=(const Monom& rightMonom)
    {
        if (variables != rightMonom.variables)
            throw std::invalid_argument("Monomials must have the same variables!");
        else if ((coefficient -= rightMonom.coefficient) == 0)
            variables.clear();

        return *this;
    }
    Monom operator-(const Monom& rightMonom) const
    {
        return Monom(*this) -= rightMonom;
    }
    Monom& operator*=(const Monom& rightMonom)
    {
        if (rightMonom.coefficient == 0)
        {
            coefficient = 0;
            variables.clear();
        }
        else
        {
            coefficient *= rightMonom.coefficient;
            for (auto& iter : rightMonom.variables)
            {
                auto requiredElement = variables.find(iter.first);
                if (requiredElement != variables.end())
                    requiredElement->second += iter.second;
                else
                    variables.insert({iter.first, iter.second});
            }
        }
        return *this;
    }
    Monom operator*(const Monom& rightMonom) const
    {
        return Monom(*this) *= rightMonom;
    }
    Monom& operator/=(char partialDerivative)
    {
        for (auto & iter : variables)
        {
            if (iter.first == partialDerivative)
            {
                coefficient *= iter.second;
                iter.second -= 1;
                if (iter.second == 0)
                    variables.erase(partialDerivative);
                return *this;
            }
        }
        coefficient = 0;
        variables.clear();
        return *this;
    }
    Monom operator/(char partialDerivative) const
    {
        return Monom(*this) /= partialDerivative;
    }
    bool operator==(const Monom& rightMonom) const
    {
        if (coefficient == rightMonom.coefficient and variables == rightMonom.variables)
            return true;
        return false;
    }
    bool operator!=(const Monom& rightMonom) const
    {
        return !(*this == rightMonom);
    }
    bool isEmpty() const
    {
        return coefficient == 0;
    }
    std::string convert() const override
    {
        std::string result;
        for (const auto& iter : variables)
            result += std::to_string(iter.first) + "^" + "{" + std::to_string(iter.second) + "}";
        return result;
    }
    ~Monom() = default;
    size_t sumOfDegrees()
    {
        size_t sum = 0;
        for (auto & variable : variables)
            sum += variable.second;
        return sum;
    }
    friend std::ostream& operator<<(std::ostream &out, const Monom& rightMonom)
    {
        for (const auto& iter : rightMonom.variables)
            out << iter.first << "^" << "{" << iter.second << "}";
        return out;
    }
    friend std::istream& operator>>(std::istream &in, Monom& rightMonom)
    {
        std::string coef, enteredMonom;
        in >> coef >> enteredMonom;
        enteredMonom = coef + " " + enteredMonom;
        char cString[enteredMonom.length()];

        for (int i = 0; i < sizeof(cString); i++)
            cString[i] = enteredMonom[i];
        rightMonom = Monom(cString);
        return in;
    }
    std::set<char> setAllVariables()
    {
        std::set<char> all;
        for (auto & variable : variables)
            all.insert(variable.first);
        return all;
    }

};

#endif //FUNDI_6_MONOM_H
