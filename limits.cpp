#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <climits>
#include <cfloat>
#include <cmath>

using namespace std;

template<typename T>
string about(T v) {
  bool negative = v < 0;
  if (negative) {
    v += 1;
    v *= -1;
  }
  int e = 0;
  while (v >= 10) {
    v /= 10;
    e++;
  }
  v = floor(v); //In case v is a float.
  ostringstream oss;
  if (negative)
    oss << "-";
  oss << v << "E" << e;
  return oss.str();
}

int main() {
  cout << "LLONG_MIN: \t" << LLONG_MIN << " \tabout: " << about(LLONG_MIN) << endl;
  cout << "LLONG_MAX: \t" << LLONG_MAX << " \tabout: " << about(LLONG_MAX) << endl;
  cout << "ULLONG_MAX: \t" << ULLONG_MAX << " \tabout: " << about(ULLONG_MAX) << endl;
  cout << "DBL_MANT_DIG: \t" << DBL_MANT_DIG << endl;
  cout << "LDBL_MANT_DIG: \t" << LDBL_MANT_DIG << endl;
  cout << "DBL_DIG: \t" << DBL_DIG << endl;
  cout << "LDBL_DIG: \t" << LDBL_DIG << endl;
  cout << "DBL_MAX: \t" << DBL_MAX << " \tabout: " << about(DBL_MAX) << endl;
  cout << "DBL_MIN: \t" << DBL_MIN << " \tabout: " << about(DBL_MIN) << endl;
  cout << "LDBL_MAX: \t" << LDBL_MAX << " \tabout: " << about(LDBL_MAX) << endl;
  cout << "LDBL_MIN: \t" << LDBL_MIN << " \tabout: " << about(LDBL_MIN) << endl;
  return 0;
}

