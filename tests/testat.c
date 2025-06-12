struct S{
	int n;
	char text[16];
	};
	
struct S a;
struct S v[10];

struct St{
	int x;
};

void f(char text[],int i,char ch){
	text[i]=ch;
	}

int h(int x,int y){
	
	// scalar if
	/*int arr[10];
	if(arr){
		return 1;
	}*/

	//scalar while
	/*int arr[10];
	while(arr){

	}*/
	
	// scalar return 
	/*int arr[10];
	return arr;*/

	// return type
	/*struct S a;
	return a;*/

	// left value assign
	/*int tt;
	(3 + 2) = tt; */

	// constant assign
	/*int v[10];
	int t;
	v = t;*/

	// Ambii operanzi trebuie sa fie scalari
	/*int v[10];
	int t;
	t = v;*/

	// structura trb sa fie convertibila
	/*struct S a;
	a = x; 	*/

	//  Tipul rezultat este tipul sursei
	/*int arr[5];
	arr = 10;*/

	// Ambii operanzi trebuie sa fie scalari si sa nu fie structuri ||
	/*int xx; 
	struct S c;
	struct S d;
	xx = c || d;*/

	// Rezultatul este un int ||
	/*int arr[10]; 
	int br;
	br = 1;
	int xx; 
	xx = arr || br;*/

	// Ambii operanzi trebuie sa fie scalari si sa nu fie structuri &&
	/*int xx; 
	struct S c;
	struct S d;
	xx = c && d;*/

	// Rezultatul este un int &&
	/*int arr[10]; 
	int br;
	br = 1;
	int xx; 
	xx = arr && br;*/

	// Ambii operanzi trebuie sa fie scalari si sa nu fie structuri rel
	/*int xx; 
	struct S c;
	struct S d;
	xx = c < d;*/

	// Rezultatul este un int rel
	/*int arr[10]; 
	int br;
	br = 1;
	int xx; 
	xx = arr < br;*/

	// Ambii operanzi trebuie sa fie scalari si sa nu fie structuri add
	/*int xx; 
	struct S c;
	struct S d;
	xx = c + d;*/

	// Ambii operanzi trebuie sa fie scalari si sa nu fie structuri mul
	/*int xx; 
	struct S c;
	struct S d;
	xx = c * d;*/

	// Structurile nu se pot converti
	/*int xx;
	struct S c;
	c = xx;*/

	// Tipul la care se converteste nu poate fi structura
	/*int xx;
	struct S c;
	c = xx;*/

	// Un array se poate converti doar la alt array
	/*int arr[10];
	int arr2[10];
	arr = x;
	arr = arr2;	*/

	// Un scalar se poate converti la un scalar
	/*int ad;
	int ad2;
	int ad3[10];
	ad = ad2;
	ad= ad3;*/

	// Structurile nu se pot converti
	/*struct S cr;
	int c;
	cr = (struct S)c;*/

	// Tipul la care se converteste nu poate fi structura
	/*struct S cr;
	int c;
	c = (int)cr;*/

	//minus si not trb un operand scalar
	/*int arr[10];
	int a;
	a = 1 - arr;*/

	// Rezultatul lui Not este un int
	/*int a;
	a = !1;*/

	// Doar un array poate fi indexat
	/*int arr[10];
	int xc;
	arr[1];
	xc[1];
	*/

	// Operatorul de selectie a unui camp de structura se poate aplica doar structurilor
	/*int xc;
	xc.n;*/

	// Campul unei structuri trebuie sa existe
	/*struct S c;
	c.v;*/

	// ID-ul trebuie sa existe in TS
	/*arc = 9;*/

	//Doar functiile pot fi apelate
	/*int a;
	a(2);*/

	//Apelul unei functii trebuie sa aiba acelasi numar de argumente ca si numarul de parametri de la definitia ei
	//h(1);

	// Tipurile argumentelor de la apelul unei functii trebuie sa fie convertibile la tipurile parametrilor functiei
	/*struct S c;
	h(c, c.n)*/

	
	if(x>0&&x<y){
		f(v[x].text,y,'#');
		return 1;
		}
	return 0;
	}

	// void return 
	/*void g(int x){
		return x;
	}*/