//---------------------------- polynomial.cpp----------------------------
// 
// polynomial.cpp CSS 343
// 
// Jan 14 2023
// 
// Jan 14 2023
// 
// ----------------------------------------------------------------------
// 
// Purpose - Implement an ADT polynomial
// 
// ----------------------------------------------------------------------
// 
// Notes on specifications, special algorithms, and assumptions.
// 
// ----------------------------------------------------------------------
#include "polynomial.h"
#include <iostream>
#include <string>

using namespace std;

//---------------------------- operator<< -----------------------------
// Description:
//     This function overloads the '<<' operator for the Polynomial class.
//     It allows the user to easily print out the polynomial in a formatted way.
//
// preconditions:
//     The polynomial should be properly initialized.
//
// postconditions:
//     The polynomial will be printed out in a formatted way, such as
//     "3x^2+2x-1".
//
//----------------------------------------------------------------------

ostream &operator<<(ostream &output, const Polynomial &p) 
{
  // empty case
  if ( p.size == 0 )
  {
    output << "0";
    return output;
  }
  // current pointer to travel the polynomial
  Polynomial::Term *current = p.head->next;

  // loop through the polynomial and print the terms
  while (current != p.head) 
  {
    if (current != p.head->next && current->coeff > 0) 
    {
      output << "+";
    }
    if (current->coeff != 1) 
    {
      output << current->coeff;
    }
    if (current->power != 0) 
    {
      output << "x";
      if (current->power != 1) 
      {
        output << "^" << current->power;
      }
    } else if (current->coeff == 1) 
    {
      output << current->coeff;
    }

    current = current->next;
  }
  return output;
}
// end of operator<<

// ------------------------ default constructor -------------------------
// Description:
//     It initializes a new polynomial object by creating a new dummy
//     header and setting the size to zero.
//
//     preconditions:   The default constructor is called
//
//     postconditions:
//          - The size will be set to zero.
//          - The head pointer will be set up, where the head coeff and
//            power variables is set to zero.
//          - The next and prev pointers of the head will be set back to the
//            head.
//
// ----------------------------------------------------------------------
Polynomial::Polynomial() 
{
  size = 0;
  head = new Term();
  head->coeff = 0;
  head->power = 0;
  head->next = head;
  head->prev = head;
}
// end of default constructor

// -------------------------- copy constructor --------------------------
// Description:
//     It initializes a new polynomial object as a deep copy of another
//     polynomial object.
//
//     preconditions:  The other Polynomial should be initialized
//
//     postconditions:
//          - This Polynomial will result in a deep copy version of
//            the other Polynomial
// ----------------------------------------------------------------------
Polynomial::Polynomial(const Polynomial &p) 
{
  size = 0;
  head = new Term();
  head->coeff = 0;
  head->power = 0;
  head->next = head;
  head->prev = head;

  // start copying
  Term *current = p.head->next;
  while (current != p.head) 
  {
    changeCoefficient(current->coeff, current->power);
    current = current->next;
  }
}
// end of copy constructor

// ----------------------------- destructor -----------------------------
// Description:
//     It is responsible for freeing up memory allocated for the polynomial.
//
//     preconditions:  The polynomial object is about to go out of scope
//
//     postconditions: The memory allocated for the polynomial's terms
//                     and the dummy header is freed to prevent memory leaks
// ----------------------------------------------------------------------

Polynomial::~Polynomial() 
{
  Term *delMe = head->next;
  while (remove(delMe)) 
  { // remove every Terms until meet head
    delMe = head->next;
  }
  delete head; // delete head memory
}
// end of destructor

// ---------------------------- degree -----------------------------
// Description
//     degree: returns the highest power of the polynomial
//
//     preconditions:   The polynomial object is initialized
//
//     postconditions: The highest power of the polynomial is returned
// ----------------------------------------------------------------------
int Polynomial::degree() const 
{
  Term *next = head->next;
  if (next == head)
    return 0;
  return next->power;
}
// end of degree

// ---------------------------- coefficient -----------------------------
// Description
//     coefficient: returns the coefficient in terms of the given power
//
//     preconditions:   The polynomial object is initialized
//
//     postconditions: The coefficient of the term of the given power is
//     returned
// ----------------------------------------------------------------------
double Polynomial::coefficient(const int power) const 
{
  Term *curr = head->next;

  // look through the whole list until it exceed the power
  while (curr != head && curr->power >= power) 
  {
    if (curr->power == power) 
    {
      return curr->coeff;
    }                  // if the power found
                       // if not found
    curr = curr->next; // look to smaller coeff
  }
  return 0; // no matching power
}
// end of coefficient

// ------------------------------- insert -------------------------------
// Description:
//     insert: Inserts a new Term with the given coefficient and power
//             into the polynomial.
//
// Preconditions:
//     newCoefficient should not be zero.
//     The function should not be called if the power already exists in
//     the polynomial.
//
// Postconditions:
//     Returns true if the new term was created successfully.
//     Returns false otherwise.
// ----------------------------------------------------------------------
bool Polynomial::insert(Term *pos, const double newCoefficient,
                        const int power) 
  {
  if (newCoefficient == 0) 
  {
    return false;
  }

  // set up the temp Term object
  Term *temp = new Term();
  temp->coeff = newCoefficient;
  temp->power = power;

  // insert the temp object
  pos->prev->next = temp;
  temp->prev = pos->prev;
  temp->next = pos;
  pos->prev = temp;

  size++;
  return true;
}
// end of insert

// ------------------------------- remove -------------------------------
// Description:
//     remove: Removes the given Term from the polynomial.
//
// Preconditions:
//     The given Term should exist in the polynomial.
//
// Postconditions:
//     Returns true if the Term was removed successfully.
//     Returns false otherwise.
// ----------------------------------------------------------------------
bool Polynomial::remove(Term *pos) 
{
  Term *curr = head->next;
  if (pos == NULL || size == 0) 
  {
    return false;
  }
  while (curr != head && curr != pos) 
  {
    curr = curr->next;
  }
  Term *prev = curr->prev;
  prev->next = curr->next;
  curr->next->prev = prev;
  delete curr;
  size--;
  return true;
}
// end of remove

// ------------------------- changeCoefficient --------------------------
// Description:
//     changeCoefficient: Changes the coefficient of the Term with the given
//     power in the polynomial, or inserts a new Term with the given coefficient
//     and power if no such Term exists, if the given coefficient is zero, the
//     Term will be removed.
//
// Preconditions:
//     newCoefficient should be a valid double value.
//     power should be a valid int value.
//
// Postconditions:
//     Return the bool value of the insert or remove function being used
// ----------------------------------------------------------------------

bool Polynomial::changeCoefficient(const double newCoefficient,
                                   const int power) 
{
  Term *curr = head->next;
  // either the curr pointer stop at the same power
  // or it stop at the next smaller power
  while (curr != head && curr->power > power) 
  {
    curr = curr->next;
  }
  // remove case
  if (newCoefficient == 0) 
  {
    if (curr->power != power)
    {
      return false; // return false if the remove object doesn't exist
    }
    return remove(curr);
  }

  // if not delete case
  // when a orgional object already exist
  if (curr->power == power && curr != head) 
  {
    curr->coeff = newCoefficient;
    return true;
  }

  // if the power doesn't exist
  return insert(curr, newCoefficient, power);
}
// end of changeCoefficient

// -------------------------------- operator+ -------------------------------
// Description:
//     operator+: Adds the current polynomial with the given polynomial 'p'
//                and returns a new polynomial as the result.
//
// Preconditions:
//     Both polynomials should be initialized.
//
// Postconditions:
//     Returns a new polynomial which is the sum of the current polynomial
//     and the given polynomial 'p'.
// ----------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial &p) const 
{
  Polynomial result; // create a new polynomial to hold the result
  Term *currentTerm = this->head->next;
  Term *otherTerm = p.head->next;

  // combine this and other polynomials together
  while (currentTerm != head && otherTerm != p.head) 
  {
    if (currentTerm->power == otherTerm->power) 
    {
      // if the powers match, add the coefficients and insert into result
      result.changeCoefficient(currentTerm->coeff + otherTerm->coeff,
                               currentTerm->power);
      currentTerm = currentTerm->next;
      otherTerm = otherTerm->next;
    } else if (currentTerm->power > otherTerm->power) 
    {
      // if currentTerm has a larger power, insert it into result
      result.changeCoefficient(currentTerm->coeff, currentTerm->power);
      currentTerm = currentTerm->next;
    } else 
    {
      // if otherTerm has a larger power, insert it into result
      result.changeCoefficient(otherTerm->coeff, otherTerm->power);
      otherTerm = otherTerm->next;
    }
  }
  // handeling the remaining terms from either current or other polynomial
  while (currentTerm != head) 
  {
    result.changeCoefficient(currentTerm->coeff, currentTerm->power);
    currentTerm = currentTerm->next;
  }
  while (otherTerm != p.head) 
  {
    result.changeCoefficient(otherTerm->coeff, otherTerm->power);
    otherTerm = otherTerm->next;
  }
  // end combining
  return result;
}
// end operator +

// ------------------------------ operator- ------------------------------
// Description
// operator-:      subtract this by other Polynomial
//
// preconditions:  both Polynomial is initalized
//
// postconditions: the polynomial will be modified according to the
//                 input variables
//
// ----------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial &p) const 
{
  Polynomial result;
  Term *currentTerm = this->head->next; // currentTerm is this
  Term *otherTerm = p.head->next;       // otherTerm is the other Polynomial

  // subtract this and other Polynomial
  while (currentTerm != head && otherTerm != p.head) 
  {
    if (currentTerm->power == otherTerm->power) 
    {
      result.changeCoefficient(currentTerm->coeff - otherTerm->coeff,
                               currentTerm->power);
      currentTerm = currentTerm->next;
      otherTerm = otherTerm->next;
    } else if (currentTerm->power > otherTerm->power) 
    {
      result.changeCoefficient(currentTerm->coeff, currentTerm->power);
      currentTerm = currentTerm->next;
    } else 
    {
      result.changeCoefficient(-1 * otherTerm->coeff, otherTerm->power);
      otherTerm = otherTerm->next;
    }
  }
  // handeling the remaining from either left or right Polynomial
  while (currentTerm != head) 
  {
    result.changeCoefficient(currentTerm->coeff, currentTerm->power);
    currentTerm = currentTerm->next;
  }
  while (otherTerm != p.head) 
  {
    result.changeCoefficient(otherTerm->coeff, otherTerm->power);
    otherTerm = otherTerm->next;
  }
  // end substracting
  return result;
}
// end operator -

// ------------------------------ operator== ------------------------------
// Description:
//     operator==:  Check if two Polynomials are equal
//
// Preconditions:
//     both Polynomials are initalized
//     assume the Polynomial class sotres Terms in decreasing order of
//     power
//
// Postconditions:
//     Returns true if the two Polynomials are equal.
//     Returns false otherwise.
// ----------------------------------------------------------------------
bool Polynomial::operator==(const Polynomial &p) const 
{
  // Compare the size of the polynomials
  if (size != p.size) 
  {
    return false;
  }

  // Compare each term of the polynomials
  Term *currentTerm = head->next;
  Term *otherTerm = p.head->next;
  while (currentTerm != head && otherTerm != p.head) 
  {
    if (currentTerm->coeff != otherTerm->coeff ||
        currentTerm->power != otherTerm->power) 
    {
      return false;
    }
    currentTerm = currentTerm->next;
    otherTerm = otherTerm->next;
  }
  return true;
}
// end operator==

// ------------------------------ operator!= ------------------------------
// Description:
// operator!=: Compares this polynomial with another polynomial to check
//             if they are not equal.
//
// Preconditions:
//             Both polynomials are initialized.
//
// Postconditions:
//             Returns true if the polynomials are not equal.
//             Returns false otherwise.
// ----------------------------------------------------------------------
bool Polynomial::operator!=(const Polynomial &p) const 
{ 
  return !(*this == p); 
}
// endl operator !=

// ------------------------------- operator= -------------------------------
// Description:
// operator=: Assigns the values of one Polynomial to another.
//
// Preconditions:
//            The other Polynomial is initialized
//
// Postconditions:
//            The current Polynomial will have the same values as the input
//            Polynomial.
//
// ----------------------------------------------------------------------
Polynomial &Polynomial::operator=(const Polynomial &p) 
{
  if (this != &p) 
  {
    clear();
    Term *currentTerm = p.head->next;
    while (currentTerm != p.head) 
    {
      this->changeCoefficient(currentTerm->coeff, currentTerm->power);
      currentTerm = currentTerm->next;
    }
  }
  return *this;
}
// end operator=

// ------------------------------ clear ------------------------------
// Description:
// clear: Clears all the terms in the polynomial
//
// Preconditions:
//        None
//
// Postconditions:
//        The polynomial is empty.
// ----------------------------------------------------------------------
void Polynomial::clear() 
{
  Term *currentTerm = head->next;
  while (currentTerm != head) 
  {
    Term *next = currentTerm->next; // store the next pointer temporary
    remove(currentTerm);
    currentTerm = next;
  }
}
// end of clear

// ------------------------------ operator+= ------------------------------
// Description:
// operator+=: Add the given Polynomial to this Polynomial
//
// Preconditions:
//             both Polynomials are initalized
//
// Postconditions:
//             This Polynomial will be modified to the sum of itself and the
//             given Polynomial.
// ----------------------------------------------------------------------
Polynomial &Polynomial::operator+=(const Polynomial &p) 
{
  *this = *this + p;
  return *this;
}
// end of operator +=

// ------------------------------ operator-= ------------------------------
// Description:
// operator-=: Subtracts the given Polynomial from this Polynomial.
//
// Preconditions:
//             both Polynomials are initalized
//
// Postconditions:
//             The current Polynomial will be substracted by the givem
//             Polynomial
// ----------------------------------------------------------------------
Polynomial &Polynomial::operator-=(const Polynomial &p) 
{
  *this = *this - p;
  return *this;
}
// end of operator -=