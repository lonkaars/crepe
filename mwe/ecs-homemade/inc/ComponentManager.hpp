
template <typename T, typename... Args>
void ComponentManager::AddComponent(std::uint32_t id, Args&&... args) {
    std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

    if (mComponents.find(type) == mComponents.end()) {	//Check if this component type is already in the unordered_map<>
        mComponents[type] = std::vector<std::vector<std::unique_ptr<Component>>>();	//If not, create a new (empty) vector<> of vector<unique_ptr<Component>>
    }

    if (id >= mComponents[type].size()) {	//Resize the vector<> if the id is greater than the current size
        mComponents[type].resize(id + 1);	//Initialize new slots to nullptr (resize does automatically init to nullptr)
    }

    mComponents[type][id].push_back(std::make_unique<T>(std::forward<Args>(args)...));	//Create a new component of type T using perfect forwarding and store its unique_ptr in the vector<>
}

template <typename T>
void ComponentManager::DeleteComponentsById(std::uint32_t id) {
	std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

	
}

template <typename T>
void ComponentManager::DeleteComponents() {
	std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

	if (mComponents.find(type) != mComponents.end()) {	//Find the type (in the unordered_map<>)
		mComponents[type].clear();	//Clear the whole vector<> of this specific type
	}
}

template <typename T>
std::vector<std::reference_wrapper<T>> ComponentManager::GetComponentsByID(std::uint32_t id) const {
    std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

	std::vector<std::reference_wrapper<T>> componentVector;	//Create an empty vector<>

    if (mComponents.find(type) != mComponents.end()) {	//Find the type (in the unordered_map<>)

        const std::vector<std::vector<std::unique_ptr<Component>>>& componentArray = mComponents.at(type);	//Get the correct vector<>

        if (id < componentArray.size()) {	//Make sure that the id (that we are looking for) is within the boundaries of the vector<>
            for (const std::unique_ptr<Component>& componentPtr : componentArray[id]) {	//Loop trough the whole vector<>
                T* castedComponent = static_cast<T*>(componentPtr.get());	//Cast the unique_ptr to a raw pointer

                if (castedComponent) {	//Ensure that the cast was successful
                    componentVector.push_back(*castedComponent); //Add the dereferenced raw pointer to the vector<>
                }
            }
        }
    }

    return componentVector; //Return the vector<>
}

template <typename T>
std::vector<std::pair<std::reference_wrapper<T>, std::uint32_t>> ComponentManager::GetComponentsByType() const {
    std::type_index type = typeid(T);	//Determine the type of T (this is used as the key of the unordered_map<>)

    std::vector<std::pair<std::reference_wrapper<T>, std::uint32_t>> componentVector;	//Create an empty vector<>
	std::uint32_t id = 0;	//Set the id to 0 (the id will also be stored in the returned vector<>)

    if (mComponents.find(type) != mComponents.end()) {	//Find the type (in the unordered_map<>)

        const std::vector<std::vector<std::unique_ptr<Component>>>& componentArray = mComponents.at(type);	//Get the correct vector<>

        for (const std::vector<std::unique_ptr<Component>>& component : componentArray) {	//Loop through the whole vector<>
            for (const std::unique_ptr<Component>& componentPtr : component) {	//Loop trough the whole vector<>
                T* castedComponent = static_cast<T*>(componentPtr.get());	//Cast the unique_ptr to a raw pointer

                if (castedComponent) {	//Ensure that the cast was successful
                    componentVector.push_back(std::make_pair(std::ref(*castedComponent), id));	//Pair the dereferenced raw pointer and the id and add it to the vector<>
                }
            }

			++id;	//Increase the id (the id will also be stored in the returned vector<>)
        }
    }

    return componentVector;	//Return the vector<>
}
