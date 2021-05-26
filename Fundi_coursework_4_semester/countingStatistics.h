//
// Created by ayttekao on 5/20/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__COUNTINGSTATISTICS_H
#define FUNDI_COURSEWORK_4_SEMESTER__COUNTINGSTATISTICS_H

#include <map>
#include <forward_list>

class CountingStatistics
{
private:
    std::list<std::shared_ptr<PopulationCensus>> statisticList;

    std::map<uint16_t, uint16_t> uint16Statistics(int choice)
    {
        std::map<uint16_t, uint16_t> statistic;
        switch (choice) {
            case 1:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getEnumerationAreaNumber());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getEnumerationAreaNumber(), 1});
                }
                break;
            case 2:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getHouseholdNumberWithinTheEnumerationArea());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getHouseholdNumberWithinTheEnumerationArea(), 1});
                }
                break;
            case 3:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getFormNumber());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getFormNumber(), 1});
                }
                break;
            case 4:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getNumberOfYears());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getNumberOfYears(), 1});
                }
                break;
            case 5:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getAmountOfChildren());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getAmountOfChildren(), 1});
                }
                break;
            case 6:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getYearOfContinuousResidence());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getYearOfContinuousResidence(), 1});
                }
                break;
            case 7:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getYearsOfComebackToRussia());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getYearsOfComebackToRussia(), 1});
                }
                break;
            default:
                throw std::invalid_argument("Invalid input!");
        }
        return statistic;
    }
    std::map<gender, uint16_t> genderStatistics()
    {
        std::map<gender, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getSelectedGender());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getSelectedGender(), 1});
        }
        return statistic;
    }
    std::map<struct tm*, uint16_t> dateStatistics(int choice)
    {
        std::map<struct tm*, uint16_t> statistic;
        switch (choice) {
            case 1:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getBirthDay());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getBirthDay(), 1});
                }
                break;
            case 2:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getBirthDayFirstChild());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getBirthDayFirstChild(), 1});
                }
                break;
            default:
                throw std::invalid_argument("Invalid input!");
        }
        return statistic;
    }
    std::map<marriageAnswer, uint16_t> marriageInfoStatistics()
    {
        std::map<marriageAnswer, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getMarriageInfo());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getMarriageInfo(), 1});
        }
        return statistic;
    }
    std::map<yesNoAnswer, uint16_t> yesNoAnswerStatistics(int choice)
    {
        std::map<yesNoAnswer, uint16_t> statistic;
        switch (choice) {
            case 1:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getThatPersonSpouseLivesHousehold());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getThatPersonSpouseLivesHousehold(), 1});
                }
                break;
            case 2:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getLivedInOtherCountries());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getLivedInOtherCountries(), 1});
                }
                break;
            case 3:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getProficiencyInRussian());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getProficiencyInRussian(), 1});
                }
                break;
            case 4:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getUseOfRussianLanguageInEverydayLife());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getUseOfRussianLanguageInEverydayLife(), 1});
                }
                break;
            case 5:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getAbilityReadAndWrite());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getAbilityReadAndWrite(), 1});
                }
                break;
            case 6:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getCurrentEducation());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getCurrentEducation(), 1});
                }
                break;
            case 7:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getWorkForCertainPeriod());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getWorkForCertainPeriod(), 1});
                }
                break;
            case 8:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getMainWorkWasInTheSameSettlement());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getMainWorkWasInTheSameSettlement(), 1});
                }
                break;
            case 9:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getJobSearchInMarch());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getJobSearchInMarch(), 1});
                }
                break;
            default:
                throw std::invalid_argument("Invalid input!");
        }
        return statistic;
    }
    std::map<std::string, uint16_t> stringStatistics(int choice)
    {
        std::map<std::string, uint16_t> statistic;
        switch (choice) {
            case 0:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getFullName());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getFullName(), 1});
                }
                break;
            case 1:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getPlaceOfBirth());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getPlaceOfBirth(), 1});
                }
                break;
            case 2:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getPreviousPlaceOfResidence());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getPreviousPlaceOfResidence(), 1});
                }
                break;
            case 3:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getPlaceOfResidenceToArrivalInRussia());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getPlaceOfResidenceToArrivalInRussia(), 1});
                }
                break;
            case 4:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getNativeLanguage());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getNativeLanguage(), 1});
                }
                break;
            case 5:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getCitizenship());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getCitizenship(), 1});
                }
                break;
            case 6:
                for (const auto& iter : statisticList)
                {
                    auto requiredItem = statistic.find(iter->getNationality());
                    if (requiredItem != statistic.end())
                        requiredItem->second++;
                    else
                        statistic.insert({iter->getNationality(), 1});
                }
                break;
            default:
                throw std::invalid_argument("Invalid input!");
        }
        return statistic;
    }
    std::map<typeOfDegree, uint16_t> typeOfDegreeStatistics()
    {
        std::map<typeOfDegree, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getAcademicDegree());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getAcademicDegree(), 1});
        }
        return statistic;
    }
    std::map<std::set<studyingPrograms>, uint16_t> studyingProgramsStatistics()
    {
        std::map<std::set<studyingPrograms>, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getCurrentEducationPrograms());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getCurrentEducationPrograms(), 1});
        }
        return statistic;
    }
    std::map<std::set<typesOfLivelihoods>, uint16_t> livelihoodsStatistics()
    {
        std::map<std::set<typesOfLivelihoods>, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getLivelihoods());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getLivelihoods(), 1});
        }
        return statistic;
    }
    std::map<typesOfLivelihoods, uint16_t> mainLivelihoodStatistics()
    {
        std::map<typesOfLivelihoods, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getMainLivelihood());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getMainLivelihood(), 1});
        }
        return statistic;
    }
    std::map<std::string, uint16_t> positionAtWorkStatistics()
    {
        std::map<std::string, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(putPositionAtWork(iter->getPositionMainJob()));
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({putPositionAtWork(iter->getPositionMainJob()), 1});
        }
        return statistic;
    }
    std::map<typeInformationAboutWork, uint16_t> informationAboutWorkStatistics()
    {
        std::map<typeInformationAboutWork, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getInformationAboutWork());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getInformationAboutWork(), 1});
        }
        return statistic;
    }
    std::map<workScheduleOptions, uint16_t> scheduleStatistics()
    {
        std::map<workScheduleOptions, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getSchedule());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getSchedule(), 1});
        }
        return statistic;
    }
    std::map<jobOptionsMarch, uint16_t> suitableJobInMarchStatistics()
    {
        std::map<jobOptionsMarch, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getSuitableJobInMarch());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getSuitableJobInMarch(), 1});
        }
        return statistic;
    }
    std::map<mainReasonWorkMarch, uint16_t> jobSearchDuringMarchStatistics()
    {
        std::map<mainReasonWorkMarch, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getJobSearchDuringMarch());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getJobSearchDuringMarch(), 1});
        }
        return statistic;
    }
    std::map<registrationInfoInHousehold, uint16_t> registrationInThisHouseholdStatistics()
    {
        std::map<registrationInfoInHousehold, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getRegistrationInThisHousehold());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getRegistrationInThisHousehold(), 1});
        }
        return statistic;
    }
    std::map<residenceRegistrationInfo, uint16_t> residenceRegistrationStatistics()
    {
        std::map<residenceRegistrationInfo, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getResidenceRegistration());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getResidenceRegistration(), 1});
        }
        return statistic;
    }
    std::map<std::set<std::string>, uint16_t> languagesStatistics()
    {
        std::map<std::set<std::string>, uint16_t> statistic;
        for (const auto& iter : statisticList)
        {
            auto requiredItem = statistic.find(iter->getLanguages());
            if (requiredItem != statistic.end())
                requiredItem->second++;
            else
                statistic.insert({iter->getLanguages(), 1});
        }
        return statistic;
    }
public:
    explicit CountingStatistics(const std::list<std::shared_ptr<PopulationCensus>>& list)
    {
        statisticList = list;
    }
    explicit CountingStatistics(const std::forward_list<std::shared_ptr<PopulationCensus>>& forwardList)
    {
        for (const auto& iter : forwardList)
            statisticList.emplace_back(iter);
    }
    void countingStatistics()
    {
        int choice;
        std::cout << "Выберите поле для сбора статистики:\n"
                     "1. номер переписного участка\n"
                     "2. номер помещения в пределах счетного участка\n"
                     "3. номер бланка\n"
                     "4. имя\n"
                     "5. пол\n"
                     "6. дата рождения\n"
                     "7. число полных лет\n"
                     "8. ваше состояние в браке\n"
                     "9. супруг(а) этого лица проживает в домохозяйстве\n"
                     "10. сколько детей вы родили\n"
                     "11. год рождения первого ребенка\n"
                     "12. место вашего рождения\n"
                     "13. с какого года вы непрерывно проживаете в этом населенном пункте\n"
                     "14. прежднее место жительства\n"
                     "15. проживали ли выболее 12 месяцев в других странах\n"
                     "16. где вы проживали до прибытия в Россию (если выбрано проживание в других странах)\n"
                     "17. год прибытия (возвращения) в Россию\n"
                     "18. владаете ли вы русским языком\n"
                     "19. используете ли вы его в повседневной жизни\n"
                     "20. какими иными языками вы владеете\n"
                     "21. родной язык\n"
                     "22. гражданство\n"
                     "23. национальная принадлежность\n"
                     "24. умеете ли вы читать и писать\n"
                     "25. имеете ли вы ученую степень\n"
                     "26. получаете ли вы образование в настоящее время\n"
                     "27. все программы по которым обучаетесь\n"
                     "28. имеющиеся источники средств к существованию\n"
                     "29. какой из отмеченных источников вы считаете для себя основным\n"
                     "30. имели ли вы какую-либо оплачиваемую работу или доходное занятие с 25 по 31 марта 2021 года\n"
                     "31. кем вы являлись на основной работе\n"
                     "32. ваша основная работа находилась в том же населенном пункте, где вы проживаете постоянно\n"
                     "33. где находилась ваша основная работа\n"
                     "34. вы выезжали(выходили) на работу\n"
                     "35. если бы вам предложили подходящую работу в последнюю неделю марта, то когда вы смогли бы приступить к ней\n"
                     "36. вы искали работу в течении марта\n"
                     "37. вы искали работу в течении марта\n"
                     "38. зарегистрированы ли вы в этом помещении\n"
                     "39. где вы зарегистрировваны по месту жительства\n>";
        std::cin >> choice;
        switch (choice) {
            case 1:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(1);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 2:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(2);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 3:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(3);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 4:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(0);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 5:
            {
                std::map<gender, uint16_t> statistic = genderStatistics();
                for (auto iter : statistic)
                    std::cout << (iter.first ? "мужской" : "женский") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 6:
            {
                std::map<struct tm*, uint16_t> statistic = dateStatistics(1);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 7:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(4);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 8:
            {
                std::map<marriageAnswer, uint16_t> statistic = marriageInfoStatistics();
                for (auto iter : statistic)
                    std::cout << putMarriageAnswer(iter.first) << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: "
                              << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 9:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(1);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 10:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(5);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 11:
            {
                std::map<struct tm*, uint16_t> statistic = dateStatistics(2);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 12:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(1);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 13:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(6);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 14:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(2);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 15:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(2);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 16:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(3);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 17:
            {
                std::map<uint16_t, uint16_t> statistic = uint16Statistics(7);
                for (auto iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 18:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(3);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 19:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(4);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 20:
            {
                std::map<std::set<std::string>, uint16_t> statistic = languagesStatistics();
                for (const auto& iter : statistic)
                {
                    for (const auto &secondIter : iter.first)
                        std::cout << "'" << secondIter << "'";
                    std::cout << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                }
                break;
            }
            case 21:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(4);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 22:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(5);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 23:
            {
                std::map<std::string, uint16_t> statistic = stringStatistics(6);
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 24:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(5);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 25:
            {
                std::map<typeOfDegree, uint16_t> statistic = typeOfDegreeStatistics();
                for (auto iter : statistic)
                    std::cout << putTypeOfDegree(iter.first) << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 26:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(6);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 27:
            {
                std::map<std::set<studyingPrograms>, uint16_t> statistic = studyingProgramsStatistics();
                for (const auto& iter : statistic)
                {
                    for (const auto &secondIter : iter.first)
                        std::cout << "'" << putStudyingPrograms(secondIter) << "'";
                    std::cout << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                }
                break;
            }
            case 28:
            {
                std::map<std::set<typesOfLivelihoods>, uint16_t> statistic = livelihoodsStatistics();
                for (const auto& iter : statistic)
                {
                    for (const auto &secondIter : iter.first)
                        std::cout << "'" << putTypesOfLivelihoods(secondIter) << "'";
                    std::cout << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                }
                break;
            }
            case 29:
            {
                std::map<typesOfLivelihoods, uint16_t> statistic = mainLivelihoodStatistics();
                for (auto iter : statistic)
                    std::cout << putTypesOfLivelihoods(iter.first) << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 30:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(7);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 31:
            {
                std::map<std::string, uint16_t> statistic = positionAtWorkStatistics();
                for (const auto& iter : statistic)
                    std::cout << iter.first << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 32:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(8);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 33:
            {
                std::map<typeInformationAboutWork, uint16_t> statistic = informationAboutWorkStatistics();
                for (const auto& iter : statistic)
                    std::cout << "'" << iter.first.subject << "'" << "'" << iter.first.urbanSettlement << "'" << "'"
                              << iter.first.district << "'" << "'" << iter.first.anotherState << "'" << " Статистика:\nАбсолютная: "
                              << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 34:
            {
                std::map<workScheduleOptions, uint16_t> statistic = scheduleStatistics();
                for (auto iter : statistic)
                    std::cout << putWorkScheduleOptions(iter.first) << " Статистика:\nАбсолютная: " << iter.second
                              << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 35:
            {
                std::map<jobOptionsMarch, uint16_t> statistic = suitableJobInMarchStatistics();
                for (auto iter : statistic)
                    std::cout << putJobOptionsMarch(iter.first) << " Статистика:\nАбсолютная: " << iter.second
                              << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 36:
            {
                std::map<yesNoAnswer, uint16_t> statistic = yesNoAnswerStatistics(9);
                for (auto iter : statistic)
                    std::cout << (iter.first ? "да" : "нет") << " Статистика:\nАбсолютная: " << iter.second << "\nОтносительная: " << float(iter.second) / float(statistic.size())
                              << std::endl;
                break;
            }
            case 37:
            {
                std::map<mainReasonWorkMarch, uint16_t> statistic = jobSearchDuringMarchStatistics();
                for (auto iter : statistic)
                    std::cout << putMainReasonWorkMarch(iter.first) << " Статистика:\nАбсолютная: " << iter.second
                              << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 38:
            {
                std::map<registrationInfoInHousehold, uint16_t> statistic = registrationInThisHouseholdStatistics();
                for (auto iter : statistic)
                    std::cout << putRegistrationInfoInHousehold(iter.first) << "\n->Статистика:\nАбсолютная: " << iter.second
                              << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            case 39:
            {
                std::map<residenceRegistrationInfo, uint16_t> statistic = residenceRegistrationStatistics();
                for (auto iter : statistic)
                    std::cout << putResidenceRegistrationInfo(iter.first) << " Статистика:\nАбсолютная: " << iter.second
                              << "\nОтносительная: " << float(iter.second) / float(statistic.size()) << std::endl;
                break;
            }
            default:
                throw std::invalid_argument("Invalid input!");
        }
    }
};
#endif //FUNDI_COURSEWORK_4_SEMESTER__COUNTINGSTATISTICS_H
