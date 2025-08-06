// find least common multiple of two number a and b in o(log min(a,b))
// a * b = lcm(a,b) * gcd(a,b) 

int gcd(int a , int b){
    return b ? gcd(b,a%b) : a ; 
}

int lcm(int a, int b){
    return a / gcd(a,b) * b ; 
}