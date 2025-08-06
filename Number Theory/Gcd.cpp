// find the greatest common divisor of two number a and b in o(log min(a,b))

int gcd(int a , int b){
    return b ? gcd(b,a%b) : a ; 
}

int gcd(int a , int b){
    while(b){
        a %=b ; 
        swap(a,b);
    }
    return a;
}