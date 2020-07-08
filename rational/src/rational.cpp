#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <vector>

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

Rational operator /(const Rational& a, const Rational& b){
    int p = (a.Numerator() * b.Denominator());
    int q = (b.Numerator() * a.Denominator());
    return Rational(p, q);
}
Rational operator *(const Rational& a, const Rational& b){
    int p = (a.Numerator() * b.Numerator());
    int q = (b.Denominator() * a.Denominator());
    return Rational(p, q);
}

istream& operator >>(istream& stream, Rational& a){
	int p = 0;
	int q = 0;
	if(stream >> p && stream.ignore(1) && stream >> q){
		a = {p, q};
	}
	return stream;
}

ostream& operator <<(ostream& stream, const Rational& a){
	stream << a.Numerator() << "/" << a.Denominator();
	return stream;
}

bool operator <(const Rational& a, const Rational& b){
	int r = a.Numerator() * b.Denominator();
	int r1 = b.Numerator() * a.Denominator();
	if(r < r1){
		return true;
	}
	else
		return false;
}

bool operator >(const Rational& a, const Rational& b){
	int r = a.Numerator() * b.Denominator();
	int r1 = b.Numerator() * a.Denominator();
	if(r > r1){
		return true;
	}
	else
		return false;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
