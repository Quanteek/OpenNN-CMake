/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   N E U R A L   P A R A M E T E R S   N O R M   C L A S S   H E A D E R                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __NEURALPARAMETERSNORM_H__
#define __NEURALPARAMETERSNORM_H__

// System includes

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>

// OpenNN includes

#include "performance_term.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

/// This class represents the neural parameters norm performance term. 
/// This performance term is very useful as a regularization functional in data modeling, optimal control or inverse problems.

class NeuralParametersNorm : public PerformanceTerm
{

public:

   // DEFAULT CONSTRUCTOR

   explicit NeuralParametersNorm(void);

   // NEURAL NETWORK CONSTRUCTOR

   explicit NeuralParametersNorm(NeuralNetwork*);

   // XML CONSTRUCTOR

   explicit NeuralParametersNorm(const tinyxml2::XMLDocument&);

   // DESTRUCTOR

   virtual ~NeuralParametersNorm(void);    

   // METHODS

   // Get methods

   const double& get_neural_parameters_norm_weight(void) const;

   // Set methods

   void set_neural_parameters_norm_weight(const double&);

   void set_default(void);

   // Checking methods

   void check(void) const;

   // performance methods

   double calculate_performance(void) const;   
   Vector<double> calculate_gradient(void) const;
   Matrix<double> calculate_Hessian(void) const;

   double calculate_performance(const Vector<double>&) const;
   Vector<double> calculate_gradient(const Vector<double>&) const;
   Matrix<double> calculate_Hessian(const Vector<double>&) const;

//   double calculate_generalization_performance(void) const;

   std::string write_performance_term_type(void) const;

   std::string write_information(void) const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML(void) const;   

   void from_XML(const tinyxml2::XMLDocument&);

private:

   /// Weight value for the neural parameters norm regularization term.

   double neural_parameters_norm_weight;

};

}

#endif


// OpenNN: Open Neural Networks Library.
// Neural Designer Copyright © 2013 Roberto López and Ismael Santana (Intelnics)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
