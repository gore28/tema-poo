#include <iostream>

using namespace std;

class nr_complex
{
    float re,im;

public:
    nr_complex();
    nr_complex(float,float);
    ~nr_complex();
    nr_complex(const nr_complex &);
    void operator=(const nr_complex&);
    friend istream& operator>>(istream&,nr_complex&);
    friend ostream& operator<<(ostream&,nr_complex);
    friend nr_complex operator+(const nr_complex&, const nr_complex&);
    friend nr_complex operator*(const nr_complex&, const nr_complex&);
    friend nr_complex operator*(const nr_complex&, int);
    friend nr_complex operator-(const nr_complex&, const nr_complex&);
    friend int operator!=(const nr_complex&,const nr_complex&);
};

nr_complex::nr_complex()
{
    re=0.0;
    im=0.0;

}

nr_complex::nr_complex(float a,float b)
{
    re=a;
    im=b;

}

nr_complex::~nr_complex()
{

    re=0.0;
    im=0.0;

}

nr_complex::nr_complex(const nr_complex& x)
{
    this->re=x.re;
    this->im=x.im;

}

void nr_complex::operator=(const nr_complex& x)
{
    this->re=x.re;
    this->im=x.im;
}

istream& operator>>(istream& in,nr_complex& x)
{
    cout<<"Dati partea reala:";
    in>>x.re;
    cout<<"Dati partea imaginara:";
    in>>x.im;
    return in;
}

ostream& operator<<(ostream& out,nr_complex x)
{
        out<<x.re<<" "<<x.im<<"i";
    return out;
}

nr_complex operator+(const nr_complex& x, const nr_complex& y)
{
    nr_complex z;
    z.im=x.im+y.im;
    z.re=x.re+y.re;

    return z;
}

nr_complex operator*(const nr_complex& x,const nr_complex& y)
{
    nr_complex z;
    z.re=x.re*y.re-x.im*y.im;
    z.im=x.re*y.im+x.im*y.re;

    return z;
}

nr_complex operator*(const nr_complex &x,int i)
{
    nr_complex z;
    z.re=x.re*i;
    z.im=x.im*i;

    return z;
}
nr_complex operator-(const nr_complex& x,const nr_complex& y)
{
    nr_complex z;
    z.im=x.im-y.im;
    z.re=x.re-y.re;

    return z;
}

int operator!=(const nr_complex& x, const nr_complex& y)
{
    if(x.re!=y.re && x.im!=y.im)
        return 1;
    else
        return 0;
}

class matrice {
private:
	int n, m;       // n=nr linii; m=nr coloane
	nr_complex *mat;
public:
	matrice();
	matrice(int, int);
	~matrice();
	matrice(const matrice &obj);
	matrice& operator=(const matrice&);

	nr_complex* operator ()(int, int);
	friend istream& operator>>(istream&, matrice&);
	friend ostream& operator<<(ostream&, matrice);
	friend matrice operator+(matrice&, matrice&);
	friend matrice operator*(matrice&, matrice&);
	friend class nr_complex;
	nr_complex determinant0(matrice a);
	matrice& submatrice(int, int, int, matrice&, matrice&);
	nr_complex determ(matrice&, int);
	friend matrice transpusa(matrice&);
};
matrice::matrice() {
	n=0;
	m=0;
	mat=NULL;
}
matrice::matrice(int i, int j) {
	n=i;
	m=j;
	mat=new nr_complex[n*m];
}
matrice::~matrice() {
	delete[] mat;
}
matrice& matrice::operator=(const matrice &obj) {
	m=obj.m;
	n=obj.n;
	mat=new nr_complex[obj.m*obj.n];
	for(int i=0;i<obj.m*obj.n;i++)
		mat[i]=obj.mat[i];
	return *this;
}
matrice::matrice(const matrice &obj){
	*this=obj;
}
// supraincarcarea operatorului ()
nr_complex* matrice::operator()(int i, int j) {
	return mat+(i*m+j);                // elementul de pe linia i si coloana j
}
//supraincarcarea operatorului >> pentru matrici
istream& operator>>(istream& input, matrice& a) {
	int i, j;
	a.mat=new nr_complex[a.m*a.n];           /// trebuie alocata memorie pentru fiecare matrice
	for(i=0;i<a.n;i++)
    for(j=0;j<a.m;j++)
        input>>*a(i,j);
	return input;
}
//supraincarcarea operatorului << pentru matrici
ostream& operator<<(ostream& output, matrice a) {
	int i, j;
	//printf("%d %d \n", a.m, a.n);
	cout<<a.m<<" "<<a.n;             // dimensiunea fiecarei matrici
	for(i=0;i<a.n;i++) {
		for(j=0;j<a.m;j++)
			output<<*a(i,j)<<' ';
		output<<endl;
	}
	return output;
}
//supraincarcarea operatorului + pentru matrici
matrice operator+(matrice& a1, matrice& a2) {
	matrice a3;
	a3.n=a1.n;
	a3.m=a1.m;
	a3.mat=new nr_complex[a3.m*a3.n];             /// trebuie alocata memorie
	int i, j;
	if(a1.n!=a2.n || a1.m!=a2.m) {
		cout<<"Nu au aceeasi dimensiune"<<endl;
		return a3;
	}
	else
		for(i=0;i<a1.n;i++)
        for(j=0;j<a1.m;j++)
            *a3(i,j)=(*a1(i,j))+(*a2(i,j));
	return a3;
}
//supraincarcarea operatorului * pentru matrici
matrice operator*(matrice& a1, matrice& a2) {
	matrice a3(a1.n, a2.m), b(a1.n, a2.m);
	int i, j, k;
	a3.n=a1.n;
	a3.m=a2.m;
	b.n=a1.n;
	b.m=a2.m;
	a3.mat=new nr_complex[a3.m*a3.n];             /// trebuie alocata memorie
	b.mat=new nr_complex[b.m*b.n];
	//for(i=0;i<a1.n;i++)
    //for(j=0;j<a2.m;j++)
      //  *a3(i,j) = 0;
	if(a1.m!=a2.n) {
		cout<<"Nu se pot inmulti\n";
		return a3;
	}
	else {
		for(i=0;i<a1.n;i++)
        for(j=0;j<a2.m;j++)
        for(k=0;k<a1.m;k++) {
            *b(i,j)=(*a1(i,k))*(*a2(k,j));
            *a3(i,j)=(*a3(i,j))+(*b(i,j));
        }
	}
	return a3;
}

int main()
{nr_complex x;
    matrice a,b;
    cin>>a;
    cout<<a<<endl;
    return 0;
}
