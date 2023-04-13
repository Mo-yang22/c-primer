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
        {cout<<1<<endl;return n * price;}
    virtual ~Quote() = default;
    void virtual debug()const{
        cout<<"bookNo: "<<bookNo<<endl;
        cout<<"price: "<<price<<endl;
    } 
private:
    string bookNo;
protected:
    double price = 0.0;
};
class Disc_quote : public Quote
{
public:
    Disc_quote()=default;
    Disc_quote(const string&,double, size_t, double);
    double net_price(size_t) const =0;
protected:
    size_t quantity = 0;
    double discount = 0.0;
};
Disc_quote::Disc_quote(const string &s,double price,size_t qty, double disc)
:Quote(s,price),quantity(qty),discount(disc){};
class Bulk_quote :public Disc_quote
{
public:
    Bulk_quote()=default;
    Bulk_quote(const string&,double, size_t, double);
    double net_price(size_t) const override;
};
Bulk_quote::Bulk_quote(const string &s , double price, size_t qty, double disc)
:Disc_quote(s,price,qty,disc){};
double Bulk_quote::net_price(size_t num) const
{
    cout<<2<<endl;
    if(num>=quantity)
        return num*(1-discount) * price;
    else
        return num*price;
}
class Good_quote: public Disc_quote
{
public:
    Good_quote()=default;
    Good_quote(const string &,double, size_t, double);
    double net_price(size_t) const override;
};
Good_quote::Good_quote(const string &s , double price, size_t qty, double disc)
:Disc_quote(s,price,qty,disc){};
double Good_quote::net_price(size_t cnt) const
{
    if(cnt<=quantity)
        return cnt * (1-discount) * price;
    else
        return (quantity *(1-discount) *price) + ((cnt-quantity) * price);
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