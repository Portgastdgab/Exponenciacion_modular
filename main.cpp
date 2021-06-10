#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include<sstream>

using namespace std;
using namespace NTL;


ZZ module(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}


ZZ RandomNumber(int bits) {
    //[2n−1,2n-1]
    ZZ begin = power(ZZ(2), bits-1);
    ZZ end = power(ZZ(2), bits) - 1;
    return  RandomBnd(end - begin + 1) + begin;
}

int countBits(ZZ n){
    int count =0;
    while(n != 0){
        count++;
        n>>=1;
    }
    return count;
}

ZZ reverseBits(ZZ n){
    ZZ rev(0);
    while(n>0){
        rev <<=1;
        if((n&1) == 1)  rev ^= 1;
        n >>= 1;
    }
    return rev;
}



/*-----------------------------------*/

ZZ Right_to_Left_Binary(ZZ g , ZZ e ,ZZ m){
    ZZ A,S;
    A = 1;
    while(e != 0){
        if((e & 1) == 1) A=module(A*g,m);
        e>>=1;
        g*=g;
    }
    return A;
}


ZZ Left_to_Right_Binary(ZZ g , ZZ e ,ZZ m){

    ZZ bits = power(ZZ(2), countBits(e));
    ZZ A (1);
    while(bits !=0){
        A= module(A*A,m);
        if((e & bits) != 0) A=module(A*g,m);
        bits>>=1;
    }
    return A;
}


ZZ NaiveExponentiation(ZZ g , ZZ e ,ZZ m){
    ZZ A (1);
    for(int i=0;i<e;i++){
        A = module(A*g,m);
    }
    return A;
}



ZZ FastExponentiation(ZZ a,ZZ p,ZZ n){
    ZZ t;
    if(p == 0) return ZZ(1);
    if((p&1)==0){
        t = FastExponentiation(a,p>>1,n);
        return module(t*t,n);
    }
    t = FastExponentiation(a,(p-1)>>1,n);
    return module(a *module(t*t,n),n);


}

ZZ BinaryExponentiation(ZZ g,ZZ e ,ZZ m){
    ZZ A(1);
    while(e > 0){
        if((e&1)==1) A=module(A*g,m);
        g*=g;
        e>>=1;
    }
    return A;
}





int main() {


    ZZ g = RandomNumber(4);
    ZZ e = RandomNumber(6);
    ZZ m = RandomNumber(6);

/*
    ZZ g (11);
    ZZ e (48);
    ZZ m(54);*/

    cout<<"\ng: "<<g;
    cout<<"\ne: "<<e;
    cout<<"\nm: "<<m;
    cout<<"\nRLB: "<<Right_to_Left_Binary(g,e,m);
    cout<<"\nLRB: "<<Left_to_Right_Binary(g,e,m);
    cout<<"\nNaive: "<<NaiveExponentiation(g,e,m);
    cout<<"\nFast: "<<FastExponentiation(g,e,m);
    cout<<"\nBinary: "<<BinaryExponentiation(g,e,m);
   

    cout<<"\n\n\n";

    return 0;
}
