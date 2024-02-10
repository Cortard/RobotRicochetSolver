#ifndef RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H
#define RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H

class MultipleTypePointer {
private:
    void* data;
public:
    [[maybe_unused]] MultipleTypePointer() {
        this->data = nullptr;
    }

    template<typename T>
    [[maybe_unused]] explicit MultipleTypePointer(T* data){
        this->data = static_cast<T*>(data);
    }

    template<typename T>
    [[maybe_unused]] explicit MultipleTypePointer(MultipleTypePointer& other) {
        this->data = static_cast<T*>(other.data);
    }

    template<typename T>
    [[nodiscard]] T* get(){
        return static_cast<T*>(data);
    }

    template<typename T>
    void set(T* newData){
        this->data = static_cast<T*>(newData);
    }

    template<typename oldT, typename T>
    void replace(T* newData){
        this->clear<oldT>();
        this->data = static_cast<T*>(newData);
    }

    template<typename T>
    void clear(){
        delete static_cast<T*>(data);
        this->data = nullptr;
    }
};

#endif //RICOCHETSOCKETSSERVER_MULTIPLE_TYPE_POINTER_H
