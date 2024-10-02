
template <typename T, typename... Args>
void ComponentManager::AddComponent(std::uint32_t id, Args&&... args) {
    std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

    if (mComponents.find(type) == mComponents.end()) {	//Check if this component type is already in the unordered_map<>
        mComponents[type] = std::vector<std::vector<std::unique_ptr<Component>>>();	//If not, create a new (empty) vector<> of unique_ptr<Component>
    }

    if (id >= mComponents[type].size()) {	//Resize the vector<> if the id is greater than the current size
        mComponents[type].resize(id + 1);	//Initialize new slots to nullptr (resize does this automatically)
    }

    mComponents[type][id].push_back(std::make_unique<T>(std::forward<Args>(args)...));	//Create a new component of type T using perfect forwarding and store its unique_ptr in the correct vector
}

template <typename T>
std::vector<std::reference_wrapper<T>> ComponentManager::GetComponentsOfID(std::uint32_t id) {
    std::type_index type = typeid(T);

	std::vector<std::reference_wrapper<T>> componentVector;

    if (mComponents.find(type) != mComponents.end()) {

        const auto& componentArray = mComponents[type];

        if (id < componentArray.size()) {
            for (const auto& componentPtr : componentArray[id]) {
                // Use static_cast instead of dynamic_cast
                T* castedComponent = static_cast<T*>(componentPtr.get());
                if (castedComponent) { // Ensure cast was successful
                    componentVector.push_back(*castedComponent); // Add the raw pointer to the vector
                }
            }
        }
    }

    return componentVector; // Return empty vector if not found
}

/*// GetAllComponentIDs implementation
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
}*/
