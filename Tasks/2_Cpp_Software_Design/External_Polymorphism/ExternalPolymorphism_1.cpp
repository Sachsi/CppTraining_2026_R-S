/**************************************************************************************************
*
* \file ExternalPolymorphism_1.cpp
* \brief C++ Training - Programming Task for the External Polymorphism Design Pattern
*
* Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Refactor the given 'Shape' hierarchy by means of the External Polymorphism design
*         pattern to extract the 'draw()' operation from shapes.
*
* Step 2: Switch from one to another graphics library. Discuss the feasibility of the change:
*         how easy is the change? How many pieces of code on which level of the architecture
*         have to be touched?
*
* Task 3: Add the new feature to serialize shapes by means of the 'FastSerialization' library.
*         Observe how well the new code can be integrated and how many new dependencies are
*         created.
*
**************************************************************************************************/


//---- <GraphicsLibrary.h> (external) -------------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

namespace gl {

enum class Color
{
   red   = 0xFF0000,
   green = 0x00FF00,
   blue  = 0x0000FF
};

std::string to_string( Color color )
{
   switch( color ) {
      case Color::red:
         return "red (0xFF0000)";
      case Color::green:
         return "green (0x00FF00)";
      case Color::blue:
         return "blue (0x0000FF)";
      default:
         return "unknown";
   }
}

} // namespace gl


//---- <GraphicsFramework.h> (external) -----------------------------------------------------------

#include <sstream>
#include <string>
// ... and many more graphics-related headers

namespace gf {

enum class Color : int
{
   yellow  = 0xFFFF00,
   cyan    = 0x00FFFF,
   magenta = 0xFF00FF
};

using Brightness = unsigned int;

std::string print_string( Color color, Brightness brightness )
{
   std::ostringstream oss;

   switch( color ) {
      case Color::yellow:
         oss << "yellow (0xFFFF00)";
         break;
      case Color::cyan:
         oss << "cyan (0x00FFFF)";
         break;
      case Color::magenta:
         oss << "magenta (0xFF00FF)";
         break;
      default:
         oss << "unknown";
         break;
   }

   oss << ", brightness=" << brightness;

   return oss.str();
}

} // namespace gf


//---- <FastSerialization.h> (external) -----------------------------------------------------------

#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>
// ... and many more serialization-related headers

namespace fs {

class Serializer
{
 public:
   std::string to_string() const
   {
      return std::string( buffer_.data(), buffer_.size() );
   }

 private:
   std::vector<char> buffer_;

   template< typename T, typename = std::enable_if_t< std::is_arithmetic_v<T> > >
   //   requires std::is_arithmetic_v<T>  // C++20 concept
   friend Serializer& operator<<( Serializer& serializer, T value )
   {
      size_t const old_size = serializer.buffer_.size();
      serializer.buffer_.resize( old_size + sizeof(T) );

      auto* data = serializer.buffer_.data() + old_size;
      ::new (data) T{value};

      return serializer;
   }
};

} // namespace fs


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

//removed base class of shape


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Circle
{
 public:
   explicit Circle( double radius)
      : radius_{ radius }
   {}

   double radius() const { return radius_; }
   Point  center() const { return center_; }

   void draw() const;

 private:
   double radius_{};
   Point center_{};
};


//---- <Circle.cpp> -------------------------------------------------------------------------------

//#include <Circle.h>
#include <iostream>

void Circle::draw() const
{
   std::cout << "circle: radius=" << radius_;
             //<< ", color = " << gl::to_string(color_) << '\n';
}


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Square
{
 public:
   explicit Square( double side)
      : side_{ side }
   {}

   double side() const { return side_; }
   Point  center() const { return center_; }

   void draw() const;

 private:
   double side_{};
   Point center_{};
};


//---- <Square.cpp> -------------------------------------------------------------------------------

//#include <Square.h>
#include <iostream>

void Square::draw() const
{
   std::cout << "square: side=" << side_;
            // << ", color = " << gl::to_string(GLDrawer{ gl::Color::green }) << '\n';
}


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <Draw.h> -----------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>

void free_draw( Circle const& circle, gl::Color color );
void free_draw( Square const& square, gl::Color color );


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
#include <iostream>

void free_draw( Circle const& circle, gl::Color color )
{
   std::cout << "circle: radius=" << circle.radius()
             << ", color = " << gl::to_string(color) << '\n';
}

void free_draw( Square const& square, gl::Color color )
{
   std::cout << "square: side=" << square.side()
             << ", color = " << gl::to_string(color) << '\n';
}


//---- <GLDrawer.h> -------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

//removed glDrawer class because of own free_drawer function
class GLDrawer
{
 public:
   explicit GLDrawer( gl::Color color ) : color_{color} {}

   void operator()( Circle const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   void operator()( Square const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << gl::to_string(color_) << '\n';
   }

 private:
   gl::Color color_{};
};

//---- <ShapeConcept.h> ---------------------------------------------------------------------------

// TODO: Create an external hierarchy for shapes that represents the polymorphic behavior
//       of shapes.

// 1. Introduce the ShapeConcept hierarchy (incl. the "ShapeModel" class)
// 2. Compiling and "test" 
// 3. Switch from 'Shape' to 'ShapeConcept' (update main and all other places where 'Shape' is used)
// 4. compile and "test" again
// 5. Remove the old 'Shape' hierarchy (incl. the "ShapeModel" class)
// 6. compile and "test" again
// 7.

class Shape
{
   public:
      template <typename ShapeT, typename DrawStrategy>
      Shape( ShapeT shape, DrawStrategy drawer )
      : model_{ std::make_unique<ShapeModel<ShapeT, DrawStrategy>>( shape, drawer ) }
      {}

      void draw() const
      {
         model_->draw();
      }

   private:
      class ShapeConcept
      {
         public:
            virtual ~ShapeConcept() = default;
            virtual void draw() const = 0;
      };

      template <typename ShapeT, typename DrawStrategy>
      class ShapeModel : public ShapeConcept
      {
         public:
            explicit ShapeModel( ShapeT shape, DrawStrategy drawer )
            : shape_{shape},
            drawer_{drawer}
            {}
            void draw() const override
            {
               drawer_( shape_);
            }
         private:
            ShapeT shape_;
            DrawStrategy drawer_;
      };

      std::unique_ptr< ShapeConcept > model_; // Pointer - to - IMPLementation (PIMPL) idiom
};

//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector<Shape>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape.draw();
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>


int main()
{
   Shapes shapes{};

   shapes.emplace_back( Shape( Circle{2.3}, GLDrawer{ gl::Color::red } ) );
   shapes.emplace_back( Shape( Square{1.2}, GLDrawer{ gl::Color::green } ) );
   shapes.emplace_back( Shape( Circle{4.5}, GLDrawer{ gl::Color::blue } ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

