#include "Header.h"

//----------------------------------------------------------------
//version 3

int main()
{
	try {

		Patron U1("Tom", 112233);
		add_user(U1);
		Library_info.print_users();

		std::cout << U1;
		U1.fee_owed_print();
		U1.set_fee(1.99);
		U1.fee_owed_print();
		std::cout << U1;

		//crate a second object of patron, and set its values using default and then use the copy constructor
		Patron U2;
		add_user(U2);
		std::cout << U2;
		U2 = U1;
		std::cout << U2;
		Library_info.print_users();

		//create a third & fourth object of patron, set U3 to default and give values for constructor for U4
		Patron U3;
		add_user(U3);
		Patron U4("Greg", 123456);
		add_user(U4);

		Books B1("Kafka on the shore", "H.Murikami", "123X", Genre::fiction);
		add_book(B1);
		set_book_info(B1, 2001, Months::oct, 27, true);

		//creation of second book given no value so everything is set to default
		Books B2;
		std::cout << B2;
		std::cin >> B2;
		std::cout << B2;
		B1 != B2;	//compare ISBN

		Books B3("Fight club", "C.Palanchuck", "300A", Genre::fiction);

		add_book(B2);
		add_book(B3);

		//should create two transactions to be stored in vector upon book being checked out
		Library_info.check_out_book(B3, U3);
		Library_info.check_out_book(B3, U4);
		Library_info.print_trans();

		Books B4{ B1 };	//copy constructor called for initilazation
		operator<<(std::cout, B3);	//print operation
		B1 != B3;	//compare ISBN
		add_book(B4);
		Library_info.print_books();
		Library_info.all_fees();

	}
	catch (const char* txtException) {
		std::cerr << "Exception: " << txtException;
	}
	catch (...) {
		std::cerr << "Exception: Unknown error:";
	}
}
