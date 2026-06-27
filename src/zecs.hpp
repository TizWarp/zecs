#pragma once

#include <cstdint>
#include <cstdio>
#include <map>
typedef uint64_t Entity;
#include "component_pool.hpp"
#include <memory>

namespace ZECS {

static uint64_t id_count = 0;

template <typename T> uint64_t getTypeId() {
  static uint64_t id = id_count += 1;
  return id;
}

class zecs {
public:
  Entity createEntity() { return (entity_count += 1) - 1; }

  template <typename C> bool addEntityComponent(Entity entity, C component) {
    auto [has_pool, pool_ptr] = getComponentPool<C>();
    if (has_pool) {
      pool_ptr->addEntityComponent(entity, component);
      return true;
    }
    return false;
  }

  template <typename C> bool removeEntityComponent(Entity entity) {
    auto [has_pool, pool_ptr] = getComponentPool<C>();
    if (has_pool){
      pool_ptr->removeEntityComponent(entity);
      return true;
    }
    return false;
  }

  template <typename C> bool registerComponentType() {
    if (getComponentPool<C>().first)
      return false;
    component_pools[getTypeId<C>()] = std::make_unique<ComponentPool<C>>();
    return true;
  }

private:
  template <typename C> std::pair<bool, ComponentPool<C> *> getComponentPool() {
    uint64_t component_type_id = getTypeId<C>();
    if (component_pools.find(component_type_id) != component_pools.end()) {
      return std::pair(true, static_cast<ComponentPool<C> *>(
                                 component_pools[component_type_id].get()));
    }
    return std::pair(false, nullptr);
  }

  Entity entity_count = 0;

  std::map<uint64_t, std::unique_ptr<IComponentPool>> component_pools;
};
} // namespace ZECS
