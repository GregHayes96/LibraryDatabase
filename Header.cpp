#include "Header.h"
//-----------------------------------------------------------------
//global variables
//-----------------------------------------------------------------
Library Library_info;

//-----------------------------------------------------------------
// Books class & member functions
// ----------------------------------------------------------------

//set the books values if not filled in for the constructor
const Books& default_book() {
	static Books db{ "N/A", "000X", "N/A" };
	return db;
}

//-----------------------------------------------------------------
//constructor to set values
Books::Books(std::string title, std::string author, std::string ISBN, Genre g, int d, Months m, int y) :title(title), ISBN(ISBN), author(author), g(g), d(d), m(m), y(y)
//copyright date automaticaqlly set to (0000/0/0) until member function to set called
{

}

//-----------------------------------------------------------------
//copy constructor
Books::Books(const Books& source)
	:Books{ source.title ,source.author,source.ISBN,source.g, source.d , source.m, source.y }
{

}

//-----------------------------------------------------------------
//member function to set a copy right date
void Books::set_copyright(Books& b, int y, Months m, int d) {
	b.y = { y };
	b.m = { m };
	b.d = { d };
}

//-----------------------------------------------------------------
//returns or puts back the book
void Books::c_out_in(bool check_out) {
	this->checked_out = check_out;
}

//-----------------------------------------------------------------
//can be used to ask user to input book details
std::istream& operator>>(std::istream& is, Books& obj) {
	std::cout << "please input book title, author name & ISBN in format: (title author ISBN)" << std::endl;
	is >> obj.title >> obj.author >> obj.ISBN;
	if (is)
	{
		is_valid(obj);
	}
	else throw "Book not entered into database correctly, try again";
}

//-----------------------------------------------------------------
//this is to convert the enum into a type that can be output by the << operator
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

//-----------------------------------------------------------------
//prints out the information of the book using an overload operator
std::ostream& operator<<(std::ostream& os, Books& obj) {
	std::string out = "Yes";
	if (obj.check_outf() == false) out = "No";
	return os << "Title:\t" << obj.titlef() << std::endl
		<< "Author:\t" << obj.authorf() << std::endl
		<< "ISBN:\t" << obj.ISBNf() << std::endl
		<< "Genre:\t" << obj.genre() << std::endl
		<< "currently out: \t" << out << std::endl
		<< "copyright date: (" << obj.year() << "/" << int(obj.month()) << "/" << obj.day() << ")" << std::endl << std::endl;
}

//-----------------------------------------------------------------
//overload operator for coparing ISBN
Books& Books::operator!=(const Books& rhs) {
	std::cout << "ISBN match check called: ";
	if (this == &rhs) {
		return *this;
	}
	if (this->ISBN == rhs.ISBN) {
		std::cout << "matching ISBN" << std::endl << std::endl;
		return *this;
	}
	else
		std::cout << "Different ISBN" << std::endl << std::endl;
}

//----------------------------------------------------------------
//Operator to compare two user defined objects for the book class
bool Books::operator==(const Books& rhs) const {
	this->authorf();
	if (this->title == rhs.title && this->author == rhs.author)
		return true;
	else
		return false;
};

//----------------------------------------------------------------
//Books class helper functions
//----------------------------------------------------------------

//simple check for the ISBN for a valid format
bool is_valid(Books entry) {
	//unsigned int to stop mismatch of data types.
	for (unsigned int i = 0; i < entry.ISBNf().size(); ++i) {
		std::string check = entry.ISBNf();
		if (i < 3 && isdigit(check[i]));	//checks the first three digits to be a number
		else if (i != 3) throw" ISBN format incorrect first 3 digits";
		if (isalpha(check[i]) || isdigit(check[i])); //cheacks the last character to be a digit or letter
		else throw "ISBN format incorrect last digit";
	}
	return true;
}

//-----------------------------------------------------------------
//call to set up all the values at once to set data values for class objects
void set_book_info(Books& obj, int y, Months m, int d, bool check_out) {
	is_valid(obj);
	obj.c_out_in(check_out);
	obj.set_copyright(obj, y, m, d);
	operator<<(std::cout, obj);
}

//-----------------------------------------------------------------
//Patron class & member functions
//-----------------------------------------------------------------
Patron::Patron(std::string name, int card_no, double fee) :name(name), card_no(card_no), fee(fee)
{

}

//-----------------------------------------------------------------
//copy constructor
Patron::Patron(const Patron& source)
	:Patron{ source.name,source.card_no,source.fee }
{

}

//------------------------------------------------------------------
//overload operator to print out object information from patron class
std::ostream& operator<<(std::ostream& os, Patron& obj) {
	return os << "Account name:\t " << obj.namef() << std::endl
		<< "Card Number: \t" << obj.card_nof() << std::endl
		<< "Fees owed(GBP): \t" << obj.feef() << std::endl << std::endl;
}

//-----------------------------------------------------------------
//Three patron class setter member functions
void Patron::set_card_no(int c) {
	card_no = { c };
}

void Patron::set_fee(double d) {
	fee = { d };
}

void Patron::set_name(std::string n) {
	name = n;
}

//------------------------------------------------------------------
//checks if user owes a fee
void Patron::fee_owed_print() {
	if (this->feef() > 0.0)
		std::cout << "Fee is owed" << std::endl;
	else
		std::cout << "No fee is owed" << std::endl;
}

bool Patron::operator==(const Patron& rhs) const {
	if (this->name == rhs.name && this->card_no == rhs.card_no)
		return true;
	else
		return false;

}

//------------------------------------------------------------------
//library class & member functions
//------------------------------------------------------------------

//print member functions to show books/users stored in vectors
void Library::print_users() {
	for (int i = 0; i < Library_info.user.size(); i++) {
		std::cout << i + 1 << ":\t" << Library_info.user[i].namef() << std::endl;
	}
	std::cout << std::endl;
}

void Library::print_books() {
	for (int i = 0; i < Library_info.list.size(); i++) {
		std::cout << i + 1 << ":\t" << Library_info.list[i].titlef() << std::endl;
	}
	std::cout << std::endl;
}

//-------------------------------------------------------------------
//if you know the object number (U1, U2 etc) can use that to print the name stored in object
std::string Library::name_return(int n) {
	return Library_info.user[n - 1].namef();
}

//-------------------------------------------------------------------
//member functions to add user/book object to vector in library class
void Library::add_user_mf(Patron& obj) {
	Library_info.user.push_back(obj);
}

void Library::add_book_mf(const Books& obj) {
	Library_info.list.push_back(obj);
}

void Library::add_trans_mf(const Transaction& obj) {
	Library_info.trans.push_back(obj);
}

void Library::add_user_ptr(Patron& obj) {
	Patron* patron;
	patron = &obj;
	Library_info.userPtrs.push_back(patron);
}

//slightly verbertose but improves readability in main body of code 
void add_user(Patron &obj) {
	Library_info.add_user_mf(obj);
	Library_info.add_user_ptr(obj);
}

void add_book(Books& obj) {
	Library_info.add_book_mf(obj);
}

//------------------------------------------------------------------
//returns size of transaction class so the tr
void Library::print_trans() {
	std::cout << "All transactions in Library Database:" << std::endl;
	for (int i = 0; i < Library_info.trans.size(); i++) {
		std::cout << i + 1 << ". " << Library_info.trans[i].Book_rent.titlef() << "\t" << Library_info.trans[i].User_taken.namef() << std::endl;
	}
	std::cout << std::endl;
}

//this will check to see if the user and the book are in the database and throw an error if not
void Library::check_out_book(Books& b_obj, const Patron& u_obj) {
	//fist iterator to search if the book to be checked out is in the database
	this->search_vec_b(b_obj);
	this->search_vec_P(u_obj);

	//then check if the user owes any fees
	if (u_obj.feef() > 0.0)
		throw "User owes a fee, can't check out new book until fee settled";

	//then check if the book is already checked out
	if (b_obj.check_outf() == true)
		throw "Book already out, cant be checked out twice";
	else
		b_obj.c_out_in(true);	//check out book now. reason for b_obj not being const

	//creation of transaction after checks
	Transaction T1(b_obj, u_obj);
	Library_info.add_trans_mf(T1);
}

//------------------------------------------------------------------
//the two searches for the vectors inside the class which make up the stored database. one for books, one for patron
void Library::search_vec_b(const Books& obj) {

	std::vector<Books>::iterator it;
	it = find(this->list.begin(), this->list.end(), obj);
	if (it == this->list.end()) throw "Book not in database stored vector";
}

void Library::search_vec_P(const Patron& obj) {
	std::vector<Patron>::iterator it;
	it = find(this->user.begin(), this->user.end(), obj);
	if (it == this->user.end()) throw "User not in database stored vector";

}

void Library::all_fees() {
	std::cout << "All fees owed:" << std::endl;
	for (int i = 0; i < this->user.size(); i++) {
		
		if (userPtrs[i]->feef() > 0) std::cout << userPtrs[i]->namef() << std::endl;

	}
}


//------------------------------------------------------------------
//Transaction struct & member functions
//------------------------------------------------------------------

//constructor for transaction
Transaction::Transaction(Books Book_rent, Patron User_taken)
	:Book_rent(Book_rent), User_taken(User_taken)
{

}

