#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int compare(const string& num1, const string& num2){
   if(num1.size() > num2.size()) return 1;
   if(num1.size() < num2.size()) return -1;
   return num1.compare(num2);
}

string substract(const string& a, const string& b){
   string result = "";
   int carry = 0;
   int i = a.size() - 1, j = b.size() - 1;
   int digitA,digitB;
   while( i>=0 || j>=0 || carry){
      
        int digitA = (i >= 0) ? a[i] - '0' : 0;
        int digitB = (j >= 0) ? b[j] - '0' : 0;
        
      int diff = digitA - digitB - carry;
      if(diff<0){
         diff +=10;
         carry = 1;
      }else {
         carry = 0;}
         result.insert(result.begin(), diff + '0');
         i--;
         j--;
      
      }
    while (result.size() > 1 && result[0] == '0') { //Удаление нулей
        result.erase(result.begin());
    }

    return result;
}

void dividing (const string& dividend, const string& divisor,string& quotient, string& remainder){
   if( divisor == "0"){
      throw invalid_argument ("Nelzy delit na 0!");
   }
   quotient = "";
   remainder = "";
   
   for(size_t i= 0; i<dividend.size(); ++i){
      remainder +=dividend[i];
   
   int count = 0;
   while( compare(remainder,divisor)>= 0){
      remainder = substract(remainder,divisor);
      ++count;
   }
   quotient +=(count + '0');
}
while(quotient.size() > 1 && quotient[0]== '0'){
        quotient.erase(quotient.begin());}
        }
int main(){ 
   string divisor,dividend;
cout << "Enter dividend: ";
cin >> dividend;
cout << "Enter divisor: ";
cin >> divisor;
if(divisor=="0"){
   cout<<"Error,divisor cant be 0!"<<endl;
   return 1;
}
string quotient,remainder;
dividing(dividend,divisor,quotient,remainder);
cout<<"Chastnoe: "<<quotient<<endl;
cout<<"Remainder: "<<remainder<<endl;

    return 0;
}