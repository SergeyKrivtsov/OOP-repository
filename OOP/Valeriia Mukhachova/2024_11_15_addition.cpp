#include <iostream>
#include <string>

using namespace std;

string find_sum(string number1, string number2, string sum);

int main()
{
    string number1 = "999";
    string number2 = "9000000";
    
    cout << "Please enter the first number" << endl;
    cin >> number1;
    cout << "Please enter the second number" << endl;
    cin >> number2;

    string result(max(number1.size(), number2.size())+1, ' ');

    result = find_sum(number1, number2, result);
    cout << result<<endl;

    return 0;
}

string find_sum(string number1, string number2, string sum)
{
    int length1 = number1.size();
    int length2 = number2.size();
    int length_res = max(number1.size(), number2.size())+1;
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
            digit1 = number1[i]-'0';
            i--;
        }
        else
            digit1 = 0;

        if(j>=0)
        {
            digit2 = number2[j]-'0';
            j--;
        }
        else
            digit2 = 0;


        sum_bits = digit1 + digit2 + rest;
        sum[k] = (sum_bits%10) + '0';
        k--;
        rest = sum_bits/10;
    }

    if (rest != 0)
        sum[0] = rest + '0';
    else
    {
        sum[0] = '0';
        int buf = 0;
        int check = 0;
        for(int i = 0; i<length_res; i++)
        {
            if(sum[i]!='0'&&sum[i]!=' ')
                check = 1;
            else
            {
                if(check==0)
                    buf = buf+1;
            }
        }
        if(buf<length_res)
            sum.erase(0, buf);
        else
            sum[0] = '0';
    }

    return sum;
}
