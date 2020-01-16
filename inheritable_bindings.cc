#include <iostream>
#include <memory>
#include <string>
#include <vector>

class BindingBase
{
public:
  virtual ~BindingBase(){}
  virtual bool operator()() = 0;
};

class PrintMessage : public BindingBase
{
public:
  PrintMessage(const std::string &str) : str_(str) {}

  bool operator()()
  {
    std::cout << "hello and " << str_ << std::endl;
    return true;
  }

  std::string str_;
};

class PrintAddInts : public BindingBase
{
public:
  PrintAddInts(const int &a, const int &b) : a_(a), b_(b) {}

  bool operator()()
  {
    std::cout << a_ + b_ << std::endl;
    return false;
  }

  int a_, b_;
};

int main(int argc, char **argv)
{
  std::vector<std::unique_ptr<BindingBase>> bindings;
  bindings.emplace_back(std::make_unique<PrintAddInts>(2, 3));
  bindings.emplace_back(std::make_unique<PrintMessage>("goodbye"));

  for (auto&& binding : bindings)
  {
    (*binding)();
  }

  return 0;
}
