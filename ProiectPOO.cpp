//Tema: Supermarket
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Produs {
private:
	string nume;
	float pret;
	int* cantitate;
	static int nrProduseInStoc;
	const int codBare;

public:

	Produs() :codBare(100000) {
		this->nume = "Apa";
		this->pret = 2.5;
		this->cantitate = new int(30);
		nrProduseInStoc++;
	}
	Produs(string nume, int* cantitate) :codBare(100001) {
		this->nume = nume;
		this->pret = 0.0;
		this->cantitate = new int(*cantitate);
		nrProduseInStoc++;
	}
	Produs(string nume, float pret, int* cantitate, const int cod) :codBare(cod) {
		this->nume = nume;
		this->pret = pret;
		this->cantitate = new int(*cantitate);
		nrProduseInStoc++;
	}

	//Destructor
	~Produs() {
		if (this->cantitate != NULL) {
			delete[]this->cantitate;
			this->cantitate = NULL;
		}
	}

	//constr de copiere
	Produs(const Produs& p) : codBare(p.codBare) {
		this->nume = p.nume;
		this->pret = p.pret;
		if (p.cantitate != NULL) {
			this->cantitate = new int(*(p.cantitate));
		}
		else {
			this->cantitate = NULL;
		}
		nrProduseInStoc++;
	}
	//op de indexare
	int operator[](int index) {
		return(*this->cantitate);
	}

	//op functie
	float operator()() {
		return this->pret * (*this->cantitate);
	}

	//op !
	bool operator!() {
		return(this->pret == 0);
	}




	//op =
	Produs& operator= (const Produs& p) {
		if (this != &p)

		{
			if (this->cantitate != NULL) {
				delete[]this->cantitate;
				this->cantitate = NULL;
			}
			this->nume = p.nume;
			this->pret = p.pret;
			if (p.cantitate != NULL) {
				this->cantitate = new int(*(p.cantitate));
			}
			else {
				this->cantitate = NULL;
			}
			nrProduseInStoc++;
		}

		return *this;

	}

	//getteri si setteri
	string getNumeProdus() {
		return this->nume;
	}

	void setNumeProdus(string nume) {
		this->nume = nume;
	}

	float getPretProdus() {
		return this->pret;
	}

	void setPretProdus(float pret) {
		this->pret = pret;
	}

	int* getCantitate() {
		return this->cantitate;
	}

	void setCantitate(int* cantitate)
	{
		if (this->cantitate != NULL) {
			delete[] this->cantitate;
		}
		this->cantitate = new int(*cantitate);
	}

	static int getNrProduseInStoc() {
		return nrProduseInStoc;
	}

	const int getCodBare() {
		return this->codBare;
	}


	void afisareProdus() {
		cout << "Nume: " << this->nume << "\nPret: " << this->pret << "\nCantitate: " << *cantitate << "\nCod Bare: " << this->codBare << "\nNr. Produse in Stoc: " << this->nrProduseInStoc << endl;
	}


	static float CalculeazaValoareTotala(float pret, int cantitate) {
		return pret * cantitate;
	}

	friend void ProcesareProdus(const Produs& produs);


	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "Nume: " << p.nume << endl;
		out << "\nPret: " << p.pret << endl;
		out << "\nCantitate: " << *p.cantitate << endl;
		out << "\nCod Bare: " << p.codBare << endl;
		out << "\nNr. Produse in Stoc: " << p.nrProduseInStoc << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Produs& p) {
		cout << "Introduceti numele produsului: ";
		in >> p.nume;
		cout << "Introduceti pretul produsului: ";
		in >> p.pret;
		cout << "Introduceti cantitatea produsului: ";
		if (p.cantitate != nullptr) {
			delete p.cantitate;
			p.cantitate = nullptr;
		}
		p.cantitate = new int;
		in >> *(p.cantitate);
		return in;
	}
	//op ++ pre-increm
	Produs& operator++() {
		++(*this->cantitate);
		return *this;
	}
	//op ++ post-increm
	Produs operator++(int) {
		Produs temp(*this);
		++(*this->cantitate);
		return temp;
	}
	//op -- pre-decrem
	Produs& operator--() {
		--(*this->cantitate);
		return *this;
	}

	//op -- post-decrem
	Produs operator--(int) {
		Produs temp(*this);
		--(*this->cantitate);
		return temp;
	}

	//compar doua produse, si daca au acelasi cod de bare => returneaza true
	bool operator==(const Produs& p) const {
		return this->codBare == p.codBare;
	}

	Produs& operator+=(int valoare) {
		if (valoare > 0) {
			*cantitate += valoare;
		}
		return *this;
	}

	Produs& operator-=(int valoare) {
		if (*cantitate - valoare >= 0) {
			*cantitate -= valoare;
		}
		return *this;
	}
};
int Produs::nrProduseInStoc = 0;

class Raion {
private:
	string numeRaion;
	int capacitate;
	float* venitLunar;
	static int nrRaioaneActive;
	const string tipRaion;
public:
	Raion() : tipRaion("Nedefinit") {
		this->numeRaion = "Anonim";
		this->capacitate = 0;
		this->venitLunar = new float[12] {};
		nrRaioaneActive++;
	}
	Raion(string numeRaion, int capacitate) : tipRaion("Nedefinit") {
		this->numeRaion = numeRaion;
		this->capacitate = capacitate;
		this->venitLunar = new float[12] {};
		nrRaioaneActive++;
	}
	Raion(string numeRaion, int capacitate, float* venitLunar, const string tipRaion) : tipRaion(tipRaion) {
		this->numeRaion = numeRaion;
		this->capacitate = capacitate;
		this->venitLunar = new float[capacitate];
		for (int i = 0; i < capacitate; i++) {
			this->venitLunar[i] = venitLunar[i];
		}
		nrRaioaneActive++;
	}

	~Raion() {
		if (this->venitLunar != NULL) {
			delete[]this->venitLunar;
			this->venitLunar = NULL;
		}
	}

	Raion(const Raion& r) : tipRaion(r.tipRaion) {
		this->numeRaion = r.numeRaion;
		this->capacitate = r.capacitate;
		this->venitLunar = new float[r.capacitate];
		for (int i = 0; i < r.capacitate; i++) {
			this->venitLunar[i] = r.venitLunar[i];
		}
		nrRaioaneActive++;
	}

	Raion& operator= (const Raion& r) {

		if (this != &r)
		{
			if (this->venitLunar != NULL) {
				delete[]this->venitLunar;
				this->venitLunar = NULL;
			}
			this->numeRaion = r.numeRaion;
			this->capacitate = r.capacitate;
			this->venitLunar = new float[r.capacitate];
			for (int i = 0; i < r.capacitate; i++) {
				this->venitLunar[i] = r.venitLunar[i];
			}
			nrRaioaneActive++;
		}
		return *this;
	}

	static float CalculeazaVenitMediu(float* venitLunar, int nrLuni) {
		float venitTotal = 0.0;
		for (int i = 0; i < nrLuni; ++i) {
			venitTotal += venitLunar[i];
		}
		return venitTotal / nrLuni;
	}

	string getNumeRaion() {
		return this->numeRaion;
	}

	void setNumeRaion(string numeRaion) {
		this->numeRaion = numeRaion;
	}

	int getCapacitate() {
		return this->capacitate;
	}

	void setCapacitate(int capacitate) {
		this->capacitate = capacitate;
	}

	float* getVenitLunar() {
		return this->venitLunar;
	}

	void setVenitLunar(float* venitLunar) {
		if (this->venitLunar != NULL)
		{
			delete[]this->venitLunar;
		}

		this->venitLunar = new float[this->capacitate];
		for (int i = 0; i < this->capacitate; i++) {
			this->venitLunar[i] = venitLunar[i];
		}

	}

	void AfisareRaion() {
		cout << "Nume Raion: " << numeRaion << "\nCapacitate: " << capacitate << "\nTip Raion: " << tipRaion << "\nNr. Raioane Active: " << nrRaioaneActive << endl;
		cout << "Venit Lunar: ";
		for (int i = 0; i < 12; i++) {
			cout << venitLunar[i] << " ";
		}
		cout << "\nVenit Mediu Lunar: " << CalculeazaVenitMediu(venitLunar, 12) << endl;
	}

	friend ostream& operator<< (ostream& out, const Raion& r) {
		out << "Nume Raion: " << r.numeRaion << endl;
		out << "\nCapacitate: " << r.capacitate << endl;
		out << "\nTip Raion: " << r.tipRaion << endl;
		out << "\nNr. Raioane Active: " << r.nrRaioaneActive << endl;
		out << "Venit Lunar: ";
		for (int i = 0; i < 12; i++) {
			out << r.venitLunar[i] << " ";
		}
		out << endl;
		return out;
	}

	float& operator[](int index) {
		if (index >= 0 && index < capacitate) {
			return venitLunar[index];
		}
		throw out_of_range("Indexul este în afara limitelor");
	}

	float operator()() const {
		return CalculeazaVenitMediu(venitLunar, 12);
	}

	bool operator!() const {
		return capacitate == 0;
	}

	//post-increm
	Raion operator++(int) {
		Raion temp(*this);
		nrRaioaneActive++;
		return temp;
	}

	//pre-increm 
	Raion& operator++() {
		nrRaioaneActive++;
		return *this;
	}

	//post-decrem 
	Raion operator--(int) {
		Raion temp(*this);
		nrRaioaneActive--;
		return temp;
	}

	//pre-decrem 
	Raion& operator--() {
		nrRaioaneActive--;
		return *this;
	}


	friend void ProcesareRaion(const Raion& raion);
};
int Raion::nrRaioaneActive = 0;

class Client {
private:
	string numeClient;
	int varsta;
	bool* esteFidel;
	static int nrClientiFideli;
	const string tipClient;

public:
	string getNumeClient() {
		return this->numeClient;
	}
	int getVarsta() {
		return this->varsta;
	}
	bool* getEsteFidel() {
		return this->esteFidel;
	}
	void setNumeClient(string numeClient) {
		this->numeClient = numeClient;
	}
	void setVarsta(int varsta) {
		this->varsta = varsta;
	}
	void setEsteFidel(bool* esteFidel)
	{
		if (this->esteFidel != nullptr) {
			delete[]this->esteFidel;
		}
		this->esteFidel = new bool(*esteFidel);
	}


	Client() : tipClient("Nespecificat") {
		this->numeClient = "Anonim";
		this->varsta = 0;
		this->esteFidel = new bool(false);
		nrClientiFideli++;
	}
	Client(string numeClient, int varsta) : tipClient("Nou") {
		this->numeClient = numeClient;
		this->varsta = varsta;
		this->esteFidel = new bool(false);
		nrClientiFideli++;
	}
	Client(string numeClient, int varsta, bool* esteFidel, const string tipC) : tipClient(tipC) {
		this->numeClient = numeClient;
		this->varsta = varsta;
		this->esteFidel = new bool(*esteFidel);
		nrClientiFideli++;
	}
	Client(const Client& c) : tipClient(c.tipClient) {
		this->numeClient = c.numeClient;
		this->varsta = c.varsta;
		this->esteFidel = new bool(*c.esteFidel);
		nrClientiFideli++;
	}
	~Client() {
		if (this->esteFidel != nullptr)
		{
			delete this->esteFidel;
			this->esteFidel = nullptr;
		}
	}
	Client& operator= (const Client& c) {
		if (this != &c) {
			if (this->esteFidel != nullptr)
			{
				delete this->esteFidel;
				this->esteFidel = nullptr;
			}
			this->numeClient = c.numeClient;
			this->varsta = c.varsta;
			this->esteFidel = new bool(*c.esteFidel);
			nrClientiFideli++;

		}
		return *this;
	}

	void AfisareClient() {
		cout << "Nume Client: " << numeClient << "\nVarsta: " << varsta << "\nTip Client: " << tipClient << "\nNr. Clienti Fideli: " << nrClientiFideli << endl;
		cout << "Este Fidel: " << (*esteFidel ? "Da" : "Nu") << endl;
	}

	static void ActualizeazaStatus(bool* esteFidel, bool nouStatus) {
		*esteFidel = nouStatus;
	}

	friend ostream& operator<<(ostream& out, const Client& c) {
		out << "Nume Client: " << c.numeClient << endl;
		out << "Varsta: " << c.varsta << endl;
		out << "Tip Client: " << c.tipClient << endl;
		out << "Nr. Clienti Fideli: " << c.nrClientiFideli << endl;
		out << "Este Fidel: " << (*c.esteFidel ? "Da" : "Nu") << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Client& c) {
		cout << "Introduceti nume client: ";
		in >> c.numeClient;

		cout << "Introduceti varsta client: ";
		in >> c.varsta;

		cout << "Introduceti status fidel (1 pentru Da, 0 pentru Nu): ";
		in >> *c.esteFidel;

		return in;
	}

	bool operator[](int index) const {
		if (index == 0) {
			return *esteFidel;
		}
		throw out_of_range("Indexul este in afara limitelor");
	}

	bool operator()() const {
		return *esteFidel;
	}

	bool operator!() const {
		return !(*esteFidel);
	}

	//postincrem
	Client operator++(int) {
		Client temp(*this);
		nrClientiFideli++;
		return temp;
	}

	//preincrem
	Client& operator++() {
		nrClientiFideli++;
		return *this;
	}

	//postdecrem 
	Client operator--(int) {
		Client temp(*this);
		nrClientiFideli--;
		return temp;
	}

	//predecrem 
	Client& operator--() {
		nrClientiFideli--;
		return *this;
	}

	friend void ProcesareClient(const Client& client);
};
int Client::nrClientiFideli = 0;

class Produs;
class Raion;
class Client;

//void ProcesareProdus(const Produs& produs) {
//	cout << "Procesare Produs: " << produs.getNumeProdus() << " cu pretul: " << produs.getPretProdus() << endl;
//}
//void ProcesareRaion(const Raion& raion) {
//	cout << "Procesare Raion: " << raion.getNumeRaion() << " cu capacitatea: " << raion.getCapacitate() << endl;
//}
//void ProcesareClient(const Client& client) {
//	cout << "Procesare Client: " << client.getNumeClient() << " cu varsta: " << client.getVarsta() << endl;
//}




int main()
{
	Produs p1;
	cout << "---------------------------------------------" << endl;
	p1.afisareProdus();
	cout << "---------------------------------------------" << endl;

	int* cantitateP2 = new int(10);
	Produs p2("Suc", cantitateP2);
	cout << "---------------------------------------------" << endl;
	p2.afisareProdus();
	cout << "---------------------------------------------" << endl;

	int* cantitateP3 = new int(50);
	Produs p3("Ciocolata", 3.0, cantitateP3, 100002);
	cout << "---------------------------------------------" << endl;
	p3.afisareProdus();
	cout << "---------------------------------------------" << endl;



	//float valoareTotalaP3 = Produs::CalculeazaValoareTotala(p3.pret, *p3.cantitate);
	//cout << "Valoare totala pentru produsul P3: " << valoareTotalaP3 << endl;

	//cout << endl << endl << "------------" << endl;
	//Raion r1;
	//cout << "---------------------------------------------" << endl;
	//r1.AfisareRaion();
	//cout << "---------------------------------------------" << endl;

	//Raion r2("Electronice", 100);
	//cout << "---------------------------------------------" << endl;
	//r2.AfisareRaion();
	//cout << "---------------------------------------------" << endl;

	/*float venitLunar[] = { 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000 };
	Raion r3("Haine", 200, venitLunar, "Vestimentar");
	r3.AfisareRaion();
	cout << "---------------------------------------------" << endl;

	cout << endl << endl << "------------" << endl;
	Client c1;
	cout << "---------------------------------------------" << endl;
	c1.AfisareClient();
	cout << "---------------------------------------------" << endl;

	Client c2("John Doe", 30);
	cout << "---------------------------------------------" << endl;
	c2.AfisareClient();
	cout << "---------------------------------------------" << endl;

	bool* esteFidel = new bool(true);
	Client c3("Alice Wonderland", 25, esteFidel, "VIP");
	c3.AfisareClient();
	cout << "---------------------------------------------" << endl;

	Produs prodExe;
	Raion raionExe;
	Client clientExe;

	ProcesareProdus(prodExe);
	ProcesareRaion(raionExe);
	ProcesareClient(clientExe);*/


	Raion r1;

	cout << "Op <<" << endl;
	cout << p1 << endl;
	cout << "Op <<" << endl;
	cout << r1 << endl;

	return 0;
}
