template <typename T>
ContiguousContainer<T>::ContiguousContainer() : mSize(0),
												mCapacity(10) {
	// Allocate memory for 10 objects initially
	mData = static_cast<T *>(malloc(mCapacity * sizeof(T)));
	if (!mData) {
		throw std::bad_alloc();
	}
}

template <typename T>
ContiguousContainer<T>::~ContiguousContainer() {
	// Destroy all constructed objects
	for (size_t i = 0; i < mSize; ++i) {
		mData[i].~T();
	}
	// Free the allocated memory
	free(mData);
}

template <typename T>
template <typename... Args>
void ContiguousContainer<T>::pushBack(Args &&... args) {
	if (mSize == mCapacity) {
		// Double the capacity if the container is full
		resize(mCapacity * 2);
	}
	// Use placement new with perfect forwarding to construct the object in place
	new (mData + mSize) T(std::forward<Args>(args)...);
	++mSize;
}

template <typename T>
void ContiguousContainer<T>::popBack() {
	if (mSize > 0) {
		--mSize;
		// Explicitly call the destructor
		mData[mSize].~T();
	}
}

template <typename T>
T & ContiguousContainer<T>::operator[](size_t index) {
	if (index >= mSize) {
		throw std::out_of_range("Index out of range");
	}
	return mData[index];
}

template <typename T>
size_t ContiguousContainer<T>::getSize() const {
	return mSize;
}

// Function that returns a vector of references to all stored objects
template <typename T>
std::vector<std::reference_wrapper<T>>
ContiguousContainer<T>::getAllReferences() {
	std::vector<std::reference_wrapper<T>> references;
	references.reserve(mSize); // Reserve space to avoid reallocation
	for (size_t i = 0; i < mSize; ++i) {
		references.push_back(std::ref(mData[i]));
	}
	return references;
}

template <typename T>
void ContiguousContainer<T>::resize(size_t new_capacity) {
	// Allocate new memory block with the updated capacity
	T * new_data = static_cast<T *>(malloc(new_capacity * sizeof(T)));
	if (!new_data) {
		throw std::bad_alloc();
	}

	// Move or copy existing objects to the new memory block
	for (size_t i = 0; i < mSize; ++i) {
		new (new_data + i) T(std::move(mData[i])); // Move the objects
		mData[i].~T(); // Call the destructor for the old object
	}

	// Free the old memory block
	free(mData);
	mData = new_data;
	mCapacity = new_capacity;
}
