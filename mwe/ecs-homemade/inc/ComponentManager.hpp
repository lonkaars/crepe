// AddComponent implementation
template <typename T>
void ComponentManager::AddComponent(T* component, std::uint32_t id) {
    std::type_index type = typeid(T);
    if (mComponents.find(type) == mComponents.end()) {
        mComponents[type] = std::vector<Component*>();
    }
    // Resize the vector if the id is greater than current size
    if (id >= mComponents[type].size()) {
        mComponents[type].resize(id + 1, nullptr); // Initialize new slots to nullptr
    }
    mComponents[type][id] = component; // Store the raw pointer
}

// GetComponent implementation
template <typename T>
T* ComponentManager::GetComponent(std::uint32_t id) {
    std::type_index type = typeid(T);
    if (mComponents.find(type) != mComponents.end()) {
        auto& componentArray = mComponents[type];
        if (id < componentArray.size()) {
            return static_cast<T*>(componentArray[id]); // Cast to the correct type
        }
    }
    return nullptr; // Return nullptr if not found
}

// GetAllComponentIDs implementation
template <typename T>
std::vector<std::uint32_t> ComponentManager::GetAllComponentIDs() {
    std::type_index type = typeid(T);
    std::vector<std::uint32_t> ids;
    if (mComponents.find(type) != mComponents.end()) {
        const auto& componentArray = mComponents[type];
        for (std::uint32_t id = 0; id < componentArray.size(); ++id) {
            if (componentArray[id] != nullptr) {
                ids.push_back(id); // Collect IDs of non-null components
            }
        }
    }
    return ids;
}

// GetAllComponentPointer implementation
template <typename T>
std::vector<T*> ComponentManager::GetAllComponentPointer() {
    std::type_index type = typeid(T);
    std::vector<T*> pointers;
    if (mComponents.find(type) != mComponents.end()) {
        const auto& componentArray = mComponents[type];
        for (const auto& component : componentArray) {
            if (component != nullptr) {
                pointers.push_back(static_cast<T*>(component)); // Cast to the correct type
            }
        }
    }
    return pointers;
}
