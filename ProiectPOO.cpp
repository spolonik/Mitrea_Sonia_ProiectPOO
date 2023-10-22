//Tema: Supermarket

#include <iostream>
#include <string>

using namespace std;

class Produs {
public:
	float pret;
	int* cantitate;
	static int nrProduseInStoc;
	const int codBare;

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

	~Produs() {
		if (this->cantitate != NULL) {
			delete[]this->cantitate;
			this->cantitate = NULL;
		}
	}

	void afisareProdus() {
		cout<< "Nume: "<< this->nume << "\nPret: "<< this->pret<< "\nCantitate: " << *cantitate << "\nCod Bare: " << this->codBare << "\nNr. Produse in Stoc: " << this->nrProduseInStoc << endl;
	}

	static float CalculeazaValoareTotala(float pret, int cantitate) {
		return pret * cantitate;
	}
};
int Produs::nrProduseInStoc = 0;

class Raion {
public:
	string numeRaion;
	int capacitate;
	float* venitLunar;
	static int nrRaioaneActive;
	const string tipRaion;

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
	Raion(string numeRaion, int capacitate, float* venitLunar, const string tip) : tipRaion(tip) {
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

	static float CalculeazaVenitMediu(float* venitLunar, int nrLuni) {
		float venitTotal = 0.0;
		for (int i = 0; i < nrLuni; ++i) {
			venitTotal += venitLunar[i];
		}
		return venitTotal / nrLuni;
	}

	void AfisareRaion() {
		cout << "Nume Raion: " << numeRaion << "\nCapacitate: " << capacitate << "\nTip Raion: " << tipRaion << "\nNr. Raioane Active: " << nrRaioaneActive << endl;
		cout << "Venit Lunar: ";
		for (int i = 0; i < 12; i++) {
			cout << venitLunar[i] << " ";
		}
		cout << "\nVenit Mediu Lunar: " << CalculeazaVenitMediu(venitLunar, 12) << endl;
	}
};
int Raion::nrRaioaneActive = 0;

class Client {
public:
	string numeClient;
	int varsta;
	bool* esteFidel;
	static int nrClientiFideli;
	const string tipClient;

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
		this->esteFidel = new bool(esteFidel);
		nrClientiFideli++;
	}
	~Client() {
		if (this->esteFidel != nullptr)
		{
			delete this->esteFidel;
			this->esteFidel = nullptr;
		}
	}

	void AfisareClient() {
		cout << "Nume Client: " << numeClient << "\nVarsta: " << varsta << "\nTip Client: " << tipClient << "\nNr. Clienti Fideli: " << nrClientiFideli << endl;
		cout << "Este Fidel: " << (*esteFidel ? "Da" : "Nu") << endl;
	}

	static void ActualizeazaStatus(bool* esteFidel, bool nouStatus) {
		*esteFidel = nouStatus;
	}
};
int Client::nrClientiFideli = 0;

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

	float valoareTotalaP3 = Produs::CalculeazaValoareTotala(p3.pret, *p3.cantitate);
	cout << "Valoare totala pentru produsul P3: " << valoareTotalaP3 << endl;

	cout << endl << endl << "------------" << endl;
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



	return 0;
}
