/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M I N K O W S K I   E R R O R   C L A S S                                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "minkowski_error.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates Minkowski error performance term not associated to any neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.

MinkowskiError::MinkowskiError(void) : PerformanceTerm()
{
   set_default();
}


// NEURAL NETWORK CONSTRUCTOR

/// Neural network constructor. 
/// It creates a Minkowski error performance term associated to a neural network but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.

MinkowskiError::MinkowskiError(NeuralNetwork* new_neural_network_pointer)
: PerformanceTerm(new_neural_network_pointer)
{
   set_default();
}


// DATA SET CONSTRUCTOR

/// Data set constructor. 
/// It creates a Minkowski error performance term not associated to any neural network but to be measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.

MinkowskiError::MinkowskiError(DataSet* new_data_set_pointer)
: PerformanceTerm(new_data_set_pointer)
{
   set_default();
}


// NEURAL NETWORK AND DATA SET CONSTRUCTOR

/// Neural network and data set constructor. 
/// It creates a Minkowski error performance term object associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

MinkowskiError::MinkowskiError(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
 : PerformanceTerm(new_neural_network_pointer, new_data_set_pointer)
{
   set_default();
}


// XML CONSTRUCTOR

/// XML constructor. 
/// It creates a Minkowski error object neither associated to a neural network nor to a data set. 
/// The object members are loaded by means of a XML document.
/// @param mean_squared_error_document TinyXML document with the Minkowski error elements.

MinkowskiError::MinkowskiError(const tinyxml2::XMLDocument& mean_squared_error_document)
 : PerformanceTerm(mean_squared_error_document)
{
   set_default();

   from_XML(mean_squared_error_document);
}


// DESTRUCTOR

/// Destructor.
/// It does not delete any pointer. 

MinkowskiError::~MinkowskiError(void) 
{
}


// METHODS

// double get_Minkowski_parameter(void) const method

/// Returns the Minkowski exponent value used to calculate the error. 

double MinkowskiError::get_Minkowski_parameter(void) const
{
   return(Minkowski_parameter);
}


// void set_default(void) method

/// Sets the default values to a Minkowski error object:
/// <ul>
/// <li> Minkowski parameter: 1.5.
/// <li> Display: true.
/// </ul>

void MinkowskiError::set_default(void)
{
   Minkowski_parameter = 1.5;

   display = true;
}


// void set_Minkowski_parameter(const double&) method

/// Sets a new Minkowski exponent value to be used in order to calculate the error. 
/// The Minkowski R-value must be comprised between 1 and 2. 
/// @param new_Minkowski_parameter Minkowski exponent value. 

void MinkowskiError::set_Minkowski_parameter(const double& new_Minkowski_parameter)
{
   // Control sentence

   if(new_Minkowski_parameter < 1.0 || new_Minkowski_parameter > 2.0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Error. MinkowskiError class.\n"
             << "void set_Minkowski_parameter(const double&) method.\n"
             << "The Minkowski parameter must be comprised between 1 and 2\n";
    
      throw std::logic_error(buffer.str());
   }

   // Set Minkowski parameter
  
   Minkowski_parameter = new_Minkowski_parameter;
}


// void check(void) const method

/// Checks that there are a neural network and a data set associated to the Minkowski error, 
/// and that the numbers of inputs and outputs in the neural network are equal to the numbers of inputs and targets in the data set. 
/// If some of the above conditions is not hold, the method throws an exception. 

void MinkowskiError::check(void) const
{
   std::ostringstream buffer;

   // Neural network stuff

   if(!neural_network_pointer)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to neural network is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   if(!multilayer_perceptron_pointer)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to multilayer perceptron is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   if(inputs_number == 0)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Number of inputs in multilayer perceptron object is zero.\n";

      throw std::logic_error(buffer.str());	  
   }

   if(outputs_number == 0)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Number of outputs in multilayer perceptron object is zero.\n";

      throw std::logic_error(buffer.str());	  
   }

   // Data set stuff

   if(!data_set_pointer)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to data set is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   // Sum squared error stuff

   const Variables& variables = data_set_pointer->get_variables();

   const unsigned targets_number = variables.count_targets_number();

   if(inputs_number != inputs_number)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Number of inputs in multilayer perceptron must be equal to number of inputs in data set.\n";

      throw std::logic_error(buffer.str());	  
   }

   if(outputs_number != targets_number)
   {
      buffer << "OpenNN Exception: MinkowskiError class.\n"
             << "void check(void) const method.\n"
             << "Number of outputs in multilayer perceptron must be equal to number of targets in data set.\n";

      throw std::logic_error(buffer.str());
   }
}


// double calculate_performance(void) const method

/// Returns the Minkowski error performance.

double MinkowskiError::calculate_performance(void) const
{
   // Control sentence

   #ifndef NDEBUG 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set

   const Instances& instances = data_set_pointer->get_instances();
   const unsigned training_instances_number = instances.count_training_instances_number();

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double Minkowski_error = 0.0;

   for(unsigned i = 0; i < training_instances_number; i++)
   {
      // Input vector

	  inputs = data_set_pointer->get_training_input_instance(i);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_training_target_instance(i);

      // Minkowski error

      Minkowski_error += (outputs-targets).calculate_p_norm(Minkowski_parameter);
   }

   return(Minkowski_error);
}


// double calculate_performance(const Vector<double>&) const method

/// Returns which would be the Minkowski error of for an hypothetical vector of parameters.
/// It does not set that vector of parameters to the neural network.
/// @param parameters Vector of potential parameters for the neural network associated to the Minkowski error.

double MinkowskiError::calculate_performance(const Vector<double>& parameters) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   check();

   #endif

   #ifndef NDEBUG

   const unsigned size = parameters.size();

   const unsigned parameters_number = neural_network_pointer->count_parameters_number();

   if(size != parameters_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: MeanSquaredError class.\n"
             << "double calculate_performance(const Vector<double>&) const method.\n"
             << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set

   const Instances& instances = data_set_pointer->get_instances();
   const unsigned training_instances_number = instances.count_training_instances_number();

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double Minkowski_error = 0.0;

   for(unsigned i = 0; i < training_instances_number; i++)
   {
      // Input vector

      inputs = data_set_pointer->get_training_input_instance(i);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs, parameters);

      // Target vector

      targets = data_set_pointer->get_training_target_instance(i);

      // Minkowski error

      Minkowski_error += (outputs-targets).calculate_p_norm(Minkowski_parameter);
   }

   return(Minkowski_error);
}


// double calculate_generalization_performance(void) const method

/// Returns the Minkowski error of the multilayer perceptron measured on the generalization instances of the 
/// data set.

double MinkowskiError::calculate_generalization_performance(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   check();

   #endif

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   const Instances& instances = data_set_pointer->get_instances();

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double generalization_performance = 0.0;

   for(unsigned i = 0; i < generalization_instances_number; i++)
   {
      // Input vector

	  inputs = data_set_pointer->get_generalization_input_instance(i);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_generalization_target_instance(i);

      // Minkowski error

      generalization_performance = (outputs-targets).calculate_p_norm(Minkowski_parameter);
   }

   return(generalization_performance);
}


// Vector<double> calculate_gradient(void) const method

/// Returns the Minkowski error gradient of a neural network measured on a data set.
/// It uses the error back-propagation method.

Vector<double> MinkowskiError::calculate_gradient(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   check();

   #endif


   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   // Neural network stuff

   const bool has_conditions_layer = neural_network_pointer->has_conditions_layer();

   const ConditionsLayer* conditions_layer_pointer = has_conditions_layer ? neural_network_pointer->get_conditions_layer_pointer() : NULL;

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   const unsigned layers_number = multilayer_perceptron_pointer->get_layers_number();

   const unsigned neural_parameters_number = multilayer_perceptron_pointer->count_parameters_number();

   Vector< Vector< Vector<double> > > first_order_forward_propagation(2);

   Vector<double> particular_solution;
   Vector<double> homogeneous_solution;

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const unsigned training_instances_number = instances.count_training_instances_number();

   Vector<double> inputs(inputs_number);
   Vector<double> targets(outputs_number);

   // Minkowski error stuff

   Vector<double> output_gradient(outputs_number);

   Vector< Matrix<double> > layers_combination_parameters_Jacobian;

   Vector< Vector<double> > layers_inputs(layers_number);
   Vector< Vector<double> > layers_delta;

   Vector<double> point_gradient(neural_parameters_number, 0.0);

   Vector<double> gradient(neural_parameters_number, 0.0);

   for(unsigned i = 0; i < training_instances_number; i++)
   {
       // Data set

      inputs = data_set_pointer->get_training_input_instance(i);

      targets = data_set_pointer->get_training_target_instance(i);

      // Neural network

      first_order_forward_propagation = multilayer_perceptron_pointer->calculate_first_order_forward_propagation(inputs);

      const Vector< Vector<double> >& layers_activation = first_order_forward_propagation[0];
      const Vector< Vector<double> >& layers_activation_derivative = first_order_forward_propagation[1];

      layers_inputs = multilayer_perceptron_pointer->arrange_layers_input(inputs, layers_activation);

      layers_combination_parameters_Jacobian = multilayer_perceptron_pointer->calculate_layers_combination_parameters_Jacobian(layers_inputs);

      // Performance functional

      if(!has_conditions_layer)
      {
         output_gradient = (layers_activation[layers_number-1]-targets).calculate_p_norm_gradient(Minkowski_parameter);

         layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
      }
      else
      {
         particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
         homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);

         output_gradient = (particular_solution+homogeneous_solution*layers_activation[layers_number-1] - targets).calculate_pow(Minkowski_parameter-1.0)*Minkowski_parameter;

         layers_delta = calculate_layers_delta(layers_activation_derivative, homogeneous_solution, output_gradient);
      }

      point_gradient = calculate_point_gradient(layers_combination_parameters_Jacobian, layers_delta);

      gradient += point_gradient;
   }

   return(gradient);
}


// Matrix<double> calculate_Hessian(void) const method

/// @todo

Matrix<double> MinkowskiError::calculate_Hessian(void) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    check();

    #endif

   Matrix<double> Hessian;

   return(Hessian);
}


// std::string write_performance_term_type(void) const method

/// Returns a string with the name of the Minkowski error performance type, "MINKOWSKI_ERROR".

std::string MinkowskiError::write_performance_term_type(void) const
{
   return("MINKOWSKI_ERROR");
}


// tinyxml2::XMLDocument* to_XML(void) const method 

/// Serializes the Minkowski error object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this document-> 

tinyxml2::XMLDocument* MinkowskiError::to_XML(void) const
{
   std::ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   // Minkowski error

   tinyxml2::XMLElement* Minkowski_error_element = document->NewElement("MinkowskiError");

   document->InsertFirstChild(Minkowski_error_element);

   // Minkowski parameter
   {
      tinyxml2::XMLElement* Minkowski_parameter_element = document->NewElement("MinkowskiParameter");
      Minkowski_error_element->LinkEndChild(Minkowski_parameter_element);

      buffer.str("");
      buffer << Minkowski_parameter;

      tinyxml2::XMLText* Minkowski_parameter_text = document->NewText(buffer.str().c_str());
      Minkowski_parameter_element->LinkEndChild(Minkowski_parameter_text);
   }

   // Display
   {
      tinyxml2::XMLElement* display_element = document->NewElement("Display");
      Minkowski_error_element->LinkEndChild(display_element);

      buffer.str("");
      buffer << display;

      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
      display_element->LinkEndChild(display_text);
   }

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Loads a Minkowski error object from a XML document.
/// @param document TinyXML document containing the members of the object.

void MinkowskiError::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("MinkowskiError");

    if(!root_element)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: MinkowskiError class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Minkowski error element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

  // Minkowski parameter
  {
     const tinyxml2::XMLElement* element = root_element->FirstChildElement("MinkowskiParameter");

     if(element)
     {
        const double new_Minkowski_parameter = atof(element->GetText());

        try
        {
           set_Minkowski_parameter(new_Minkowski_parameter);
        }
        catch(const std::logic_error& e)
        {
           std::cout << e.what() << std::endl;
        }
     }
  }

  // Display
  {
     const tinyxml2::XMLElement* display_element = root_element->FirstChildElement("Display");

     if(display_element)
     {
        const std::string new_display_string = display_element->GetText();

        try
        {
           set_display(new_display_string != "0");
        }
        catch(const std::logic_error& e)
        {
           std::cout << e.what() << std::endl;
        }
     }
  }
}

}


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
