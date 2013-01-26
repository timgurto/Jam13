// (C) 2013 Tim Gurto

#include "Entity.h"
#include "Surface.h"
#include "util.h"

namespace Game {

//The collision box for this object
   SDL_Rect Entity::getCollisionBox() const{
      SDL_Rect r = this->collisionRect();
      r.x += pixels_t(this->loc_.x + .5);
      r.y += pixels_t(this->loc_.y + .5);
      return r;
   }

   const Location &Entity::getLoc() const{
      return loc_;
   }

   bool Entity::collidesWithEntity(const Entity &rhs) const{
      return collision(getCollisionBox(), rhs.getCollisionBox());
   }

   bool Entity::collidesWithPoint(const Point &rhs) const{
      return collision(getCollisionBox(), rhs);
   }

   void Entity::draw(Point offset, Surface &surface) const{
	  if (image()) {
	     SDL_Rect rect = drawRect() + offset;
         image()->draw(surface, &rect);
	  }
	  const bool drawDebug = DEBUG;
	  if (drawDebug) {
		  SDL_Rect locRect = makeRect(-5, -5, 5, 5);
		  locRect.x = loc_.x;
		  locRect.y = loc_.y;
		  SDL_Color color = BLACK;
          surface.fill(color, &locRect);
	  }
   }

   //comparison, for sorting/sets/maps.  Compares y co-ordinate of location.
   bool lessThan(const Entity &lhs, const Entity &rhs){
      return lhs.loc_.y < rhs.loc_.y;
   }

} //namespace Game