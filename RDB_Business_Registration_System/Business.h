#ifndef BUSINESS_H
#define BUSINESS_H

#include <string>

class Business
{
protected:
    std::string regNumber;
    std::string businessName;
    std::string ownerName;
    std::string regDate;

public:
    Business(
        std::string regNo,
        std::string name,
        std::string owner,
        std::string date
    );

    virtual ~Business();

    std::string getRegNumber() const;
    std::string getBusinessName() const;
    std::string getOwnerName() const;
    std::string getRegDate() const;

    void setBusinessName(
        std::string name
    );

    virtual double calculateFee() const = 0;

    virtual std::string getType() const = 0;

    virtual void display() const;
};

#endif
