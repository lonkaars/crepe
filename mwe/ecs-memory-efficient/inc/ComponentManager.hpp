	
template<typename... Args>
void ComponentManager::addSpriteComponent(Args&&... args) {
	mSpriteContainer.pushBack(std::forward<Args>(args)...);
}

template<typename... Args>
void ComponentManager::addRigidbodyComponent(Args&&... args) {
	mRigidbodyContainer.pushBack(std::forward<Args>(args)...);
}

template<typename... Args>
void ComponentManager::addColiderComponent(Args&&... args){
	mColiderContainer.pushBack(std::forward<Args>(args)...);
}
