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

ZZ fast(ZZ a,ZZ p,ZZ n){
    ZZ t;
    if(p == 0) return ZZ(1);
    if((p&1)==0){
        t = fast(a,p>>1,n);
        return module(t*t,n);
    }
    t = fast(a,(p-1)>>1,n);
    return module(a *module(t*t,n),n);


}

void binary(ZZ b, ZZ e, ZZ m)
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

    ZZ base = conv <ZZ> ("197564123456785645645675645345675645679");
    ZZ expo = conv <ZZ> ("277897456412375674564126789756456378975");
    ZZ mod = conv <ZZ> ("245678641237897897564567897456456123458");

    fast(base, expo, mod);
    //binary(base, expo, mod);
    //right_to_left_binary(base, expo, mod);
    //left_to_right_binary(base, expo, mod);
    //NaiveExponentiation(base, expo, mod);
    //484216375

}
