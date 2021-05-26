//
// Created by ayttekao on 5/14/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__POPULATIONCENSUS_H
#define FUNDI_COURSEWORK_4_SEMESTER__POPULATIONCENSUS_H
#include "customTypes.h"
#include <random>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <memory>

#define MAX_NUM_OF_SECONDS (5*365*24*60*60) // number of seconds in 5 years

struct tm* GetTimeAndDate()
{
    unsigned int now_seconds  = (unsigned int)time(nullptr);
    unsigned int rand_seconds = (rand()*rand())%(MAX_NUM_OF_SECONDS+1);
    time_t       rand_time    = (time_t)(now_seconds-rand_seconds);
    return localtime(&rand_time);
}

std::string randomString(size_t length)
{
    auto randChar = []() -> char
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 25);
        const char charset[] =
                "abcdefghijklmnopqrstuvwxyz";
        return charset[ distribution(generator) ];
    };
    std::string str(length,0);
    std::generate_n(str.begin(), length, randChar );
    return str;
}

class PopulationCensus
{
protected:
    /*1*/uint16_t        enumerationAreaNumber; /* номер переписного участка */
    /*2*/uint16_t        householdNumberWithinTheEnumerationArea; /* номер помещения в пределах счетного участка */
    /*3*/uint16_t        formNumber; /* номер бланка */
    /*4*/std::string     fullName; /* ваше имя */
    /*5*/gender          selectedGender; /* ваш пол */
    /*6*/struct tm*      birthDay; /* дата вашего рождения */
    /*7*/uint8_t         numberOfYears; /* число полных лет */
    /*8*/marriageAnswer  marriageInfo; /* ваше состояние в браке */
    /*9*/yesNoAnswer     thatPersonSpouseLivesHousehold; /* супруг(а) этого лица проживает в домохозяйстве */
    /*10*/uint8_t         amountOfChildren; /* сколько детей вы родили */
    /*11*/struct tm*      birthDayFirstChild; /* год рождения первого ребенка */
    /*12*/std::string     placeOfBirth; /* место вашего рождения */
    /*13*/uint8_t         yearOfContinuousResidence; /* с какого года вы непрерывно проживаете в этом населенном пункте */
    /*14*/std::string     previousPlaceOfResidence; /* ваше пржднее место жительства */
    /*15*/yesNoAnswer     livedInOtherCountries; /* проживали ли выболее 12 месяцев в других странах */
    /*16*/std::string     placeOfResidenceToArrivalInRussia; /* где вы проживали до прибытия в Россию (если выбрано проживание
                                                    * в других странах) */
    /*17*/uint8_t         yearsOfComebackToRussia; /* год прибытия (возвращения) в Россию */
    /*18*/yesNoAnswer     proficiencyInRussian; /* владаете ли вы русским языком */
    /*19*/yesNoAnswer     useOfRussianLanguageInEverydayLife; /* используете ли вы его в повседневной жизни */
    /*20*/std::set<std::string> languages; /* какими иными языками вы владеете */
    /*21*/std::string     nativeLanguage; /* ваш родной язык */
    /*22*/std::string     citizenship; /* ваше гражданство */
    /*23*/std::string     nationality; /* ваша национальная принадлежность */
    /*24*/yesNoAnswer     abilityReadAndWrite; /* умеете ли вы читать и писать (если выбрано не имею образования) */
    /*25*/typeOfDegree    academicDegree; /* имеете ли вы ученую степень (для лиц с высшим образованием и кадров высшей квалификации) */
    /*26*/yesNoAnswer     currentEducation; /* получаете ли вы образование в настоящее время */
    /*27*/std::set<studyingPrograms> currentEducationPrograms; /* отметье все программы по которым обучаетесь (если есть текущее образование) */
    /*28*/std::set<typesOfLivelihoods> livelihoods; /* укажите все имеющиеся у вас источники средств к существованию */
    /*29*/typesOfLivelihoods mainLivelihood; /* какой из отмеченных источников вы считаете для себя основным */
    /*30*/yesNoAnswer     workForCertainPeriod; /* имели ли вы какую-либо оплачиваемую работу или доходное занятие с 25 по 31 марта 2021 года */
    /*31*/positionAtWork  positionMainJob; /* кем вы являлись на основной работе */
    /*32*/yesNoAnswer     mainWorkWasInTheSameSettlement; /* ваша основная работа находилась в том же населенном пункте, где вы проживаете постоянно */
    /*33*/typeInformationAboutWork informationAboutWork; /* где находилась ваша основная работа */
    /*34*/workScheduleOptions schedule; /* вы выезжали(выходили) на работу */
    /*35*/jobOptionsMarch     suitableJobInMarch; /* если бы вам предложили подходящую работу в последнюю неделю марта,
                                        * то когда вы смогли бы приступить к ней */
    /*36*/yesNoAnswer                 jobSearchInMarch; /* вы искали работу в течении марта */
    /*37*/mainReasonWorkMarch         jobSearchDuringMarch; /* вы искали работу в течении марта */
    /*38*/registrationInfoInHousehold registrationInThisHousehold; /* зарегистрированы ли вы в этом помещении */
    /*39*/residenceRegistrationInfo   residenceRegistration; /* где вы зарегистрировваны по месту жительства */

    static yesNoAnswer generateYesNo()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 1);
        auto answer = static_cast<yesNoAnswer>(distribution(generator));
        return answer;
    };

    static gender generateGender()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 1);
        auto answer = static_cast<gender>(distribution(generator));
        return answer;
    }

    static marriageAnswer generateMarriageAnswer()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 5);
        auto answer = static_cast<marriageAnswer>(distribution(generator));
        return answer;
    }

    static typeOfDegree generateTypeOfDegree()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 2);
        auto answer = static_cast<typeOfDegree>(distribution(generator));
        return answer;
    }

    static typesOfLivelihoods generateTypesOfLivelihoods()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 13);
        auto answer = static_cast<typesOfLivelihoods>(distribution(generator));
        return answer;
    }

    static positionAtWork generatePositionAtWork()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 5);
        auto answer = static_cast<positionAtWork>(distribution(generator));
        return answer;
    }

    static workScheduleOptions generateWorkScheduleOptions()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 4);
        auto answer = static_cast<workScheduleOptions>(distribution(generator));
        return answer;
    }

    static jobOptionsMarch generateJobOptionsMarch()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 2);
        auto answer = static_cast<jobOptionsMarch>(distribution(generator));
        return answer;
    }

    static mainReasonWorkMarch generateMainReasonWorkMarch()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 10);
        auto answer = static_cast<mainReasonWorkMarch>(distribution(generator));
        return answer;
    }

    static registrationInfoInHousehold generateRegistrationInfoInHousehold()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 2);
        auto answer = static_cast<registrationInfoInHousehold>(distribution(generator));
        return answer;
    }

    static residenceRegistrationInfo generateResidenceRegistrationInfo()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 3);
        auto answer = static_cast<residenceRegistrationInfo>(distribution(generator));
        return answer;
    }

    static std::set<studyingPrograms> generateSetCurrentEducationPrograms()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distributionNumElements(1, 2);
        size_t numTotalOfAllElements = distributionNumElements(generator);
        std::set<studyingPrograms> set;
        std::uniform_int_distribution<unsigned int> distributionNumEnums(0, 3);
        for (int i = 0; i < numTotalOfAllElements; i++)
            set.insert(static_cast<studyingPrograms>(distributionNumEnums(generator)));
        return set;
    }

    static std::set<typesOfLivelihoods> generateSetTypesOfLivelihoods()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distributionNumElements(1, 2);
        size_t numTotalOfAllElements = distributionNumElements(generator);
        std::set<typesOfLivelihoods> set;
        std::uniform_int_distribution<unsigned int> distributionNumEnums(0, 13);
        for (int i = 0; i < numTotalOfAllElements; i++)
            set.insert(static_cast<typesOfLivelihoods>(distributionNumEnums(generator)));
        return set;
    }

    static std::set<std::string> generateSetLanguages()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distributionNumElements(0, 4);
        size_t numTotalOfAllElements = distributionNumElements(generator);
        std::set<std::string> set;
        std::uniform_int_distribution<unsigned int> distributionLenString(5, 10);
        for (int i = 0; i < numTotalOfAllElements; i++)
            set.insert(randomString(distributionLenString(generator)));
        return set;
    }
public:
    friend class StrategyEnumerationAreaNumber;
    friend class StrategyFullName;
    friend class StrategyPlaceOfBirth;
    friend class StrategyCitizenship;
    friend class StrategyFormNumber;

    ~PopulationCensus() = default;

    static std::shared_ptr<PopulationCensus> randomGenerateObjectPopulationCensus()
    {
        PopulationCensus *object = new PopulationCensus;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 65535);
        std::uniform_int_distribution<> distribLengthForStrings(4, 13);
        std::uniform_int_distribution<unsigned int> distribution(0, 1);
        object->enumerationAreaNumber = distrib(gen);
        object->householdNumberWithinTheEnumerationArea = distrib(gen);
        object->formNumber = distrib(gen);
        object->fullName = randomString(distribLengthForStrings(gen));
        object->selectedGender = generateGender();
        object->birthDay = GetTimeAndDate();
        distrib = std::uniform_int_distribution<>(1, 89);
        object->numberOfYears = distrib(gen);
        object->marriageInfo = generateMarriageAnswer();
        object->thatPersonSpouseLivesHousehold = generateYesNo();
        distrib = std::uniform_int_distribution<>(1, 6);
        object->amountOfChildren = distrib(gen);
        object->birthDayFirstChild = GetTimeAndDate();
        object->placeOfBirth = randomString(distribLengthForStrings(gen));
        distrib = std::uniform_int_distribution<>(1993, 2020);
        object->yearOfContinuousResidence = distrib(gen);
        object->previousPlaceOfResidence = randomString(distribLengthForStrings(gen));
        object->livedInOtherCountries = object->thatPersonSpouseLivesHousehold = generateYesNo();
        object->placeOfResidenceToArrivalInRussia = randomString(distribLengthForStrings(gen));
        object->yearsOfComebackToRussia = distrib(gen);
        object->proficiencyInRussian = generateYesNo();
        object->useOfRussianLanguageInEverydayLife = generateYesNo();
        object->languages = generateSetLanguages();
        object->nativeLanguage = randomString(distribLengthForStrings(gen));
        object->citizenship = randomString(distribLengthForStrings(gen));
        object->nationality = randomString(distribLengthForStrings(gen));
        object->abilityReadAndWrite = generateYesNo();
        object->academicDegree = generateTypeOfDegree();
        object->currentEducation = generateYesNo();
        object->currentEducationPrograms = generateSetCurrentEducationPrograms();
        object->livelihoods = generateSetTypesOfLivelihoods();
        object->mainLivelihood = generateTypesOfLivelihoods();
        object->workForCertainPeriod = generateYesNo();
        object->positionMainJob = generatePositionAtWork();
        object->mainWorkWasInTheSameSettlement = generateYesNo();
        object->informationAboutWork.anotherState = randomString(distribLengthForStrings(gen));
        object->informationAboutWork.district = randomString(distribLengthForStrings(gen));
        object->informationAboutWork.subject = randomString(distribLengthForStrings(gen));
        object->informationAboutWork.urbanSettlement = randomString(distribLengthForStrings(gen));
        object->schedule = generateWorkScheduleOptions();
        object->suitableJobInMarch = generateJobOptionsMarch();
        object->jobSearchInMarch = generateYesNo();
        object->jobSearchDuringMarch = generateMainReasonWorkMarch();
        object->registrationInThisHousehold = generateRegistrationInfoInHousehold();
        object->residenceRegistration = generateResidenceRegistrationInfo();
        return std::shared_ptr<PopulationCensus>(object);
    }
    bool operator==(const PopulationCensus& rhs)
    {
        if (enumerationAreaNumber == rhs.enumerationAreaNumber and householdNumberWithinTheEnumerationArea
                                                                   == rhs.householdNumberWithinTheEnumerationArea and formNumber == rhs.formNumber and selectedGender == rhs.selectedGender
                                                                                                                                                       and birthDay == rhs.birthDay and numberOfYears == rhs.numberOfYears and marriageInfo == rhs.marriageInfo and
            thatPersonSpouseLivesHousehold == rhs.thatPersonSpouseLivesHousehold and amountOfChildren == rhs.amountOfChildren
                                                                                                                                                       and birthDayFirstChild == rhs.birthDayFirstChild and placeOfBirth == rhs.placeOfBirth and yearOfContinuousResidence
                                                                                                      == rhs.yearOfContinuousResidence and previousPlaceOfResidence == rhs.previousPlaceOfResidence and livedInOtherCountries
                                                                                                                                                                                                        == rhs.livedInOtherCountries and thatPersonSpouseLivesHousehold == rhs.thatPersonSpouseLivesHousehold and
            placeOfResidenceToArrivalInRussia == rhs.placeOfResidenceToArrivalInRussia and yearsOfComebackToRussia ==
                                                                                           rhs.yearOfContinuousResidence and proficiencyInRussian == rhs.proficiencyInRussian and useOfRussianLanguageInEverydayLife ==
                                                                                                                                                                                  rhs.useOfRussianLanguageInEverydayLife and languages == rhs.languages and nativeLanguage == rhs.nativeLanguage and
            citizenship == rhs.citizenship and nationality == rhs.nationality and abilityReadAndWrite == rhs.abilityReadAndWrite
                                                                                                                                                       and academicDegree == rhs.academicDegree and currentEducation == rhs.currentEducation and currentEducationPrograms ==
                                                                                                      rhs.currentEducationPrograms and livelihoods == rhs.livelihoods and mainLivelihood == rhs.mainLivelihood and
            workForCertainPeriod == rhs.workForCertainPeriod and positionMainJob ==
                                                                 rhs.positionMainJob and mainWorkWasInTheSameSettlement == rhs.mainWorkWasInTheSameSettlement and informationAboutWork.urbanSettlement ==
                                                                                                                                                                  rhs.informationAboutWork.urbanSettlement and informationAboutWork.subject == rhs.informationAboutWork.subject and
            informationAboutWork.district == rhs.informationAboutWork.district and informationAboutWork.anotherState == rhs.informationAboutWork.urbanSettlement
            and schedule == rhs.schedule and suitableJobInMarch == rhs.suitableJobInMarch and jobSearchInMarch == rhs.jobSearchInMarch and
            jobSearchDuringMarch == rhs.jobSearchDuringMarch and registrationInThisHousehold == rhs.registrationInThisHousehold and
            residenceRegistration == rhs.residenceRegistration)
            return true;
        else
            return false;
    }
    friend std::istream& operator>>(std::istream &in, PopulationCensus& census)
    {
        uint16_t    tmpNum;
        std::string tmpString;
        int year, month, day;

        std::cout << "Номер переписного участка: ";
        in >> tmpNum;
        tmpNum = census.enumerationAreaNumber;
        std::cout << "Номер помещения в пределах счетного участка: ";
        in >> census.householdNumberWithinTheEnumerationArea;
        std::cout << "Номер бланка: ";
        in >> census.formNumber;
        std::cout << "Ваше имя: ";
        in >> census.fullName;
        std::cout << "Ваш пол (1 - мужской, 2 - женский): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.selectedGender = gender::male;
        else if (tmpNum == 2)
            census.selectedGender = gender::female;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "число полных лет: ";
        in >> census.numberOfYears;
        std::cout << "ваше состояние в браке:\n"
                     "1. состою в зарегистрированном браке\n"
                     "2.состою в незарегистрированном супружеском союзе\n"
                     "3. разведен(а) официально\n"
                     "4. разошелся(лась)\n"
                     "5. вдвовец(вдова)\n"
                     "6. никогда не состоял(а) в браке, супружеском союзе\n>";

        in >> tmpNum;
        if (tmpNum == 1)
            census.marriageInfo = marriageAnswer::registeredMarriage;
        switch (tmpNum) {
            case 1:
                census.marriageInfo = marriageAnswer::registeredMarriage;
                break;
            case 2:
                census.marriageInfo = marriageAnswer::unregisteredMaritalUnion;
                break;
            case 3:
                census.marriageInfo = marriageAnswer::officiallyDivorced;
                break;
            case 4:
                census.marriageInfo = marriageAnswer::breakUp;
                break;
            case 5:
                census.marriageInfo = marriageAnswer::widow;
                break;
            case 6:
                census.marriageInfo = marriageAnswer::neverMarried;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "супруг(а) этого лица проживает в домохозяйстве (1 - да, 2 - нет)\n>";

        in >> tmpNum;
        if (tmpNum == 1)
            census.thatPersonSpouseLivesHousehold = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.thatPersonSpouseLivesHousehold = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "сколько детей вы родили: ";
        in >> census.amountOfChildren;
        std::cout << "место вашего рождения: ";
        in >> census.placeOfBirth;
        std::cout << "с какого года вы непрерывно проживаете в этом населенном пункте: ";
        in >> census.yearOfContinuousResidence;
        std::cout << "ваше пржднее место жительства: ";
        in >> census.previousPlaceOfResidence;
        std::cout << "проживали ли выболее 12 месяцев в других странах(1 - да, 2 - нет): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.livedInOtherCountries = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.livedInOtherCountries = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "где вы проживали до прибытия в Россию: ";
        in >> census.placeOfResidenceToArrivalInRussia;
        std::cout << "год прибытия (возвращения) в Россию: ";
        in >> census.yearsOfComebackToRussia;
        std::cout << "владаете ли вы русским языком(1 - да, 2 - нет): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.proficiencyInRussian = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.proficiencyInRussian = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "используете ли вы его в повседневной жизни(1 - да, 2 - нет): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.useOfRussianLanguageInEverydayLife = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.useOfRussianLanguageInEverydayLife = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "какими иными языками вы владеете(количество языков, языки)";
        in >> tmpNum;
        for (int i = 0; i < tmpNum; i++) {
            in >> tmpString;
            census.languages.insert(tmpString);
        }
        std::cout << "ваш родной язык: ";
        in >> census.nativeLanguage;
        std::cout << "ваше гражданство: ";
        in >> census.citizenship;
        std::cout << "ваша национальная принадлежность: ";
        in >> census.nationality;
        std::cout << "умеете ли вы читать и писать(1 - да, 2 - нет): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.useOfRussianLanguageInEverydayLife = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.useOfRussianLanguageInEverydayLife = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "имеете ли вы ученую степень (для лиц с высшим образованием и кадров высшей квалификации):\n"
                     "1. кандидат наук\n"
                     "2. доктор наук\n"
                     "3. не имею\n>";
        in >> tmpNum;
        if (tmpNum == 1)
            census.academicDegree = typeOfDegree::PhD;
        else if (tmpNum == 2)
            census.academicDegree = typeOfDegree::DoctorOfScience;
        else if (tmpNum == 3)
            census.academicDegree = typeOfDegree::dontHave;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "получаете ли вы образование в настоящее время(1 - да, 2 - нет): ";
        in >> tmpNum;
        if (tmpNum == 1)
            census.currentEducation = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.currentEducation = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "отметье все программы по которым обучаетесь\n"
                     "1. программы дошкольного образования\n"
                     "2. основные профессиональные программы\n"
                     "3. дополнительные образовательные программы\n"
                     "4. отмечены все программы\n>";
        in >> tmpNum;
        while (tmpNum != 4)
        {
            switch (tmpNum) {
                case 1:
                    census.currentEducationPrograms.insert(studyingPrograms::preschoolEducationPrograms);
                    break;
                case 2:
                    census.currentEducationPrograms.insert(studyingPrograms::generalEducationPrograms);
                    break;
                case 3:
                    census.currentEducationPrograms.insert(studyingPrograms::basicProfessionalPrograms);
                    break;
                case 4:
                    census.currentEducationPrograms.insert(studyingPrograms::additionalEducationalPrograms);
                    break;
                default:
                    throw std::invalid_argument("Incorrect input!");
            }
            in >> tmpNum;
            std::cout << ">";
        }
        std::cout << "укажите все имеющиеся у вас источники средств к существованию:\n"
                     "1. заработная плата\n"
                     "2. предпринимательский доход, самозанятость\n"
                     "3. производство товаров для собственного использования\n"
                     "4. сдача в аренду имущества\n"
                     "5. доход от патентов, авторских прав\n"
                     "6. сбережения, дивиденды, проценты, ссуды, реализация капитала\n"
                     "7. пенсия(кроме пенсии по инвалидности)\n"
                     "8. пенсия по инвалидности\n"
                     "9. стипендия\n"
                     "10. пособие по безработице\n"
                     "11. другие пособия и выплаты от организаций, государства\n"
                     "12. льготы, компенсации, субсидии, выигрыши\n"
                     "13. обеспечение со стороны других лиц, иждивение\n"
                     "14. иной источник\n"
                     "15. указаны все источники\n>";
        in >> tmpNum;
        while (tmpNum != 15)
        {
            switch (tmpNum) {
                case 1:
                    census.livelihoods.insert(typesOfLivelihoods::wage);
                    break;
                case 2:
                    census.livelihoods.insert(typesOfLivelihoods::entrepreneurialIncome);
                    break;
                case 3:
                    census.livelihoods.insert(typesOfLivelihoods::productionOfGoodsForOwnUse);
                    break;
                case 4:
                    census.livelihoods.insert(typesOfLivelihoods::rentalOfProperty);
                    break;
                case 5:
                    census.livelihoods.insert(typesOfLivelihoods::incomeFromPatents);
                    break;
                case 6:
                    census.livelihoods.insert(typesOfLivelihoods::capital);
                    break;
                case 7:
                    census.livelihoods.insert(typesOfLivelihoods::pension);
                    break;
                case 8:
                    census.livelihoods.insert(typesOfLivelihoods::disabilityPension);
                    break;
                case 9:
                    census.livelihoods.insert(typesOfLivelihoods::scholarship);
                    break;
                case 10:
                    census.livelihoods.insert(typesOfLivelihoods::unemploymentBenefits);
                    break;
                case 11:
                    census.livelihoods.insert(typesOfLivelihoods::otherBenefits);
                    break;
                case 12:
                    census.livelihoods.insert(typesOfLivelihoods::compensation);
                    break;
                case 13:
                    census.livelihoods.insert(typesOfLivelihoods::dependency);
                    break;
                case 14:
                    census.livelihoods.insert(typesOfLivelihoods::anotherSource);
                    break;
                case 15:
                    break;
                default:
                    throw std::invalid_argument("Incorrect input!");
            }
        }
        std::cout << "какой из отмеченных источников вы считаете для себя основным\n"
                     "1. заработная плата\n"
                     "2. предпринимательский доход, самозанятость\n"
                     "3. производство товаров для собственного использования\n"
                     "4. сдача в аренду имущества\n"
                     "5. доход от патентов, авторских прав\n"
                     "6. сбережения, дивиденды, проценты, ссуды, реализация капитала\n"
                     "7. пенсия(кроме пенсии по инвалидности)\n"
                     "8. пенсия по инвалидности\n"
                     "9. стипендия\n"
                     "10. пособие по безработице\n"
                     "11. другие пособия и выплаты от организаций, государства\n"
                     "12. льготы, компенсации, субсидии, выигрыши\n"
                     "13. обеспечение со стороны других лиц, иждивение\n";
        in >> tmpNum;
        switch (tmpNum) {
            case 1:
                census.livelihoods.insert(typesOfLivelihoods::wage);
                break;
            case 2:
                census.livelihoods.insert(typesOfLivelihoods::entrepreneurialIncome);
                break;
            case 3:
                census.livelihoods.insert(typesOfLivelihoods::productionOfGoodsForOwnUse);
                break;
            case 4:
                census.livelihoods.insert(typesOfLivelihoods::rentalOfProperty);
                break;
            case 5:
                census.livelihoods.insert(typesOfLivelihoods::incomeFromPatents);
                break;
            case 6:
                census.livelihoods.insert(typesOfLivelihoods::capital);
                break;
            case 7:
                census.livelihoods.insert(typesOfLivelihoods::pension);
                break;
            case 8:
                census.livelihoods.insert(typesOfLivelihoods::disabilityPension);
                break;
            case 9:
                census.livelihoods.insert(typesOfLivelihoods::scholarship);
                break;
            case 10:
                census.livelihoods.insert(typesOfLivelihoods::unemploymentBenefits);
                break;
            case 11:
                census.livelihoods.insert(typesOfLivelihoods::otherBenefits);
                break;
            case 12:
                census.livelihoods.insert(typesOfLivelihoods::compensation);
                break;
            case 13:
                census.livelihoods.insert(typesOfLivelihoods::dependency);
                break;
            case 14:
                census.livelihoods.insert(typesOfLivelihoods::anotherSource);
                break;
            case 15:
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "кем вы являлись на основной работе\n"
                     "1. работающий по найму\n"
                     "2. владелец(совладелец) собственного предприятия(дела)\n"
                     "3. индивидуальный предприниматель\n"
                     "4. самозанятый\n"
                     "5. помогающий на семейном предприятии\n"
                     "6. иное\n>";
        in >> tmpNum;
        switch (tmpNum){
            case 1:
                census.positionMainJob = positionAtWork::employed;
                break;
            case 2:
                census.positionMainJob = positionAtWork::businessOwner;
                break;
            case 3:
                census.positionMainJob = positionAtWork::individualEntrepreneur;
                break;
            case 4:
                census.positionMainJob = positionAtWork::selfEmployed;
                break;
            case 5:
                census.positionMainJob = positionAtWork::familyBusiness;
                break;
            case 6:
                census.positionMainJob = positionAtWork::otherwise;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "ваша основная работа находилась в том же населенном пункте, где вы проживаете постоянно\n"
                     "1. Да\n"
                     "2. Нет\n>";
        in >> tmpNum;
        if (tmpNum == 1)
            census.currentEducation = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.currentEducation = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "где находилась ваша основная работа\n"
                     "1. субъект РФ\n"
                     "2. городской населенный пункт\n"
                     "3. муниципальный район/округ, городской округ\n"
                     "4. иное государство\n>";
        in >> census.informationAboutWork.subject >> census.informationAboutWork.urbanSettlement
           >> census.informationAboutWork.district >> census.informationAboutWork.anotherState;
        std::cout << "вы выезжали(выходили) на работу\n"
                     "1. ежедневно\n"
                     "2. несколько раз в неделю\n"
                     "3. несколько раз в месяц\n"
                     "4. один раз в месяц и реже\n"
                     "5. работаю дистанционно\n>";
        in >> tmpNum;
        switch (tmpNum){
            case 1:
                census.schedule = workScheduleOptions::daily;
                break;
            case 2:
                census.schedule = workScheduleOptions::fewTimesAWeek;
                break;
            case 3:
                census.schedule = workScheduleOptions::fewTimesAMonth;
                break;
            case 4:
                census.schedule = workScheduleOptions::onceAMonthOrLess;
                break;
            case 5:
                census.schedule = workScheduleOptions::remotely;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "если бы вам предложили подходящую работу в последнюю неделю марта,\n"
                     "то когда вы смогли бы приступить к ней:\n"
                     "1. с 25 по 31 марта\n"
                     "2. с 1 по 14 апреля\n"
                     "3. не смог бы приступить в эти периоды\n>";
        in >> tmpNum;
        switch (tmpNum){
            case 1:
                census.suitableJobInMarch = jobOptionsMarch::from25To31March;
                break;
            case 2:
                census.suitableJobInMarch = jobOptionsMarch::from1To14April;
                break;
            case 3:
                census.suitableJobInMarch = jobOptionsMarch::couldNotStartDuringThesePeriods;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "вы искали работу в течении марта:\n"
                     "1. Да\n"
                     "2. Нет\n>";
        in >> tmpNum;
        if (tmpNum == 1)
            census.jobSearchInMarch = yesNoAnswer::yes;
        else if (tmpNum == 2)
            census.jobSearchInMarch = yesNoAnswer::no;
        else
            throw std::invalid_argument("Incorrect input!");
        std::cout << "зарегистрированы ли вы в этом помещении\n"
                     "1. по месту жительства(постоянно)\n"
                     "2. по месту пребывания(временно)\n"
                     "3. нет\n";
        in >> tmpNum;
        switch (tmpNum) {
            case 1:
                census.registrationInThisHousehold = registrationInfoInHousehold::atThePlaceOfResidence;
                break;
            case 2:
                census.registrationInThisHousehold = registrationInfoInHousehold::atThePlaceOfStay;
                break;
            case 3:
                census.registrationInThisHousehold = registrationInfoInHousehold::notRegistered;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }
        std::cout << "где вы зарегистрировваны по месту жительства:\n"
                     "1. том же населенном пункте, где проживаю постоянно\n"
                     "2. в другом населенном пункте того же субъекта РФ, где проживаю постоянно\n"
                     "3. в другом субъекте РФ\n"
                     "4. нет регистрации по месту жительства в России\n>";
        in >> tmpNum;
        switch (tmpNum) {
            case 1:
                census.residenceRegistration = residenceRegistrationInfo::inTheSameSettlementWhereLivePermanently;
                break;
            case 2:
                census.residenceRegistration = residenceRegistrationInfo::inAnotherLocalityOfTheSameSubjectWhereLivePermanently;
                break;
            case 3:
                census.residenceRegistration = residenceRegistrationInfo::inAnotherSubject;
                break;
            case 4:
                census.residenceRegistration = residenceRegistrationInfo::noRegistrationInTheRF;
                break;
            default:
                throw std::invalid_argument("Incorrect input!");
        }

        return in;
    }

    void setEnumerationAreaNumber(uint16_t inputEnumerationArea)
    {
        this->enumerationAreaNumber = inputEnumerationArea;
    }

    void setFullName(const std::string& name)
    {
        this->fullName = name;
    }

    void setPlaceOfBirth(const std::string& input)
    {
        this->placeOfBirth = input;
    }

    void setCitizenship(std::string inputCitizenship)
    {
        this->citizenship = std::move(inputCitizenship);
    }

    void setFormNumber(uint16_t input)
    {
        this->formNumber = input;
    }

    uint16_t getEnumerationAreaNumber() const
    {
        return this->enumerationAreaNumber;
    }

    uint16_t getHouseholdNumberWithinTheEnumerationArea() const
    {
        return this->householdNumberWithinTheEnumerationArea;
    }

    uint16_t getFormNumber() const
    {
        return this->formNumber;
    }

    gender getSelectedGender()
    {
        return this->selectedGender;
    }

    struct tm* getBirthDay()
    {
        return this->birthDay;
    }

    uint8_t getNumberOfYears() const
    {
        return this->numberOfYears;
    }

    marriageAnswer getMarriageInfo()
    {
        return this->marriageInfo;
    }

    yesNoAnswer getThatPersonSpouseLivesHousehold()
    {
        return this->thatPersonSpouseLivesHousehold;
    }

    uint8_t getAmountOfChildren() const
    {
        return this->amountOfChildren;
    }

    struct tm* getBirthDayFirstChild()
    {
        return this->birthDayFirstChild;
    }

    std::string getFullName()
    {
        return this->fullName;
    }

    std::string getPlaceOfBirth()
    {
        return this->placeOfBirth;
    }

    uint8_t getYearOfContinuousResidence() const
    {
        return this->yearOfContinuousResidence;
    }

    std::string getPreviousPlaceOfResidence()
    {
        return this->previousPlaceOfResidence;
    }

    yesNoAnswer getLivedInOtherCountries()
    {
        return this->livedInOtherCountries;
    }

    std::string getPlaceOfResidenceToArrivalInRussia()
    {
        return this->placeOfResidenceToArrivalInRussia;
    }

    uint8_t getYearsOfComebackToRussia() const
    {
        return this->yearsOfComebackToRussia;
    }

    yesNoAnswer getProficiencyInRussian()
    {
        return this->proficiencyInRussian;
    }

    yesNoAnswer getUseOfRussianLanguageInEverydayLife()
    {
        return this->useOfRussianLanguageInEverydayLife;
    }

    std::set<std::string> getLanguages()
    {
        return this->languages;
    }

    std::string getNativeLanguage()
    {
        return this->nativeLanguage;
    }

    std::string getCitizenship()
    {
        return this->citizenship;
    }

    std::string getNationality()
    {
        return this->nationality;
    }

    yesNoAnswer getAbilityReadAndWrite()
    {
        return this->abilityReadAndWrite;
    }

    typeOfDegree getAcademicDegree()
    {
        return this->academicDegree;
    }

    yesNoAnswer getCurrentEducation()
    {
        return this->currentEducation;
    }

    std::set<studyingPrograms> getCurrentEducationPrograms()
    {
        return this->currentEducationPrograms;
    }

    std::set<typesOfLivelihoods> getLivelihoods()
    {
        return this->livelihoods;
    }

    typesOfLivelihoods getMainLivelihood()
    {
        return this->mainLivelihood;
    }

    yesNoAnswer getWorkForCertainPeriod()
    {
        return this->workForCertainPeriod;
    }

    positionAtWork getPositionMainJob()
    {
        return this->positionMainJob;
    }

    yesNoAnswer getMainWorkWasInTheSameSettlement()
    {
        return this->mainWorkWasInTheSameSettlement;
    }

    typeInformationAboutWork getInformationAboutWork()
    {
        return this->informationAboutWork;
    }

    workScheduleOptions getSchedule()
    {
        return this->schedule;
    }

    jobOptionsMarch getSuitableJobInMarch()
    {
        return this->suitableJobInMarch;
    }

    yesNoAnswer getJobSearchInMarch()
    {
        return this->jobSearchInMarch;
    }

    mainReasonWorkMarch getJobSearchDuringMarch()
    {
        return this->jobSearchDuringMarch;
    }

    registrationInfoInHousehold getRegistrationInThisHousehold()
    {
        return this->registrationInThisHousehold;
    }

    residenceRegistrationInfo getResidenceRegistration()
    {
        return this->residenceRegistration;
    }

};

#endif //FUNDI_COURSEWORK_4_SEMESTER__POPULATIONCENSUS_H
