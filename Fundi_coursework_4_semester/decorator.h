//
// Created by ayttekao on 5/13/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__DECORATOR_H
#define FUNDI_COURSEWORK_4_SEMESTER__DECORATOR_H

template <class TypeData>
class Decorator
{
public:
    Decorator() = default;
    virtual void add(std::shared_ptr<TypeData> data) = 0;
    virtual void remove() = 0;
    virtual void countingStatistics() = 0;
    virtual std::list<std::shared_ptr<TypeData>> find() = 0;
    virtual ~Decorator() = default;
};


void generateOver(Decorator<PopulationCensus>* container, size_t count)
{
    std::shared_ptr<PopulationCensus> populationCensus;
    for (int i = 0; i < count; i++)
    {
        populationCensus = PopulationCensus::randomGenerateObjectPopulationCensus();
        try{
            container->add(std::shared_ptr<PopulationCensus>(populationCensus));
        } catch (const std::exception& e) {
//            std::cout << e.what();
        }
    }
}

#endif //FUNDI_COURSEWORK_4_SEMESTER__DECORATOR_H
