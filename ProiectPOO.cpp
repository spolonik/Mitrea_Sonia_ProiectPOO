//Tema: Supermarket
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class EvidentaTipProdus {
public:
	virtual string evidentaTipProdus() = 0;
};

class RecunoastereTipClient {
public:
	virtual string evidentaTipClient() = 0;
};

class Produs : public EvidentaTipProdus {
protected:
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
	float operator()() const {
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
	string getNumeProdus() const {
		return this->nume;
	}

	void setNumeProdus(string nume) {
		this->nume = nume;
	}

	float getPretProdus() const {
		return this->pret;
	}

	void setPretProdus(float pret) {
		this->pret = pret;
	}

	int* getCantitate() const {
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
		Produs aux(*this);
		++(*this->cantitate);
		return aux;
	}
	//op -- pre-decrem
	Produs& operator--() {
		if (*cantitate > 0) {
			--(*cantitate);
		}
		return *this;
	}

	//op -- post-decrem
	Produs operator--(int) {
		Produs aux(*this);
		--(*this->cantitate);
		return aux;
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

	friend void ProcesareProdus(const Produs& produs);
	friend void AltaFunctiePrietena(const Produs& p1, const Produs& p2);

	string evidentaTipProdus() {
		return "Produs neperisabil";
	}
};
int Produs::nrProduseInStoc = 0;

void ProcesareProdus(const Produs& produs) {
	cout << "Procesare Produs: " << produs.getNumeProdus() << " cu pretul: " << produs.getPretProdus() << endl;
}
void AltaFunctiePrietena(const Produs& p1, const Produs& p2) {
	cout << "Valoarea totala a produsului 1: " << p1() << endl;
	cout << "Valoarea totala a produsului 2: " << p2() << endl;
}


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

	string getNumeRaion() const {
		return this->numeRaion;
	}

	void setNumeRaion(string numeRaion) {
		this->numeRaion = numeRaion;
	}

	int getCapacitate() const {
		return this->capacitate;
	}

	void setCapacitate(int capacitate) {
		this->capacitate = capacitate;
	}

	float* getVenitLunar() const {
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

	friend istream& operator>>(istream& input, Raion& r) {
		cout << "Introdu numeRaion: ";
		input >> r.numeRaion;
		cout << "Introdu capacitate: ";
		input >> r.capacitate;
		r.venitLunar = new float[r.capacitate];
		for (int i = 0; i < r.capacitate; ++i) {
			cout << "Introdu venitLunar[" << i << "]: ";
			input >> r.venitLunar[i];
		}
		return input;
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
		Raion aux(*this);
		nrRaioaneActive++;
		return aux;
	}

	//pre-increm 
	Raion& operator++() {
		nrRaioaneActive++;
		return *this;
	}

	//post-decrem 
	Raion operator--(int) {
		Raion aux(*this);
		nrRaioaneActive--;
		return aux;
	}

	//pre-decrem 
	Raion& operator--() {
		nrRaioaneActive--;
		return *this;
	}


	friend void ProcesareRaion(const Raion& raion);
};
int Raion::nrRaioaneActive = 0;

class Client : public RecunoastereTipClient {
protected:
	string numeClient;
	int varsta;
	bool* esteFidel;
	static int nrClientiFideli;
	const string tipClient;

public:
	string getNumeClient() const {
		return this->numeClient;
	}
	int getVarsta() const {
		return this->varsta;
	}
	bool* getEsteFidel() const {
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

	string evidentaTipClient() {
		return "Client obisnuit!";
	}

	//postincrem
	Client operator++(int) {
		Client aux(*this);
		nrClientiFideli++;
		return aux;
	}

	//preincrem
	Client& operator++() {
		nrClientiFideli++;
		return *this;
	}

	//postdecrem 
	Client operator--(int) {
		Client aux(*this);
		nrClientiFideli--;
		return aux;
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


void ProcesareRaion(const Raion& raion) {
	cout << "Procesare Raion: " << raion.getNumeRaion() << " cu capacitatea: " << raion.getCapacitate() << endl;
}
void ProcesareClient(const Client& client) {
	cout << "Procesare Client: " << client.getNumeClient() << " cu varsta: " << client.getVarsta() << endl;
}



class ProdusPerisabil : public Produs {
	int ziExp;
	int lunaExp;
	int anExp;
public:

	ProdusPerisabil() :Produs()
	{
		this->ziExp = 1;
		this->lunaExp = 1;
		this->anExp = 2024;
	}

	ProdusPerisabil(string nume, float pret, int* cantitate, const int cod, int zi, int luna, int an) :Produs(nume, pret, cantitate, cod)
	{
		this->ziExp = zi;
		this->lunaExp = luna;
		this->anExp = an;
	}

	ProdusPerisabil(const Produs& p) :Produs(p) {
		this->ziExp = 10;
		this->lunaExp = 5;
		this->anExp = 2026;
	}

	ProdusPerisabil(const ProdusPerisabil& p) :Produs(p) {
		this->ziExp = p.ziExp;
		this->lunaExp = p.lunaExp;
		this->anExp = p.anExp;
	}

	~ProdusPerisabil() {

	}

	ProdusPerisabil& operator=(const ProdusPerisabil& p) {
		if (this != &p) {
			Produs::operator=(p);
			this->ziExp = p.ziExp;
			this->lunaExp = p.lunaExp;
			this->anExp = p.anExp;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const ProdusPerisabil& pp) {
		out << (Produs&)pp << endl;
		out << "Zi Expirare: " << pp.ziExp << endl << endl;
		out << "Luna Expirare: " << pp.lunaExp << endl << endl;
		out << "An Expirare: " << pp.anExp << endl << endl;

		return out;
	}

	int getZiExp() {
		return ziExp;
	}

	void setZiExp(int ziExp) {
		this->ziExp = ziExp;
	}

	int getLunaExp() {
		return lunaExp;
	}

	void setLunaExp(int lunaExp) {
		this->lunaExp = lunaExp;
	}

	int getAnExp() {
		return anExp;
	}

	void setAnExp(int anExp) {
		this->anExp = anExp;
	}

	string evidentaTipProdus() {
		string dataExpirare = to_string(ziExp) + "." + to_string(lunaExp) + "." + to_string(anExp);
		return "Produs perisabil! Expira la data " + dataExpirare;
	}
};


class ClientVIP : public Client {
	int nivelVIP;
	float discountSuma;
public:
	ClientVIP() :Client() {
		this->nivelVIP = 1;
		this->discountSuma = 10.5;
	}

	ClientVIP(string numeClient, int varsta, bool* esteFidel, const string tipC, int nivelVIP, float discountSuma) :Client(numeClient, varsta, esteFidel, tipC) {
		this->nivelVIP = nivelVIP;
		this->discountSuma = discountSuma;
	}


	ClientVIP(const ClientVIP& c) :Client(c) {
		this->nivelVIP = c.nivelVIP;
		this->discountSuma = c.discountSuma;
	}

	ClientVIP(const Client& c) :Client(c) {
		this->nivelVIP = 4;
		this->discountSuma = 25.5;
	}

	~ClientVIP() {

	}

	ClientVIP& operator=(const ClientVIP& c) {
		if (this != &c) {
			Client::operator=(c);
			this->nivelVIP = c.nivelVIP;
			this->discountSuma = c.discountSuma;
		}
		return *this;
	}

	friend ostream& operator <<(ostream& out, const ClientVIP& c) {
		out << (Client&)c;
		out << "Nivel VIP: " << c.nivelVIP << endl;
		out << "Discount Suma(In procente): " << c.discountSuma << endl;
		return out;
	}

	int getNivelVIP() {
		return nivelVIP;
	}

	void setNivelVIP(int nivel) {
		nivelVIP = nivel;
	}

	float getDiscountSuma() {
		return discountSuma;
	}

	void setDiscountSuma(float discount) {
		discountSuma = discount;
	}

	string evidentaTipClient() {
		return "Client VIP! Nivelul VIP este " + to_string(nivelVIP);
	}
};


class Depozit {
	string localitate;
	int nrProduse;
	Produs** prod;
	float suprafata;
public:
	Depozit() {
		this->localitate = "Necunoscut";
		this->nrProduse = 0;
		this->prod = NULL;
		this->suprafata = 0;
	}

	Depozit(string localitate, int nrProduse, Produs** prod, float suprafata) {
		this->localitate = localitate;
		this->nrProduse = nrProduse;
		this->prod = new Produs * [this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++) {
			this->prod[i] = prod[i];
		}
		this->suprafata = suprafata;
	}

	Depozit(const Depozit& d) {
		this->localitate = d.localitate;
		this->nrProduse = d.nrProduse;
		this->prod = new Produs * [this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++) {
			this->prod[i] = d.prod[i];
		}
		this->suprafata = d.suprafata;
	}

	~Depozit() {
		if (this->prod != NULL) {
			delete[]this->prod;
		}
	}

	Depozit& operator =(const Depozit& d) {
		if (this != &d) {
			if (this->prod != NULL) {
				delete[]this->prod;
			}
			this->localitate = d.localitate;
			this->nrProduse = d.nrProduse;
			this->prod = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++) {
				this->prod[i] = d.prod[i];
			}
			this->suprafata = d.suprafata;
		}
		return *this;
	}

	Depozit& operator+=(float adaugaSuprafata) {
		if (adaugaSuprafata > 0) {
			this->suprafata += adaugaSuprafata;
		}
		return *this;
	}

	Produs& operator[](int index) {
		if (index >= 0 && index < nrProduse) {
			return *prod[index];
		}
		else {
			Produs* p = new Produs();
			return *p;
		}

	}

	string operator()()
	{
		return "Depozitul se afla in " + this->localitate;
	}

	string getLocalitate() {
		return localitate;
	}

	void setLocalitate(string loc) {
		localitate = loc;
	}

	int getNrProduse() {
		return nrProduse;
	}

	float getSuprafata() {
		return suprafata;
	}

	void setSuprafata(float sup) {
		suprafata = sup;
	}

	Produs** getProduse() {
		return prod;
	}

	friend ostream& operator<<(ostream& out, const Depozit& d) {
		out << "Localitate: " << d.localitate << endl;
		out << "Numar produse: " << d.nrProduse << endl;
		if (d.nrProduse > 0) {
			out << "Produse: " << endl;
			for (int i = 0; i < d.nrProduse; ++i) {
				out << *d.prod[i] << endl;
			}
		}
		out << "-------------------------------------" << endl;
		out << "Suprafata: " << d.suprafata << " mp" << endl;
		return out;
	}
};


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

	cout << "Nume produs1: " << p3.getNumeProdus() << endl;
	cout << "Pret produs1: " << p3.getPretProdus() << endl;
	cout << "Cantitate produs1: " << *p3.getCantitate() << endl;

	cout << "Op <<" << endl;
	cout << p1 << endl;

	p2.afisareProdus();
	cout << "Op +=" << endl;
	p2 += 5;
	cout << p2 << endl;
	cout << "-------------------------" << endl;
	cout << "P1 inainte: " << endl << p1 << endl;
	p1 = p3;
	cout << "P1 dupa op = : " << endl << p1 << endl;
	cout << "-------------------------" << endl;
	cout << p3 << endl;
	p3++;
	cout << p3 << endl;

	Raion r1;
	cout << "---------------------------------------------" << endl;
	r1.AfisareRaion();
	cout << "---------------------------------------------" << endl;

	Raion r2("Electronice", 100);
	cout << "---------------------------------------------" << endl;
	r2.AfisareRaion();
	cout << "---------------------------------------------" << endl;

	float venitLunar[] = { 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000 };
	Raion r3("Haine", 200, venitLunar, "Vestimentar");
	cout << "---------------------------------------------" << endl;
	r3.AfisareRaion();
	cout << "---------------------------------------------" << endl;

	// Testare getteri si setteri pentru Raion
	cout << "Nume Raion r1: " << r1.getNumeRaion() << endl;
	cout << "Capacitate Raion r1: " << r1.getCapacitate() << endl;
	cout << "Venit Lunar Raion r1: ";
	for (int i = 0; i < 12; i++) {
		cout << r1.getVenitLunar()[i] << " ";
	}
	cout << endl;

	r1.setNumeRaion("Raion Nou");
	r1.setCapacitate(150);
	float venitLunarNou[] = { 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000 };
	r1.setVenitLunar(venitLunarNou);

	cout << "Nume Raion r1 dupa set: " << r1.getNumeRaion() << endl;
	cout << "Capacitate Raion r1 dupa set: " << r1.getCapacitate() << endl;
	cout << "Venit Lunar Raion r1 dupa set: ";
	for (int i = 0; i < 12; i++) {
		cout << r1.getVenitLunar()[i] << " ";
	}
	cout << endl;

	// Testare constructor de copiere pentru Raion
	Raion r4 = r2;
	cout << "---------------------------------------------" << endl;
	cout << "Afisare Raion r2 (original): " << endl;
	r2.AfisareRaion();
	cout << "Afisare Raion r4 (copie): " << endl;
	r4.AfisareRaion();
	cout << "---------------------------------------------" << endl;

	// Testare destructor pentru Raion
	{
		Raion r5("Test Destructor", 50);
		cout << "Raion creat in bloc" << endl;
	}

	cout << "Raion dupa iesirea din bloc" << endl;

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
	cout << "---------------------------------------------" << endl;
	c3.AfisareClient();
	cout << "---------------------------------------------" << endl;

	// Testare getteri si setteri pentru Client
	cout << "Nume Client c1: " << c1.getNumeClient() << endl;
	cout << "Varsta Client c1: " << c1.getVarsta() << endl;
	cout << "Este Fidel Client c1: " << (*c1.getEsteFidel() ? "Da" : "Nu") << endl;

	c1.setNumeClient("Client Nou");
	c1.setVarsta(40);
	bool* esteFidelNou = new bool(false);
	c1.setEsteFidel(esteFidelNou);

	cout << "Nume Client c1 dupa set: " << c1.getNumeClient() << endl;
	cout << "Varsta Client c1 dupa set: " << c1.getVarsta() << endl;
	cout << "Este Fidel Client c1 dupa set: " << (*c1.getEsteFidel() ? "Da" : "Nu") << endl;

	// Testare constructor de copiere pentru Client
	Client c4 = c2;
	cout << "---------------------------------------------" << endl;
	cout << "Afisare Client c2 (original): " << endl;
	c2.AfisareClient();
	cout << "Afisare Client c4 (copie): " << endl;
	c4.AfisareClient();
	cout << "---------------------------------------------" << endl;

	// Testare destructor pentru Client
	{
		Client c5("Test Destructor", 30);
		cout << "Client creat in blocul interior" << endl;
	}

	cout << "Client dupa iesirea din blocul interior" << endl;

	ProcesareProdus(p1);
	ProcesareRaion(r1);
	ProcesareClient(c1);

	cout << endl;

	Produs produse[3] = { p1,p2,p3 };
	Raion raioane[3] = { r1,r2,r3 };
	Client clienti[3] = { c1,c2,c3 };


	for (int i = 0; i < 3; i++) {
		//cin >> produse[i];
	}

	cout << endl << endl;
	for (int i = 0; i < 3; i++) {
		cout << produse[i] << endl;
	}

	for (int i = 0; i < 3; i++) {
		//cin >> raioane[i];
	}

	cout << endl << endl;
	for (int i = 0; i < 3; i++) {
		cout << raioane[i] << endl;
	}


	cout << endl << endl;

	for (int i = 0; i < 3; i++) {
		//cin >> clienti[i];
	}

	cout << endl << endl;
	for (int i = 0; i < 3; i++) {
		cout << clienti[i] << endl;
	}



	cout << "---------------------------------------------" << endl;
	const int nr = 2;
	Produs matrixProd[nr][nr];
	for (int i = 0; i < nr; ++i) {
		for (int j = 0; j < nr; ++j) {
			//cin >> matrixProd[i][j];
		}
	}

	for (int i = 0; i < nr; ++i) {
		for (int j = 0; j < nr; ++j) {
			cout << matrixProd[i][j] << endl;
		}
	}
	cout << "---------------------------------------------" << endl;

	ProdusPerisabil pp;
	cout << pp.getZiExp() << endl;
	cout << pp.getLunaExp() << endl;
	cout << pp.getAnExp() << endl;
	cout << endl;

	pp.setZiExp(5);
	pp.setLunaExp(11);
	pp.setAnExp(2025);

	cout << pp << endl;

	cout << endl;

	ProdusPerisabil pp1 = p1;
	cout << pp1 << endl;

	ProdusPerisabil pp2 = pp;
	cout << pp2 << endl;

	pp2 = pp1;

	cout << pp2 << endl;

	Produs pCasting = pp1;

	cout << pCasting << endl;

	cout << "---------------------------------------------" << endl;
	ClientVIP cv;
	cout << cv.getNivelVIP() << endl;
	cout << cv.getDiscountSuma() << endl;
	cv.setDiscountSuma(15.5);
	cv.setNivelVIP(3);

	cout << cv << endl;

	ClientVIP cv1 = c1;

	cout << cv1 << endl;

	ClientVIP cv2 = cv;

	cout << cv2 << endl;

	cv2 = cv1;

	cout << cv2 << endl;

	cout << "---------------------------------------------" << endl;
	Produs* vecPp[10] = { &p1,&pp1,&p1,&pp1, &p1,&pp1, &p1,&pp1, &p1,&pp1 };
	Produs* pProd = new Produs(p1);
	Produs* pProd1 = new ProdusPerisabil(pp1);
	cout << pProd->evidentaTipProdus() << endl;
	cout << pProd1->evidentaTipProdus() << endl;
	for (int i = 0; i < 10; i++) {
		cout << vecPp[i]->evidentaTipProdus() << endl;
	}

	cout << endl << endl;

	Client* pClient = new Client(c1);
	Client* pClient1 = new ClientVIP(cv1);

	cout << pClient->evidentaTipClient() << endl;
	cout << pClient1->evidentaTipClient() << endl;

	cout << "---------------------------------------------" << endl;

	Produs* vecProd[4] = { &p1,&pp1,&pp2,&p2 };

	Depozit d;
	cout << d.getLocalitate() << endl;
	cout << d.getNrProduse() << endl;
	if (d.getNrProduse() > 0) {
		for (int i = 0; i < d.getNrProduse(); i++)
		{
			cout << *(d.getProduse()[i]) << endl;
		}
	}
	cout << d.getSuprafata() << endl;

	d.setLocalitate("Pantelimon");
	d.setSuprafata(4500);

	cout << d << endl;


	cout << endl << endl;

	Depozit d1("Straulesti", 4, vecProd, 1500);

	cout << d1 << endl;


	Depozit d2 = d;
	cout << d2 << endl;

	d2 = d1;
	cout << d2 << endl;

	cout << d2() << endl;

	d2 += 1500;

	cout << d2 << endl;

	cout << d2[2] << endl;
	cout << d2[1] << endl;
	cout << d2[-1] << endl;
	cout << d2[11] << endl << endl;

	for (int i = 0; i < d2.getNrProduse(); i++) {
		cout << d2.getProduse()[i]->evidentaTipProdus() << endl;
	}

	cout << "---------------------------------------------" << endl;

	return 0;
}