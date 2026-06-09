#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
private:
    std::string customerID;
    std::string fullName;
    std::string district;
    std::string category;
    double monthlyConsumption;
    bool billComputed;

public:
    Customer();

    Customer(
        std::string id,
        std::string name,
        std::string district,
        std::string category,
        double consumption
    );

    // Getters
    std::string getCustomerID() const;
    std::string getFullName() const;
    std::string getDistrict() const;
    std::string getCategory() const;
    double getConsumption() const;
    bool isBillComputed() const;

    // Setters
    void setFullName(std::string name);
    void setCategory(std::string category);
    void setConsumption(double consumption);
    void setBillComputed(bool status);
};

#endif
