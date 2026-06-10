#ifndef CORPORATION_H
#define CORPORATION_H

#include "Business.h"

class Corporation : public Business
{
private:
    int boardSize;
    double shareCapital;

public:
    Corporation(
        std::string regNo,
        std::string name,
        std::string owner,
        std::string date,
        int board,
        double capital
    );

    double calculateFee() const override;

    std::string getType() const override;

    void display() const override;
};

#endif
