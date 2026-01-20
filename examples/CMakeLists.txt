cmake_minimum_required(VERSION 3.15)

# Abstraction examples
add_executable(abstraction_01_basic 01-abstraction/01_basic_class.cpp)
add_executable(abstraction_02_attributes 01-abstraction/02_attributes_and_methods.cpp)
add_executable(abstraction_03_abstract 01-abstraction/03_abstract_classes.cpp)

# Encapsulation examples
add_executable(encapsulation_01_bank 02-encapsulation/01_bank_account.cpp)
add_executable(encapsulation_02_access 02-encapsulation/02_access_modifiers.cpp)

# Inheritance examples
add_executable(inheritance_01_basic 03-inheritance/01_basic_inheritance.cpp)
add_executable(inheritance_02_virtual 03-inheritance/02_virtual_functions.cpp)
add_executable(inheritance_03_abstract 03-inheritance/03_abstract_classes.cpp)

# Polymorphism examples
add_executable(polymorphism_01_animals 04-polymorphism/01_animal_example.cpp)
add_executable(polymorphism_02_payment 04-polymorphism/02_payment_processors.cpp)
add_executable(polymorphism_03_vtables 04-polymorphism/03_vtable_explanation.cpp)
