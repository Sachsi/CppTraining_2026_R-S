/**************************************************************************************************
*
* \file Prototype.cpp
* \brief C++ Training - Example for the Prototype Design Pattern
*
* Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Discuss the advantages and disadvantages of the given implementation of the classic
*       Prototype design pattern.
*
**************************************************************************************************/


//---- <Animal.h> ---------------------------------------------------------------------------------

#include <memory>

class Animal
{
 public:
   virtual ~Animal() = default;
   virtual void make_sound() const = 0;
   virtual std::unique_ptr<Animal> clone() const = 0;
};


//---- <Sheep.h> ----------------------------------------------------------------------------------

//#include <Animal.h>
#include <iostream>

class Sheep : public Animal
{
 public:
   void make_sound() const override
   {
      std::cout << " Sheep::make_sound(): baa!\n";
   }

   std::unique_ptr<Animal> clone() const override
   {
      std::cout << " Sheep::clone()\n";
      return std::make_unique<Sheep>(*this);
   }
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Sheep.h>
#include <cstdlib>
#include <memory>

int main()
{
   // Creating the one and only Dolly
   std::unique_ptr<Animal> sheep{ std::make_unique<Sheep>() };
   sheep->make_sound();

   // Cloning Dolly
   auto cloned_sheep{ sheep->clone() };
   cloned_sheep->make_sound();

   return EXIT_SUCCESS;
}
