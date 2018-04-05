/* Author@varunjain0606
 * Trivial Singleton implementation in c++
 * Purpose: To understand Singleton pattern,
 *          This is a trivial implementation,
 *          It does not ensure thread safety
 */
#include <iostream>

class Singleton{
 private:
  int s_instance_member_;
  static Singleton *s_instance_;

  explicit Singleton(int default_member_value = 0) {
    s_instance_member_ = default_member_value;
    std::cout << "Created Singleton Instance" << std::endl;
  }
 public:
  static Singleton *GetInstance() {
    if (s_instance_ == NULL)
      s_instance_ =  new Singleton;
    return s_instance_;
  }

  int GetInstanceMemberValue() {
    return s_instance_member_;
  }

  void SetInstanceMemberValue(int s_instance_member) {
    s_instance_member_ = s_instance_member;
  }
};

Singleton *Singleton::s_instance_ = NULL;

/************* Driver stub to test the trivial singleton ********************/

/*int main() {
  Singleton *singleton_1 = Singleton::GetInstance();
  int var = singleton_1->GetInstanceMemberValue();

  singleton_1->SetInstanceMemberValue(var + 1);
  var = singleton_1->GetInstanceMemberValue();
  std::cout << var << std::endl;

  Singleton *singleton_2 = Singleton::GetInstance();
  var = singleton_2->GetInstanceMemberValue();

  singleton_2->SetInstanceMemberValue(var + 3);
  var = singleton_2->GetInstanceMemberValue();
  std::cout << var << std::endl;

  return 0;
} */
