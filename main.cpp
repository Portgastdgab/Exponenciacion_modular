#include <iostream>
#include <bitset>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

string toBinary(ZZ n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    return r;
}

ZZ module(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

void rapida(ZZ b, ZZ e, ZZ m)
{
	ZZ result = (e & 1)==1 ? b : ZZ(1);
	while (e != 0) {
		e >>= 1;
		b = module((b * b), m);
		if ((e & 1)==1)
			result = module((result * b), m);
	}
	cout<<result;
}

void binary(ZZ a,ZZ b, ZZ mod) {
	ZZ res(1);
    while (b > 0) {
        if ((b & 1)==1)
            res = module(res * a, mod);
        a = a * a;
        b >>= 1;
    }
    cout<<res;
}

void right_to_left_binary(ZZ b, ZZ e, ZZ mod){
    ZZ A(1);
    ZZ S = b;
    while (e != 0){
        if (module(e, ZZ(2)) != 0){
            A = module(A * S, mod);
        }
        e = e/2;
        if (S != 0){
            S = S * S;
        }
    }
    cout<<A;
}

void left_to_right_binary(ZZ b, ZZ e, ZZ mod){
    ZZ A(1);
    string bin = toBinary(e);
    for (int i = bin.size(); i != -1; i--){
        A = module(A * A, mod);
        if(bin[i] == '1'){
            A = module(A * b, mod);
        }
    }
    cout<<A;
}

void NaiveExponentiation (ZZ b, ZZ e, ZZ mod){
    ZZ r(1);
    for (ZZ i(1); i <= e; i++){
        r = module(r * b, mod);
    }
    cout<<r;
}

int main()
{

    ZZ base(572);
    ZZ expo(29);
    ZZ mod(713);
    binary(base, expo, mod);

}
