class InParser {
private:
  static const int BUFF_SIZE = 1 << 12;
  FILE *f;
  char buff[BUFF_SIZE];
  int sp = BUFF_SIZE;
 
  char read_ch() {
    if (sp == BUFF_SIZE) {
      sp = 0;
      fread(buff, 1, BUFF_SIZE, f);
    }
    return buff[sp++];
  }
 
public:
  InParser(const char* file) {
    f = fopen(file, "r");
  }
  
  InParser& operator >> (int &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    int sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
  
  InParser& operator >> (long long &n) {
    char c;
    n = 0;
    while (!isdigit(c = read_ch()) && c != '-');
    long long sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
};
