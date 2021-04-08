#include "centrale.hpp"

centrale* centrale::la_centrale = nullptr;

centrale::centrale()
{
  // ....
}

centrale& centrale::get()
{
  if (centrale::la_centrale == nullptr)
      centrale::la_centrale = new centrale;
  return *centrale::la_centrale;
}
