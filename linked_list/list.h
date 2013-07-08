#ifndef H_LISTA
#define H_LISTA

#include <cstdlib>
#include <cassert>

/* Estas 3 clases, Lista, IteradorLista y Nodo representan un contenedor de tipo
lista simplemente enlazada con templates */

////////////////////////////////////////////////////////////////////////////////
// Implementation of node
////////////////////////////////////////////////////////////////////////////////

template <class TTT>
class Node {
public:
    Node():dato(), next(0) {}
    Node(TTT dato):dato(dato), next(0) {}
    virtual ~Node() { next = 0; }

    TTT dato;
    Node<TTT>* next;
};


////////////////////////////////////////////////////////////////////////////////
// List interface
////////////////////////////////////////////////////////////////////////////////

template <class TTT>
class IteradorLista;

template <class TTT>
class Lista {
    public:
        Lista(); // Crea una lista vacia
        Lista(const Lista<TTT> &that);
        Lista<TTT>& operator=(const Lista<TTT> &that);

        virtual ~Lista();

        /* devuelve el tamaño de elementos en la lista.  */
        int size() const;

        /* vacia la lista (borrando todos sus elementos).
         * pos: this->size() = 0 */
        void clear();

        // vacia la lista y le modifica el tamaño 
        // con objetos TTT por defecto.
        // pos: this->size() = amount (con valor TTT())
        void resize(int amount);

        /* devuelve true si la lista está vacia (size() == 0)
         * de lo contrario, devuelve false */
        bool empty();
        
        /* agrega un elemento al final de la lista.
         * pos: tamaño uno mayor que el anterior y 
         * elemento agregado. */
        void push_back(const TTT &valor);

        /* obtiene el elemento en la posicion 'index' de la 
         * lista.
         * pre: size() > 'index' (osea, que exista un elemento en esa posicion) */
        TTT& getElementoAt(int index);

        /* elimina el último elemento de la lista y devuelve una copia del mismo.
         * pre: empty() = false (al menos 1 elemento)
         * pos: el tamaño será uno menor al anterior.
         * */
        TTT pop_back();

    private:
        Node<TTT>* head;

    public:
        friend class IteradorLista<TTT>;
};


////////////////////////////////////////////////////////////////////////////////
// Interface de iterador para la clase Lista.
////////////////////////////////////////////////////////////////////////////////

template<class TTT>
class IteradorLista {
public:
    /* Construye el iterador
     * pos: El iterador apunta al comienzo de la lista.  */
    IteradorLista(Lista<TTT>& lista);

    ~IteradorLista();

    /* vuelve a ubicar al iterador al principio de la lista */
    void reset();

    /* Si aun no ha llegado al final
     * devuelve true.  De lo contrario, false*/
    bool isNotDone();
    
    /* pre: isNotDone() = true
     * avanza el iterador al siguiente elemento de la lista */
    void next();

    /* pre: isNotDone() = true
     * debe haber un elemento en */
    TTT& get();

private:
    Node<TTT>* current;
    Node<TTT>* start;
};


////////////////////////////////////////////////////////////////////////////////
// Implementacion de Lista
////////////////////////////////////////////////////////////////////////////////

template <class TTT>
Lista<TTT>::Lista():head(0) {
}

template <class TTT>
Lista<TTT>::Lista(const Lista<TTT> &that):head(0) {
    Node<TTT>* current = *&that.head;
    // mientras no sea cola.
    while(current) {
        this->push_back(current->dato);
        current = current->next; // avanzar.
    }
}

template <class TTT>
Lista<TTT>& Lista<TTT>::operator=(const Lista<TTT> &that) {
    if(this != &that) {
        this->clear();
        if(that.head) {
            Node<TTT>* current = *&that.head;
            // mientras no sea cola.
            while(current) {
                this->push_back(current->dato);
                current = current->next; // avanzar.
            }
        }
    }
    // assert(this->size() == that.size());
    return *this;
}

template <class TTT>
Lista<TTT>::~Lista() {
    Node<TTT>* current = head;
    Node<TTT>* toErase = 0;
    while(current) {
        toErase = current;
        current = current->next;
        delete toErase;
    }
}

template <class TTT>
void Lista<TTT>::resize(int amount) {
    clear();
    for(int i=0;i<amount;++i) {
       TTT valor;
       push_back(valor);
    }
    // assert(size() == amount);
}

template <class TTT>
void Lista<TTT>::clear() {
    while(!empty()) {
        pop_back();
    }
    // assert(size() == 0);
}

template <class TTT>
int Lista<TTT>::size() const {
    int quantity = 0;
    Node<TTT>* current = head;
    while(current) {
        current = current->next;
        quantity++;
    }
    return quantity;
}

template <class TTT>
bool Lista<TTT>::empty() {
    return size() == 0;
}

template <class TTT>
void Lista<TTT>::push_back(const TTT &valor) {
    // int oldSize = size();
    Node<TTT>* nuevoNode = new Node<TTT>(valor);

    if(!head) {
        head = nuevoNode;
    }
    else {
        Node<TTT>* temporalNode = head;
        while(temporalNode->next) {
            temporalNode = temporalNode->next;
        }
        temporalNode->next = nuevoNode;
    }
    // assert(oldSize + 1 == size());
}

template <class TTT>
TTT Lista<TTT>::pop_back() {
    // int oldSize = size();
    TTT valor;

    if(size() == 1) {
        valor = head->dato;
        delete head;
        head=0;
    }
    else {
        Node<TTT>* temporalNode = head;
        Node<TTT>* beforeLast = temporalNode;
        if(temporalNode) {
            while(temporalNode->next) {
                beforeLast = temporalNode;
                temporalNode = temporalNode->next;
            }
            valor = temporalNode->dato;
            delete temporalNode;
            beforeLast->next = 0;
        }
    }

    // assert(oldSize - 1 == size() || (oldSize == 0 && size() == 0));
    return valor;
}

template <class TTT>
TTT& Lista<TTT>::getElementoAt(int index) {
    // assert(size() > index);
    int contador = 0;
    Node<TTT>* temporalNode = head;
    while(contador < index && temporalNode->next) {
        temporalNode = temporalNode->next;
        contador++;
    }
    return temporalNode->dato;
}


////////////////////////////////////////////////////////////////////////////////
// Implementacion de iteradores
////////////////////////////////////////////////////////////////////////////////

template<class TTT>
IteradorLista<TTT>::IteradorLista(Lista<TTT>& lista) {
   start = lista.head;
   current = start;
}

template<class TTT>
void IteradorLista<TTT>::reset() {
   current = start;
}

template<class TTT>
IteradorLista<TTT>::~IteradorLista() {}

template<class TTT>
void IteradorLista<TTT>::next() {
    current = current->next;
}

template<class TTT>
bool IteradorLista<TTT>::isNotDone() {
    return current;
}

template<class TTT>
TTT& IteradorLista<TTT>::get() {
    return current->dato;
}

#endif
