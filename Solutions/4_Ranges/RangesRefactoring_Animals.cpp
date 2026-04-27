/**************************************************************************************************
*
* \file RangesRefactoring_Animals.cpp
* \brief C++ Training - Refactoring Task from Imperative to Declarative Code
*
* Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Understand the code of the 'main()' function: what does the final output print?
*
* Step 2: Improve readability by choosing better names for the variables.
*
* Step 3: Refactor the 'main()' function from an imperative to a declarative style by means
*         of C++20 ranges.
*
**************************************************************************************************/


//---- <ranges> -----------------------------------------------------------------------------------

#include <concepts>
#include <ranges>
#include <type_traits>

// Simplified implementation of C++23 'std::ranges::to<>()'
template< template<typename...> class C >
struct to_range
{};

template< template<typename...> class C, std::ranges::input_range R >
constexpr auto to( R&& range )
{
   using T = std::ranges::range_value_t<R>;
   static_assert( !std::is_reference_v<T> );
   return C<T>( std::ranges::begin(range), std::ranges::end(range) );
}

template< template<typename...> class C >
constexpr auto to()
{
   return to_range<C>{};
}

template< std::ranges::input_range R, template<typename...> class C >
constexpr auto operator|( R&& range, to_range<C> )
{
   return to<C>(range);
}


//---- <Animal.h> ---------------------------------------------------------------------------------

#include <iomanip>
#include <ostream>
#include <string>

enum class AnimalType
{
   mammal,
   reptile,
   insect
};

std::ostream& operator<<( std::ostream& os, AnimalType type )
{
   switch( type )
   {
      case AnimalType::mammal:
         os << "mammal";
         break;
      case AnimalType::reptile:
         os << "reptile";
         break;
      case AnimalType::insect:
         os << "insect";
         break;
   }

   return os;
}

struct Animal
{
   std::string name;
   double size{};      // size in cm
   double weight{};    // weight in kg
   double speed{};     // speed in km/h
   AnimalType type{};  // type of animal

   friend std::ostream& operator<<( std::ostream& os, Animal const& animal )
   {
      os << std::setw(24) << std::left << animal.name
         << ": size=" << std::setw(5) << std::right << animal.size
         << ", weight=" << std::setw(7)  << std::right << animal.weight
         << ", speed=" << std::setw(4)  << std::right << animal.speed
         << ", type=" << std::setw(7) << std::left << animal.type;
      return os;

      // C++20 format solution
      /*
      os << std::format( "{:<24}: size={:>5}, weight={:>7}, speed={:>4}, type={:<7}"
                       , animal.name, animal.size, animal.weight, animal.speed, animal.type );
      return os;
      */

      // C++23 'println()' solution
      /*
      std::println( "{:<24}: size={:>5}, weight={:>7}, speed={:>4}, type={:<7}"
                  , animal.name, animal.size, animal.weight, animal.speed, animal.type );
      return os;
      */
   }
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using namespace std::string_literals;


auto is_mammal()
{
   return []( Animal const& animal )
   {
      return animal.type == AnimalType::mammal;
   };
}

auto is_insect()
{
   return []( Animal const& animal )
   {
      return animal.type == AnimalType::insect;
   };
}

auto is_smaller()
{
   return []( Animal const& animal1, Animal const& animal2 )
   {
      return animal1.size < animal2.size;
   };
}

auto fold_animal_by_speed()
{
   return []( double accu, Animal const& animal )
   {
      return accu + animal.speed;
   };
}


int main()
{
   std::map<std::string,std::vector<Animal>> books
      { std::make_pair( "Fantastic Animals and Where to Find Them"s,
         std::vector{ Animal{ "Lion", 250.0, 270.0, 80.0, AnimalType::mammal }
                    , Animal{ "King Cobra", 550.0, 20.0, 18.0, AnimalType::reptile }
                    , Animal{ "Housefly", 0.8, 0.0001, 10.0, AnimalType::insect }
                    , Animal{ "Giant Kangaroo", 140.0, 55.0, 80.0, AnimalType::mammal }
                    , Animal{ "Mosquito", 0.5, 0.000002, 2.5, AnimalType::insect }
                    , Animal{ "Polar Bear", 280.0, 1000.0, 40.0, AnimalType::mammal } } )
      , std::make_pair( "Animals Around the World"s,
         std::vector{ Animal{ "Dragonfly", 8.0, 0.001, 50.0, AnimalType::insect }
                    , Animal{ "Komodo Dragon", 304.0, 91.0, 20.0, AnimalType::reptile }
                    , Animal{ "Great Anaconda", 900.0, 250.0, 27.0, AnimalType::reptile }
                    , Animal{ "Red Garden Ant", 0.6, 0.00001, 0.9, AnimalType::insect }
                    , Animal{ "Blue Whale", 33000.0, 200'000.0, 48.0, AnimalType::mammal } } )
      , std::make_pair( "Winners from the Animal World",
         std::vector{ Animal{ "Gorilla", 180.0, 220.0, 35.0, AnimalType::mammal }
                    , Animal{ "Nile Crocodile", 650.0, 1000.0, 0.5, AnimalType::reptile }
                    , Animal{ "Bee", 1.8, 0.0003, 28.0, AnimalType::insect }
                    , Animal{ "Giraffe", 600.0, 1600.0, 55.0, AnimalType::mammal }
                    , Animal{ "Galapagos Giant Tortoise", 180.0, 300.0, 0.5, AnimalType::reptile }
                    , Animal{ "African Elephant", 750.0, 6000.0, 40.0, AnimalType::mammal } } )
      };


   // Manual solution (imperative style)

   std::vector<Animal>::const_iterator const default_iterator{};
   std::vector<Animal>::const_iterator biggest_mammal{ default_iterator };
   std::vector<Animal>::const_iterator smallest_insect{ default_iterator };
   double average_speed{};
   size_t number_of_animals{};

   for( auto const& book : books )
   {
      auto const& animals = book.second;
      for( auto animal=animals.begin(); animal!=animals.end(); ++animal )
      {
         if( animal->type == AnimalType::mammal ) {
            if( biggest_mammal == default_iterator or biggest_mammal->size < animal->size ) {
               biggest_mammal = animal;
            }
         }

         if( animal->type == AnimalType::insect ) {
            if( smallest_insect == default_iterator or animal->size < smallest_insect->size ) {
               smallest_insect = animal;
            }
         }

         average_speed += animal->speed;
         ++number_of_animals;
      }
   }

   average_speed /= number_of_animals;

   if( biggest_mammal != default_iterator ) {
      std::cout << "The biggest mammal is the " << biggest_mammal->name << '\n';
   }

   if( smallest_insect != default_iterator ) {
      std::cout << "The smallest insect is the " << smallest_insect->name << '\n';
   }

   std::cout << "Average speed is " << average_speed << '\n';



   // C++17 algorithms solution (declarative style)
   /*
   std::vector<Animal> mammals{};
   std::vector<Animal> insects{};
   double average_speed{};
   std::size_t size{};

   for( auto const& book : books )
   {
      auto const& animals = book.second;
      std::copy_if( begin(animals), end(animals), std::back_inserter(mammals), is_mammal() );
      std::copy_if( begin(animals), end(animals), std::back_inserter(insects), is_insect() );
      average_speed += std::accumulate( begin(animals), end(animals), double{}, fold_animal_by_speed() );
      size += book.second.size();
   }

   auto biggest_mammal = std::ranges::max_element( mammals, is_smaller() );
   auto smallest_insect = std::ranges::min_element( insects, is_smaller() );
   average_speed /= size;

   if( biggest_mammal != std::end(mammals) ) {
      std::cout << "The biggest mammal is the " << biggest_mammal->name << '\n';
   }

   if( smallest_insect != std::end(insects) ) {
      std::cout << "The smallest insect is the " << smallest_insect->name << '\n';
   }

   std::cout << "Average speed is " << average_speed << '\n';
   */


   // C++20 ranges solution (declarative style)
   /*
   auto animal_view = books | std::views::values | std::views::join;
   auto mammals = animal_view | std::views::filter( is_mammal() );
   auto insects = animal_view | std::views::filter( is_insect() );

   auto sizes = books
              | std::views::values
              | std::views::transform( [](auto const& animals){ return animals.size(); } );

   auto const size = std::ranges::fold_left( sizes, 0U, std::plus{} );

   auto biggest_mammal = std::max_element( mammals.begin(), mammals.end(), is_smaller() );
   auto smallest_insect = std::min_element( insects.begin(), insects.end(), is_smaller() );
   auto average_speed = std::ranges::fold_left( animal_view, double{}, fold_animal_by_speed() ) / size;

   if( biggest_mammal != std::end(mammals) ) {
      std::cout << "The biggest mammal is the " << biggest_mammal->name << '\n';
   }

   if( smallest_insect != std::end(insects) ) {
      std::cout << "The smallest insect is the " << smallest_insect->name << '\n';
   }

   std::cout << "Average speed is " << average_speed << '\n';
   */


   return EXIT_SUCCESS;
}
