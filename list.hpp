#ifndef LIST_H
#define LIST_H 1

template<class T>
struct Item {
    T data;
    struct Item * next;
    Item(T pdata = T(),struct Item* pNext = nullptr){
        data = pdata;
        next = pNext;
    }
};

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T*, int);
    LinkedList(const LinkedList <T> & list);
    T GetFirst() const;
    T GetLast() const;
    T Get(int) const;
    LinkedList<T> * GetSubList(int,int);
    int GetLenght() const;
    void Append(const T&);
    void Prepend(T );
    void InsertAt(T , int);
    void Set(int,T);
    LinkedList<T>* Concat(LinkedList<T> *);
    ~LinkedList();
protected:
    Item<T> * getHead();
    Item<T> * getTail();
private:
    Item<T> * head;
    Item<T> * tail;
    int len;
};


template<class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    len = 0;
}

template<class T>
LinkedList<T>::LinkedList(T* item, int count){
    head = new Item<T>(item[0]);
    Item<T> * prev_ptr = this->head;
    for (int i = 1; i < count; i++){
        Item<T> * ptr = new Item<T>(item[i]);
        prev_ptr->next = ptr;
        prev_ptr = ptr;
    }
    tail = prev_ptr;
    len = count;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList <T> & list){
    Item<T> * ptr = list.head;
    len = 0;
    head = nullptr;
    tail = nullptr;
    while(ptr) {
        Append(ptr->data);
        ptr = ptr->next;
    }
    len = list.len;
}

template<class T>
void LinkedList<T>::Append(const T& item){
    
    Item<T> * ptr = new Item<T>(item);
    if(len == 0) {
        head = ptr;
        tail = ptr;
    }else{
        tail->next = ptr;
        tail = ptr;
    }
    len++;
}

template<class T>
void LinkedList<T>::Prepend(T item){
    Item<T> * ptr = new Item<T>(item, head);
    head = ptr;
    len++;
}

template<class T>
T LinkedList<T>::GetFirst() const{
    return head->data;
}

template<class T>
T LinkedList<T>::GetLast() const{
    return tail->data;
}

template<class T>
int LinkedList<T>::GetLenght() const{
    return len;
}

template<class T>
T LinkedList<T>::Get(int index) const{
    if(index >= len){
        throw "IndexOutOfRange";
    }
    Item<T> * ptr  = head;
    for(int i = 0; i < index; i++){
        ptr = ptr->next;
    }
    return ptr->data;
}

template <class T>
LinkedList<T>::~LinkedList(){
    #ifdef DEBUG 
        std::cerr << "Destroy Object type LinkedList<T>" << std::endl;
    #endif


    Item<T> * ptr = head;
    while(ptr) {
        Item<T> * prev_ptr = ptr;
        ptr = ptr->next;
        delete (prev_ptr);
    } 

}

template<class T>
void LinkedList<T>::InsertAt(T item, int count){
    if (count == 0) {
        Prepend(item);
        return;
    } else if(count == len){
        Append(item);
    }
    Item<T> * ptr = head;
    Item<T> * prev_ptr = nullptr;
    int amont = 0;
    while(ptr && amont < count){
        prev_ptr = ptr;
        ptr = head->next;
    }
    if(ptr == nullptr) {
        throw "IndexOutOfRange";
    }
    Item<T> * elem = new Item<T>(item, ptr);
    prev_ptr->next = elem;
    len++;
}

template<class T>
Item<T> * LinkedList<T>::getHead(){
    return head;
}

template<class T>
Item<T> * LinkedList<T>::getTail(){
    return tail;
}

template<class T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> * item) {
    tail -> next = item->getHead();
    len += item->GetLenght();
    return this;
}

template<class T>
LinkedList<T> * LinkedList<T>::GetSubList(int start,int end){
    if(start < 0 or start >= len or end >= len or end < 0 or start > end) {
        throw "IndexOutOfRange";
        return nullptr;
    }
    LinkedList<T> * elem = new LinkedList<T>();
    Item<T> * startptr = head;
    Item<T> * endptr = nullptr;
    for(int i = 0; i < start; i++){
        startptr = startptr->next;
    }
    endptr = startptr;
    for(int i = 0; i < end - start; i++){
        endptr = endptr->next;
    }
    elem->head = startptr;
    elem->tail = endptr;

    elem->len = end - start + 1;

    return elem; 
}

template<class T>
void LinkedList<T>::Set(int ind,T item){
    if(ind < 0 or ind > GetLenght()){
        throw "IndexOutOfRange";
    }
    Item<T> * ptr = head;
    for(int i = 0; i < ind; i++) {
        ptr = ptr->next;
    }
    ptr->data = item;
}

#endif