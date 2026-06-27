#include <cassert>
#include <cstdint>
#include <cstdio>
#include <zecs.hpp>

int main(){
  ZECS::zecs ecs = ZECS::zecs();


  
  ecs.registerComponentType<uint64_t>();
  Entity entity = ecs.createEntity();
  ecs.addEntityComponent(entity, uint64_t(1));


}
