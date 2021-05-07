//
// Created by ayttekao on 4/17/21.
//

#ifndef FUNDI_6_POLYNOM_H
#define FUNDI_6_POLYNOM_H

#include <list>
#include <set>
#include "monom.h"

class Polynom : public TeX_convertible
{
private:
    std::list<Monom> listWithMonomials;
public:
    Polynom()=default;
    explicit Polynom(char* cString)
    {
        std::vector<char*> tmpValues;
        char *pch = std::strtok(cString, "[]");
        while (pch != nullptr)
        {
            tmpValues.push_back(pch);
            pch = std::strtok(nullptr, "[]");
        }
        for (int count = 0; count < tmpValues.size(); count++)
        {
            if (std::strcmp(tmpValues[count], "+") == 0)
                continue;
            else if (std::strcmp(tmpValues[count], "-") == 0)
            {
                char *tmpString = tmpValues[count + 1];
                if (*tmpString == '-')
                    replace(&tmpString, '-', '+');
            }
            else
                listWithMonomials.emplace_back(tmpValues[count]);
        }
    }
    static void replace(char **cString, char replaceable, char substitute)
    {
        size_t len = strlen(*cString);
        for (int count = 0; count < len; count++)
            if ((*(*cString + count)) == replaceable)
            {
                (*(*cString + count)) = substitute;
                break;
            }
    }
    Polynom(const Polynom& originalPolynom)
    {
        listWithMonomials = originalPolynom.listWithMonomials;
    }
    ~Polynom()=default;
    Polynom& operator=(const Polynom& originalPolynom)
    {
        if (this == &originalPolynom)
            return *this;
        else if (originalPolynom.listWithMonomials.empty())
            listWithMonomials.clear();
        else
            listWithMonomials = originalPolynom.listWithMonomials;

        return *this;
    }
    Polynom& operator+=(const Monom& rightMonom)
    {
        bool isAdded = false;
        for (auto & listWithMonomial : listWithMonomials)
        {
            try{
                listWithMonomial += rightMonom;
                isAdded = true;
            } catch (const std::exception& e) {
                std::cerr << "Error:" << e.what() << std::endl;
            }
        }
        if (not isAdded)
            listWithMonomials.emplace_back(rightMonom);
        return *this;
    }
    Polynom operator+(const Monom& rightMonom)
    {
        return Polynom(*this) += rightMonom;
    }
    Polynom& operator-=(const Monom& rightMonom)
    {
        bool isAdded = false;
        for (auto & listWithMonomial : listWithMonomials)
        {
            try{
                listWithMonomial -= rightMonom;
                isAdded = true;
            } catch (const std::exception& e) {
                std::cerr << "Error:" << e.what() << std::endl;
            }
        }
        if (not isAdded)
            listWithMonomials.emplace_back(rightMonom);
        return *this;
    }
    Polynom operator-(const Monom& rightMonom)
    {
        return Polynom(*this) -= rightMonom;
    }
    Polynom& operator+=(const Polynom& rightPolynom)
    {
        for (const auto& iter : rightPolynom.listWithMonomials)
            *this += iter;

        return *this;
    }
    Polynom operator+(const Polynom& rightPolynom)
    {
        return Polynom(*this) += rightPolynom;
    }
    Polynom& operator-=(const Polynom& rightPolynom)
    {
        for (const auto& iter : rightPolynom.listWithMonomials)
            *this -= iter;

        return *this;
    }
    Polynom operator-(const Polynom& rightPolynom)
    {
        return Polynom(*this) -= rightPolynom;
    }
    Polynom& operator*=(const Monom& rightMonom)
    {
        for (auto iter : listWithMonomials)
            iter *= rightMonom;
        simplify(*this);
        return *this;
    }
    Polynom operator*(const Monom& rightMonom)
    {
        return Polynom(*this) *= rightMonom;
    }
    Polynom& operator*=(const Polynom& rightPolynom)
    {
        Polynom result;
        for (const auto& firstIter : listWithMonomials)
            for (const auto& secondIter : rightPolynom.listWithMonomials)
                result.listWithMonomials.emplace_back(Monom(firstIter) * Monom(secondIter));

        simplify(result);
        *this = result;
        return *this;
    }
    Polynom operator*(const Polynom& rightPolynom)
    {
        return Polynom(*this) *= rightPolynom;
    }
    Polynom& operator/=(char partialDerivative)
    {
        for (auto& iter : listWithMonomials)
            iter /= partialDerivative;
        return *this;
    }
    Polynom operator/(char partialDerivative)
    {
        return Polynom(*this) /= partialDerivative;
    }
    Polynom& operator/=(char* mixedDerivative)
    {
        size_t len = strlen(mixedDerivative);
        for (int count = 0; count < len; count++)
            *this /= mixedDerivative[count];
        simplify(*this);
        return *this;
    }
    Polynom operator/(char* mixedDerivative)
    {
        return Polynom(*this) /= mixedDerivative;
    }
    bool operator==(const Polynom& rightPolynom) const
    {
        auto it = rightPolynom.listWithMonomials.begin();
        auto it2 = listWithMonomials.begin();
        if (listWithMonomials.size() != rightPolynom.listWithMonomials.size())
            return false;
        while (it != rightPolynom.listWithMonomials.end() || it2 != listWithMonomials.end())
        {
            if (Monom(*it) != Monom(*it2))
                return false;
            ++it;
            ++it2;
        }
        return true;
    }

    bool operator!=(const Polynom& rightMonom) const
    {
        return !(*this == rightMonom);
    }
    friend std::ostream& operator<<(std::ostream &out, const Polynom& rightPolynom)
    {
        size_t len = rightPolynom.listWithMonomials.size() - 1;
        size_t count = 0;
        for (const auto& iter : rightPolynom.listWithMonomials)
        {
            if (count != len)
                out << "[" << iter << "]" << "+";
            else
                out << "[" << iter << "]"   ;
            count++;
        }
        return out;
    }
    friend std::istream& operator>>(std::istream &in, Polynom& rightPolynom)
    {
        std::string enteredPolynom;
        std::getline(in, enteredPolynom, '\n');
        char* tmpStringC = (char*)malloc((enteredPolynom.length() + 1) * sizeof(char));
        std::strcpy(tmpStringC, enteredPolynom.c_str());


        if (not rightPolynom.listWithMonomials.empty())
            rightPolynom.listWithMonomials.clear();
        rightPolynom = Polynom(tmpStringC);

        free(tmpStringC);
        return in;
    }
    static void simplify(Polynom& rightPolynom)
    {
        Polynom res;
        for (auto iter = rightPolynom.listWithMonomials.begin(); iter != rightPolynom.listWithMonomials.end(); ++iter)
        {
            auto secondIter = iter;
            secondIter++;
            try
            {
                Monom tmp = (*iter) + (*secondIter);
                if (not tmp.isEmpty())
                    res.listWithMonomials.emplace_back(tmp);
                iter++;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
                Monom tmp = *iter;
                if (not tmp.isEmpty())
                    res.listWithMonomials.emplace_back(tmp);
            }
        }
        rightPolynom = res;
        if (rightPolynom.listWithMonomials.empty())
            rightPolynom.listWithMonomials.emplace_back(Monom("0"));
    }
    friend bool uniformity(const Polynom& rightPolynom)
    {
        auto it = rightPolynom.listWithMonomials.begin();
        auto it2 = it++;
        while (it2 != rightPolynom.listWithMonomials.end())
        {
            if (Monom(*it).sumOfDegrees() != Monom(*it2).sumOfDegrees())
                return false;
            it2++;
        }
        return true;
    }
    static bool harmony(Polynom& rightPolynom)
    {
        std::set<char> setVariables;
        Polynom result, zero;
        zero.listWithMonomials.emplace_back(Monom("0"));
        for (auto iter : rightPolynom.listWithMonomials)
        {
            for (auto secondIter : iter.setAllVariables())
                setVariables.insert(secondIter);
        }
        for (char setVariable : setVariables)
        {
            rightPolynom /= setVariable;
            rightPolynom /= setVariable;
            result += rightPolynom;
        }
        if(result == zero)
            return true;
        return false;
    }
    std::string convert() const override
    {
        std::string result;
        for (const auto& iter : listWithMonomials)
            result += iter.convert();
        return result;
    }
};

#endif //FUNDI_6_POLYNOM_H
