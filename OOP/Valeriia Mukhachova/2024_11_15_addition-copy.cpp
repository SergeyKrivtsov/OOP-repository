#include <iostream>
#include <string>

using namespace std;

class Number
{
    public:
        string num;
    public:
        Number operator+(Number input)
        {
            Number sum;
            sum.num.resize(max(this->num.size(), input.num.size())+1, ' ');
            int length1 = this->num.size();
            int length2 = input.num.size();
            int length_res = max(this->num.size(), input.num.size())+1;
            int sum_bits = 0, rest = 0;
            int i = length1 - 1;
            int j = length2 - 1;
            int k = length_res - 1;

            while(i>=0||j>=0)
            {
                int digit1 = 0;
                int digit2 = 0;
                if(i>=0)
                {
                    digit1 = this->num[i]-'0';
                    i--;
                }
                else
                    digit1 = 0;

                if(j>=0)
                {
                    digit2 = input.num[j]-'0';
                    j--;
                }
                else
                    digit2 = 0;


                sum_bits = digit1 + digit2 + rest;
                sum.num[k] = (sum_bits%10) + '0';
                k--;
                rest = sum_bits/10;
            }

            if (rest != 0)
                sum.num[0] = rest + '0';
            else
            {
                sum.num[0] = '0';
                int buf = 0;
                int check = 0;
                for(int i = 0; i<length_res; i++)
                {
                    if(sum.num[i]!='0'&&sum.num[i]!=' ')
                        check = 1;
                    else
                    {
                        if(check==0)
                            buf = buf+1;
                    }
                }
                if(buf<length_res)
                    sum.num.erase(0, buf);
                else
                    sum.num[0] = '0';
            }

            return sum;
        }

};

string find_sum(string number1, string number2, string sum);

int main()
{
    Number string1, string2, sum;
    
    cout << "Please enter the first number" << endl;
    cin >> string1.num;
    cout << "Please enter the second number" << endl;
    cin >> string2.num;

    sum = string1+string2;
    cout << sum.num<<endl;

    return 0;
}

