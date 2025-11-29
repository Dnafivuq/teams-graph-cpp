// Public headers go here

/*!
 \file Test.h
 \author Mateusz Guliński
*/

//! Test class to showcase doxygen syntax.
/*!
  This class showcases doxygen with the Qt syntax. For more examples visit
  https://www.doxygen.nl/manual/docblocks.html#docexamples
*/
class Test {
public:
    //! Brief description of add()
    /*!
     Detailed description of add().

     Returns the parameter sum \p a and \p b
     \param a the first number to add
     \param b the second number to add
     \return the sum of \p a \p b
    */
    int add(int first_number, int second_number);
};