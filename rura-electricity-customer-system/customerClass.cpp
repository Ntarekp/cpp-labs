/** \brief

class Customer
{
private:
    string customerID;
    string fullName;
    string district;
    string category;
    double monthlyConsumption;
    bool billComputed;

public:
    Customer();
    Customer(
        string id,
        string name,
        string district,
        string category,
        double consumption
    )

    //Getters
    string getCustomerID() const;
    string getFullName() const;
    string getDistrict() const;
    string getCategory() const;
    string getConsumption() const;


    //setters
    void setFullName(string name);
    void setCategory(string category);
    void setConsumption(double consumption);
    void setBilledComputed(bool status);
};
*/
