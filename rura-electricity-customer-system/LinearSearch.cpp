
/** \brief
 *
 bool idExists(
    Customer customers[],
    int count,
    string id)
{
    for(int i = 0; i < count; i++)
    {
        if(customers[i].getCustomerID() == id)
            return true;
    }

    return false;
}

 *
 */
