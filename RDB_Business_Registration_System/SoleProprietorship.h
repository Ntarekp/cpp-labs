#ifndef SOLEPROPRIETORSHIP_H
#define SOLEPROPRIETORSHIP_H
#include "Business.h"

class SoleProprietorship : public Business
{

private :
    double annualTurnover;

public:
    SoleProprietorship(
        std::string regNo,
        std::string name,
        std::string owner,
        std::string date,
        double turnover
    );

    double calculateFee() const override;
    std::string getType() const override;
    void display() const override;
};
#endif // SOLEPROPRIETORSHIP_H
