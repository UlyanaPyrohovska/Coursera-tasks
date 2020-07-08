#include <cstdlib>
#include <iostream>

using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
    	if(denominator < 0){
    		if(numerator < 0){
    			numerator = abs(numerator);
    			denominator = abs(denominator);
    		}
    		else {
    			denominator = abs(denominator);
    			numerator = numerator - 2 * numerator;
    		}
    	}
    	if(numerator == 0){
    		denominator = 1;
    	}
    	int k = dup(abs(numerator), abs(denominator));
    	p = numerator/k;
    	q = denominator/k;
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int dup(int numerator, int denominator){
    	while(numerator > 0 && denominator > 0){
    			if(numerator > denominator)
    				numerator = numerator % denominator;
    			else
    				denominator = denominator % numerator;
    		}
    	return denominator + numerator;
    }
    int p;
    int q;
};

bool operator ==(const Rational& a, const Rational& b){
    if((a.Numerator() == b.Numerator()) && (a.Denominator() == b.Denominator())){
        return true;
    }
    else{
        return false;
    }

}

Rational operator +(const Rational& a,const Rational& b){
    int q = (a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator());
    int p = (a.Denominator() * b.Denominator());
	return Rational(q, p);
}

Rational operator -(const Rational& a,const Rational& b){
    int p = (a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator());
    int q = (a.Denominator() * b.Denominator());
	return Rational(p, q);
}
int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }
    bool tr = (Rational(2, 3) + Rational(1, 3) == Rational(1, 1));
    cout << tr << endl;
    cout << "OK" << endl;
    return 0;
}
