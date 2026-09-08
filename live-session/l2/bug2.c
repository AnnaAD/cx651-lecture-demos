#include <stdio.h>

struct person {
  int age;
  int grad_year;
  double height;
};

struct person* make_person() {
  struct person p = {0, 2024, 0.1};
  return &p;
}

int main(void) {
  struct person* greg = make_person();

  printf("greg's age: %d\n", greg->age);
  return 0;
}

