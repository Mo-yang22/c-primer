#include <iostream>
#include <string>
using namespace std;
class Quote{
public:
    Quote() =default;
    Quote(const string &book ,double sales_price):
        bookNo(book),price(sales_price){}
    string isbn() const { return bookNo; }
    virtual double net_price( size_t n) const
        {return n * price;}
    virtual ~Quote() = default;
private:
    string bookNo;
protected:
    double price = 0.0;
};
class Bulk_quote : public Quote
{
public:
    Bulk_quote()=default;
    Bulk_quote(const string&,double, size_t, double);
    double net_price(size_t) const override;
private:
    size_t min_qty = 0;
    double discount = 0.0;
};
Bulk_quote::Bulk_quote(const string& s, double price, size_t qty, double disc):
Quote(s,price),min_qty(qty),discount(disc){}
double Bulk_quote::net_price(size_t num) const
{
    if(num>=min_qty)
        return num*(1-discount) * price;
    else
        return num*price;
}
class Good_quote: public Quote
{
public:
    Good_quote()=default;
    Good_quote(const string &, double, size_t, double);
    double net_price(size_t) const override;
private:
    size_t max_qty = 0;
    double discount = 0.0;
};
Good_quote::Good_quote(const string & s, double price, size_t qty, double disc)
:Quote(s,price),max_qty(qty),discount(disc){}
double Good_quote::net_price(size_t cnt) const 
{
    if(cnt<=max_qty)
        return cnt * (1-discount) * price;
    else
        return (max_qty *(1-discount) *price) + ((cnt-max_qty) * price);
}
double print_total(ostream &os,const Quote &item, size_t n)
{
    double ret=item.net_price(n);
    os << "ISBN:" <<item.isbn()<<" # sold: "<< n <<" total due "<< ret <<endl;
    return ret;
}
int main()
{
    Quote q("123",5);
    Bulk_quote bq("1234",5,10,0.2);
    Good_quote gq("12345",5,10,0.2);
    print_total(cout,q,11);
    print_total(cout,bq,11);
    print_total(cout,gq,11);
    return 0;
}