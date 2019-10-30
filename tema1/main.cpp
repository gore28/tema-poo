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

class matrice
{
protected:
    nr_complex **v;
public:
    virtual void matrice_al(int,int)=0;
    virtual void delet()=0;

};

class matrice_oarecare:public matrice
{
    int lin,col;

public:
    void matrice_al(int,int);
    void delet();

    void copie(matrice_oarecare&);
    matrice_oarecare();
    matrice_oarecare(int, int);
    ~matrice_oarecare();
    matrice_oarecare(const matrice_oarecare &);
    matrice_oarecare& operator =(const matrice_oarecare&);
    friend istream& operator >>(istream&, matrice_oarecare&);
    friend ostream& operator <<(ostream&, matrice_oarecare&);
};

void matrice_oarecare::matrice_al(int i,int j)
{
    int z;
    v=new nr_complex*[i];
    for(z=0; z<i; z++)
        v[z]=new nr_complex[j];
}

void matrice_oarecare::delet()
{
    for(int i=0; i<lin; i++)
        delete[] v[i];
    delete[] v;
    lin=0;
    col=0;
}

void matrice_oarecare::copie(matrice_oarecare& a)
{
    delet();
    lin=a.lin;
    col=a.col;
    matrice_al(lin,col);
    int i,j;
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
            v[i][j]=a.v[i][j];
}

matrice_oarecare::matrice_oarecare()
{
    lin=0;
    col=0;

}

matrice_oarecare::matrice_oarecare(int i, int j)
{
    lin=i;
    col=j;
    matrice_al(lin,col);

}

matrice_oarecare::~matrice_oarecare()
{
    for(int i=0; i<lin; i++)
        delete[] v[i];
    delete[] v;
    lin=0;
    col=0;
}

matrice_oarecare& matrice_oarecare::operator=(const matrice_oarecare &obj)
{
    int l=obj.lin,c=obj.col;
    matrice_al(l,c);
    for(int i=0; i<l*c; i++)
        v[i]=obj.v[i];
    return *this;
}

istream& operator>>(istream &in, matrice_oarecare &a)
{
    cout<<"Linii: ";
    in>>a.lin;
    cout<<"Coloane: ";
    in>>a.col;
    a.matrice_al(a.lin, a.col);
    int i, j;
    for(i = 0; i < a.lin; i++)
        for(j = 0; j < a.col; j++)
            in>>a.v[i][j];
    return in;
}

ostream& operator<<(ostream &out, matrice_oarecare &a)
{
    out<<endl<<"Nr linii si coloane: "<<a.lin<<" "<<a.col<<endl;
    int i, j;
    for(i=0; i<a.lin; i++)
    {
        for(j=0; j<a.col; j++)
            out<<a.v[i][j]<<" ";
        out<<endl;
    }
    return out;
}

class matrice_patratica:public matrice
{
    int dim;

public:
    void matrice_al(int,int);
    void delet();

    void copie(matrice_patratica&);
    matrice_patratica();
    matrice_patratica(int);
    ~matrice_patratica();
    matrice_patratica(const matrice_patratica &);
    matrice_patratica& operator =(const matrice_patratica&);
    friend istream& operator >>(istream&, matrice_patratica&);
    friend ostream& operator <<(ostream&, matrice_patratica&);

};

void matrice_patratica::matrice_al(int i,int j)
{
    int z;
    v=new nr_complex*[i];
    for(z=0; z<i; z++)
        v[z]=new nr_complex[j];
}

void matrice_patratica::delet()
{
    for(int i=0; i<dim; i++)
        delete[] v[i];
    delete[] v;
    dim=0;

}

void matrice_patratica::copie(matrice_patratica& a)
{
    delet();
    dim=a.dim;
    matrice_al(dim,dim);
    int i,j;
    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
            v[i][j]=a.v[i][j];
}

matrice_patratica::matrice_patratica()
{
    dim=0;

}

matrice_patratica::matrice_patratica(int i)
{
    dim=i;
    matrice_al(dim,dim);

}

matrice_patratica::~matrice_patratica()
{
    for(int i=0; i<dim; i++)
        delete[] v[i];
    delete[] v;
    dim=0;
}

matrice_patratica& matrice_patratica::operator=(const matrice_patratica &obj)
{
    int d=obj.dim;
    matrice_al(d,d);
    for(int i=0; i<d*d; i++)
        v[i]=obj.v[i];
    return *this;
}

istream& operator>>(istream &in, matrice_patratica &a)
{
    cout<<"Linii si Coloane:";
    in>>a.dim;
    a.matrice_al(a.dim, a.dim);
    int i, j;
    for(i = 0; i < a.dim; i++)
        for(j = 0; j < a.dim; j++)
            in>>a.v[i][j];
    return in;
}

ostream& operator<<(ostream &out, matrice_patratica &a)
{
    out<<endl<<"Nr linii si coloane: "<<a.dim<<endl;
    int i, j;
    for(i=0; i<a.dim; i++)
    {
        for(j=0; j<a.dim; j++)
            out<<a.v[i][j]<<" ";
        out<<endl;
    }

    return out;
}

int main()
{nr_complex x;
    matrice_patratica a,b;
    cin>>a;
    cout<<a<<endl;
    return 0;
}
