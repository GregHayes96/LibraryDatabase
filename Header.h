#include <string>
#include <vector>
#include <iostream>

enum class Months
{
	nil = 0, jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Genre
{
	fiction, nonfiction, periodical, biograpgical, children, unknown
};

//-----------------------------------------------------------------
//class containing all the information for a book and renting it out
class Books {
	std::string title;
	std::string ISBN;
	std::string author;
	int d;
	Months m{ Months::nil };
	int y;
	bool checked_out = false;
	Genre g{};
	std::vector<Books> list{};

public:
	//constructor & copy constructor
	Books(std::string title = "N/A", std::string author = "000X", std::string ISBN = "N/A", Genre g = Genre::unknown, int d = 0, Months m = Months::nil, int y = 0000);	//default constructor
	Books(const Books& source);

	//setter functions
	void set_copyright(Books& b, int y, Months m, int d);
	void c_out_in(bool check_out);

	//overload operators
	friend::std::istream& operator>>(std::istream& is, Books& obj);
	Books& operator!=(const Books& rhs);
	bool operator==(const Books& rhs) const;

	//getter member functions
	std::string titlef() const { return title; }
	std::string authorf() const { return author; }
	std::string ISBNf() const { return ISBN; }
	bool check_outf() const { return checked_out; }
	Genre genre() const { return g; }
	int day() const { return d; }
	Months month() const { return m; }
	int year() const { return y; }
};

class Patron {
	std::string name;
	int card_no;
	double fee;
public:
	//default constructor & copy constructor
	Patron(std::string name = "Unknown", int card_no = 000000, double fee_owed = 0.0);
	Patron(const Patron& source);

	//setter functions
	void set_card_no(int c);
	void set_fee(double f);
	void set_name(std::string n);
	//getter functions
	std::string namef() const { return name; }
	int card_nof() const { return card_no; }
	double feef() const { return fee; }

	//print & other member functions functions
	void fee_owed_print();


	//operator overload functions
	bool operator==(const Patron& rhs) const;

};

struct Transaction {
	Books Book_rent;
	Patron User_taken;
	Transaction(Books Book_rent, Patron User_taken);
};

class Library {
	std::vector<Books> list{};
	std::vector<Patron> user{};
	//std::vector<Patron*> userPtrs{};		might be added later, vector of object pointers to track changes to the object without updating the vector
	std::vector<Transaction> trans{};
public:
	void search_vec_b(const Books& obj);
	void search_vec_P(const Patron& obj);

	//print functions
	void print_users();
	void print_books();
	void print_trans();

	//add functions or setter functions
	void add_user_mf(Patron& obj);
	void add_book_mf(const Books& obj);
	void add_trans_mf(const Transaction& obj);

	//getter functions
	std::string name_return(int n);
	void all_fees();

	void check_out_book(Books& b_obj, const Patron& u_obj);

};

//-------------------------------------------------------------
//Helper function declarations
//-------------------------------------------------------------

//essential clobal variable, must be global for all the functions to have access to it
extern Library Library_info;

void add_user(Patron obj);

void set_book_info(Books& obj, int y, Months m, int d, bool check_out);

bool is_valid(Books entry);

std::istream& operator>>(std::istream& is, Books& obj);

std::ostream& operator<<(std::ostream& os, Books& obj);

std::ostream& operator<<(std::ostream& os, Patron& obj);

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e);


