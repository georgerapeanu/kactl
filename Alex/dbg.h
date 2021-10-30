template<class A, class B>
std::ostream& operator<<(std::ostream &os, const std::pair<A, B> &p) {
  return os << '(' << p.first << ',' << p.second << ')';
}

template<class T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
  auto it = v.begin();
  os << '[' << *it;
  ++it;
  while (it != v.end()) os << ' ' << *it++;
  return os << ']';
}

template<class T>
std::ostream& operator<<(std::ostream &os, const std::deque<T> &v) {
  auto it = v.begin();
  os << '[' << *it;
  ++it;
  while (it != v.end()) os << ' ' << *it++;
  return os << ']';
}

template<class T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &v) {
  auto it = v.begin();
  os << '[' << *it;
  ++it;
  while (it != v.end()) os << ' ' << *it++;
  return os << ']';
}

template<class A, class B>
std::ostream& operator<<(std::ostream &os, const std::map<A, B> &v) {
  auto it = v.begin();
  os << '[' << *it;
  ++it;
  while (it != v.end()) os << ' ' << *it++;
  return os << ']';
}

#define dbg(args...) __dbg(#args, args)
void __fix(const char* &s) {
  while (*s == ' ' || *s == ',') ++s;
}

template<class Arg1>
void __dbg(const char *name, Arg1 &&arg1) {
  __fix(name);
  if (*name == '\"' || *name == '\'') std::cerr << arg1 << std::endl;
  else if (isdigit(*name)) std::cerr << arg1 << std::endl;
  else std::cerr << '{' << name << ": " << arg1 << '}' << std::endl;
}

template<class Arg1, class... Args>
void __dbg(const char *names, Arg1 &&arg1, Args&&... args) {
  __fix(names);
  const char *comma = strchr(names, ',');
  if (*names == '\"' || *names == '\'') std::cerr << arg1;
  else if (isdigit(*names)) std::cerr << arg1;
  else (std::cerr << '{').write(names, comma - names) << ": " << arg1 << "} ";
  __dbg(comma, args...);
}
