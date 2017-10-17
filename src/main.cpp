#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

class CTimeImpl {
 public:
  CTimeImpl(int hr, int min) : m_hr(hr), m_min(min) {}

  virtual ~CTimeImpl() = default;

  virtual void tell() {
    cout << "time is: " << m_hr << ':' << m_min;
  }

 private:
  int m_hr;
  int m_min;
};

class CCivilianTimeImpl : public CTimeImpl {
 public:
  CCivilianTimeImpl(int hr, int min, string&& pm) : CTimeImpl(hr, min), m_pm(move(pm)) {}

  void tell() override {
    CTimeImpl::tell();
    cout << m_pm;
  }

 private:
  string m_pm;
};

class CZuluClassImpl : public CTimeImpl {
 public:
  CZuluClassImpl(int hr, int min, string&& zone) : CTimeImpl(hr, min), m_zone(move(zone)) {}

  void tell() override {
    CTimeImpl::tell();
    cout << m_zone;
  }

 private:
  string m_zone;
};

class CTime {
 public:
  CTime(int hr, int min) : m_timeImpl(make_unique<CTimeImpl>(hr, min)) {}

  CTime(unique_ptr<CTimeImpl> timeImpl) : m_timeImpl(move(timeImpl)) {}

  void tell() {
    m_timeImpl->tell();
    cout << endl;
  }

 private:
  unique_ptr<CTimeImpl> m_timeImpl;
};

class CCivilianTime : public CTime {
 public:
  CCivilianTime(int hr, int min, string&& pm)
      : CTime(make_unique<CCivilianTimeImpl>(hr, min, move(pm))) {}
};

class CZuluTime : public CTime {
 public:
  CZuluTime(int hr, int min, string&& zone)
      : CTime(make_unique<CZuluClassImpl>(hr, min, move(zone))) {}
};

int main() {
  vector<unique_ptr<CTime>> times;

  times.push_back(make_unique<CTime>(14, 30));
  times.push_back(make_unique<CCivilianTime>(14, 30, "AM"));
  times.push_back(make_unique<CZuluTime>(14, 30, " Eastern Standard Time"));

  for (auto& t : times) {
    t->tell();
  }
}
