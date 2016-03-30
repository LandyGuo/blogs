#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include <initializer_list>
using namespace std;

template<typename T>
class myVector
{
  //friend function
  //ostream & operator<<(ostream & os, myVector<T>const & vec);
private:
 shared_ptr<vector<T>> pdata;
public:
 //Constructor
 myVector()
 {
  pdata = make_shared<vector<T>>();
 };
 myVector(initializer_list<T> il)
 {
  pdata = make_shared<vector<T>>(il);

 };
 //注意：如果类的实例是const的话，只能调用const的方法
 const int size() const
 {
  return pdata->size();
 }
 //add and remove element
 void add(T elem)
 {
  pdata->push_back(elem);
 };
 void remove(int pos)
 {
  pdata->erase(pos);
 }
 //access to  elements
 T & back()
 {
  return pdata->back();
 }
 T & operator[](int i)
 {
  return (*pdata)[i];
 }
};

template<typename T>
ostream & operator<< (ostream & os, myVector<T>  & vec)
{
 for (auto i = 0; i < vec.size();i++)
  os << vec[i] << "\t";
 return os;
};


int main()
{
 myVector<string> vec1 = {"1","2"};
 vec1.add("123");
 vec1.add("456");
 cout << vec1;
 system("pause");
}
