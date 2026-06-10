#ifndef PARTNERSHIP_H
#define PARTNERSHIP_H

#include "Business.h"

class Partnership : public Business
{
private:
    int numPartners;

public:
    Partnership(
        std::string regNo,
        std::string name,
        std::string owner,
        std::string date,
        int partners
    );

    double calculateFee() const override;

    std::string getType() const override;

    void display() const override;
};

#endif
