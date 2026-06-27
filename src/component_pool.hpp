#pragma once

#include <cstdint>
#include <vector>
namespace ZECS {

typedef uint64_t Entity;

class IComponentPool {
public:
  virtual ~IComponentPool() {};
  virtual void removeEntityComponent(Entity entity) = 0;
  virtual bool hasEntity(Entity entity) = 0;
};

template <typename C> class ComponentPool : public IComponentPool {
public:
  ComponentPool() {
    entity_index = {};
    component_vec = {};
  }

  bool hasEntity(Entity entity) override {
    return getEntityIndex(entity) != -1;
  }

  void addEntityComponent(Entity entity, C component) {
    if (hasEntity(entity))
      return;
    entity_index.push_back(entity);
    component_vec.push_back(component);
  }

  void removeEntityComponent(Entity entity) override {
    int index = getEntityIndex(entity);
    if (index == -1)
      return;
    int last_index = entity_index.size() - 1;
    entity_index[index] = entity_index[last_index];
    component_vec[index] = entity_index[last_index];
    entity_index.pop_back();
    component_vec.pop_back();
  }

  C *getEntityComponent(Entity entity) {
    int index = getEntityIndex(entity);
    if (index == -1)
      return nullptr;
    return &component_vec[index];
  }

private:
  int getEntityIndex(Entity entity){
    for (int i = 0; i < entity_index.size(); i++) {
      if (entity_index[i] == entity) {
        return i;
      }
    }
    return -1;
  }

  std::vector<Entity> entity_index;
  std::vector<C> component_vec;
};
} // namespace ZECS
