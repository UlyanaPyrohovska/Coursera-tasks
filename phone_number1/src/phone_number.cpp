#include "phone_number.h"
#include <sstream>
#include <iostream>

/* Принимает строку в формате +XXX-YYY-ZZZZZZ
 Часть от '+' до первого '-' - это код страны.
 Часть между первым и вторым символами '-' - код города
 Всё, что идёт после второго символа '-' - местный номер.
 Код страны, код города и местный номер не должны быть пустыми.
 Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

 Примеры:
 * +7-495-111-22-33
 * +7-495-1112233
 * +323-22-460002
 * +1-2-coursera-cpp
 * 1-2-333 - некорректный номер - не начинается на '+'
 * +7-1233 - некорректный номер - есть только код страны и города
 */

string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

PhoneNumber::PhoneNumber(const string &international_number) {
	istringstream s(international_number);
	string pusto;
	int str2;
	int str1;
	char ch1, ch2;
	if (s.peek() == '+') {
		if (s.ignore(1) && s >> str1 && s >> ch1 && s >> str2 && s >> ch2
				&& s >> pusto) {
			if (ch1 == '-' && ch2 == '-') {
				country_code_ = to_string(str1);
				//cout << country_code_;
				city_code_ = to_string(str2);
				local_number_ = pusto;
			} else {
				throw invalid_argument("no -");
			}
		} else {
			throw invalid_argument("no stuff");
		}
	} else {
		throw invalid_argument("no +");
	}

}
int main() {
	std::string num { "+7-495-111-22-33" };
	try {
		auto phone = new PhoneNumber(num);

		std::cout << phone->GetCountryCode() << ' ' << phone->GetCityCode()
				<< ' ' << phone->GetLocalNumber() << ' '
				<< phone->GetInternationalNumber() << '\n';
	} catch (const std::exception &e) {
		std::cout << e.what() << '\n';
	}
}
