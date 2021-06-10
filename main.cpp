#include <iostream>
#include <NTL/ZZ.h>


using namespace std;
using namespace NTL;



ZZ module(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}


ZZ binaryGCD(ZZ u,ZZ v){
    ZZ t, g, a, b;
    g=1;
    a=abs(u);
    b=abs(v);
    while((a&1)==0 && (b&1)==0){
        a>>=1;
        b>>=1;
        g<<=1;
    }
    while(a!=0){
        if((a&1)==0){
            a>>=1;
        }else if((b&1)==0){
            b>>=1;
        }else{
            t=abs(a-b)>>1;
            if(a>= b){
                a=t;
            }else{
                b=t;
            }
        }
    }
    return g*b;
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

void gcdExtended(ZZ a, ZZ b, ZZ& x, ZZ& y) {
    x = ZZ(1), y = ZZ(0);

    ZZ x1(0), y1(1), a1(a), b1(b);
    while (b1 != 0) {
        ZZ q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
}

ZZ inverse(ZZ a,ZZ n){
    ZZ x,y;
    gcdExtended(a,n,x,y);
    return module(x,n);
}

ZZ Pow(ZZ g,ZZ e ){
    ZZ A(1);
    while(e > 0){
        if((e&1)==1) A*=g;
        g*=g;
        e>>=1;
    }
    return A;
}


ZZ modPow(ZZ a ,ZZ n,ZZ m){

    ZZ exp (1);
    ZZ x = module(a,m);

    while(n>0){
        if(module(n, ZZ(2)) == 1)
            exp = module(exp*x,m);
        x = module(x*x,m);
        n>>=1;
    }
    return exp;
}



ZZ RandomNumber(int bits) {
    //[2n−1,2n-1]
    ZZ begin = power(ZZ(2), bits-1);
    ZZ end = power(ZZ(2), bits) - 1;
    return  RandomBnd(end - begin + 1) + begin;
}

ZZ RandomNumber(ZZ init,ZZ end) {
    ZZ k = end - init + 1;
    ZZ num = RandomBnd(k)+init;
    return num;
}

bool MillerRabinTest(ZZ d, ZZ n)
{

    // obtener un numero random en [2..n-2]
    ZZ a = RandomNumber(ZZ(2),n-2);

    // X =  a^d mod( n)
    ZZ x = modPow(a, d, n);

    if (x == 1  || x == n-1)
        return true;


    while (d != n-1)
    {
        x= module(x*x,n);
        //x= x*x % n;
        d *= 2;

        if (x == 1)      return false;
        if (x == n-1)    return true;
    }

    return false;
}


bool isPrime(ZZ number, ZZ iter)
{
    // Casos Base
    if(module(number,ZZ(2))== 0) return false;
    if (number <= 1 || number == 4)  return false;
    if (number <= 3) return true;

    // number-1 = 2^d * r ; r >= 1
    ZZ d = number - 1;

    //Hallar  el exponente d
    while (module(d,ZZ(2)) == 0)
        d /= 2;


    // Iterar
    for (ZZ i (0); i < iter; i++)
        if (!MillerRabinTest(d, number))
            return false;

    return true;
}


ZZ RandomPrime(int bits){
    ZZ num;
    do{
        num= RandomLen_ZZ(bits);
        //cout<<"\nRandom Number: "<<num<<"\n\n";

    }while(!(isPrime(num,ZZ(5))));

    return num;
}



/*-----------------------------------*/

ZZ Right_to_Left_Binary(ZZ g , ZZ e ,ZZ m){
    ZZ A;
    A = 1;
    while(e != 0){
        if((e & 1) == 1) A=module(A*g,m);
        e>>=1;
        g= module(g*g,m);
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
        g= module(g*g,m);
        e>>=1;
    }
    return A;
}


//Teorema chino para Descifrar

bool check(ZZ p ,ZZ q){
    return (binaryGCD(p,q)==1)? 1:0;
}


ZZ TRC(ZZ a , ZZ e,ZZ N ,ZZ p, ZZ q){
    //descomponer
    ZZ a1,a2,d1,d2,P,P1,P2,q1,q2,D;
    d1 = module(e,p-1);
    d2 = module(e,q-1);
    a1 = Left_to_Right_Binary(a,d1,p);
    a2 = Left_to_Right_Binary(a,d2,q);
    // calculo de P
    P = p*q;
    P1 = P/p;
    P2 = P/q;
    // q*P=1modp
    q1 = inverse(P1,p);
    q2 = inverse(P2,q);
    // D = a*P*q ..
    D = module(module(a1*P1,P)*q1 + module(a2*P2,P)*q2,P);

    /*
    cout<<"\nd1: "<<d1;
    cout<<"\nd2: "<<d2;
    cout<<"\na1: "<<a1;
    cout<<"\na2: "<<a2;
    cout<<"\nP: "<<P;
    cout<<"\nP1: "<<P1;
    cout<<"\nP2: "<<P2;
    cout<<"\nq1: "<<q1;
    cout<<"\nq2: "<<q2;
    cout<<"\nD: "<<D;
    cout<<endl;*/

    return D;
}




int main() {


    ZZ g = RandomNumber(3);
    ZZ e = RandomNumber(3);
    ZZ p = RandomPrime(5);
    ZZ q = RandomPrime(5);
    ZZ m = p*q;

    /*
    ZZ g (115);
    ZZ e (103);
    ZZ m(143);
    ZZ p(11);
    ZZ q(13);*/


    cout<<"\ng: "<<g;
    cout<<"\ne: "<<e;
    cout<<"\nm: "<<m;
    cout<<"\np: "<<p;
    cout<<"\nq: "<<q;

    cout<<"\nRLB: "<<Right_to_Left_Binary(g,e,m);
    cout<<"\nLRB: "<<Left_to_Right_Binary(g,e,m);
    cout<<"\nNaive: "<<NaiveExponentiation(g,e,m);//slow
    cout<<"\nFast: "<<FastExponentiation(g,e,m);
    cout<<"\nBinary: "<<BinaryExponentiation(g,e,m);

    if(check(p,q))
        cout<<"\nTRC: "<<TRC(g,e,m,p,q);


    cout<<"\n\n\n";

    return 0;
}
