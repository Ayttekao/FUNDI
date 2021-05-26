//
// Created by ayttekao on 5/10/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__CUSTOMTYPES_H
#define FUNDI_COURSEWORK_4_SEMESTER__CUSTOMTYPES_H

enum gender
{
    male,
    female
};

enum marriageAnswer
{
    registeredMarriage, /* состою в зарегистрированном браке */
    unregisteredMaritalUnion, /*состою в незарегистрированном супружеском союзе*/
    officiallyDivorced, /* разведен(а) официально */
    breakUp, /* рашелся(лась) */
    widow, /* вдвовец(вдова) */
    neverMarried /* никогда не состоял(а) в браке, супружеском союзе */
};

std::string putMarriageAnswer(marriageAnswer answer)
{
    switch (answer) {
        case marriageAnswer::registeredMarriage:
            return "состою в зарегистрированном браке";
        case marriageAnswer::unregisteredMaritalUnion:
            return "состою в незарегистрированном супружеском союзе";
        case marriageAnswer::officiallyDivorced:
            return "разведен(а) официально";
        case marriageAnswer::breakUp:
            return "рашелся(лась)";
        case marriageAnswer::widow:
            return "вдвовец(вдова)";
        case marriageAnswer::neverMarried:
            return "никогда не состоял(а) в браке, супружеском союзе";
        default:
            return "invalid";
    }
}

enum yesNoAnswer
{
    yes,
    no
};

enum typeOfDegree
{
    PhD, /* кандидат наук */
    DoctorOfScience, /* доктор наук */
    dontHave /* не имею */
};

std::string putTypeOfDegree(typeOfDegree type)
{
    if (type == typeOfDegree::PhD)
        return "кандидат наук";
    else if (type == typeOfDegree::DoctorOfScience)
        return "доктор наук";
    else if (type == typeOfDegree::dontHave)
        return "не имею";
    return "invalid";
}

enum studyingPrograms
{
    preschoolEducationPrograms, /* программы дошкольного образования */
    generalEducationPrograms, /* программы общего образования */
    basicProfessionalPrograms, /* основные профессиональные программы */
    additionalEducationalPrograms /* дополнительные образовательные программы */
};

std::string putStudyingPrograms(studyingPrograms type)
{
    if (type == studyingPrograms::preschoolEducationPrograms)
        return "программы дошкольного образования";
    else if (type == studyingPrograms::generalEducationPrograms)
        return "программы общего образования";
    else if (type == studyingPrograms::basicProfessionalPrograms)
        return "основные профессиональные программы";
    else if (type == studyingPrograms::additionalEducationalPrograms)
        return "дополнительные образовательные программы";
    else
        return "ivalid";
}

enum typesOfLivelihoods
{
    wage, /* заработная плата */
    entrepreneurialIncome, /* предпринимательский доход, самозанятость */
    productionOfGoodsForOwnUse, /* производство товаров для собственного использования */
    rentalOfProperty, /* сдача в аренду имущества */
    incomeFromPatents, /* доход от патентов, авторских прав */
    capital, /* сбережения, дивиденды, проценты, ссуды, реализация капитала */
    pension, /* пенсия(кроме пенсии по инвалидности) */
    disabilityPension, /* пенсия по инвалидности */
    scholarship, /* стипендия */
    unemploymentBenefits, /* пособие по безработице */
    otherBenefits, /* другие пособия и выплаты от организаций, государства */
    compensation, /* льготы, компенсации, субсидии, выигрыши */
    dependency, /* обеспечение со стороны других лиц, иждивение */
    anotherSource /* иной источник */
};

std::string putTypesOfLivelihoods(typesOfLivelihoods type)
{
    switch (type) {
        case typesOfLivelihoods::wage:
            return "заработная плата";
        case typesOfLivelihoods::entrepreneurialIncome:
            return "предпринимательский доход, самозанятость";
        case typesOfLivelihoods::productionOfGoodsForOwnUse:
            return "производство товаров для собственного использования";
        case typesOfLivelihoods::rentalOfProperty:
            return "сдача в аренду имущества";
        case typesOfLivelihoods::incomeFromPatents:
            return "доход от патентов, авторских прав";
        case typesOfLivelihoods::capital:
            return "сбережения, дивиденды, проценты, ссуды, реализация капитала";
        case typesOfLivelihoods::pension:
            return "пенсия(кроме пенсии по инвалидности)";
        case typesOfLivelihoods::disabilityPension:
            return "пенсия по инвалидности";
        case typesOfLivelihoods::scholarship:
            return "стипендия";
        case typesOfLivelihoods::unemploymentBenefits:
            return "пособие по безработице";
        case typesOfLivelihoods::otherBenefits:
            return "другие пособия и выплаты от организаций, государства";
        case typesOfLivelihoods::compensation:
            return "льготы, компенсации, субсидии, выигрыши";
        case typesOfLivelihoods::dependency:
            return "обеспечение со стороны других лиц, иждивение";
        case typesOfLivelihoods::anotherSource:
            return "иной источник";
        default:
            return "invalid";
    }
}

enum positionAtWork
{
    employed, /* работающий по найму */
    businessOwner, /* владелец(совладелец) собственного предприятия(дела) */
    individualEntrepreneur, /* индивидуальный предприниматель */
    selfEmployed, /* самозанятый */
    familyBusiness, /* помогающий на семейном предприятии */
    otherwise /* иное */
};

std::string putPositionAtWork(positionAtWork type)
{
    switch (type) {
        case positionAtWork::employed:
            return "работающий по найму";
        case positionAtWork::businessOwner:
            return "владелец(совладелец) собственного предприятия(дела)";
        case positionAtWork::individualEntrepreneur:
            return "индивидуальный предприниматель";
        case positionAtWork::selfEmployed:
            return "самозанятый";
        case positionAtWork::familyBusiness:
            return "помогающий на семейном предприятии";
        case positionAtWork::otherwise:
            return "иное";
        default:
            return "invalid";
    }
}

enum workScheduleOptions
{
    daily, /* ежедневно */
    fewTimesAWeek, /* несколько раз в неделю */
    fewTimesAMonth, /* несколько раз в месяц */
    onceAMonthOrLess, /* один раз в месяц и реже */
    remotely, /* работаю дистанционно */
};

std::string putWorkScheduleOptions(workScheduleOptions option)
{
    switch (option) {
        case workScheduleOptions::daily:
            return "ежедневно";
        case workScheduleOptions::fewTimesAWeek:
            return "несколько раз в неделю";
        case workScheduleOptions::fewTimesAMonth:
            return "несколько раз в месяц";
        case workScheduleOptions::onceAMonthOrLess:
            return "один раз в месяц и реже";
        case workScheduleOptions::remotely:
            return "работаю дистанционно";
        default:
            return "invalid";
    }
}

enum jobOptionsMarch
{
    from25To31March, /* с 25 по 31 марта */
    from1To14April, /* с 1 по 14 апреля */
    couldNotStartDuringThesePeriods /* не смог бы приступить в эти периоды */
};

std::string putJobOptionsMarch(jobOptionsMarch type)
{
    switch (type) {
        case jobOptionsMarch::from25To31March:
            return "с 25 по 31 марта";
        case jobOptionsMarch::from1To14April:
            return "с 1 по 14 апреля";
        case jobOptionsMarch::couldNotStartDuringThesePeriods:
            return "не смог бы приступить в эти периоды";
        default:
            return "invalid";
    }
}

enum mainReasonWorkMarch
{
    wasOrganizingHisOwnBusiness, /* занимался(лась) организацией собственного дела */
    foundJobAndWasWaitingForAnAnswer, /* нашел(ла) работу и ждал(а) ответа */
    lookingForwardToTheStartOfTheSeason, /* ожидаю начало сезона */
    learning, /* учусь */
    retired, /* нахожусь на пенсии */
    forHealthReasons, /* по состоянию здоровья */
    caringForTheSick, /* ухаживал(а) за больным */
    ranHouseholdOrRaisedChildren, /* вел(а) домашнее хозяйство и/или воспитывал(а) детей */
    canFindWork, /* не могу найти работу */
    noNeedToWork, /* нет необходимости работать */
    otherReason /* иная причина */
};

std::string putMainReasonWorkMarch(mainReasonWorkMarch type)
{
    switch (type) {
        case mainReasonWorkMarch::wasOrganizingHisOwnBusiness:
            return "занимался(лась) организацией собственного дела";
        case mainReasonWorkMarch::foundJobAndWasWaitingForAnAnswer:
            return "нашел(ла) работу и ждал(а) ответа";
        case mainReasonWorkMarch::lookingForwardToTheStartOfTheSeason:
            return "ожидаю начало сезона";
        case mainReasonWorkMarch::learning:
            return "учусь";
        case mainReasonWorkMarch::retired:
            return "нахожусь на пенсии";
        case mainReasonWorkMarch::forHealthReasons:
            return "по состоянию здоровья";
        case mainReasonWorkMarch::caringForTheSick:
            return "ухаживал(а) за больным";
        case mainReasonWorkMarch::ranHouseholdOrRaisedChildren:
            return "вел(а) домашнее хозяйство и/или воспитывал(а) детей";
        case mainReasonWorkMarch::canFindWork:
            return "не могу найти работу";
        case mainReasonWorkMarch::noNeedToWork:
            return "нет необходимости работать";
        case mainReasonWorkMarch::otherReason:
            return "иная причина";
        default:
            return "invalid";
    }
}

enum registrationInfoInHousehold
{
    atThePlaceOfResidence, /* по месту жительства(постоянно) */
    atThePlaceOfStay, /* по месту пребывания(временно) */
    notRegistered /* нет */
};

std::string putRegistrationInfoInHousehold(registrationInfoInHousehold type)
{
    switch (type) {
        case registrationInfoInHousehold::atThePlaceOfResidence:
            return "по месту жительства(постоянно)";
        case registrationInfoInHousehold::atThePlaceOfStay:
            return "по месту пребывания(временно)";
        case registrationInfoInHousehold::notRegistered:
            return "нет";
        default:
            return "invalid";
    }
}

enum residenceRegistrationInfo
{
    inTheSameSettlementWhereLivePermanently, /* том же населенном пункте, где проживаю постоянно */
    inAnotherLocalityOfTheSameSubjectWhereLivePermanently, /* в другом населенном пункте того же субъекта РФ,
                                                                * где проживаю постоянно */
    inAnotherSubject, /* в другом субъекте РФ */
    noRegistrationInTheRF, /* нет регистрации по месту жительства в России */
};

std::string putResidenceRegistrationInfo(residenceRegistrationInfo type)
{
    switch (type) {
        case residenceRegistrationInfo::inTheSameSettlementWhereLivePermanently:
            return "том же населенном пункте, где проживаю постоянно";
        case residenceRegistrationInfo::inAnotherLocalityOfTheSameSubjectWhereLivePermanently:
            return "в другом населенном пункте того же субъекта РФ, где проживаю постоянно";
        case residenceRegistrationInfo::inAnotherSubject:
            return "в другом субъекте РФ";
        case residenceRegistrationInfo::noRegistrationInTheRF:
            return "нет регистрации по месту жительства в России";
        default:
            return "invalid";
    }
}

struct typeInformationAboutWork
{
    std::string subject; /* субъект РФ */
    std::string urbanSettlement; /* городской населенный пункт */
    std::string district; /* муниципальный район/округ, городской округ */
    std::string anotherState; /* иное государство */
    bool operator==(const typeInformationAboutWork& rhs) const
    {
        if (subject == rhs.subject and urbanSettlement == rhs.urbanSettlement and
        district == rhs.district and anotherState == rhs.anotherState)
            return true;
        return false;
    }
    bool operator<(const typeInformationAboutWork& rhs) const
    {
        if (subject < rhs.subject or urbanSettlement < rhs.urbanSettlement or
            district < rhs.district or anotherState < rhs.anotherState)
            return true;
        return false;
    }
    bool operator>(const typeInformationAboutWork& rhs) const
    {
        if (subject > rhs.subject or urbanSettlement > rhs.urbanSettlement or
            district > rhs.district or anotherState > rhs.anotherState)
            return true;
        return false;
    }
};

#endif //FUNDI_COURSEWORK_4_SEMESTER__CUSTOMTYPES_H
