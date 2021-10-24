#pragma once
#include <fstream>
#include "Doc_Info.h"
#include "DList.h"
#include <string>

using namespace std;

class Term_Info {
private:
	string keyterm;
	DList<Doc_Info>* Docs;
public:
	Term_Info() {
		keyterm = "";	Docs = new DList<Doc_Info>;
	}
	int count(string& word, string& line);
	Term_Info(string term);
	string GetTerm();
	DList<Doc_Info>* GetDocs();
	void SetTerm(string term);
	void SetDocs(DList<Doc_Info>* docs);
	void Analyze(string& file);
	bool operator ==(Term_Info* T2);
	bool operator <(Term_Info* T2);
	bool operator >(Term_Info* T2);
	bool operator ==(const string& T2);
	bool operator <(const string& T2);
	bool operator >(const string& T2);
	bool operator ==(Term_Info const & T2);
	bool Compare(Term_Info const & T2);
	bool Compare(Term_Info * T2);
	void copy(Term_Info* T2);
	void Merge(Term_Info* T2);
	friend ostream& operator <<(ostream& out, Term_Info* test) {
		test->print();
		return out;
	};
	void print();
	~Term_Info();
};

//Parametarized constructor
Term_Info::Term_Info(string term) {
    keyterm = term;
	Docs = new DList<Doc_Info>;
};

//Getters and Setters
string Term_Info::GetTerm() {
	return this->keyterm;
};

DList<Doc_Info>* Term_Info::GetDocs() {
	return this->Docs;
};

void Term_Info::SetTerm(string term) {
	this->keyterm = term;
};

void Term_Info::SetDocs(DList<Doc_Info>* docs) {
	this->Docs->CopyDList(*docs);
};

void Term_Info::copy(Term_Info* T2) {
    this->keyterm = T2->GetTerm();
    this->SetDocs(T2->GetDocs());
};

//Print All occurances of the term in the docs
void Term_Info::print() {
	std::cout << "KeyTerm is: " << this->keyterm << "\n";

	Node<Doc_Info>* p = this->Docs->GetHead()->Getnext();

	for (; p != this->Docs->GetTail(); p = p->Getnext()) {
		std::cout << "DocID: " << p->Data.GetDocID() << ", Term Frequency: " << p->Data.GetTFreq() << "\n";
	}
};

//Analyze how many times the term occured in the document topics
void Term_Info::Analyze(std::string& file) {
	std::string topic;
	ifstream fin;

	fin.open(file);
	if (!fin.is_open()) {
		std::cout << "File did not open. \n";
	}

	int i, j, T, freq;
    i = j = T = freq = 0;

	if (this->Docs->GetHead()->Getnext() != this->Docs->GetTail() && this->Docs->GetTail()->Getprev() != this->Docs->GetHead()) {

		while (Docs->GetHead()->Getnext() != Docs->GetTail()) {
			Node<Doc_Info>* del = this->Docs->GetHead()->Getnext();
			this->Docs->GetHead()->Setnext(this->Docs->GetHead()->Getnext()->Getnext());
			delete del; del = nullptr;
		}
	}

	for (;; i++) {
		getline(fin, topic, '\n');

		if (!topic.empty()) {
			T++;
			freq = count(this->keyterm, topic);
			if (T != 0 && freq != 0) {
				Doc_Info dax(T,freq);
				this->Docs->insertAtEnd(dax);
			}
		}
		else if (topic.empty()) {
			break;
		}
	}
};

//For counting all occurances in a document topic
int Term_Info::count(string& word, string& line) {
	int i, res; i = res = 0;
	string temp;

	for (;; i++) {
		if (line[i] != '\n' && line[i] != '\0' && line[i] != ' ') {
			temp  += line[i];
		}
		if (line[i] == '\n' || line[i] == ' ') {
			if (temp == word) {
				res++;
			}
			temp = "";
		}
		else if (line[i] == '\0') {
			if (temp == word) {
				res++;
			}
			break;
		}
	}

	return res;
};

bool Term_Info::operator==(Term_Info* T2) {
	if (this->keyterm == T2->GetTerm())
		return true;
	return false;
};

bool Term_Info::Compare(Term_Info const & T2) {
	if (this->keyterm == T2.keyterm)
		return true;
	return false;
};

bool Term_Info::Compare(Term_Info * T2) {
	if (this->keyterm == T2->keyterm)
		return true;
	return false;
};

bool Term_Info::operator==(Term_Info const & T2) {
	if (this->keyterm == T2.keyterm)
		return true;
	return false;
};

void Term_Info::Merge(Term_Info* T2) {
	this->Docs->Merge(T2->GetDocs());
};

bool Term_Info::operator<(Term_Info* T2) {
	if (this->keyterm < T2->GetTerm())
		return true;
	return false;
};

bool Term_Info::operator>(Term_Info* T2) {
	if (this->keyterm > T2->GetTerm())
		return true;
	return false;
};

bool Term_Info::operator==(const string& T2) {
	if (this->keyterm == T2)
		return true;
	return false;
};

bool Term_Info::operator<(const string& T2) {
	if (this->keyterm < T2)
		return true;
	return false;
};

bool Term_Info::operator>(const string& T2) {
	if (this->keyterm > T2)
		return true;
	return false;
};

//Destructor
Term_Info::~Term_Info() {
	this->keyterm = "\0";
	DList<Doc_Info>* Del = this->Docs;
	this->Docs = nullptr;
	delete Del; Del = nullptr;
};
