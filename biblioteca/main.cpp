#include <iostream>
#include <string>
using namespace std;

class Elemento{ // Clase padre
protected:
    string autor;
    string titulo;
    double precio;
    double costo;
    double descuento;
public:
	Elemento(){} // Constructor
    Elemento(string autor, string titulo){ // Constructor sobrecargado
        this->autor = autor;
        this->titulo = titulo;
    }
    ~Elemento(){} // Destructor
    double getPrecio(){ return this->precio; }
};

class Articulo: public Elemento { // Herencia
private:
    int np; // Numero de paginas
    int nd; // Numero de dias
public:
	Articulo(){} // Constructor
    Articulo(string autor, string titulo, int np, int nd): Elemento(autor, titulo){ // Constructor sobrecargado
        this->np = np;
        this->nd = nd;
        // Calculo del costo
        this->costo = 20 + this->np*0.5;
        // Calculo del descuento
        if(this->nd<5){ // Si se alquila por menos de 5 dias
            this->descuento = 0.10*this->costo;
        }else{ // Si se alquila desde 5 dias o mas
            this->descuento = 0.20*this->costo;
        }
        // Calculo del precio
        this->precio = this->costo-this->descuento;
    }
    ~Articulo(){} // Destructor
    friend ostream &operator <<(ostream &output, const Articulo &a){
        output << "Autor: " << a.autor << ", ";
        output << "Titulo: " << a.titulo << ", ";
        output << "Numero de paginas: " << a.np << ", ";
        output << "Numero de dias: " << a.nd << ", ";
        output << "Precio: S/." << a.precio;
        return output;
    }
};

class Libro: public Elemento { // Herencia
private:
    int a; // Anho de publicacion
    double p; // Peso
public:
	Libro(){} // Constructor
    Libro(string autor, string titulo, int a, double p): Elemento(autor, titulo){ // Constructor sobrecargado
        this->a = a;
        this->p = p;
        // Calculo del costo
        this->costo = 50 + (this->p*0.75)/10;
        // Calculo del descuento
        if(this->a < 2000){ // Si el libro se ha publicado hasta antes del anho 2000
            this->descuento = 0.20*this->costo;
        }else if(this->a <= 2010){ // Si el libro se ha publicado desde el anho 2000 al 2010
            this->descuento = 0.25*this->costo;
        }else if(2011 <= this->a){ // Si el libro se ha publicado desde el anho 2011 en adelante
            this->descuento = 0.30*this->costo;
        }
        // Calculo del precio
        this->precio = this->costo-this->descuento;
    }
    ~Libro(){} // Destructor
    
    friend ostream &operator <<(ostream &output, const Libro &l){ // Sobrecarga del operador de escritura
        output << "Autor: " << l.autor << ", ";
        output << "Titulo: " << l.titulo << ", ";
        output << "Anho de publicacion: " << l.a << ", ";
        output << "Peso (en gramos): " << l.p << ", ";
        output << "Precio: S/." << l.precio;
        return output;
    }
};

class Bibioteca{
private:
    Articulo* articulos; // Arreglo dinamico de articulos
    Libro* libros; // Arreglo dinamico de libros
    int cantidadMax;
    int cantidadArticulos;
    int cantidadLibros;
public:
    Bibioteca(int cantidadMax){ // Constructor
        // Inicializacion de la cantidad maxima
        this->cantidadMax = cantidadMax;
		// Inicializacion del arreglo dinamico de articulos y la cantidad correspondiente
		this->articulos = new Articulo[this->cantidadMax];
		this->cantidadArticulos = 0;
        // Inicializacion del arreglo dinamico de libros y la cantidad correspondiente
		this->libros = new Libro[this->cantidadMax];
        this->cantidadLibros = 0;
    }
    
    ~Bibioteca(){ // Destructor
        // Liberamos la memoria de articulos
        delete [] this->articulos;
        this->articulos = NULL;
        // Liberamos la memoria de libros
        delete [] this->libros;
        this->libros = NULL;
    }
    
    void menu(){ // Menu de opciones
    	cout << "------------------------------\n";
        cout << "Menu de opcion\n";
        cout << "------------------------------\n";
        cout << "Opcion 1. Registrar nuevo elemento (articulo o libro)\n";
        cout << "Opcion 2. Elemento con el menor precio\n";
        cout << "Opcion 3. Mostrar todos los elementos registrados\n";
        cout << "Opcion 4. Salir\n";
        cout << "------------------------------\n";
        cout << "Ingresa opcion: ";
    }
    
    void mostrarElementos(){ // Muestra de elementos (todos)
    	cout << "------------------------------\n";
		cout << "Elementos registrados\n";
		cout << "------------------------------\n";
		cout << "Articulos (" << cantidadArticulos << ")\n";
		if(this->cantidadArticulos > 0){
			for(int i=0; i<this->cantidadArticulos; i++){
				cout << this->articulos[i] << endl;
			}
		}else{
			cout << "Aun no se ha registrado articulos\n";
		}
		cout << "------------------------------\n";
		cout << "Libros (" << cantidadLibros << ")\n";
		if(this->cantidadLibros > 0){
			for(int i=0; i<this->cantidadLibros; i++){
				cout << this->libros[i] << endl;
			}
		}else{
			cout << "Aun no se ha registrado libros\n";
		}
		cout << "------------------------------\n";
    }
    
    void mostrarElementoMenorPrecio(){ // Muestra de elemento de menor precio
    	cout << "------------------------------\n";
    	cout << "Elemento (articulo o libro) con menor precio\n";
    	cout << "------------------------------\n";
    	
    	if(this->cantidadArticulos+this->cantidadLibros > 0){ // Validacion de existencia de al menor un elemento (articulo o libro)
    		// Articulo de menor precio
    		double precioArticuloMin = -1;
    		Articulo aMin;
    		if(this->cantidadArticulos > 0){
    			precioArticuloMin = this->articulos[0].getPrecio();
    			aMin = this->articulos[0];
    			for(int i=0; i<this->cantidadArticulos; i++){
    				if(precioArticuloMin > this->articulos[i].getPrecio()){
    					precioArticuloMin = this->articulos[i].getPrecio();
    					aMin = this->articulos[i];
					}
				}
			}
			
			// Libro de menor precio
    		double precioLibroMin = -1;
    		Libro lMin;
    		if(this->cantidadLibros > 0){
    			precioLibroMin = this->libros[0].getPrecio();
    			lMin = this->libros[0];
    			for(int i=0; i<this->cantidadLibros; i++){
    				if(precioLibroMin > this->libros[i].getPrecio()){
    					precioLibroMin = this->libros[i].getPrecio();
    					lMin = this->libros[i];
					}
				}
			}
			
			// Elemento de menor precio
			if(precioArticuloMin !=-1 && precioLibroMin !=-1){
				if(precioArticuloMin<precioLibroMin){
					cout << "Articulo\n" << aMin << "\n";
				}else{
					cout << "Libro\n" << lMin << "\n";
				}
			}else if(precioArticuloMin !=-1){
				cout << "Articulo\n" << aMin << "\n";
			}else{
				cout << "Libro\n" << lMin << "\n";
			}
		}else{ // Caso en el que aun no se han registrado ni articulos ni libros
			cout << "Aun no se ha registrado articulos ni libros\n";
		}
		
    	cout << "------------------------------\n";
	}
	
	bool esEntero(string cadena){ // Verifica si una cadena corresponde a un numero entero
    	int puntos = 0;
        for(int i=0; i<cadena.size(); i++){
            char c = cadena[i];
            if(c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9'){
                return false;
            }
        }
        return true;
    }
    
    bool esDecimal(string cadena){ // Verifica si una cadena corresponde a un numero decimal (con punto decimal)
    	int puntos = 0;
        for(int i=0; i<cadena.size(); i++){
            char c = cadena[i];
            if(c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '.'){
                return false;
            }
            if(c == '.'){
            	puntos++;
			}
        }
        if(puntos <= 1){
        	return true;
		}
    }
    
    void registrarElemento(){
        string tipoElemento;
        cout << "------------------------------\n";
        cout << "Registro de nuevo elemento\n";
        cout << "------------------------------\n";
        if(this->cantidadArticulos+this->cantidadLibros < this->cantidadMax){
            cout << "Tipo de elemento ('a': articulo, 'l' libro): ";
            getline(cin, tipoElemento);
            if(tipoElemento == "a"){
                string titulo, autor, np_s, nd_s;
                cout << "Titulo del articulo: "; getline(cin, titulo);
                cout << "Autor del articulo: "; getline(cin, autor);
                cout << "Numero de paginas del articulo: "; getline(cin, np_s);
                cout << "Numero de dias del articulo: "; getline(cin, nd_s);
                if(esEntero(np_s) == true && esEntero(np_s) == true){
	                int np = stoi(np_s);
	                int nd = stoi(nd_s);
	                Articulo a(titulo, autor, np, nd);
	                this->articulos[this->cantidadArticulos] = a;
	                this->cantidadArticulos++;
	                cout << "------------------------------\n";
	                cout << "Articulo registrado exitosamente\n";
	            }else{
	            	cout << "------------------------------\n";
	                cout << "Error! Numero de paginas y/o numero de dias invalidos\n";
				}
            }else if(tipoElemento == "l"){
                string titulo, autor, a_s, p_s;
                cout << "Titulo del libro: "; getline(cin, titulo);
                cout << "Autor del libro: "; getline(cin, autor);
                cout << "Anho de publicacion del libro: "; getline(cin, a_s);
                cout << "Peso del libro: "; getline(cin, p_s);
                if(esEntero(a_s) == true && esDecimal(p_s) == true){
	                int a = stoi(a_s);
	                double p = stod(p_s);
	                Libro l(titulo, autor, a, p);
	                this->libros[this->cantidadLibros] = l;
	                this->cantidadLibros++;
	                cout << "------------------------------\n";
	                cout << "Libro registrado exitosamente\n";
	            }else{
	            	cout << "------------------------------\n";
	                cout << "Error! Anho de publicacion y/o peso invalidos\n";
				}
            }else{
            	cout << "------------------------------\n";
                cout << "Error! tipo de elemento invalido\n";
            }
        }else{
            cout << "Error! No se pueden agregar mas elementos. Se llego al limite maximo de "<< this->cantidadMax << "\n";
        }
    }
    
    void iniciar(){
        string opcion;
        do{
            system("CLS");
            menu();
            getline(cin, opcion);
            if(opcion == "1"){
            	system("CLS");
                this->registrarElemento();
                system("PAUSE");
            }else if(opcion == "2"){
            	system("CLS");
                this->mostrarElementoMenorPrecio();
                system("PAUSE");
            }else if(opcion == "3"){
            	system("CLS");
                this->mostrarElementos();
                system("PAUSE");
            }else if(opcion == "4"){
                cout << "Hasta pronto\n";
                system("PAUSE");
            }else{
                cout << "Error! Opcion incorrecta\n";
                system("PAUSE");
            }
        }while(opcion != "4");
        
    }
};

int main() {
    Bibioteca b(50);
    b.iniciar();
    return 0;
}
