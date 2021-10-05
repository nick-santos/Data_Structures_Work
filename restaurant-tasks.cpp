#include <iostream>
using namespace std;

int codigocliente = 1;
float totaldodia = 0;

struct produto { 
  int codP; 
  float valor; 
  struct produto * proxP; 
};
typedef struct produto * prPtr;

struct cliente {
  int codC; 
  struct produto * prod; 
  struct cliente * proxC;
}; 
typedef struct cliente * clPtr;
clPtr inicio = NULL;
clPtr fim = NULL;

bool listavazia () {
  if (inicio == NULL) {
    return true;
  } else {
    return false;
  }
} 

void cardapio () {
  cout << "\n============ CÓDIGOS DO CARDÁPIO ============\n";
  cout << "\n       - Entradas: ";
  cout << "\nCódigo 1: (preço único) ............. R$6,90";
  cout << "\n       - Pratos: ";
  cout << "\nCódigo 2: Prato A       ............. R$16,90";
  cout << "\nCódigo 3: Prato B       ............. R$20,00";
  cout << "\nCódigo 4: Prato C       ............. R$24,90";
  cout << "\n       - Sobremesas: ";
  cout << "\nCódigo 5: (preço único) ............. R$6,90";
  cout << "\n       - Bebidas: ";
  cout << "\nCódigo 6: Água          ............. R$3,50";
  cout << "\nCódigo 7: Refrigerantes ............. R$5,00";
  cout << "\nCódigo 8: Sucos         ............. R$4,00\n";
  cout << "\n=============================================";
}

void inserircliente () {
  clPtr p = new cliente;  
  p -> codC = codigocliente++;

  if (listavazia()) {
    p -> proxC = inicio;
    inicio = p;
    fim = p;
  } else {
    p -> proxC = fim ->  proxC;
    fim -> proxC = p;
    fim = p;
  }
  cout << "\nCliente " << p -> codC << " inserido.";
}

void inserirproduto () {
  clPtr p = inicio;
  int x;
  bool achei = false;

  if (!listavazia()) {
    cout << "\nDigite o código do cliente: ";
    cin >> x;
    while (p != NULL && achei == false) {
      if (p -> codC == x) {
        achei = true;
      } else {
        p = p -> proxC;
      }
    }
    if (achei) {
      prPtr q = new produto;
      cout << "\nDigite o código do produto: ";
      cin >> q -> codP;
      switch (q -> codP) {
        case 1: q -> valor = 6.90;
        break;
        case 2: q -> valor = 16.90;
        break;
        case 3: q -> valor = 20.00;
        break;
        case 4: q -> valor = 24.90;
        break;
        case 5: q -> valor = 6.90;
        break;
        case 6: q -> valor = 3.50;
        break;
        case 7: q -> valor = 5.00;
        break;
        case 8: q -> valor = 4.00;
        break;
      }      
      q -> proxP = p -> prod;
      p -> prod = q;
      cout << "\nProduto " << q -> codP << " de valor R$" << q -> valor <<" inserido.";
    } else {
      cout << "\nCliente não encontrado.";
    }
  } else {
    cout << "\nSem clientes.";
  }  

}

void saida () {
  if (listavazia()) {
    cout << "\nSem clientes.\n";
  } else {
    clPtr retira = inicio, aux = inicio;
    int x;
    bool achei = false;
    cout << "\nDigite o código do cliente: ";
    cin >> x;
    while (retira != NULL && achei == false) {
      if (retira -> codC == x) {
        achei = true;
      } else {
        aux = retira;
        retira = retira -> proxC;
      }
    }
    if (achei) {
      prPtr q = retira -> prod;

      if (retira -> prod == NULL) {
        cout << "\nSem pedidos.";
      } else {
        float contPreço = 0;
        cout << "\nOs pedidos foram: \n";
        cout << "\nCódigo     Preço ";
        while (q != NULL) {
          cout << "\n   " << q -> codP << "       R$" << q -> valor;
          contPreço += q -> valor;
          q = q -> proxP;
        }
        cout << "\n\nValor total a pagar: R$" << contPreço;
        totaldodia += contPreço;

        while (retira -> prod != NULL) {
          q = retira -> prod;
          retira -> prod = q -> proxP;
          delete (q);
        }
      }
      if (aux == retira) {
        inicio = retira -> proxC;
        delete (retira);
        cout << "\n\nCliente retirado.";
      } else {
        aux -> proxC = retira -> proxC;
        delete (retira);
        cout << "\n\nCliente retirado.";
      }
    } else {
      cout << "\nCliente não encontrado.";
    }
  }
}

void listarP () {
  clPtr p = inicio;
  int x;
  bool achei = false;

  if (!listavazia()) {
    cout << "\nDigite o código do cliente: ";
    cin >> x;
    while (p != NULL && achei == false) {
      if (p -> codC == x) {
        achei = true;
      } else {
        p = p -> proxC;
      }
    }
    if (achei) {
      float contPreço = 0;
      prPtr q = p -> prod;

      if (p -> prod == NULL) {
        cout << "\nSem pedidos!\n";
      } else {
        cout << "\nOs pedidos foram: \n";
        cout << "\nCódigo:    Preço:";
        while (q != NULL) {
          cout << "\n   " << q -> codP << "       R$" << q -> valor;
          contPreço += q -> valor;
          q = q -> proxP;
        }
        cout << "\nValor total a pagar: R$" << contPreço;
      }
    } else {
      cout << "\nCliente não encontrado.";
    }
  } else {
    cout << "\nSem clientes.";
  }  
}

void listarC () {
  clPtr p = inicio;
  if (listavazia()) {
    cout << "\nSem clientes.";
  } else {
    cout << "\nCliente(s): \n";
    while (p != NULL) {
      cout << p -> codC << " | ";
      p = p -> proxC;
    }
  }
}

int fechar () {
  if (!listavazia()) {
    cout << "\nNão é possível fechar, pois ainda há clientes no restaurante.";
    return 0;
  } else {
    cout << "\n\nTotal recebido no dia: R$" << totaldodia;
    cout << "\n\nRestaurante fechado.\n";
    return 1;
  }
}

int main() {
  int op, fecha = 0;
  cardapio();

  do {
    cout << "\n_____________________________________\n";
    cout << "\n(1) Para inserir CLIENTE";
    cout << "\n(2) Para inserir PRODUTO";
    cout << "\n(3) Para listar produtos do cliente";
    cout << "\n(4) Para fechar conta do cliente";
    cout << "\n(5) Para listar clientes atuais";
    cout << "\n(0) Para fechar o restaurante";
    cout << "\n    Digite uma opção: ";
    cout << "\n_____________________________________\n\n";
    cin >> op;

    switch (op) {
      case 1: inserircliente(); 
      break;
      case 2: inserirproduto(); 
      break;
      case 3: listarP(); 
      break;
      case 4: saida(); 
      break;
      case 5: listarC(); 
      break;
      case 0: fecha = fechar();
      break;
    }
  } while (fecha != 1);
  return 0;
}
