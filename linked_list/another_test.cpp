#include "list.h"
#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

typedef Lista<char> ListaSimpleChars ;
typedef Lista<ListaSimpleChars> ListaDeListasChars;
using namespace std;


// 1) construir y push_back varias veces
// 2) clear
// 3) empty
// 4) resize, size
// 5) pop
// 6) construir resize, push_back, size, pop
ListaSimpleChars creaListaSimpleChars() {
    ListaSimpleChars lista;
    lista.push_back('a');
    lista.push_back('b');
    lista.push_back('c');
    lista.push_back('d');
    lista.push_back('e');
    return lista;
}


TEST_CASE( "Construir y push_back" , "[lista_simple_chars]") {
    ListaSimpleChars lista = creaListaSimpleChars();
    CHECK ( lista.size() == 5 );
    CHECK ( lista.empty() == false);

    lista.push_back('f');
    CHECK ( lista.size() == 6 );
    CHECK ( lista.empty() == false);

    char letra = lista.pop_back();
    CHECK ( lista.size() == 5 );
    CHECK ( lista.empty() == false);
    CHECK ( letra == 'f' );
    // CHECK_NOTHROW (lista.show());

    letra = lista.pop_front();
    CHECK ( lista.size() == 4 );
    CHECK ( lista.empty() == false);
    CHECK ( letra == 'a' );

    lista.clear();
    CHECK ( lista.size() == 0 );
    CHECK ( lista.empty() == true);

    lista.resize(2);
    CHECK ( lista.size() == 2 );
    CHECK ( lista.empty() == false);
    // CHECK_NOTHROW (lista.show());
    

    ListaSimpleChars otraLista = creaListaSimpleChars();
    otraLista.resize(4);
    CHECK ( otraLista.size() == 4 );
    CHECK ( otraLista.empty() == false);

    otraLista.push_back('o');
    CHECK ( otraLista.size() == 5 );
    CHECK ( otraLista.empty() == false);

    ListaSimpleChars unaMas = creaListaSimpleChars();
    CHECK ( unaMas.getElementoAt(0) == 'a');
    CHECK ( unaMas.getElementoAt(1) == 'b');
    CHECK ( unaMas.getElementoAt(2) == 'c');
    CHECK ( unaMas.getElementoAt(3) == 'd');
    CHECK ( unaMas.getElementoAt(4) == 'e');
}

TEST_CASE( "Lista compleja de chars" , "[lista_lista_chars]") {
    // asignar y recorrer.
    ListaSimpleChars listaOne = creaListaSimpleChars();
    ListaSimpleChars listaTwo = creaListaSimpleChars();
    ListaSimpleChars listaThree = creaListaSimpleChars();

    ListaDeListasChars listaCompleja;
    listaCompleja.push_back(listaOne);
    listaCompleja.push_back(listaTwo);
    listaCompleja.push_back(listaThree);
    CHECK(listaCompleja.size() == 3);

    ListaSimpleChars listaNueva = listaCompleja.getElementoAt(1);
    CHECK(listaNueva.size() == 5);
    // listaNueva.show();
    CHECK(listaNueva.getElementoAt(1) == 'b');

    int alto = 3;
    int ancho = 4;
    ListaDeListasChars casillero;
    casillero.resize(alto);
    CHECK(casillero.size() == alto);

    casillero.getElementoAt(0).push_back('a');
    casillero.getElementoAt(0).push_back('b');
    casillero.getElementoAt(0).push_back('c');
    casillero.getElementoAt(0).push_back('d');
    CHECK(casillero.getElementoAt(0).size() == ancho);

    casillero.getElementoAt(1).push_back('e');
    casillero.getElementoAt(1).push_back('f');
    casillero.getElementoAt(1).push_back('g');
    casillero.getElementoAt(1).push_back('h');
    CHECK(casillero.getElementoAt(1).size() == ancho);

    casillero.getElementoAt(2).push_back('i');
    casillero.getElementoAt(2).push_back('j');
    casillero.getElementoAt(2).push_back('k');
    casillero.getElementoAt(2).push_back('l');
    CHECK(casillero.getElementoAt(2).size() == ancho);

    for(int y=0;y<casillero.size();++y) {
        for(int x=0;x<casillero.getElementoAt(y).size();++x) {
            cout << casillero.getElementoAt(y).getElementoAt(x) ;
        }
        cout << endl;

    }
}

class CharClass {
public:
    CharClass(char value='a'):value(value){}
    char getChar() {return value;}
    void setChar() {this->value = value;}
private:
    char value;
};

TEST_CASE( "Lista compleja de CharClass" , "[lista_lista_char_class]") {

    int alto = 3;
    int ancho = 4;
    Lista <Lista<CharClass> > casillero;
    casillero.resize(alto);
    CHECK(casillero.size() == alto);

    casillero.getElementoAt(0).push_back(CharClass('a'));
    casillero.getElementoAt(0).push_back(CharClass('b'));
    casillero.getElementoAt(0).push_back(CharClass('c'));
    casillero.getElementoAt(0).push_back(CharClass('d'));
    CHECK(casillero.getElementoAt(0).size() == ancho);

    casillero.getElementoAt(1).push_back(CharClass('e'));
    casillero.getElementoAt(1).push_back(CharClass('f'));
    casillero.getElementoAt(1).push_back(CharClass('g'));
    casillero.getElementoAt(1).push_back(CharClass('h'));
    CHECK(casillero.getElementoAt(1).size() == ancho);

    casillero.getElementoAt(2).push_back(CharClass('i'));
    casillero.getElementoAt(2).push_back(CharClass('j'));
    casillero.getElementoAt(2).push_back(CharClass('k'));
    casillero.getElementoAt(2).push_back(CharClass('l'));
    CHECK(casillero.getElementoAt(2).size() == ancho);

    for(int y=0;y<casillero.size();++y) {
        for(int x=0;x<casillero.getElementoAt(y).size();++x) {
            cout << casillero.getElementoAt(y).getElementoAt(x).getChar() ;
        }
        cout << endl;

    }
}


TEST_CASE( "Lista CharClass" , "[what]") {

    int alto = 3;
    int ancho = 4;
    CHECK (alto != ancho);
    Lista <Lista<CharClass> > casillero;
    casillero.resize(alto);
    CHECK(casillero.size() == alto);

    casillero.getElementoAt(0).push_back(CharClass('a'));
    casillero.getElementoAt(0).push_back(CharClass('b'));
    casillero.getElementoAt(0).push_back(CharClass('c'));
    casillero.getElementoAt(0).push_back(CharClass('d'));
    // CHECK(casillero.getElementoAt(0).size() == ancho);

    casillero.getElementoAt(1).push_back(CharClass('e'));
    casillero.getElementoAt(1).push_back(CharClass('f'));
    casillero.getElementoAt(1).push_back(CharClass('g'));
    casillero.getElementoAt(1).push_back(CharClass('h'));
    // CHECK(casillero.getElementoAt(1).size() == ancho);

    casillero.getElementoAt(2).push_back(CharClass('i'));
    casillero.getElementoAt(2).push_back(CharClass('j'));
    casillero.getElementoAt(2).push_back(CharClass('k'));
    casillero.getElementoAt(2).push_back(CharClass('l'));
    // CHECK(casillero.getElementoAt(2).size() == ancho);

    for(int y=0;y<casillero.size();++y) {
        for(int x=0;x<casillero.getElementoAt(y).size();++x) {
            cout << casillero.getElementoAt(y).getElementoAt(x).getChar() ;
        }
        cout << endl;
    }

    cout << endl << endl << "Iterators" << endl;
    int x = 0, y = 0;
    for(IteradorLista<Lista<CharClass> > iter(casillero); iter.isNotDone(); iter.next()) {
        for(IteradorLista<CharClass> iterSmall(iter.get()); iterSmall.isNotDone(); iterSmall.next()) {
            cout << casillero.getElementoAt(y).getElementoAt(x).getChar() ;
            CHECK( iterSmall.get().getChar() == casillero.getElementoAt(y).getElementoAt(x).getChar());
            x++;        
        }
        cout << endl;
        y++; x = 0;
    }
    // IteradorLista< Lista<CharClass> > iter(casillero); 
    // while(iter.nextExists()) {
    //     IteradorLista< CharClass > iterSmall(iter.get());
    //     while(iterSmall.nextExists()) {
    //         // cout << iterSmall.get();
    //         // CHECK( iterSmall.get() == casillero.getElementoAt(y).getElementoAt(x).getChar());
    //         cout << casillero.getElementoAt(y).getElementoAt(x).getChar() ;
    //         iterSmall.next();
    //         x++;
    //     }
    //     cout << casillero.getElementoAt(y).getElementoAt(x).getChar() ;
    //     iter.next();
    //     y++; x = 0;
    //     cout << endl;
    // }
}
