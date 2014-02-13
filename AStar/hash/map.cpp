#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


using namespace std;


typedef struct {
    int x;
    int y;
    string get(){
        return std::to_string(x) + std::to_string(y);
    }
} mypair;

bool operator==(const mypair & v1,const mypair & v2)
{
    if(v1.x == v2.x && v1.y == v2.y) return true;
    return false;
}

int main(){
    unordered_map<string, int> M;
    mypair x = {1,3};
    mypair y = {3,3};
    mypair z = {3,9};

    M[x.get()] = 1;
    M[y.get()] = 2;
    M[z.get()] = 3;
    cout << M[z.get()] <<endl;
}
