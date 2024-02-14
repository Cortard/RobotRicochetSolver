#ifndef RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H
#define RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H

/**
 * @brief This class is a wrapper for the void* type
 * @note This class is entirely in the header file because it is a template class
 */
class MultipleTypePointer {
private:
    /**
     * @brief The pointer to the data
     */
    void* data;
public:
    /**
     * @brief Initialize the class
     */
    [[maybe_unused]] MultipleTypePointer() {
        this->data = nullptr;
    }

    /**
     * @brief Initialize the class with the given data
     * @param data The data to initialize the class with
     */
    [[maybe_unused]] explicit MultipleTypePointer(void* data){
        this->data = data;
    }

    /**
     * @brief Initialize the class with the given data
     * @tparam T The type of the data
     * @param data The data to initialize the class with
     */
    template<typename T>
    [[maybe_unused]] explicit MultipleTypePointer(T* data){
        this->data = static_cast<T*>(data);
    }

    /**
     * @brief Copy constructor
     * @param other The other object to copy
     */
    template<typename T>
    [[maybe_unused]] explicit MultipleTypePointer(MultipleTypePointer& other) {
        this->data = static_cast<T*>(other.data);
    }

    /**
     * @brief Get the stored data
     * @tparam T The type of the data
     * @return The data
     */
    template<typename T>
    [[nodiscard]] T* get(){
        return static_cast<T*>(data);
    }

    /**
     * @brief Set the pointer to the given data, forgetting the old data
     * @tparam T The type of the data
     * @param newData The new data
     */
    template<typename T>
    void set(T* newData){
        this->data = static_cast<T*>(newData);
    }

    /**
     * @brief Replace the old data with the new data, deleting the old data
     * @tparam oldT The type of the old data
     * @tparam T The type of the new data
     * @param newData The new data
     */
    template<typename oldT, typename T>
    void replace(T* newData){
        this->clear<oldT>();
        this->data = static_cast<T*>(newData);
    }

    /**
     * @brief Clear the data
     * @tparam T The type of the data
     */
    template<typename T>
    void clear(){
        delete static_cast<T*>(data);
        this->data = nullptr;
    }
};

#endif //RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H
