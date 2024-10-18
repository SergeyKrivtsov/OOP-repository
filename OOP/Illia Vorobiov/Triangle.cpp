#include <iostream>
using namespace std;

int main()
{
    int n;
    int m;
    cin >> n;
    m = n;
    int ** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i < n/2){
                if(j >= (m - i) - 1){
                    arr[i][j] = 0;
                    cout << "1 ";
                }
                else{
                    arr[i][j] = 0;
                    cout << "0 ";
                }
            }
            else{
                if(j >= i){
                    arr[i][j] = 0;
                    cout << "1 ";
                }
                else{
                    arr[i][j] = 0;
                    cout << "0 ";
                }
            }
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        delete(arr[i]);
    }
    delete(arr);
    return 0;
}